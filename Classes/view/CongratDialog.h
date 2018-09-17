#ifndef CongratDialog_h__
#define CongratDialog_h__

#include "cocos2d.h"
#include "base\BasePopupDialog.h"
#include "ui\UIButton.h"
#include "PlayScene.h"

USING_NS_CC;

class CongratDialog : public BasePopupDialog{
public:
	CongratDialog();
	~CongratDialog();

	ui::Button* continueButton;
	ui::Button*	homeButton;
	ui::Button*	shareButton;

	Node *bgImage;
	PlayScene *playLayer;

	CREATE_FUNC(CongratDialog);
	virtual bool init();
	void startDialog(PlayScene *parent);
	virtual void _removeFromParent();
	void setCallBackFunc(CCCallFunc *callBackFunc);
	void onContinue(Ref *obj);
	void onShare(Ref *obj);

	static CongratDialog *getInstance();
	static void destroyInstance();

};
#endif