LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

# 配置源文件目录和源文件后缀名
MY_FILES_PATH  := $(LOCAL_PATH)/../../../Classes \
                  $(LOCAL_PATH)/hellocpp
MY_FILES_SUFFIX := %.cpp %.c

# 遍历目录及子目录的函数
define walk
    $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef

# 去除字串的重复单词
define uniq =
  $(eval seen :=)
  $(foreach _,$1,$(if $(filter $_,${seen}),,$(eval seen += $_)))
  ${seen}
endef

# 遍历Jni和Classes目录
ALLFILES := $(foreach src_path,$(MY_FILES_PATH), $(call walk,$(src_path),*.*) )
#$(warning ALLFILES $(ALLFILES))

# 从所有文件中提取出所有.c和.cpp文件
FILE_LIST  := $(filter $(MY_FILES_SUFFIX),$(ALLFILES))
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
# $(warning LOCAL_SRC_FILES= $(LOCAL_SRC_FILES))

# windows递归遍历获取所有目录
MY_ALL_DIRS := $(dir $(foreach src_path,$(MY_FILES_PATH), $(call walk,$(src_path),*/) ) )
MY_ALL_DIRS := $(call uniq,$(MY_ALL_DIRS))
LOCAL_C_INCLUDES := $(MY_ALL_DIRS)

# $(warning LOCAL_C_INCLUDES= $(LOCAL_C_INCLUDES))

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
