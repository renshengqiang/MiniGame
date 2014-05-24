#include "Arrow.h"
USING_NS_CC;

bool Arrow::init()
{
	for(int i=0; i<3; ++i)
	{
		mSprite[i] = CCSprite::create("EnermyAttack1.png"); //10ÏñËØ³¤£¬20ÏñËØ¿í
		mSprite[i]->setVisible(false);
		this->addChild(mSprite[i]);
	}
	index = 0;
	return true;
}

void Arrow::show(const cocos2d::CCPoint &beginPos, const cocos2d::CCPoint &endPos)
{
	delta = endPos - beginPos;
	float angle = delta.getAngle(CCPoint(1, 0));
	for(int i=0; i<3; ++i)
		mSprite[i]->setRotation(angle*180/M_PI);
	mSprite[0]->setVisible(true);

	CCActionInterval *move = CCMoveBy::create(0.3f, delta);
	CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(Arrow::showEnd));
	CCActionInterval *actions = CCSequence::create(move, callFunc, NULL);
	mSprite[0]->runAction(actions);
}

void Arrow::showEnd()
{
	if(index < 2)
	{
		mSprite[index]->setVisible(false);
		mSprite[index]->removeFromParentAndCleanup(true);

		index++;
		CCActionInterval *move = CCMoveBy::create(0.3f, delta);
		CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(Arrow::showEnd));
		CCActionInterval *actions = CCSequence::create(move, callFunc, NULL);
		mSprite[index]->setVisible(true);
		mSprite[index]->runAction(actions);
	}
}