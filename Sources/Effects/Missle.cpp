#include "Missle.h"
USING_NS_CC;

bool Missle::init()
{

	mSprite = CCSprite::create("missle.png");
	mSprite->setVisible(false);
	this->addChild(mSprite);

	return true;
}

void Missle::show(const cocos2d::CCPoint &beginPos, const cocos2d::CCPoint &endPos)
{
	CCPoint delta = endPos - beginPos;
	float angle = delta.getAngle(CCPoint(1, 0));
	mSprite->setRotation(angle*180/M_PI);
	mSprite->setVisible(true);

	CCActionInterval *move = CCMoveBy::create(1.3f, delta);
	CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(Missle::showEnd));
	CCActionInterval *actions = CCSequence::create(move, callFunc, NULL);
	mSprite->runAction(actions);
}

void Missle::showEnd()
{
	mSprite->setVisible(false);
	mSprite->removeFromParentAndCleanup(true);
}