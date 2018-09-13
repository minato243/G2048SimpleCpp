#include "PlayScene.h"
#include "cocostudio\ActionTimeline\CSLoader.h"
#include "base\ccMacros.h"
#include "SceneManager.h"
#include "GameConstant.h"
#include "deprecated\CCDeprecated.h"
#include "GameDataMgr.h"
#include "base\CCEventKeyboard.h"
#include "GameOverDialog.h"

using namespace ui;

int GAME_MATRIX_SIZE[5] = { 3, 4, 5, 6, 8 };

int POS_X[] = { 138, 289, 438, 587 };
int POS_Y[] = { 252, 461, 670, 880 };


PlayScene::PlayScene()
{
	isMoving = false;
	isSpawning = false;
	scaleRate = 1;
}

PlayScene::~PlayScene()
{

}

Scene * PlayScene::createScene()
{
	auto scene = PlayScene::create();
	return scene;
}

bool PlayScene::init()
{
	if (!Scene::init()){
		return false;
	}

	this->initGui();
	this->addListener();

	return true;
}

void PlayScene::onClickHome(Ref* obj)
{
	CCLOG("onClickHome");
	this->onBackPress();
}

void PlayScene::onEnter()
{
	Scene::onEnter();
	this->initData();
}

void PlayScene::initGui()
{
	auto layer = Layer::create();
	this->addChild(layer);

	Node* node = CSLoader::createNode("PlayScene.csb");
	layer->addChild(node);

	this->bgImage = (ui::Widget *)node->getChildByName("bgImage");

	this->homeButton = (ui::Button *)this->bgImage->getChildByName("btn_back");
	this->scoreLabel = dynamic_cast<ui::TextBMFont *>(this->bgImage->getChildByName("lb_score"));
	this->highScoreLabel = dynamic_cast<ui::TextBMFont *>(this->bgImage->getChildByName("lb_high_score"));

	float scaleX = Director::getInstance()->getOpenGLView()->getScaleX();
	this->homeButton->setZoomScale(0.1f * scaleX);
	this->homeButton->setPressedActionEnabled(true);
	this->homeButton->addClickEventListener(CC_CALLBACK_1(PlayScene::onClickHome, this));
	this->bgMode = CCSprite::create();
	this->bgImage->addChild(this->bgMode);
}

void PlayScene::initListNumber()
{
	CCLOG("init List Number");
	int mode = this->gameData->mode;
	//int imageSize = IMAGE_SIZE[this->gameData->mode];
	this->bgMode->removeAllChildren();
	this->bgNumberList.clear();
	for (int i = 0; i < this->board->size; i++) {
		vector<CCSprite *> spriteList;
		for (int j = 0; j < this->board->size; j++) {
			CCSprite* numberBgImage = CCSprite::createWithSpriteFrameName("item/bg_2.png");
			CCPoint pos = ccp(POS_X[j], POS_Y[this->board->size - i - 1]);
			CCLOG("pos = [%f, %f]" ,pos.x, pos.y);
			numberBgImage->setPosition(pos);
			this->bgMode->addChild(numberBgImage);
			spriteList.push_back(numberBgImage);
			//if (this->scaleRate == 0)
			//    this->scaleRate = imageSize / numberBgImage.getContentSize().width;
			//numberBgImage.setScale(this->scaleRate);
			numberBgImage->setVisible(false);
		}
		this->bgNumberList.push_back(spriteList);
	}
}

void PlayScene::initData()
{
	CCLOG("initData");
	this->gameData = GameDataMgr::getInstance();
	this->board = new Board(GAME_MATRIX_SIZE[1]);
	this->savedData = this->gameData->loadData();
	if (this->savedData == "") {
		this->board->createNewMatrix();
		this->initListNumber();
		this->updateData();
	}
	else {
		this->loadData();
	}
}

void PlayScene::addListener()
{   
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this->bgImage);
}



bool PlayScene::onTouchBegan(Touch* touch, cocos2d::Event* event){
	this->touchBeganPos = touch->getLocation();
	CCLOG("onTouchBegan (%f, %f)", this->touchBeganPos.x, this->touchBeganPos.y);
	return true;
}

