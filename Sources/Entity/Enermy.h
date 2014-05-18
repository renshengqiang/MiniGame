#ifndef _MINIGAME_ENERMY_H_
#define _MINIGAME_ENERMY_H_
#include "Entity.h"

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
	void attackEnd(float delta);
	void die();
	void propsMoveEnd(cocos2d::CCNode *pSender, void *data);

private:
	int mAttackHurt;	// ººƒ‹…À∫¶÷µ
	int mType;
};

#endif