#ifndef GameDataMgr_h__
#define GameDataMgr_h__

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class GameDataMgr{
public:
	GameDataMgr();
	~GameDataMgr();

	int mode;
	int currentLevel;
	int highScore;
	int bestTitle;
	bool usedUndo;

	void nextMode();
	void previousMode();
	void resetData();
	void gameOver();
	std::string loadData();
	void saveData(int mode, std::string dataStr);
	void saveHighScore();
	void updateHighScore(int score, int title);
	void loadHighScore();

	static string getCache(string key, string defaultValue);
	static void saveCache(string key, string value);
	static GameDataMgr *getInstance();
};
#endif
