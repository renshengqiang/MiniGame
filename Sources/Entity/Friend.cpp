#include "Friend.h"
#include "Enermy.h"
#include "Controller\GameController.h"
#include "Utils.h"
#include "SimpleAudioEngine.h"
#include "Effects\LightBunch.h"

USING_NS_CC;
using namespace cocos2d::extension;

Friend::Friend(const char *fileName)
{
	mAttackTimeLeft = 0;
	mxSpeed = 0;
	mySpeed = 0;
	mLastConflictedEntity = NULL;
	mTriggleFlag = false;
	mParticleSystem = NULL;
	mLevel = 0;

	CCSprite *sprite = CCSprite::create(fileName);
	bindSprite(sprite);

	mWeapon[0] = CCSprite::create("weapon1.png");
	mWeapon[1] = CCSprite::create("weapon2.png");
	mWeapon[2] = CCSprite::create("weapon3.png");
}

void Friend::bindSprite(cocos2d::CCSprite *sprite)
{
	Entity::bindSprite(sprite);
	/*初始化血量条*/
	m_hpSlider = CCControlSlider::create(
							CCSprite::create("background.png"),
							CCSprite::create("progress_friend.png"),
							CCSprite::create("sliderThumb.png"));
	
	m_hpSlider->setPosition(ccp(0,FRIEND_SIZE*0.75));
	m_hpSlider->setTouchEnabled(false);
	m_hpSlider->setMaximumValue(m_fullHp);
	m_hpSlider->setMinimumValue(0);
	m_hpSlider->setValue(m_fullHp);
	Entity::addChild(m_hpSlider, 0);
}

void Friend::setAttackSpeed(float x, float y) 
{
	mxSpeed = x;
	mySpeed = y;
	mAcceleration = CCPoint(x,y).getLength()/FRIEND_ATTACK_TIME;	//保证最后的速度是原来的一半
}
void Friend::setController(GameController *controller)
{
	Entity::setController(controller);

	// 具体的通知controller的函数不一样
	controller->addFriend(this);

	// 创建三种武器，需要setController在addChild后执行
	for(int i=0; i<3; ++i)
	{
		getParent()->addChild(mWeapon[i], 0);
		mWeapon[i]->setVisible(false);
	}
}

void Friend::update(float delta)
{
	// 展示光环效果
	if(m_activated)
	{
		m_magicTime += delta;
		if(NULL == m_magicSprite)
		{
			m_magicSprite = CCSprite::create("magic.png");
			m_magicSprite->setScale(0.3);
			m_magicSprite->setPosition(CCNode::getPosition());
			CCNode::getParent()->addChild(m_magicSprite, 1);		//放在英雄下面
		}
		else
		{
			m_magicSprite->setRotation(m_magicTime*180);
		}
	}
	else
	{
		if(m_magicSprite != NULL)
		{
			m_magicSprite->getParent()->removeChild(m_magicSprite, true);
			m_magicSprite = NULL;
			m_magicTime = 0;
		}
	}

	// 普通攻击效果
	if(m_attacking)
	{
		CCPoint dest = Entity::getTagPosition();
		float ratio = (CCPoint(mxSpeed, mySpeed).getLength() -delta* mAcceleration)/CCPoint(mxSpeed, mySpeed).getLength();
		dest.x += mxSpeed * delta;
		dest.y += mySpeed * delta;
		mxSpeed *= ratio;
		mySpeed *= ratio;

		//CCLOG("speed %f %f %f\n", CCPoint(mxSpeed, mySpeed).getLength(), mxSpeed, mySpeed);
		// 设置友军的新位置
		Entity::setTagPosition(dest.x, dest.y);
		mWeapon[mLevel-1]->setPosition(ccp(dest.x, dest.y));

		// 设置友军攻击武器的旋转
		float angle = CCPoint(mxSpeed, mySpeed).getAngle(CCPoint(1,0));
		mWeapon[mLevel-1]->setRotation(angle*180/M_PI);
		CCLOG("-----------angle: %f\n", angle);

		mAttackTimeLeft -= delta;
		if(NULL == m_controller) 
		{
			m_attacking = false;
			return;
		}

		if(mAttackTimeLeft <= 0)
		{
			attackEnd();
			return;
		}

		// 和友军的碰撞只考虑友情技能，不考虑弹射
		Friend *pConflictedFriend = m_controller->conflictWithFriend(this);
		if(pConflictedFriend != NULL)
		{
			pConflictedFriend->attack2();
		}
/*
		if(mLevel <= 2 && pConflictedFriend != NULL)
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
			setAttackSpeed(reflectedVelocity.x, reflectedVelocity.y);

			//TODO: 触发队友的友情技能
			pConflictedFriend->attack2();
		
			return;
		}
*/
		// 等级大于等于三级的时候会进行穿透
		Enermy *pConflictedEnermy = m_controller->conflictWithEnermy(this);
		if(pConflictedEnermy != NULL)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Collide.mp3");
		}
		if(mLevel <= 2 && pConflictedEnermy != NULL)
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
			setAttackSpeed(reflectedVelocity.x, reflectedVelocity.y);
			
			m_controller->enermyAttacked(pConflictedEnermy, mAttack1Hurt);

			return;
		}
		else if(pConflictedEnermy != NULL)
		{
			m_controller->enermyAttacked(pConflictedEnermy, mAttack1Hurt);
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
			setAttackSpeed(reflectedVelocity.x, reflectedVelocity.y);
		}
	}
	m_controller->normalizePos(this);
}

