#include "MainScene.h"
#include "cocostudio\ActionTimeline\CSLoader.h"
#include "ui\UIButton.h"
#include "SceneManager.h"
#include "GameConstant.h"
#include "dragonBones\parser\JSONDataParser.h"
#include "dragonBones\cocos2dx\CCFactory.h"

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

	
	const auto factory = dragonBones::CCFactory::getFactory();
	//factory->loadDragonBonesData("mecha_1002_101d_show/mecha_1002_101d_show_ske.json");
	//factory->loadDragonBonesData("mecha_1002_101d_show/mecha_1002_101d_show_ske.dbbin");
	//factory->loadTextureAtlasData("mecha_1002_101d_show/mecha_1002_101d_show_tex.json");
	//const auto armatureDisplay = factory->buildArmatureDisplay("mecha_1002_101d", "mecha_1002_101d_show");
	//armatureDisplay->getAnimation()->play("idle");

	//armatureDisplay->setPosition(0.0f, -200.0f);
	//addChild(armatureDisplay);

	//factory->loadDragonBonesData("skeleton_ske.json");
	//factory->loadTextureAtlasData("skeleton_tex.json");
	//const auto armatureDisplay = factory->buildArmatureDisplay("Win");
	//addChild(armatureDisplay);

	return true;
}

void MainScene::loadResource()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item_pack.plist");
}

void MainScene::onRate(Ref *obj)
{

}

void MainScene::onHighScore(Ref *obj)
{

}

void MainScene::onPlay(Ref *obj)
{
	SceneManager::getInstance()->changeScene(PLAY_SCENE);
}

