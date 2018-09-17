#include "SceneManager.h"
#include "ExtensionExport.h"
#include "base\GameConstant.h"
#include "PlayScene.h"
#include "MainScene.h"
#include "base\PlatformUtils.h"


SceneManager *sceneMgrInstance = NULL;

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::changeScene(int sceneId)
{
	switch (sceneId)
	{
	case LOADING_SCENE:

		break;
	case PLAY_SCENE:
		this->currentScene = PlayScene::createScene();
		Director::getInstance()->replaceScene(TransitionSlideInB::create(0.5, this->currentScene));
		PlatformUtils::getInstance()->showInterstitialAd();
		break;
	case MENU_SCENE:
		this->currentScene = MainScene::createScene();
		Director::getInstance()->replaceScene(TransitionSlideInT::create(0.5, this->currentScene));
		PlatformUtils::getInstance()->showInterstitialAd();
		break;
		
	default:
		break;
	}
}

SceneManager * SceneManager::getInstance()
{
	if (sceneMgrInstance == nullptr){
		sceneMgrInstance = new SceneManager();
	}

	return sceneMgrInstance;
}

void SceneManager::deystroyInstance()
{
	if (sceneMgrInstance != NULL){
		delete sceneMgrInstance;
		sceneMgrInstance = NULL;
	}
}

