#include "Toolbar.h"
#include "Entity\Friend.h"
#include "Entity\Enermy.h"

USING_NS_CC;

Toolbar::Toolbar():
	mBGSprite(NULL),
	mHp(NULL),
	mAttackHurt(NULL)
{
}

bool Toolbar::init()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	mBGSprite = CCSprite::create("toolbar.png");
	mBGSprite->setPosition(ccp(360, visibleSize.height-48));
	CCNode::addChild(mBGSprite);

	mHp = CCLabelTTF::create("100/100", "Arial", 40);
	mBGSprite->addChild(mHp);
	mHp->setPosition(ccp(170, 48));

	mAttackHurt = CCLabelTTF::create("30", "Arial", 40);
	mBGSprite->addChild(mAttackHurt);
	mAttackHurt->setPosition(ccp(370, 48));

	mFriendAttackHurt = CCLabelTTF::create("30", "Arial", 40);
	mBGSprite->addChild(mFriendAttackHurt);
	mFriendAttackHurt->setPosition(ccp(620, 48));
	return true;
}

void Toolbar::setEntity(Entity *pEntity)
{
	int hp = pEntity->getHp();
	int fullHp = pEntity->getFullHp();
	int attackHurt1 = 0;
	int attackHurt2 = 0;

	Friend *pFriend = dynamic_cast<Friend*>(pEntity);
	if(pFriend != NULL)
	{
		attackHurt1 = pFriend->getAttack1Hurt();
		attackHurt2 = pFriend->getAttack2Hurt();
	}
	else
	{
		Enermy *pEnermy = dynamic_cast<Enermy*>(pEntity);

		if(pEnermy != NULL)
		{
			attackHurt1 = pEnermy->getAttackHurt();
		}
	}
	mHp->setString(CCString::createWithFormat("%d/%d", hp, fullHp)->getCString());
	mAttackHurt->setString(CCString::createWithFormat("%d",attackHurt1)->getCString());
	mFriendAttackHurt->setString(CCString::createWithFormat("%d",attackHurt2)->getCString());
}
