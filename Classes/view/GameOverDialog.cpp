#include "GameOverDialog.h"
#include "cocostudio\ActionTimeline\CSLoader.h"
#include "base\GameConstant.h"
#include "SceneManager.h"

GameOverDialog::GameOverDialog(){
	CCLOG("new GameOverDialog");
}


GameOverDialog::~GameOverDialog()
{

}

void GameOverDialog::startDialog(int score, int maxNumber, PlayScene *parent){
	this->playLayer = parent;

	this->scoreLabel->setString(StringUtils::toString(score));
	this->numberLabel->setString(StringUtils::toString(maxNumber));
	this->bestScoreLabel->setString(StringUtils::toString(parent->gameData->highScore));
	this->bestTitleLabel->setString(StringUtils::toString(parent->gameData->bestTitle));

	if (this->getParent() != NULL) {
		this->_removeFromParent();
	}
	SceneManager::getInstance()->currentScene->addChild(this, LAYER_DIALOG);
}

void GameOverDialog::_removeFromParent(){
//if(this->callBackFunc != NULL){
//    this->callBackFunc->execute();
//    this->callBackFunc->release();
//}
	BasePopupDialog::_removeFromParent();
}


void GameOverDialog::setCallBackFunc(CCCallFunc *callBackFunc){
	this->callBackFunc = callBackFunc;
	if (this->callBackFunc != NULL) 
		this->callBackFunc->retain();
}


void GameOverDialog::onRestart(Ref *obj){
	CCLOG("onRestart");
	//SoundManager.playClickSound();
	this->playLayer->createNewGame();
	this->closeDialog();
}

void GameOverDialog::onHome(Ref *obj){
	this->closeDialog();
	SceneManager::getInstance()->changeScene(MENU_SCENE);
}


void GameOverDialog::onShare(Ref *obj)
{
	CCLOG("onShare");
}

bool GameOverDialog::init()
{
	if(!BasePopupDialog::init())
		return false;
	Node* node = CSLoader::createNode("GameOverDialog.csb");
	this->addChild(node);
	this->bgImage = node->getChildByName("bgImage");
	auto bgImage = this->bgImage;
	auto bgMessage = bgImage->getChildByName("bg_message");
	this->scoreLabel = dynamic_cast<ui::TextBMFont *>(bgMessage->getChildByName("lb_score"));
	this->numberLabel = dynamic_cast<ui::TextBMFont *>(bgMessage->getChildByName("lb_title"));
	this->bestScoreLabel = dynamic_cast<ui::TextBMFont *>(bgMessage->getChildByName("lb_best_score"));
	this->bestTitleLabel = dynamic_cast<ui::TextBMFont *>(bgMessage->getChildByName("lb_best_title"));

	this->restartButton = dynamic_cast<ui::Button *>(bgImage->getChildByName("btn_restart"));
	this->restartButton->addClickEventListener(CC_CALLBACK_1(GameOverDialog::onRestart, this));
	this->homeButton = dynamic_cast<ui::Button *>(bgImage->getChildByName("btn_home"));
	this->homeButton->addClickEventListener(CC_CALLBACK_1(GameOverDialog::onHome, this));
	this->shareButton = dynamic_cast<ui::Button *>(bgImage->getChildByName("btn_share"));
	this->shareButton->addClickEventListener(CC_CALLBACK_1(GameOverDialog::onShare, this));
	return true;
}



GameOverDialog* gameOverDialogInstance = NULL;

GameOverDialog * GameOverDialog::getInstance()
{
	if (gameOverDialogInstance == NULL){
		gameOverDialogInstance = GameOverDialog::create();
		gameOverDialogInstance->retain();
	}
	return gameOverDialogInstance;
}

void GameOverDialog::destroyInstance()
{
	if (gameOverDialogInstance != NULL){
		gameOverDialogInstance->release();
		gameOverDialogInstance = NULL;
	}
}


