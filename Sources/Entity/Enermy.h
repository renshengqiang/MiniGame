#ifndef _MINIGAME_ENERMY_H_
#define _MINIGAME_ENERMY_H_
#include "Entity.h"

class Enermy : public Entity
{
public:
	Enermy(const char *fileName);

	void bindSprite(cocos2d::CCSprite *sprite);

	virtual void setController(GameController *controller);

private:
	bool mActive;	// ��ǰ�Լ��Ƿ��ǻ�Ծ����
};

#endif