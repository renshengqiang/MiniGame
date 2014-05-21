#ifndef _MINIGAME_Arrow_H_
#define _MINIGAME_Arrow_H_
#include <cocos2d.h>

class Arrow :
	public cocos2d::CCNode
{
public:
	CREATE_FUNC(Arrow);
	bool init();
	void show(const cocos2d::CCPoint &beginPos, const cocos2d::CCPoint &endPos);

private:
	cocos2d::CCPoint delta;
	cocos2d::CCSprite *mSprite[3];
	void showEnd();
	int index;
};

#endif