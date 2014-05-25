#ifndef _MINIGAME_PAUSE_SCENE_H_
#define _MINIGAME_PAUSE_SCENE_H_
#include "cocos2d.h"
#include "cocos-ext.h"

class PauseScene : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(PauseScene);
	virtual bool init();
	static cocos2d::CCScene* scene(cocos2d::CCRenderTexture *renderTexture, bool isFlip);

private:
	void onResume(cocos2d::CCObject *pSender);
};


#endif