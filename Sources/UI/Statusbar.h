#ifndef _MINIGAME_STATUSBAR_H_
#define _MINIGAME_STATUSBAR_H_
#include <cocos2d.h>

class Entity;
class Statusbar :
	public cocos2d::CCNode
{
public:
	Statusbar();
	CREATE_FUNC(Statusbar);
	bool init();
	void addBuff1(int num);
	void addBuff2(int num);

private:
	cocos2d::CCSprite *mBGSprite;
	cocos2d::CCLabelTTF *mBuff1;
	cocos2d::CCLabelTTF *mBuff2;
	int mBuff1Count, mBuff2Count;
};

#endif