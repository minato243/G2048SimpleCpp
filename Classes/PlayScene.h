#ifndef PlayScene_h__
#define PlayScene_h__

#include "cocos2d.h"
#include "2d\CCLabelBMFont.h"
#include "ui\UIButton.h"
#include "GameDataMgr.h"
#include "Board.h"
#include "deprecated\CCDeprecated.h"
#include "2d\CCLabel.h"
#include "ui\UITextBMFont.h"
#include "math\Vec2.h"

USING_NS_CC;
using namespace std;

class PlayScene : public Scene{
public:
	PlayScene();
	~PlayScene();

	ui::Widget *bgImage;
	ui::TextBMFont *scoreLabel, *highScoreLabel;
	ui::Button *homeButton;
	CCSprite *bgMode;
	vector<vector<CCSprite *>> bgNumberList;

	Vec2 touchBeganPos;

	GameDataMgr *gameData;
	Board *board;
	string savedData;

	float scaleRate;
	int maxStepEffect;
	bool isMoving;
	bool isSpawning;
	int curDir;

	static Scene *createScene();
	CREATE_FUNC(PlayScene);
	virtual bool init();
	void initGui();
	void initListNumber();
	void initData();
	void addListener();
	void addKeyBoardListener();
	void createNewGame();
	
	void updateData();
	void loadData();

	string getSpriteFrameNameForNumber(int number);
	bool checkGameOver();
	void gameOver();

	virtual void onEnter();
	void onClickHome(Ref *obj);
	bool onTouchBegan(Touch* touch, cocos2d::Event* event);
	void onTouchMoved(Touch* touch, cocos2d::Event* event);
	void onTouchEnded(Touch* touch, cocos2d::Event* event);

	void showMoveEffect(int dir);
	void moveLeftEffect();
	void moveRightEffect();
	void moveUpEffect();
	void moveDownEffect();
	void moveEffect(Node *icon, int i, int j, int dir, int numStep);
	void moveEffectComplete();
	void spawnEffect(Vec2 pos);
	void spawnEffectComplete();
	void mergeEffect();
	void mergeEffectComplete();
	void onBackPress();
	void saveCurrentData();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
};
#endif