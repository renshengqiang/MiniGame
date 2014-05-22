#include "Statusbar.h"
#include "Entity\Friend.h"
#include "Entity\Enermy.h"

USING_NS_CC;

Statusbar::Statusbar():
	mBGSprite(NULL),
	mBuff1(NULL),
	mBuff2(NULL),
	mBuff1Count(0),
	mBuff2Count(0)
{
}

bool Statusbar::init()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	mBGSprite = CCSprite::create("statusbar.png");
	mBGSprite->setPosition(ccp(360, 48));
	CCNode::addChild(mBGSprite);

	mBuff1 = CCLabelTTF::create("0", "Arial", 40);
	mBGSprite->addChild(mBuff1);
	mBuff1->setPosition(ccp(270, 48));

	mBuff2 = CCLabelTTF::create("0", "Arial", 40);
	mBGSprite->addChild(mBuff2);
	mBuff2->setPosition(ccp(530, 48));

	return true;
}

void Statusbar::addBuff1(int num)
{
	// TODO: 加入一个特效
	mBuff1Count += num;
	mBuff1->setString(CCString::createWithFormat("%d",mBuff1Count)->getCString());
}

void Statusbar::addBuff2(int num)
{
	// TODO: 加入一个特效
	mBuff2Count += num;
	mBuff2->setString(CCString::createWithFormat("%d",mBuff2Count)->getCString());
}