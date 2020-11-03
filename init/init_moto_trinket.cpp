/*
   Copyright (C) 2017-2018 The Android Open Source Project
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <android-base/properties.h>
#include <android-base/logging.h>
#include <sys/resource.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <vector>

namespace android {
namespace init {

using android::base::GetProperty;

std::vector<std::string> ro_props_default_source_order = {
    "",
    "odm.",
    "product.",
    "system.",
    "vendor.",
};

void property_override(char const prop[], char const value[], bool add = true)
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
    __system_property_update(pi, value, strlen(value));
    else if (add)
    __system_property_add(prop, strlen(prop), value, strlen(value));
}

void vendor_load_properties() {

    const auto set_ro_build_prop = [](const std::string &source,
            const std::string &prop, const std::string &value) {
        auto prop_name = "ro." + source + "build." + prop;
        property_override(prop_name.c_str(), value.c_str(), false);
    };

    const auto set_ro_product_prop = [](const std::string &source,
            const std::string &prop, const std::string &value) {
        auto prop_name = "ro.product." + source + prop;
        property_override(prop_name.c_str(), value.c_str(), false);
    };

    std::string device = GetProperty("ro.boot.device", "");
    if (device == "sofia") {
        property_override("ro.build.description", "sofia_retail-user 10 QPMS30.80-94-2 604e5 release-keys");
        property_override("ro.build.version.security_patch", "2020-07-01");
        for (const auto &source : ro_props_default_source_order) {
            set_ro_build_prop(source, "fingerprint", "motorola/sofia_retail/sofia:10/QPMS30.80-94-2/604e5:user/release-keys");
            set_ro_product_prop(source, "device", "sofia");
            set_ro_product_prop(source, "model", "moto g power");
            set_ro_product_prop(source, "name", "sofia_retail");
        }
    } else if (device == "sofiap") {
        property_override("ro.build.description", "sofiap_retail-user 10 QPRS30.80-58-5 5f0ed release-keys");
        property_override("ro.build.version.security_patch", "2020-07-01");
        for (const auto &source : ro_props_default_source_order) {
            set_ro_build_prop(source, "fingerprint", "motorola/sofiap_retail/sofiap:10/QPRS30.80-58-5/5f0ed:user/release-keys");
            set_ro_product_prop(source, "device", "sofiap");
            set_ro_product_prop(source, "model", "moto g stylus");
            set_ro_product_prop(source, "name", "sofiap_retail");
        }
    } else if (device == "sofiar") {
        property_override("ro.build.description", "sofiar_retail-user 10 QPES30.79-124-2 42d236 release-keys");
        property_override("ro.build.version.security_patch", "2020-07-01");
        for (const auto &source : ro_props_default_source_order) {
            set_ro_build_prop(source, "fingerprint", "motorola/sofiar_retail/sofiar:10/QPES30.79-124-2/42d236:user/release-keys");
            set_ro_product_prop(source, "device", "sofiar");
            set_ro_product_prop(source, "model", "moto g(8) power");
            set_ro_product_prop(source, "name", "sofiar_retail");
        }
    } else if (device == "sofiap_ao" || device == "sofiap_sprout") {
        property_override("ro.build.description", "sofiap_ao-user 10 QPRS30.80-109-2-5 298f91 release-keys");
        property_override("ro.build.version.security_patch", "2020-07-01");
        for (const auto &source : ro_props_default_source_order) {
            set_ro_build_prop(source, "fingerprint", "motorola/sofiap_ao/sofiap_sprout:10/QPRS30.80-109-2-5/298f91:user/release-keys");
            set_ro_product_prop(source, "device", "sofiap_sprout");
            set_ro_product_prop(source, "model", "moto g pro");
            set_ro_product_prop(source, "name", "sofiap_ao");
        }
    } else if (device == "rav_t") {
        property_override("ro.build.description", "rav_t-user 10 QPJ30.131-61 95ac67 release-keys");
        property_override("ro.build.version.security_patch", "2020-07-01");
        for (const auto &source : ro_props_default_source_order) {
            set_ro_build_prop(source, "fingerprint", "motorola/rav_t/rav:10/QPJ30.131-61/95ac67:user/release-keys");
            set_ro_product_prop(source, "device", "sofiap_sprout");
            set_ro_product_prop(source, "model", "moto g fast");
            set_ro_product_prop(source, "name", "rav_t");
        }
    } else if (device == "rav") {
        property_override("ro.build.description", "rav_retail-user 10 QPJS30.63-35-1-9 2a90b release-keys");
        property_override("ro.build.version.security_patch", "2020-07-01");
        for (const auto &source : ro_props_default_source_order) {
            set_ro_build_prop(source, "fingerprint", "motorola/rav_retail/rav:10/QPJS30.63-35-1-9/2a90b:user/release-keys");
            set_ro_product_prop(source, "device", "rav");
            set_ro_product_prop(source, "model", "moto g(8)");
            set_ro_product_prop(source, "name", "rav_t");
        }
    }
}

}  // namespace init
}  // namespace android
