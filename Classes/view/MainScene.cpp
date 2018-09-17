#include "MainScene.h"
#include "cocostudio\ActionTimeline\CSLoader.h"
#include "ui\UIButton.h"
#include "SceneManager.h"
#include "base\GameConstant.h"
#include "dragonBones\parser\JSONDataParser.h"
#include "dragonBones\cocos2dx\CCFactory.h"
#include "base\PlatformUtils.h"
#include "base\SoundManager.h"

Scene * MainScene::createScene()
{
	auto scene = Scene::create();
	Layer* layer = MainScene::create();
	scene->addChild(layer);

	return scene;
}

bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//auto sprite = Sprite::create("bg_play.png");
	//sprite->setPosition(0, 0);

	//this->addChild(sprite, 0);

	this->loadResource();

	Node* node = CSLoader::createNode("MenuScene.csb");
	this->addChild(node);

	Node *bgImage = node->getChildByName("bgImage");

	ui::Button *playButton = static_cast<ui::Button*>(bgImage->getChildByName("btn_play"));
	float scaleX = Director::getInstance()->getOpenGLView()->getScaleX();
	playButton->setZoomScale(0.1f * scaleX);
	playButton->setPressedActionEnabled(true);
	playButton->addClickEventListener(CC_CALLBACK_1(MainScene::onPlay, this));

	ui::Button *rateButton = static_cast<ui::Button*>(bgImage->getChildByName("btn_rate"));
	rateButton->setZoomScale(0.1f * scaleX);
	rateButton->setPressedActionEnabled(true);
	rateButton->addClickEventListener(CC_CALLBACK_1(MainScene::onRate, this));

	ui::Button *highScoreButton = static_cast<ui::Button*>(bgImage->getChildByName("btn_high_score"));
	highScoreButton->setZoomScale(0.1f * scaleX);
	highScoreButton->setPressedActionEnabled(true);
	highScoreButton->addClickEventListener(CC_CALLBACK_1(MainScene::onHighScore, this));

	PlatformUtils::getInstance()->signInGoogle();

	PlatformUtils::getInstance()->initBanner();
	PlatformUtils::getInstance()->showBanner();
	
	this->addKeyBoardListener();

	return true;
}

void MainScene::loadResource()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item_pack.plist");
}

void MainScene::onRate(Ref *obj)
{
	SoundManager::playClickSound();
	PlatformUtils::getInstance()->rateApp();
}

void MainScene::onHighScore(Ref *obj)
{
	SoundManager::playClickSound();
	PlatformUtils::getInstance()->showHighScore();
}

void MainScene::onPlay(Ref *obj)
{
	SoundManager::playClickSound();
	SceneManager::getInstance()->changeScene(PLAY_SCENE);
}

void MainScene::addKeyBoardListener()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void MainScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	log("Key with key code %d pressed", keyCode);
	if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE || keyCode == EventKeyboard::KeyCode::KEY_BACK) {
		this->onBackPress();
	}
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	log("Key with key code %d released", keyCode);

}

void MainScene::onBackPress()
{
	CCDirector::getInstance()->end();
}

