# Copyright (C) 2016 The CyanogenMod Project
# Copyright (C) 2017 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#
# This file is the build configuration for a full Android
# build for grouper hardware. This cleanly combines a set of
# device-specific aspects (drivers) with a device-agnostic
# product configuration (apps).
#

# Enable updating of APEXes
$(call inherit-product, $(SRC_TARGET_DIR)/product/updatable_apex.mk)

# Prebuilt
PRODUCT_COPY_FILES += \
    $(call find-copy-subdir-files,*,device/motorola/sofiar/prebuilt/product,product) \
    $(call find-copy-subdir-files,*,device/motorola/sofiar/prebuilt/root,recovery/root) \
    $(call find-copy-subdir-files,*,device/motorola/sofiar/prebuilt/permissions,product/etc/permissions) \
    $(call find-copy-subdir-files,*,device/motorola/sofiar/prebuilt/system,system) \
    $(call find-copy-subdir-files,*,device/motorola/sofiar/prebuilt/permissions,system/etc/permissions) \
    $(call find-copy-subdir-files,*,device/motorola/sofiar/prebuilt/ramdisk,ramdisk)

AB_OTA_PARTITIONS += \
    boot \
    system \
    vbmeta \
    product

# Permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/handheld_core_hardware.xml:system/etc/permissions/handheld_core_hardware.xml

AB_OTA_POSTINSTALL_CONFIG += \
    RUN_POSTINSTALL_system=true \
    POSTINSTALL_PATH_system=system/bin/otapreopt_script \
    FILESYSTEM_TYPE_system=ext4 \
    POSTINSTALL_OPTIONAL_system=true

AB_OTA_POSTINSTALL_CONFIG += \
    RUN_POSTINSTALL_system=true \
    POSTINSTALL_PATH_system=system/bin/copy_ab_partitions \
    FILESYSTEM_TYPE_system=ext4 \
    POSTINSTALL_OPTIONAL_system=true

PRODUCT_PACKAGES += \
    otapreopt_script \
    update_engine \
    update_engine_sideload \
    update_verifier \
    copy_ab_partitions

PRODUCT_HOST_PACKAGES += \
    brillo_update_payload

# Boot control
PRODUCT_PACKAGES_DEBUG += \
    bootctl

# Boot control
PRODUCT_PACKAGES += \
    android.hardware.boot@1.0-impl.recovery \
    bootctrl.trinket.recovery \
    fastbootd

PRODUCT_PACKAGES_DEBUG += \
    update_engine_client

#PRODUCT_PACKAGES += \
#    omni_charger_res_images \
#    animation.txt \
#    font_charger.png

# HIDL
PRODUCT_PACKAGES += \
    libhidltransport \
    libhwbinder \
    android.hidl.base@1.0 \
    android.hidl.manager@1.0

PRODUCT_PACKAGES += \
    com.android.future.usb.accessory

# Live Wallpapers
PRODUCT_PACKAGES += \
    LiveWallpapers \
    LiveWallpapersPicker \
    VisualizationWallpapers \
    librs_jni

PRODUCT_AAPT_CONFIG := xxxhdpi
PRODUCT_AAPT_PREF_CONFIG := xxxhdpi
PRODUCT_CHARACTERISTICS := nosdcard

# Camera
PRODUCT_PACKAGES += \
    SnapdragonCamera2

PRODUCT_PACKAGES += \
    libqcomfm_jni \
    qcom.fmradio

PRODUCT_BOOT_JARS += qcom.fmradio

# ANT+
#PRODUCT_PACKAGES += \
#    AntHalService

# QMI
PRODUCT_PACKAGES += \
    libjson

PRODUCT_PACKAGES += \
    ims-ext-common \
    ims_ext_common.xml \
    qti-telephony-hidl-wrapper \
    qti_telephony_hidl_wrapper.xml \
    qti-telephony-utils \
    qti_telephony_utils.xml \
    tcmiface

# Netutils
PRODUCT_PACKAGES += \
    netutils-wrapper-1.0 \
    libandroid_net

