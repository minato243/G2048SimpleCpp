
#ifndef MainScene_h__
#define MainScene_h__

#include "cocos2d.h"
#include "platform\CCPlatformMacros.h"

USING_NS_CC;

class MainScene: public cocos2d::Layer
{
public:
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(MainScene);
	void loadResource();

	void onRate(Ref *obj);
	void onHighScore(Ref *obj);
	void onPlay(Ref *obj);
	void addKeyBoardListener();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void onBackPress();
protected:
private:
};

#endif