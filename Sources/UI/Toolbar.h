#ifndef _MINIGAME_TOOLBAR_H_
#define _MINIGAME_TOOLBAR_H_
#include <cocos2d.h>

class Entity;
class Toolbar :
	public cocos2d::CCNode
{
public:
	Toolbar();
	CREATE_FUNC(Toolbar);
	bool init();
	void setEntity(Entity *pEntity);

private:
	cocos2d::CCSprite *mBGSprite;
	cocos2d::CCLabelTTF *mHp;
	cocos2d::CCLabelTTF *mAttackHurt;
	cocos2d::CCLabelTTF *mFriendAttackHurt;
};

#endif