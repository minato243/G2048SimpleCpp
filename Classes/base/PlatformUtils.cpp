#include "PlatformUtils.h"
#include <stdio.h>
#include "cocos2d.h"
#if CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM
#include "platform\android\jni\JniHelper.h"
#endif



USING_NS_CC;

string PlatformUtils::CLASS_DEFAULT = "com.moc.g2048.AndroidUtils";

void PlatformUtils::signInGoogle(){
	CCLOG("PlatformUtils::signInGoogle");
	this->callAndroidFunction(PlatformUtils::CLASS_DEFAULT, "signIn", "()V");
}

void PlatformUtils::shareMyApp(){
	this->callAndroidFunction(PlatformUtils::CLASS_DEFAULT,"shareMyApp","()V");
}

void PlatformUtils::rateApp(){
	this->callAndroidFunction(PlatformUtils::CLASS_DEFAULT, "rateMyApp", "()V");
}

void PlatformUtils::showHighScore(){
	this->callAndroidFunction(PlatformUtils::CLASS_DEFAULT, "showRanking", "()V");
}

void PlatformUtils::updateScore(int score){
	this->callAndroidFunction(PlatformUtils::CLASS_DEFAULT, "updateHighScore", "(I)V", StringUtils::toString(score));
}

void PlatformUtils::showInterstitialAd(){
	this->callAndroidFunction(PlatformUtils::CLASS_DEFAULT, "showInterstitialAd", "()V");
}

void PlatformUtils::showVideoRewardAd(){
	this->callAndroidFunction(PlatformUtils::CLASS_DEFAULT, "showVideoRewardAd", "()V");
}

void PlatformUtils::initBanner(){
	this->callAndroidFunction(PlatformUtils::CLASS_DEFAULT, "initBanner", "()V");
}

void PlatformUtils::showBanner(){
	this->callAndroidFunction(PlatformUtils::CLASS_DEFAULT, "showBanner", "()V");
}

void PlatformUtils::hideBanner(){
	this->callAndroidFunction(PlatformUtils::CLASS_DEFAULT, "hideBanner", "()V");
}

void PlatformUtils::updateLeaderBoard(int mode, int score){
	CCLOG("PlatformUtils.updateLeaderBoard mode = %d, score = %d", mode, score);
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, PlatformUtils::CLASS_DEFAULT.c_str(), "updateLeaderBoard", "(II)V")){
		t.env->CallStaticVoidMethod(t.classID, t.methodID, mode, score);
	}

#endif
}

void PlatformUtils::callAndroidFunction(string className, string methodName, 
	string methodSignature, string parameters)
{
	CCLOG("PlatformUtils::callAndroidFunction %s, %s, %s, %s", 
		className.c_str(), methodName.c_str(), methodSignature.c_str(), parameters.c_str());
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), methodSignature.c_str())){
		if (parameters.compare("") == 0)
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
		else {
			//jstring stringArg1 = t.env->NewStringUTF(parameters.c_str());
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
		}
		t.env->DeleteLocalRef(t.classID);
	}
#endif
	
}


PlatformUtils *platformInstance = NULL;

PlatformUtils *PlatformUtils::getInstance(){
	if (platformInstance == NULL){
		platformInstance = new PlatformUtils();
	}

	return platformInstance;
};

void PlatformUtils::destroyInstance(){
	if (platformInstance != NULL){
		delete platformInstance;
		platformInstance = NULL;
	}
};

PlatformUtils::PlatformUtils()
{

}

PlatformUtils::~PlatformUtils()
{

}

