/*
 * Copyright (C) 2017 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "LightService"

#include <log/log.h>

#include <android-base/logging.h>
#include <android-base/stringprintf.h>

#include "Light.h"

#include <fstream>

namespace android {
namespace hardware {
namespace light {
namespace V2_0 {
namespace implementation {

#define LEDS            "/sys/class/leds/"

#define LCD_LED         "/sys/class/backlight/panel0-backlight/brightness"
#define RED_LED         LEDS "red_moto/"
#define GREEN_LED       LEDS "green_moto/"
#define BLUE_LED        LEDS "blue_moto/"

#define BREAH           "breath"
#define BREAH_PATTERN   "breath_pattern"
#define BRIGHTNESS      "brightness"

/*
 * Write value to path and close file.
 */
static void set(std::string path, std::string value) {
    std::ofstream file(path);
    file << value;
}

static void set(std::string path, int value) {
    set(path, std::to_string(value));
}

template <typename T>
static T get(const std::string& path, const T& def) {
    std::ifstream file(path);
    T result;

    file >> result;
    return file.fail() ? def : result;
}

static void handleBacklight(const LightState& state) {
    int brightness = Light::rgbToBrightness(state);
    set(LCD_LED, brightness);
}

/*
 * Get breath value as color + pauseHi + pauseLo
 * rise_time hold_time fall_time off_time
 */
static std::string getBreathPatternValue(uint32_t pauseHi,
    uint32_t pauseLo) {

    char buffer[40];
    snprintf(buffer, sizeof(buffer), "%d %d %d %d\n",
        pauseLo, pauseHi, pauseLo, pauseHi);
    std::string ret = buffer;
    return ret;
}

static void handleBattery(const LightState& state) {
    int brightness = Light::rgbToBrightness(state);

    set(RED_LED BREAH, brightness == 0 ? 0 : 1);
    set(RED_LED BRIGHTNESS, brightness);

    set(GREEN_LED BREAH, brightness == 0 ? 0 : 1);
    set(GREEN_LED BRIGHTNESS, brightness);

    set(BLUE_LED BREAH, brightness == 0 ? 0 : 1);
    set(BLUE_LED BRIGHTNESS, brightness);
}

static void handleNotification(const LightState& state) {
    uint32_t redBrightness, greenBrightness, blueBrightness, brightness;

    /*
     * Extract brightness from AARRGGBB.
     */
    redBrightness = (state.color >> 16) & 0xFF;
    greenBrightness = (state.color >> 8) & 0xFF;
    blueBrightness = state.color & 0xFF;

    brightness = (state.color >> 24) & 0xFF;

    /*
     * Scale RGB brightness if the Alpha brightness is not 0xFF.
     */
    if (brightness != 0xFF) {
        redBrightness = (redBrightness * brightness) / 0xFF;
        greenBrightness = (greenBrightness * brightness) / 0xFF;
        blueBrightness = (blueBrightness * brightness) / 0xFF;
    }


    /* Disable breathing. */
    set(RED_LED BREAH, 0);
    set(RED_LED BRIGHTNESS, 0);
    set(GREEN_LED BREAH, 0);
    set(GREEN_LED BRIGHTNESS, 0);
    set(BLUE_LED BREAH, 0);
    set(BLUE_LED BRIGHTNESS, 0);

    if (state.flashMode == Flash::TIMED) {
        int32_t pauseHi = state.flashOnMs;
        int32_t pauseLo = state.flashOffMs;
        int32_t breath = 0;

        if (pauseHi > 0 && pauseLo > 0) {
            breath = 1;
        }

        /* Enable breathing if times are higher than 0. */
        if (breath){
            if (redBrightness > 0 || greenBrightness > 0 || blueBrightness > 0) {
                set(RED_LED BREAH_PATTERN, getBreathPatternValue(pauseHi, pauseLo));
                set(RED_LED BREAH, 1);
                set(RED_LED BRIGHTNESS, 255);

                set(GREEN_LED BREAH_PATTERN, getBreathPatternValue(pauseHi, pauseLo));
                set(GREEN_LED BREAH, 1);
                set(GREEN_LED BRIGHTNESS, 255);

                set(BLUE_LED BREAH_PATTERN, getBreathPatternValue(pauseHi, pauseLo));
                set(BLUE_LED BREAH, 1);
                set(BLUE_LED BRIGHTNESS, 255);
            }
        }
    } else {
        if (redBrightness > 0 || greenBrightness > 0 || blueBrightness > 0) {
                set(RED_LED BRIGHTNESS, 255);
                set(GREEN_LED BRIGHTNESS, 255);
                set(BLUE_LED BRIGHTNESS, 255);
        } else {
                set(RED_LED BRIGHTNESS, 0);
                set(GREEN_LED BRIGHTNESS, 0);
                set(BLUE_LED BRIGHTNESS, 0);
        }
    }

}

static std::map<Type, std::function<void(const LightState&)>> lights = {
    {Type::BACKLIGHT, handleBacklight},
    {Type::BATTERY, handleBattery},
    {Type::NOTIFICATIONS, handleNotification},
    {Type::ATTENTION, handleNotification},
};

Light::Light() {}

int Light::rgbToBrightness(const LightState &state) {
    int color = state.color & 0x00ffffff;
    return ((77 * ((color >> 16) & 0x00ff))
            + (150 * ((color >> 8) & 0x00ff)) + (29 * (color & 0x00ff))) >> 8;
}

Return<Status> Light::setLight(Type type, const LightState& state) {
    auto it = lights.find(type);

    if (it == lights.end()) {
        return Status::LIGHT_NOT_SUPPORTED;
    }

    /*
     * Lock global mutex until light state is updated.
     */
    std::lock_guard<std::mutex> lock(globalLock);

    it->second(state);

    return Status::SUCCESS;
}

Return<void> Light::getSupportedTypes(getSupportedTypes_cb _hidl_cb) {
    std::vector<Type> types;

    for (auto const& light : lights) types.push_back(light.first);

    _hidl_cb(types);

    return Void();
}

}  // namespace implementation
}  // namespace V2_0
}  // namespace light
}  // namespace hardware
}  // namespace android