void PlayScene::onTouchMoved(Touch* touch, cocos2d::Event* event){
	//CCLOG("onTouchMoved");
	if (this->bgImage->getBoundingBox().containsPoint(touch->getLocation()))
	{
		
	}
}
void PlayScene::onTouchEnded(Touch* touch, cocos2d::Event* event){
	CCLOG("onTouchEnded");
	Vec2 pos = touch->getLocation();
	CCLOG("onTouchEnded ( %f, %f), touchBegan (%f, %f)", pos.x, pos.y, this->touchBeganPos.x, this->touchBeganPos.y);

	float dX = pos.x - this->touchBeganPos.x;
	float dY = pos.y - this->touchBeganPos.y;
	if (dX > DRAG_DISTANCE || dX < -DRAG_DISTANCE
		|| dY > DRAG_DISTANCE || dY < -DRAG_DISTANCE) {
		if (abs(dX) > abs(dY)) {
			if (dX > DRAG_DISTANCE) this->showMoveEffect(RIGHT);
			else this->showMoveEffect(LEFT);
		}
		else {
			if (dY > DRAG_DISTANCE) this->showMoveEffect(UP);
			else this->showMoveEffect(DOWN);
		}
	}
}

void PlayScene::addKeyBoardListener()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PlayScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(PlayScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void PlayScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	log("Key with key code %d pressed", keyCode);
	if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE || keyCode == EventKeyboard::KeyCode::KEY_BACK) {
		this->onBackPress();
	}
}

void PlayScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	log("Key with key code %d released", keyCode);
	
}

void PlayScene::updateData()
{
	CCLOG("update data");
	//var spriteFrameName = "res/bg_mode_" + (this->gameData->mode + 1) + ".png";
	//CCLOG("updateData " + spriteFrameName);
	//var sprite = cc.Sprite.create(spriteFrameName);
	//this->bgMode->setSpriteFrame(sprite.getSpriteFrame());
	this->scoreLabel->setString("Hello");	
	this->highScoreLabel->setString(StringUtils::toString(this->gameData->highScore));

	for (int i = 0; i < this->board->size; i++) {
		for (int j = 0; j < this->board->size; j++) {
			this->bgNumberList.at(i).at(j)->stopAllActions();
			this->bgNumberList.at(i).at(j)->setPosition(ccp(POS_X[j], POS_Y[this->board->size - i - 1]));
			if (this->board->matrix.at(i).at(j) == 0) {
				this->bgNumberList.at(i).at(j)->setVisible(false);
			}
			else {
				this->bgNumberList.at(i).at(j)->setVisible(true);
				this->bgNumberList.at(i).at(j)->setSpriteFrame(this->getSpriteFrameNameForNumber(this->board->matrix.at(i).at(j)));
				//this->bgNumberList.at(i).at(j).setScale(this->scaleRate);
			}
		}
	}

	this->scoreLabel->setString(StringUtils::toString(this->board->score));

	this->checkGameOver();
}

void PlayScene::loadData()
{
	this->board->convertDataFromString(this->savedData);
	this->initListNumber();
	this->updateData();
}

std::string PlayScene::getSpriteFrameNameForNumber(int number)
{
	char text[50];
	sprintf(text, "item/bg_%d.png", number);
	return string(text);
}

bool PlayScene::checkGameOver()
{
	if (!this->board->canMove()) {
		CCLOG("can not move");
		this->gameOver();
		return true;
	}

	return false;
}

void PlayScene::showMoveEffect(int dir)
{
	CCLOG("showMoveEffect %d", dir);

	if (this->isMoving) {
		this->board->moveAndAddNewNumber(this->curDir);
		this->updateData();
		this->isMoving = false;
		CCLOG("showMoveEffect error isMoving");
	}
	else if (this->isSpawning) {
		this->board->addNewNumber();
		this->updateData();
		this->isSpawning = false;
		CCLOG("showMoveEffect error isSpawning");
	}
	else {
		this->isMoving = true;
		this->curDir = dir;
		this->maxStepEffect = 0;
		if (dir == LEFT) this->moveLeftEffect();
		else if (dir == RIGHT) this->moveRightEffect();
		else if (dir == UP) this->moveUpEffect();
		else if (dir == DOWN) this->moveDownEffect();
	}
}

