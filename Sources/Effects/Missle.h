#ifndef _MINIGAME_MISSLE_H_
#define _MINIGAME_MISSLE_H_
#include <cocos2d.h>

class Missle :
	public cocos2d::CCNode
{
public:
	CREATE_FUNC(Missle);
	bool init();
	void show(const cocos2d::CCPoint &beginPos, const cocos2d::CCPoint &endPos);

private:
	cocos2d::CCSprite *mSprite;
	void showEnd();
};

#endif