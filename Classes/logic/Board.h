#ifndef Board_h__
#define Board_h__

#include <vector>
#include "cocos2d.h"
#include <string>

using namespace std;
USING_NS_CC;

#define LEFT	1
#define RIGHT	2
#define UP		3
#define DOWN	4
class Board{
public:
	int size;

	vector<vector<int>> matrix;
	vector<vector<int>> oldMatrix;
	vector<CCPoint> emptyList;
	int score;
	bool isCanUndo;
	vector<CCPoint> mergePosList;
	bool isCongrate;
	
	Board(int size);
	~Board();
	void createNewMatrix();
	vector<int> getNewZeroVector();
	void initRandom();
	void cloneMatrix();
	CCPoint addNewNumber();
	CCPoint createRandomPos();
	CCPoint getEmptyPos();
	CCPoint moveAndAddNewNumber(int dir);
	bool move(int direct);
	bool moveLeft();
	bool moveRight();
	bool moveUp();
	bool moveDown();
	void undo();
	string getMatrixString();
	string getOldMatrixString();
	int getScore();
	int getMaxNumber();
	void addScore(int num);
	bool canMove();
	string convertDataToSaveString();
	void convertDataFromString(string dataStr);
	vector<vector<int>> convertMatrixFromString(string dataMatrixStr);
	vector<int> convertNumListFromString(string dataArray);
	void addToMergePosList(CCPoint pos);
	void removeFromMergePosList(CCPoint pos);
};
#endif