#ifndef _MINIGAME_LASER_H_
#define _MINIGAME_LASER_H_
#include <cocos2d.h>

class Laser :
	public cocos2d::CCNode
{
public:
	CREATE_FUNC(Laser);
	bool init();

	void show(const cocos2d::CCPoint &beginPos, const cocos2d::CCPoint &endPos);
	void update(float delta);
private:
	cocos2d::CCSprite *mSprite;
	cocos2d::CCPoint mDelta;
	float mSpeed;
	float mRatio;

	void flowEnd();
};

#endif