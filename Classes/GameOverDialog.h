#ifndef GameOverDialog_h__
#define GameOverDialog_h__

#include "cocos2d.h"
#include "BasePopupDialog.h"
#include "ui\UIButton.h"
#include "PlayScene.h"

USING_NS_CC;

class GameOverDialog : public BasePopupDialog{
public:
	GameOverDialog();
	~GameOverDialog();

	CCCallFunc *callBackFunc;
	CCCallFunc *acceptCallBack;

	ui::Button* restartButton;
	ui::Button*	homeButton;
	ui::Button*	shareButton;
	ui::TextBMFont *numberLabel;
	ui::TextBMFont *scoreLabel;
	ui::TextBMFont *bestScoreLabel;
	ui::TextBMFont *bestTitleLabel;

	Node *bgImage;
	PlayScene *playLayer;

	CREATE_FUNC(GameOverDialog);
	virtual bool init();
	void startDialog(int score, int maxNumber, PlayScene *parent);
	virtual void _removeFromParent();
	void setCallBackFunc(CCCallFunc *callBackFunc);
	void onRestart(Ref *obj);
	void onHome(Ref *obj);
	void onShare(Ref *obj);

	static GameOverDialog *getInstance();
	static void destroyInstance();

};
#endif