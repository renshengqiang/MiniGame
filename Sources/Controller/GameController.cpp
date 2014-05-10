#include "GameController.h"
#include "Entity\Friend.h"
#include "Entity\Enermy.h"
#include "Utils.h"

USING_NS_CC;

bool GameController::init()
{

	CCLayer::setTouchEnabled(true);		// 设置允许触摸
	CCLayer::scheduleUpdate();			// 调用update函数

	return true;
}

void GameController::update(float delta)
{

}

void GameController::normalizePos(Entity *pEntity)
{
	CCPoint pos = pEntity->getTagPosition();
	
	if(pos.x < FRIEND_SIZE/2)
	{
		pos.x = FRIEND_SIZE/2;
	}
	else if( pos.x > SCREEN_WIDTH - FRIEND_SIZE/2)
	{
		pos.x = SCREEN_WIDTH - FRIEND_SIZE/2;
	}

	if(pos.y < FRIEND_SIZE/2)
	{
		pos.y = FRIEND_SIZE/2;
	}
	else if(pos.y > SCREEN_HEIGHT - FRIEND_SIZE/2)
	{
		pos.y = SCREEN_HEIGHT - FRIEND_SIZE/2;
	}
	pEntity->setTagPosition(pos.x, pos.y);
}

void GameController::addFriend(Friend *pFriend)
{
	mFriendVec.push_back(pFriend);
}

void GameController::addEnermy(Enermy *pEnermy)
{
	mEnermyVec.push_back(pEnermy);
}

Friend *GameController::conflictWithFriend(Friend *collider)
{
	CCPoint pos = collider->getTagPosition();

	for(int i=0; i<mFriendVec.size(); ++i)
	{
		if(mFriendVec[i] == collider) continue;
		CCPoint pos2 = mFriendVec[i]->getTagPosition();
		CCPoint dist = pos2 - pos;
		if(ccpLength(dist) <= FRIEND_SIZE)
			return mFriendVec[i];
	}
	return NULL;
}

Enermy *GameController::conflictWithEnermy(Friend *collider)
{
	CCPoint pos = collider->getTagPosition();

	for(int i=0; i<mEnermyVec.size(); ++i)
	{
		CCPoint pos2 = mEnermyVec[i]->getTagPosition();
		CCPoint dist = pos2 - pos;
		if(ccpLength(dist) <= FRIEND_SIZE)
			return mEnermyVec[i];
	}
	return NULL;
}

bool GameController::conflictWithWall(Friend *collider, cocos2d::CCPoint &wallNormal)
{
	bool ret = true;
	CCPoint pos = collider->getTagPosition();
	if(pos.x < FRIEND_SIZE/2)
	{
		wallNormal.x = 1;
		wallNormal.y = 0;
	}
	else if(pos.y < FRIEND_SIZE/2)
	{
		wallNormal.x = 0;
		wallNormal.y = 1;
	}
	else if(pos.x > SCREEN_WIDTH - FRIEND_SIZE/2)
	{
		wallNormal.x = -1;
		wallNormal.y = 0;
	}
	else if(pos.y > SCREEN_HEIGHT - FRIEND_SIZE/2)
	{
		wallNormal.x = 0;
		wallNormal.y = -1;
	}
	else
		ret = false;

	return ret;
}

void GameController::setAttackingFriend(Friend *pFriend)
{
	mAttackingFriend = pFriend;
}

void GameController::addAttackingFriend(Friend *pAttackingFriend)
{

}

void GameController::leaveFromAttacking(Friend *pAttackingFriend)
{
}

bool GameController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	// 获取单击的坐标
	CCPoint touchPos = pTouch->getLocationInView();
	touchPos = CCDirector::sharedDirector()->convertToGL(touchPos);

	mTouchBeginPos = touchPos;

	//TODO: 判断当前是哪个选手进行攻击，并且创建箭头
	//mpArrowSprite = CCSprite::create("arrow.jpg");
	//CCLayer::addChild(mpArrowSprite);
	//mpArrowSprite->setPosition(CCPoint(100, 100));

	return true;
}

void GameController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	//TODO:改变箭头方向 
}

void GameController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	// 获取单击的坐标
	CCPoint touchPos = pTouch->getLocationInView();
	touchPos = CCDirector::sharedDirector()->convertToGL(touchPos);

	mTouchEndPos = touchPos;

	CCPoint dir = mTouchEndPos - mTouchBeginPos;
	dir = dir.normalize();
	dir.x *= ATTACK_SPEED;
	dir.y *= ATTACK_SPEED;
	mAttackingFriend->setAttack1Hurt(10);
	mAttackingFriend->setSpeed(dir.x, dir.y);
	mAttackingFriend->attack1();
}

void GameController::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}