void PlayScene::moveLeftEffect()
{
	int n = this->board->size;
	vector<vector<int>> matrix = this->board->matrix;

	this->maxStepEffect = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int count = 0;
			bool added = false;
			for (int k = 0; k < j; k++) {
				if (matrix[i][k] == 0) {
					count++;
					added = false;
				}
				else if (matrix[i][k] == matrix[i][k + 1]) {
					if (!added) {
						count++;
						added = true;
					}
					else {
						added = false;
					}
				}
				else {
					added = false;
				}
			}
			if (this->maxStepEffect < count) this->maxStepEffect = count;
		}
	}
	if (this->maxStepEffect > 0) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int count = 0;
				bool added = false;
				for (int k = 0; k < j; k++) {
					if (matrix[i][k] == 0) {
						count++;
						added = false;
					}
					else if (matrix[i][k] == matrix[i][k + 1]) {
						if (!added) {
							count++;
							added = true;
						}
						else {
							added = false;
						}
					}
					else {
						added = false;
					}
				}
				if (count > 0) {
					this->moveEffect(this->bgNumberList[i][j], i, j, LEFT, count);
				}
			}
		}
	}
	else {
		this->moveEffectComplete();
	}
}

void PlayScene::moveRightEffect()
{
	int n = this->board->size;

	vector<vector<int>> matrix = this->board->matrix;

	this->maxStepEffect = 0;

	for (int i= 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int count = 0;
			bool added = false;
			for (int k = n - 1; k > j; k--) {
				if (matrix[i][k] == 0) {
					added = false;
					count++;
				}
				else if (matrix[i][k] == matrix[i][k - 1]) {
					if (!added) {
						added = true;
						count++;
					}
					else added = false;
				}
				else {
					added = false;
				}
			}
			if (this->maxStepEffect < count) this->maxStepEffect = count;
		}
	}

	if (this->maxStepEffect > 0) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int count = 0;
				bool added = false;
				for (int k = n - 1; k > j; k--) {
					if (matrix[i][k] == 0) {
						added = false;
						count++;
					}
					else if (matrix[i][k] == matrix[i][k - 1]) {
						if (!added) {
							added = true;
							count++;
						}
						else added = false;
					}
					else {
						added = false;
					}
				}
				if (count > 0) {
					this->moveEffect(this->bgNumberList[i][j], i, j, RIGHT, count);
				}
			}
		}
	}
	else {
		this->moveEffectComplete();
	}
}

void PlayScene::moveUpEffect()
{
	int n = this->board->size;
	vector<vector<int>> matrix = this->board->matrix;

	this->maxStepEffect = 0;
	for (int i= 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int count = 0;
			bool added = false;
			for (int k = 0; k < i; k++) {
				if (matrix[k][j] == 0) {
					count++;
				}
				else if (matrix[k][j] == matrix[k + 1][j]) {
					if (!added) {
						count++;
						added = true;
					}
					else {
						added = false;
					}
				}
				else {
					added = false;
				}
			}
			if (this->maxStepEffect < count) this->maxStepEffect = count;
		}
	}

	if (this->maxStepEffect > 0) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int count = 0;
				bool added = false;
				for (int k = 0; k < i; k++) {
					if (matrix[k][j] == 0) {
						count++;
					}
					else if (matrix[k][j] == matrix[k + 1][j]) {
						if (!added) {
							count++;
							added = true;
						}
						else {
							added = false;
						}
					}
					else {
						added = false;
					}
				}
				if (count > 0) {
					this->moveEffect(this->bgNumberList[i][j], i, j, UP, count);
				}
			}
		}
	}
	else {
		this->moveEffectComplete();
	}
}

void PlayScene::moveDownEffect()
{
	int n = this->board->size;
	vector<vector<int>> matrix = this->board->matrix;

	this->maxStepEffect = 0;
	for (int i= 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] == 0) continue;

			int count = 0;
			bool added = false;
			for (int k = n - 1; k > i; k--) {
				if (matrix[k][j] == 0) {
					count++;
					added = false;
				}
				else if (matrix[k][j] == matrix[k - 1][j]) {
					if (!added) {
						count++;
						added = true;
					}
					else added = false;
				}
				else {
					added = false;
				}
			}
			if (this->maxStepEffect < count) this->maxStepEffect = count;
		}
	}

	if (this->maxStepEffect > 0) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (matrix[i][j] == 0) continue;
				int count = 0;
				bool added = false;
				for (int k = n - 1; k > i; k--) {
					if (matrix[k][j] == 0) {
						count++;
						added = false;
					}
					else if (matrix[k][j] == matrix[k - 1][j]) {
						if (!added) {
							count++;
							added = true;
						}
						else added = false;
					}
					else {
						added = false;
					}
				}
				if (count > 0) {
					this->moveEffect(this->bgNumberList[i][j], i, j, DOWN, count);
				}
			}
		}
	}
	else {
		this->moveEffectComplete();
	}
}

