#include "Board.h"
#include "base\GameConstant.h"

Board::Board(int size)
{
	this->size = size;
}

Board::~Board()
{

}

void Board::createNewMatrix(){
	this->matrix.clear();
	this->oldMatrix.clear();
	for (int i = 0; i < this->size; i++) {
		vector<int> newVector = this->getNewZeroVector();
		this->matrix.push_back(newVector);

		this->oldMatrix.push_back(this->getNewZeroVector());
	}
	this->initRandom();
	this->cloneMatrix();
	this->score = 0;
	this->isCanUndo = false;
}


vector<int> Board::getNewZeroVector()
{
	vector<int> newVector;
	for (int j = 0; j < this->size; j++){
		newVector.push_back(0);
	}
	return newVector;
}

void Board::initRandom() {
	CCPoint pos = this->createRandomPos();
	CCLOG("initRandom [%f, %f]", pos.x, pos.y);
	this->matrix[pos.x][pos.y] = 2;
	this->addNewNumber();
}

void Board::cloneMatrix(){
	this->oldMatrix.clear();
	for (int i = 0; i < this->size; i++){
		vector<int> numList;
		for (int j = 0; j < this->size; j++){
			numList.push_back(matrix[i][j]);
		}
		this->oldMatrix.push_back(numList);
	}

}

CCPoint Board::addNewNumber() {
	CCPoint pos = this->getEmptyPos();
	CCLOG("addNewNumber [%f, %f]", pos.x, pos.y);
	if (pos.x == -1 && pos.y == -1) return pos;
	this->matrix[pos.x][pos.y] = 2;
	return pos;
}

CCPoint Board::createRandomPos() {
	int x = rand() % this->size;
	int y = rand() % this->size;

	return ccp(x, y);
}

CCPoint Board::getEmptyPos() {
	int size = this->size;

	this->emptyList.clear();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (this->matrix[i][j] == 0) {
				CCPoint pos = ccp(i, j);
				this->emptyList.push_back(pos);
			}
		}
	}

	int n = this->emptyList.size();
	if (n == size * size) return ccp(-1, -1);
	int r = rand() % n;

	return this->emptyList[r];
}

CCPoint Board::moveAndAddNewNumber(int dir){
	if (this->move(dir)){
		return this->addNewNumber();
	}
	return NULL;
}

bool Board::move(int direct){
	//CCLOG("move "+direct);
	vector<vector<int>> tmp = this->oldMatrix;
	this->cloneMatrix();
	//CCLOG("old matrix "+ this->getOldMatrixString());
	this->mergePosList.clear();

	bool hasMoved = false;
	this->isCongrate = false;
	switch (direct){
	case LEFT:
		hasMoved = this->moveLeft();
		break;
	case RIGHT:
		hasMoved = this->moveRight();
		break;
	case UP:
		hasMoved = this->moveUp();
		break;
	case DOWN:
		hasMoved = this->moveDown();
		break;
	}

	if (hasMoved){
		CCLOG("isCanUndo");
		this->isCanUndo = true;
	}
	else{
		this->oldMatrix = tmp;
	}

	return hasMoved;
}

bool Board::moveLeft() {
	CCLOG("moveLeft");

	int size = this->size;
	bool hasMoved = false;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (this->matrix[i][j] == 0) {
				for (int k = j + 1; k < size; k++) {
					if (this->matrix[i][k] != 0) {
						this->matrix[i][j] = this->matrix[i][k];
						this->matrix[i][k] = 0;
						//this->removeFromMergePosList(ccp(int i,k));
						hasMoved = true;
						break;
					}
				}
			}
			if (this->matrix[i][j] != 0) {
				for (int k = j + 1; k < size; k++) {
					if (this->matrix[i][k] != 0) {
						if (this->matrix[i][k] == this->matrix[i][j]) {
							int lastMaxNumber = this->getMaxNumber();
							this->matrix[i][j] += this->matrix[i][k];
							this->matrix[i][k] = 0;
							if (this->matrix[i][j] == CONGRAT_NUM && lastMaxNumber < CONGRAT_NUM){
								this->isCongrate = true;
							}
							this->addToMergePosList(ccp(i, j));
							this->addScore(this->matrix[i][j]);
							hasMoved = true;
						}
						break;
					}
				}
			}

		}
	}
	return hasMoved;
}

