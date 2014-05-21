#ifndef _MINIGAME_LASER_H_
#define _MINIGAME_LASER_H_
#include <cocos2d.h>

class LightBunch :
	public cocos2d::CCNode
{
public:
	CREATE_FUNC(LightBunch);
	bool init();

	void show();
private:
	cocos2d::CCSprite *mSprite1;
	cocos2d::CCSprite *mSprite2;

	void sprite1End();
	void sprite2End();
};

#endif