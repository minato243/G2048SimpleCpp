/*Created by thaod*/
#include "GameDataMgr.h"
#include "base\GameConstant.h"

#define GAME_DATA_KEY "game_data"
#define HIGH_SCORE_KEY "game_high_score"
#define HIGH_TITLE_KEY "game_high_title"

GameDataMgr *gameDataMgrInstance = NULL;

GameDataMgr::GameDataMgr()
{
	this->mode = 1;
	currentLevel = 0;
	highScore = 0;
	bestTitle = 0;
	usedUndo = false;
	this->loadHighScore();
}

GameDataMgr::~GameDataMgr()
{

}

void GameDataMgr::nextMode()
{
	this->mode = (this->mode + 1) % NUM_MODE;
	this->loadHighScore();
}

void GameDataMgr::previousMode()
{
	this->mode = (this->mode + NUM_MODE - 1) % NUM_MODE;
	this->loadHighScore();
}

void GameDataMgr::resetData()
{
	this->currentLevel = 0;
}

void GameDataMgr::gameOver()
{

}

std::string GameDataMgr::loadData()
{
	string gameDataStr = GameDataMgr::getCache(GAME_DATA_KEY + StringUtils::toString(this->mode), "");
	return gameDataStr;
}

void GameDataMgr::saveData(int mode, std::string dataStr)
{
	GameDataMgr::saveCache(GAME_DATA_KEY + StringUtils::toString(mode), dataStr);
}

void GameDataMgr::saveHighScore()
{
	GameDataMgr::saveCache(HIGH_SCORE_KEY + this->mode, StringUtils::toString(this->highScore));
	GameDataMgr::saveCache(HIGH_TITLE_KEY + this->mode, StringUtils::toString(this->bestTitle));
}

void GameDataMgr::updateHighScore(int score, int title)
{
	if (score > this->highScore || title > this->bestTitle){
		if (score > this->highScore){
			this->highScore = score;
		}

		if (title > this->bestTitle){
			this->bestTitle = title;
		}
		this->saveHighScore();
	}
}

void GameDataMgr::loadHighScore()
{
	string highScoreStr = GameDataMgr::getCache(string(HIGH_SCORE_KEY) + StringUtils::toString(this->mode), StringUtils::toString(0));
	this->highScore = atoi(highScoreStr.c_str());

	string highTittleStr = GameDataMgr::getCache(string(HIGH_TITLE_KEY) + StringUtils::toString(this->mode), StringUtils::toString(0));
	this->bestTitle = atoi(highTittleStr.c_str());
}

GameDataMgr * GameDataMgr::getInstance()
{
	if (gameDataMgrInstance == NULL){
		gameDataMgrInstance = new GameDataMgr();
	}

	return gameDataMgrInstance;
}


void GameDataMgr::saveCache(string key, string value)
{
	CCUserDefault::sharedUserDefault()->setStringForKey(key.c_str(), value);
	CCUserDefault::sharedUserDefault()->flush();
}

std::string GameDataMgr::getCache(string key, string defaultValue)
{
	string value = CCUserDefault::sharedUserDefault()->getStringForKey(key.c_str(), defaultValue);
	return value;
}