bool Board::moveRight() {
	CCLOG("moveRight");

	int size = this->size;
	bool hasMoved = false;
	for (int i = 0; i < size; i++) {
		for (int j = size - 1; j >= 0; j--) {
			if (this->matrix[i][j] == 0 ) {
				for (int k = j - 1; k >= 0; k--) {
					if (this->matrix[i][k] != 0) {
						this->matrix[i][j] = this->matrix[i][k];
						this->matrix[i][k] = 0;
						//this->removeFromMergePosList(ccp(int i,k));
						hasMoved = true;
						break;
					}
				}
			}
			if (this->matrix[i][j] != 0) {
				for (int k = j - 1; k >= 0; k--) {
					if (this->matrix[i][k] != 0) {
						if (this->matrix[i][k] == this->matrix[i][j]){
							int lastMaxNumber = this->getMaxNumber();
							this->matrix[i][j] += this->matrix[i][k];
							this->matrix[i][k] = 0;
							if (this->matrix[i][j] == CONGRAT_NUM && lastMaxNumber < CONGRAT_NUM){
								this->isCongrate = true;
							}
							this->addScore(this->matrix[i][j]);
							this->addToMergePosList(ccp(i, j));
							hasMoved = true;
						}
						break;
					}
				}
			}

		}
	}


	return hasMoved;
}

bool Board::moveUp() {
	CCLOG("moveUp");
	int size = this->size;

	bool hasMoved = false;
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < size; i++) {
			if (this->matrix[i][j] == 0 ) {
				for (int k = i + 1; k < size; k++) {
					if (this->matrix[k][j] != 0) {
						this->matrix[i][j] = this->matrix[k][j];
						this->matrix[k][j] = 0;
						hasMoved = true;
						break;
					}
				}
			}
			if (this->matrix[i][j] != 0) {
				for (int k = i + 1; k < size; k++) {
					if (this->matrix[k][j] != 0) {
						if (this->matrix[k][j] == this->matrix[i][j]){
							int lastMaxNumber = this->getMaxNumber();
							this->matrix[i][j] += this->matrix[k][j];
							this->matrix[k][j] = 0;
							if (this->matrix[i][j] == CONGRAT_NUM && lastMaxNumber < CONGRAT_NUM){
								this->isCongrate = true;
							}
							this->addScore(this->matrix[i][j]);
							this->addToMergePosList(ccp(i, j));
							hasMoved = true;
						}
						break;
					}
				}
			}

		}
	}
	return hasMoved;
}

bool Board::moveDown() {
	CCLOG("moveDown");
	int size = this->size;

	bool hasMoved = false;
	for (int j = 0; j < size; j++) {
		for (int i = size - 1; i >= 0; i--) {
			if (this->matrix[i][j] == 0 ) {
				for (int k = i - 1; k >= 0; k--) {
					if (this->matrix[k][j] != 0) {
						this->matrix[i][j] = this->matrix[k][j];
						this->matrix[k][j] = 0;
						hasMoved = true;
						break;
					}
				}
			}
			if (this->matrix[i][j] != 0) {
				for (int k = i - 1; k >= 0; k--) {
					if (this->matrix[k][j] != 0) {
						if (this->matrix[k][j] == this->matrix[i][j]){
							int lastMaxNumber = this->getMaxNumber();
							this->matrix[i][j] += this->matrix[k][j];
							this->matrix[k][j] = 0;
							if (this->matrix[i][j] == CONGRAT_NUM && lastMaxNumber < CONGRAT_NUM){
								this->isCongrate = true;
							}
							this->addScore(this->matrix[i][j]);
							this->addToMergePosList(ccp(i, j));
							hasMoved = true;
						}
						break;
					}
				}
			}

		}
	}
	return hasMoved;
}

void Board::undo(){
	if (this->isCanUndo){
		CCLOG("can undo");
		this->matrix = this->oldMatrix;
		this->isCanUndo = false;
	}
	else {
		CCLOG("can not undo");
	}
}

string Board::getMatrixString() {
	int size = this->size;

	string result = "";
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			result += StringUtils::toString(this->matrix[i][j]) + ", ";
		}
		result += "\n";
	}
	return result;
}

string Board::getOldMatrixString() {
	int size = this->size;

	string result = "";
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			result += StringUtils::toString(this->oldMatrix[i][j]) + ", ";
		}
		result += "\n";
	}
	return result;
}

int Board::getScore() {
	return this->score;
}

