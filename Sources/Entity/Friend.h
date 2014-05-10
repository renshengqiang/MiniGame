#ifndef _MINIGAME_FRIEND_H_
#define _MINIGAME_FRIEND_H_
#include "Entity.h"

class Friend : public Entity
{
public:
	Friend(const char *fileName);

	void bindSprite(cocos2d::CCSprite *sprite);

	void setAttack1Hurt(float hurt) { mAttack1Hurt = hurt;}
	void setAttack2Hurt(float hurt) { mAttack2Hurt = hurt;}
	void setSpeed(float x, float y) { mxSpeed = x; mySpeed = y; }
	virtual void setController(GameController *controller);
	void update(float delta);
	
	void attack1();	//普通技能
	void attack2(); //友情技能

private:
	bool mAttacking;		// 当前自己是否是活跃对象
	float mxSpeed, mySpeed; // 移动过程中x,y两个方向上的速度
	float mAttackTimeLeft;	// 移动过程剩余的时间
	float mAttack1Hurt;		//第一种技能的攻击力
	float mAttack2Hurt;		//友情技能的攻击力
	Entity *mLastConflictedEntity;//上次冲突对象
};

#endif