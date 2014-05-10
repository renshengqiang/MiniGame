#include "Friend.h"
#include "Enermy.h"
#include "Controller\GameController.h"
#include "Utils.h"

USING_NS_CC;
using namespace cocos2d::extension;

Friend::Friend(const char *fileName)
{
	mAttackTimeLeft = 0;
	mAttacking = false;
	mxSpeed = 0;
	mySpeed = 0;
	mLastConflictedEntity = NULL;

	CCSprite *sprite = CCSprite::create(fileName);
	bindSprite(sprite);
}

void Friend::bindSprite(cocos2d::CCSprite *sprite)
{
	Entity::bindSprite(sprite);
	/*初始化血量条*/
	m_hpSlider = CCControlSlider::create(
							CCSprite::create("background.png"),
							CCSprite::create("progress_friend.png"),
							CCSprite::create("sliderThumb.png"));
	
	m_hpSlider->setPosition(ccp(0,FRIEND_SIZE));
	m_hpSlider->setTouchEnabled(false);
	m_hpSlider->setMaximumValue(m_fullHp);
	m_hpSlider->setMinimumValue(0);
	m_hpSlider->setValue(m_fullHp);
	Entity::addChild(m_hpSlider, 0);
}

void Friend::setController(GameController *controller)
{
	Entity::setController(controller);

	// 具体的通知controller的函数不一样
	controller->addFriend(this);
}

void Friend::update(float delta)
{
	Entity::update(delta);

	if(mAttacking)
	{
		CCPoint dest = Entity::getTagPosition();
		dest.x += mxSpeed * delta;
		dest.y += mySpeed * delta;
		Entity::setTagPosition(dest.x, dest.y);

		mAttackTimeLeft -= delta;

		if(NULL == m_controller) 
		{
			mAttacking = false;
			return;
		}

		if(mAttackTimeLeft <= 0)
		{
			mAttacking = false;
			m_controller->leaveFromAttacking(this);
		}

		Friend *pConflictedFriend = m_controller->conflictWithFriend(this);
		if(pConflictedFriend != NULL)
		{
			//简单改变原来运行的方向导致的问题是，如果已经发生重合则导致一直在周围进行旋转的情况发生
			//解决方法之一是记录上一次冲突的对象，若这次冲突的对象相同则不进行方向改变
			if(mLastConflictedEntity == pConflictedFriend) return;
			mLastConflictedEntity = pConflictedFriend;

			//改变原来的运动方向
			CCPoint P1 = Entity::getTagPosition();
			CCPoint P2 = pConflictedFriend->getTagPosition();
			CCPoint normalVec = P1 - P2;
			CCPoint originalVelocity = CCPoint(mxSpeed, mySpeed);
			CCPoint reflectedVelocity;
			reflectedVelocity.x = -2*(mxSpeed*normalVec.x + mySpeed*normalVec.y)*normalVec.x/(normalVec.getLength()*normalVec.getLength()) + originalVelocity.x;
			reflectedVelocity.y = -2*(mxSpeed*normalVec.x + mySpeed*normalVec.y)*normalVec.y/(normalVec.getLength()*normalVec.getLength()) + originalVelocity.y;
			setSpeed(reflectedVelocity.x, reflectedVelocity.y);

			//触发队友的友情技能
			pConflictedFriend->attack2();
			m_controller->addAttackingFriend(pConflictedFriend);

			return;
		}
		
		Enermy *pConflictedEnermy = m_controller->conflictWithEnermy(this);
		if(pConflictedEnermy != NULL)
		{
			if(mLastConflictedEntity == pConflictedEnermy) return;
			mLastConflictedEntity = pConflictedEnermy;

			//改变原来的运行方向
			CCPoint P1 = Entity::getTagPosition();
			CCPoint P2 = pConflictedEnermy->getTagPosition();
			CCPoint normalVec = P1 - P2;
			CCPoint originalVelocity = CCPoint(mxSpeed, mySpeed);
			CCPoint reflectedVelocity;
			reflectedVelocity.x = -2*(mxSpeed*normalVec.x + mySpeed*normalVec.y)*normalVec.x/(normalVec.getLength()*normalVec.getLength()) + originalVelocity.x;
			reflectedVelocity.y = -2*(mxSpeed*normalVec.x + mySpeed*normalVec.y)*normalVec.y/(normalVec.getLength()*normalVec.getLength()) + originalVelocity.y;
			setSpeed(reflectedVelocity.x, reflectedVelocity.y);
			
			// TODO:这里需要判断当前在用哪种技能
			pConflictedEnermy->underAttack(mAttack1Hurt);

			return;
		}

		CCPoint normalVec;
		bool conflictWithWall = m_controller->conflictWithWall(this, normalVec);
		if(conflictWithWall)
		{
			mLastConflictedEntity = NULL;

			// 先进行位置校正，保证不会出边界
			m_controller->normalizePos(this);

			// 与墙壁相撞后直接返回
			CCPoint originalVelocity(mxSpeed, mySpeed);
			CCPoint reflectedVelocity;
			reflectedVelocity.x = -2*(mxSpeed*normalVec.x+mySpeed*normalVec.y)*normalVec.x/normalVec.getLength() + mxSpeed;
			reflectedVelocity.y = -2*(mxSpeed*normalVec.x+mySpeed*normalVec.y)*normalVec.y/normalVec.getLength() + mySpeed;
			mxSpeed = reflectedVelocity.x;
			mySpeed = reflectedVelocity.y;
		}
	}
	m_controller->normalizePos(this);
}

void Friend::attack1()
{
	mAttacking = true;
	m_activated = false;
	mAttackTimeLeft = 2;
}

void Friend::attack2()
{
	//TODO:第二种技能
}