#ifndef _MINIGAME_FRIEND_H_
#define _MINIGAME_FRIEND_H_
#include "Entity.h"

class CCParticleSystem;
class Friend : public Entity
{
public:
	Friend(const char *fileName);

	void bindSprite(cocos2d::CCSprite *sprite);

	void setAttack1Hurt(float hurt) { mAttack1Hurt = hurt;}
	void setAttack2Hurt(float hurt) { mAttack2Hurt = hurt;}
	void setAttackSpeed(float x, float y);
	void setTiggleFlag(bool flag) { mTriggleFlag = flag; }
	void setAttackTime(float time) { mAttackTimeLeft = time; }
	virtual void setController(GameController *controller);

	void update(float delta);
	
	virtual void attack();	//普通技能
	void attackEnd();		// 技能释放结束
	void attack2();			//友情技能
	void attack2End(float); //友情技能释放结束
	virtual void underAttack(int hp);

	void die(float delta);

	void increaseLevel();
	
private:
	float mxSpeed, mySpeed; // 移动过程中x,y两个方向上的速度
	float mAcceleration;	//加速度
	float mAttackTimeLeft;	// 移动过程剩余的时间
	float mAttack1Hurt;		//第一种技能的攻击力
	float mAttack2Hurt;		//友情技能的攻击力
	Entity *mLastConflictedEntity;//上次冲突对象
	bool mTriggleFlag;		// 是否已经被触发过
	cocos2d::CCParticleSystem *mParticleSystem; // 友情技能粒子系统
	int	mLevel;				// 英雄等级
	cocos2d::CCSprite*	mWeapon[3];		// 三种武器攻击效果
};

#endif