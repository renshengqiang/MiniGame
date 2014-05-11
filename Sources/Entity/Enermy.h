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

	void attackEnd(float delta);
	void die(float delta);

private:
	int mAttackHurt;	// ººƒ‹…À∫¶÷µ

};

#endif