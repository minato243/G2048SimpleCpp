LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp\
                   $(LOCAL_PATH)/../../../Classes/BasePopupDialog.cpp\
                   $(LOCAL_PATH)/../../../Classes/Board.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/animation/Animation.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/animation/AnimationState.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/animation/BaseTimelineState.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/animation/TimelineState.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/animation/WorldClock.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/armature/Armature.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/armature/Bone.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/armature/Constraint.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/armature/DeformVertices.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/armature/Slot.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/armature/TransformObject.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/cocos2dx/CCArmatureDisplay.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/cocos2dx/CCFactory.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/cocos2dx/CCSlot.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/cocos2dx/CCTextureAtlasData.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/core/BaseObject.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/core/DragonBones.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/event/EventObject.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/factory/BaseFactory.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/geom/Point.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/geom/Transform.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/model/AnimationConfig.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/model/AnimationData.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/model/ArmatureData.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/model/BoundingBoxData.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/model/CanvasData.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/model/ConstraintData.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/model/DisplayData.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/model/DragonBonesData.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/model/SkinData.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/model/TextureAtlasData.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/model/UserData.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/parser/BinaryDataParser.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/parser/DataParser.cpp\
                   $(LOCAL_PATH)/../../../Classes/dragonBones/parser/JSONDataParser.cpp\
                   $(LOCAL_PATH)/../../../Classes/GameDataMgr.cpp\
                   $(LOCAL_PATH)/../../../Classes/GameOverDialog.cpp\
                   $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp\
                   $(LOCAL_PATH)/../../../Classes/MainScene.cpp\
                   $(LOCAL_PATH)/../../../Classes/MessageDialog.cpp\
                   $(LOCAL_PATH)/../../../Classes/PlatformUtil.cpp\
                   $(LOCAL_PATH)/../../../Classes/PlayScene.cpp\
                   $(LOCAL_PATH)/../../../Classes/SceneManager.cpp\
                   $(LOCAL_PATH)/../../../Classes/SoundManager.cpp\
                   $(LOCAL_PATH)/../../../Classes/Utility.cpp\



LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
