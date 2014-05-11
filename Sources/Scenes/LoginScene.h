#ifndef _MINIGAME_LOGIN_SCENE_H_
#define _MINIGAME_LOGIN_SCENE_H_
#include "cocos2d.h"
#include "cocos-ext.h"

class LoginScene : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(LoginScene);
	virtual bool init();
	static cocos2d::CCScene* scene();

private:
	void login(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event);
};


#endif