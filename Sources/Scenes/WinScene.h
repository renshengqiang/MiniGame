#ifndef _MINIGAME_WIN_SCENE_H_
#define _MINIGAME_WIN_SCENE_H_
#include "cocos2d.h"
#include "cocos-ext.h"

class WinScene : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(WinScene);
	virtual bool init();
	static cocos2d::CCScene* scene();

private:
	void onExit(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event);
	void onResume(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event);
};


#endif