int Board::getMaxNumber(){
	int maxNumber = 0;
	for (int i = 0; i < this->size; i++){
		for (int j = 0; j < this->size; j++){
			if (maxNumber < this->matrix[i][j]) maxNumber = this->matrix[i][j];
		}
	}

	return maxNumber;
}

void Board::addScore(int num) {
	this->score += num;
}

bool Board::canMove() {
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			if (this->matrix[i][j] == 0) {
				CCLOG("can move at[%d, %d]", i, j);
				return true;
			}
		}
	}

	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			if (j + 1 < this->size && this->matrix[i][j] == this->matrix[i][j + 1]) {
				CCLOG("can move right[%d, %d]", i, j);
				return true;
			}
			if (i + 1 < this->size && this->matrix[i][j] == this->matrix[i + 1][j]) {
				CCLOG("can move down [%d, %d]", i, j);
				return true;
			}
		}
	}

	this->isCanUndo = false;

	return false;
}

string Board::convertDataToSaveString(){
	string result = "";
	int size = this->size;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
				result += StringUtils::toString(this->matrix[i][j]) + ",";
		}
		result += ".";
	}
	result += "_";

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
				result += StringUtils::toString(this->oldMatrix[i][j]) + ",";
		}
		result += ".";
	}

	result += "_";
	result += StringUtils::toString(this->score);

	return result;
}

void Board::convertDataFromString(string dataStr){
	CCLOG("convertDataFromString dataStr= %s", dataStr.c_str());
	if (dataStr.compare("") == 0){
		CCLOG("convertDataFromString error");
	}
	else {
		int startIdx = 0; int endIdx = dataStr.find_first_of("_");	
		string dataMatrixStr = dataStr.substr(startIdx, endIdx);
		startIdx = endIdx + 1; endIdx = dataStr.find("_", startIdx);
		string dataOldMatrixStr = dataStr.substr(startIdx, endIdx);
		startIdx = endIdx + 1; endIdx = dataStr.find("_", startIdx);
		int score = atoi(dataStr.substr(startIdx, endIdx).c_str());
		CCLOG("convertDataFromString score= %d", score);

		this->matrix.clear();
		this->matrix = this->convertMatrixFromString(dataMatrixStr);
		this->oldMatrix.clear();
		this->oldMatrix = this->convertMatrixFromString(dataOldMatrixStr);
		this->score = score;
	}

	CCLOG("convertDataFromString matrix = %s",this->getMatrixString().c_str());
}

vector<vector<int>> Board::convertMatrixFromString(string dataMatrixStr)
{
	vector<vector<int>> matrix;
	int startIdx = 0;
	int endIdx = dataMatrixStr.find(".", 0);
	while (endIdx != string::npos){
		
		string dataArray = dataMatrixStr.substr(startIdx, endIdx);
		vector<int> numList = this->convertNumListFromString(dataArray);
		matrix.push_back(numList);
		startIdx = endIdx + 1;
		endIdx = dataMatrixStr.find(".", startIdx);

	}
	if (startIdx > 0){
		string dataArray = dataMatrixStr.substr(startIdx, dataMatrixStr.length() - 1);
		vector<int> numList = this->convertNumListFromString(dataArray);
		matrix.push_back(numList);
	}

	return matrix;
}

vector<int> Board::convertNumListFromString(string dataArray)
{
	vector<int> numList;
	int startIdx2 = 0;
	int endIdx2 = dataArray.find(",", startIdx2);
	while (endIdx2 != string::npos)
	{
		string data = dataArray.substr(startIdx2, endIdx2);
		numList.push_back(atoi(data.c_str()));
		startIdx2 = endIdx2 + 1;
		endIdx2 = dataArray.find(",", startIdx2);
	}
	if (startIdx2 > 0) {
		string data = dataArray.substr(startIdx2, dataArray.length());
		numList.push_back(atoi(data.c_str()));
	}
	return numList;
}


void Board::addToMergePosList(CCPoint pos){
	this->mergePosList.push_back(pos);
}

void Board::removeFromMergePosList(CCPoint pos){
	int n = this->mergePosList.size();
	int isExist = false;
	int i = 0;
	for (i = 0; i < n; i++){
		CCPoint p = this->mergePosList.at(i);
		if (p.x == pos.x && p.y == pos.y){
			isExist = true;
			break;
		}
	}

	if (isExist) this->mergePosList.erase(this->mergePosList.begin() + i);
}
