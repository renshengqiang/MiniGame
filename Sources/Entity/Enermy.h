#ifndef _MINIGAME_ENERMY_H_
#define _MINIGAME_ENERMY_H_
#include "Entity.h"

class Friend;
class Enermy : public Entity
{
public:
	Enermy(const char *fileName);

	void setAttackHurt(int hp){ mAttackHurt = hp; }
	virtual void bindSprite(cocos2d::CCSprite *sprite);

	virtual void attack();
	virtual void underAttack(int hp);
	void underAttackEnd();
	virtual void setController(GameController *controller);

	void setType(int type){ mType = type; }
	void attackTempEnd(float);
	void attackEnd(float delta);
	void attackEndEnd(float delta);
	void die(float);
	void dieEnd(float);
	void propsMoveEnd(cocos2d::CCNode *pSender, void *data);
	int getAttackHurt() { return mAttackHurt; }

	float getRadius() { return mRadius; }
	void setRadius(float radius) { mRadius = radius; }

	int getBuff1() { return m_fullHp; }
	int getBuff2() { if(mType>2) return 1; else return 0;}

private:
	int mAttackHurt;	// 技能伤害值
	int mType;			// Entity类型
	float mRadius;		// 角色的半径大小
	cocos2d::CCNode *mFXSprite;	//特效图片
	Friend *mAttackedFriend;	//被攻击的敌人
	cocos2d::CCSprite *mpJinbiSprite;
};

#endif