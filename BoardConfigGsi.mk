# BoardConfigGsiCommon.mk
#
# Common compile-time definitions for GSI
# Builds upon the mainline config.
#

#TARGET_NO_KERNEL := true

# This flag is set by mainline but isn't desired for GSI.
BOARD_USES_SYSTEM_OTHER_ODEX :=

# system.img is always ext4 with sparse option
# GSI also includes make_f2fs to support userdata parition in f2fs
# for some devices
TARGET_USERIMAGES_USE_F2FS := true

# GSI specific System Properties
ifneq (,$(filter userdebug eng,$(TARGET_BUILD_VARIANT)))
TARGET_SYSTEM_PROP += build/make/target/board/gsi_system.prop
else
TARGET_SYSTEM_PROP += build/make/target/board/gsi_system_user.prop
endif

# Setup a vendor image to let PRODUCT_PROPERTY_OVERRIDES does not affect GSI
BOARD_VENDORIMAGE_FILE_SYSTEM_TYPE := ext4

# Disable 64 bit mediadrmserver
TARGET_ENABLE_MEDIADRM_64 := true