void Friend::attack()
{
	m_attacking = true;
	m_activated = false;
	mLastConflictedEntity = NULL;

	this->setVisible(false);
	mWeapon[mLevel-1]->setPosition(getPosition());
	mWeapon[mLevel-1]->setVisible(true);

	switch(mLevel)
	{
	case 1:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("FriendArrow.wav");
		break;
	case 2:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("FriendMissle.wav");
		break;
	case 3:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("FriendFireball.wav");
		break;
	}
}

void Friend::attackEnd()
{
	m_attacking = false;
	m_activated = false;
	m_controller->leaveFromAttacking(this);

	for(int i=0; i<3; ++i)
	{
		mWeapon[i]->setVisible(false);
	}
	this->setVisible(true);
}

void Friend::attack2()
{
	if(mTriggleFlag == false)
	{	
	// 通知controller多了一个攻击者
	m_controller->addAttackingFriend();
	switch(mLevel)
	{
	case 1:
		//爆炸特效
		mParticleSystem = CCParticleExplosion::create();
		mParticleSystem->setDuration(FRIEND_ATTACK_TIME);
		mParticleSystem->setLife(FRIEND_ATTACK_TIME);
		mParticleSystem->setSpeed(100);		// 200范围内全部受伤
		mParticleSystem->setSpeedVar(0);
		mParticleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
		mParticleSystem->setAutoRemoveOnFinish(true);
		mParticleSystem->setPositionType(kCCPositionTypeGrouped);
		mParticleSystem->setPosition(ccp(0, 0));
		this->addChild(mParticleSystem);
		scheduleOnce(schedule_selector(Friend::attack2End), FRIEND_ATTACK_TIME);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("FriendExplode.wav");
		break;
	case 2:
		//扩散特效
		mParticleSystem = CCParticleFlower::create();
		mParticleSystem->setTexture( CCTextureCache::sharedTextureCache()->addImage("stars.png"));
		mParticleSystem->setLifeVar(0);
		mParticleSystem->setLife(FRIEND_ATTACK_TIME);
		mParticleSystem->setSpeed(400);
		mParticleSystem->setSpeedVar(0);
		mParticleSystem->setEmissionRate(10000);
		mParticleSystem->setPosition(ccp(0, 0));
		this->addChild(mParticleSystem);
		scheduleOnce(schedule_selector(Friend::attack2End), FRIEND_ATTACK_TIME);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("FriendExpand.mp3");
		break;
	case 3:
		//激光束特效
		LightBunch *pLightBunch = LightBunch::create();
		CCNode::addChild(pLightBunch);
		pLightBunch->show();

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("FriendLightBunch.mp3");
		scheduleOnce(schedule_selector(Friend::attack2End), FRIEND_ATTACK_TIME);
		break;
	}
	mTriggleFlag = true;
	}
	/*
		// TODO:释放友情技能
		mParticleSystem = CCParticleFireworks::create();
		mParticleSystem->setDuration(ENERMY_ATTACK_TIME);
		mParticleSystem->setLife(ENERMY_ATTACK_TIME);
		mParticleSystem->setSpeed(mParticleSystem->getSpeed() * 4);
		mParticleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("friend_particle.png"));
		//设置特效贴图
		mParticleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("stars.png"));
		//设置位置
		mParticleSystem->setPosition(ccp(0, 0));
		//添加特效
		this->addChild(mParticleSystem);
		// 通知controller多了一个攻击者
		m_controller->addAttackingFriend();
		// 然后创建一个定时任务，爆炸结束后通知controller对友军进行伤害，然后到下一个继续执行
		scheduleOnce(schedule_selector(Friend::attack2End), FRIEND_ATTACK_TIME);
		mTriggleFlag = true;
		*/
}

void Friend::attack2End(float)
{
	// 需要通知controller自己的攻击已经结束了，并对友军进行一定的伤害
	// controller在收到该通知后才能继续选择下一个攻击的选手
	switch(mLevel)
	{
	case 1:
		m_controller->enermyAttacked(this, 300, mAttack2Hurt);
		mParticleSystem->getParent()->removeChild(mParticleSystem);
		break;
	case 2:
		m_controller->enermyAttacked(NULL, mAttack2Hurt);
		mParticleSystem->getParent()->removeChild(mParticleSystem);
		break;
	case 3:
		m_controller->enermyAttackedByLaser(this, mAttack2Hurt);
		break;
	}
	m_controller->removeAttackingFriend();
	mParticleSystem = NULL;
}

/*
** 受到攻击，先执行Entity的扣血
** 然后判断当前状态是否是死亡状态，若是则设置自己为不可见，同时播放死亡特效
** 播放死亡特效的过程是先创建一个特效，然后创建一个定时任务，在定时任务的处理函数中设置当前对象不可见
*/
void Friend::underAttack(int hp)
{
	if(m_hp < hp) hp = m_hp;
	Entity::underAttack(hp);

	CCActionInterval *shaky3DFX = CCShaky3D::create(0.5, CCSizeMake(15, 10), 5, false);
	CCStopGrid *stopGrid = CCStopGrid::create();
	CCSequence *action = CCSequence::create(shaky3DFX, stopGrid, NULL);
	this->runAction(action);

	if(dead())
	{
		scheduleOnce(schedule_selector(Friend::die), DIE_TIME);
		// TODO: 播放死亡特效
	}
}

void Friend::die(float)
{
	setVisible(false);
}

void Friend::increaseLevel()
{
	switch(mLevel)
	{
	case 0:
		mAttack1Hurt = 15;
		mAttack2Hurt = 10;
		setHp(150);
		break;
	case 1:
		mAttack1Hurt = 45;
		mAttack2Hurt = 100;
		setHp(400);
		break;
	case 2:
		mAttack1Hurt = 200;
		mAttack2Hurt = 200;
		setHp(700);
		break;
	}
	mLevel++;
}