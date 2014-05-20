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
	virtual void setController(GameController *controller);

	void setType(int type){ mType = type; }
	void Enermy::attackTempEnd(float);
	void attackEnd(float delta);
	void die();
	void propsMoveEnd(cocos2d::CCNode *pSender, void *data);

private:
	int mAttackHurt;	// 技能伤害值
	int mType;
	cocos2d::CCSprite *mFXSprite;		//特效图片
	Friend *mAttackedFriend;	//被攻击的敌人
};

#endif