PRODUCT_PACKAGES += \
    MotoActions

PRODUCT_PACKAGES += \
    vndk_package

PRODUCT_PACKAGES += \
    vendor.display.config@1.10 \
    libdisplayconfig \
    libqdMetaData.system \
    libqdMetaData

#Nfc
PRODUCT_PACKAGES += \
    android.hardware.nfc@1.0 \
    android.hardware.nfc@1.1 \
    android.hardware.nfc@1.2

# Display
PRODUCT_PACKAGES += \
    libion \
    libtinyxml2

PRODUCT_PACKAGES += \
    libtinyalsa

PRODUCT_COPY_FILES += \
    frameworks/av/media/libstagefright/data/media_codecs_google_audio.xml:$(TARGET_COPY_OUT_SYSTEM)/etc/media_codecs_google_audio.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_telephony.xml:$(TARGET_COPY_OUT_SYSTEM)/etc/media_codecs_google_telephony.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_video.xml:$(TARGET_COPY_OUT_SYSTEM)/etc/media_codecs_google_video.xml

PRODUCT_PACKAGES += \
    vendor.qti.hardware.wifi@1.0

# Remove unwanted packages
PRODUCT_PACKAGES += \
    RemovePackages

# Camera cutout overlys
PRODUCT_PACKAGES += \
    MotoRav \
    MotoRavT \
    MotoSofia \
    MotoSofiaP \
    MotoSofiaPSprout \
    MotoSofiaR

PRODUCT_PACKAGES += \
    SystemUI_MotoRav \
    SystemUI_MotoRavT \
    SystemUI_MotoSofia \
    SystemUI_MotoSofiaP \
    SystemUI_MotoSofiaPSprout \
    SystemUI_MotoSofiaR

PRODUCT_BOOT_JARS += \
    android.hidl.manager-V1.0-java \
    QPerformance \
    UxPerformance

PRODUCT_PACKAGES += \
    WifiOverlay \
    TetheringConfigOverlay

# Video seccomp policy files
PRODUCT_COPY_FILES += \
    device/motorola/sofiar/seccomp/codec2.software.ext.policy:$(TARGET_COPY_OUT)/etc/seccomp_policy/codec2.software.ext.policy

# Lights
PRODUCT_PACKAGES += \
    android.hardware.light@2.0-service.trinket

# Temporary handling
#
# Include config.fs get only if legacy device/qcom/<target>/android_filesystem_config.h
# does not exist as they are mutually exclusive.  Once all target's android_filesystem_config.h
# have been removed, TARGET_FS_CONFIG_GEN should be made unconditional.
DEVICE_CONFIG_DIR := $(dir $(firstword $(subst ]],, $(word 2, $(subst [[, ,$(_node_import_context))))))
ifeq ($(wildcard device/motorola/sofiar/android_filesystem_config.h),)
  TARGET_FS_CONFIG_GEN := device/motorola/sofiar/config.fs
else
  $(warning **********)
  $(warning TODO: Need to replace legacy $(DEVICE_CONFIG_DIR)android_filesystem_config.h with config.fs)
  $(warning **********)
endif

$(call inherit-product, build/make/target/product/gsi_keys.mk)

# fix TelephonyExt
PRODUCT_PACKAGES += telephony-ext

# Bluetooth
PRODUCT_SOONG_NAMESPACES += vendor/qcom/opensource/commonsys/packages/apps/Bluetooth
PRODUCT_SOONG_NAMESPACES += vendor/qcom/opensource/commonsys/system/bt/conf

PRODUCT_PACKAGE_OVERLAYS += vendor/qcom/opensource/commonsys-intf/bluetooth/overlay/qva

PRODUCT_PACKAGES +=  \
    BluetoothExt \
    vendor.qti.hardware.btconfigstore@2.0 \
    android.hardware.bluetooth@1.0 \
    vendor.qti.hardware.bluetooth_dun-V1.0-java \
    libbtconfigstore \
    libbluetooth_qti
