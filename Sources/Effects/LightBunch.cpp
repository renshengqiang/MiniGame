#include "LightBunch.h"
USING_NS_CC;

bool LightBunch::init() 
{
	mSprite1 = CCSprite::create("laser.png");
	mSprite2 = CCSprite::create("laser.png");
	mSprite1->setVisible(false);
	mSprite2->setVisible(false);
	mSprite1->setRotation(90);
	this->addChild(mSprite1);
	this->addChild(mSprite2);
	return true;
}

void LightBunch::show() 
{
	mSprite1->setVisible(true);
	mSprite2->setVisible(true);

	CCActionInterval* scale1 = CCScaleTo::create(1.0f, 7.0f, 4.0f);
	CCActionInterval* scale2 = CCScaleTo::create(1.0f, 7.0f, 4.0f);

	CCCallFunc* callFunc1 = CCCallFunc::create(this, callfunc_selector(LightBunch::sprite1End));
	CCCallFunc* callFunc2 = CCCallFunc::create(this, callfunc_selector(LightBunch::sprite2End));

	CCActionInterval *actions1 = CCSequence::create(scale1, callFunc1, NULL);
	CCActionInterval *actions2 = CCSequence::create(scale2, callFunc2, NULL);

	mSprite1->runAction(actions1);
	mSprite2->runAction(actions2);
}

void LightBunch::sprite1End() 
{
	/* 动作结束，从父节点中删除自身 */
	mSprite1->setVisible(false);
	mSprite1->removeFromParentAndCleanup(true);
}

void LightBunch::sprite2End() 
{
	/* 动作结束，从父节点中删除自身 */
	mSprite2->setVisible(false);
	mSprite2->removeFromParentAndCleanup(true);
}