void PlayScene::moveEffect(Node *icon, int i, int j, int dir, int numStep) {
	int mode = this->gameData->mode;

	if (dir == LEFT) j -= numStep;
	else if (dir == RIGHT) j += numStep;
	else if (dir == UP) i -= numStep;
	else i += numStep;
	Vec2 desPos = ccp(POS_X[j], POS_Y[this->board->size - i - 1]);
	float moveTime = 0;
	if (mode > 2) moveTime = numStep * MOVE_EFFECT_TIME * GAME_MATRIX_SIZE[1] / GAME_MATRIX_SIZE[mode];
	else moveTime = numStep * MOVE_EFFECT_TIME * GAME_MATRIX_SIZE[1] / GAME_MATRIX_SIZE[mode];

	if (numStep == this->maxStepEffect)
		icon->runAction(CCSequence::create(CCMoveTo::create(moveTime, desPos), CCCallFunc::create(this, CC_CALLFUNC_SELECTOR(PlayScene::moveEffectComplete)), NULL));
	else icon->runAction(CCMoveTo::create(moveTime, desPos));
}

void PlayScene::moveEffectComplete(){
	CCLOG("moveEffectComplete");
	if (this->isMoving) {
		CCLOG("moveEffectComplete isMoving");

		bool moved = this->board->move(this->curDir);
		this->isMoving = false;
		this->updateData();
		if (moved) {
			Vec2 pos = this->board->addNewNumber();
			//SoundManager::playMoveSound();
			this->spawnEffect(pos);
			this->mergeEffect();
		}

	}
}

void PlayScene::spawnEffect(Vec2 pos)
{
	this->isSpawning = true;
	int i= pos.x;
	int j = pos.y;

	this->bgNumberList.at(i).at(j)->stopAllActions();
	this->bgNumberList.at(i).at(j)->setPosition(ccp(POS_X[j], POS_Y[this->board->size - i - 1]));
	if (this->board->matrix[i][j] == 0) {
		this->bgNumberList.at(i).at(j)->setVisible(false);
	}
	else {
		this->bgNumberList.at(i).at(j)->setVisible(true);
		this->bgNumberList.at(i).at(j)->setSpriteFrame(this->getSpriteFrameNameForNumber(this->board->matrix[i][j]));
	}

	auto action = CCSequence::create(CCScaleTo::create(0, 0.4 * this->scaleRate), CCScaleTo::create(SPAWN_EFFECT_TIME, this->scaleRate),
		CCCallFunc::create(this, CC_CALLFUNC_SELECTOR(PlayScene::spawnEffectComplete)), NULL);
	this->bgNumberList[pos.x][pos.y]->runAction(action);
}

void PlayScene::spawnEffectComplete()
{
	this->isSpawning = false;
	this->updateData();
	CCLOG("%s", this->board->getMatrixString().c_str());
}

void PlayScene::mergeEffect()
{
	vector<CCPoint> mergePostList = this->board->mergePosList;
	for (int i = 0; i < mergePostList.size(); i++){
		CCPoint pos = mergePostList.at(i);
		auto action = CCSequence::create(CCScaleTo::create(MERGE_EFFECT_TIME / 2, 1.1), CCScaleTo::create(MERGE_EFFECT_TIME, 1), NULL);
		this->bgNumberList.at(pos.x).at(pos.y)->runAction(action);
	}
}

void PlayScene::mergeEffectComplete()
{

}

void PlayScene::onBackPress()
{
	this->saveCurrentData();
	SceneManager::getInstance()->changeScene(MENU_SCENE);
}

void PlayScene::saveCurrentData()
{
	this->gameData->saveData(this->gameData->mode, this->board->convertDataToSaveString());
	this->gameData->updateHighScore(this->board->score, this->board->getMaxNumber());
}

void PlayScene::gameOver()
{
	CCLOG("game Over");
	GameOverDialog::destroyInstance();
	GameOverDialog::getInstance()->startDialog(this->board->score, this->board->getMaxNumber(), this);
	//PlatformUtils::getInstance()->updateLeaderBoard(this->gameData->mode, this->board->score);
	//PlatformUtils::getInstance()->showInterstitialAd();
	this->gameData->saveData(this->gameData->mode, "");
}

void PlayScene::createNewGame()
{
	this->board->createNewMatrix();
	this->initListNumber();
	this->updateData();
}

