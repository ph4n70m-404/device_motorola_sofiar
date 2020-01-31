LOCAL_PATH := $(call my-dir)
include $(call all-makefiles-under,$(LOCAL_PATH))

IMS_LIBS := libimscamera_jni.so libimsmedia_jni.so
IMS_SYMLINKS := $(addprefix $(TARGET_OUT_PRODUCT_APPS_PRIVILEGED)/ims/lib/arm64/,$(notdir $(IMS_LIBS)))
$(IMS_SYMLINKS): $(LOCAL_INSTALLED_MODULE)
	@echo "IMS lib link: $@"
	@mkdir -p $(dir $@)
	@rm -rf $@
	$(hide) ln -sf /system/lib64/$(notdir $@) $@

ALL_DEFAULT_INSTALLED_MODULES += $(IMS_SYMLINKS)

NXP_LIB := libstnfc_nci_jni.so libnfc_st_dta_jni.so
NXP_SYMLINKS := $(addprefix $(TARGET_OUT_PRODUCT_APPS)/Nfc_st/lib/arm64/,$(notdir $(NXP_LIB)))
$(NXP_SYMLINKS): $(LOCAL_INSTALLED_MODULE)
	@echo "NXP lib link: $@"
	@mkdir -p $(dir $@)
	@rm -rf $@
	$(hide) ln -sf /system/product/lib64/$(notdir $@) $@

ALL_DEFAULT_INSTALLED_MODULES += $(NXP_SYMLINKS)
