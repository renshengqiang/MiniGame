#include "Friend.h"
#include "Enermy.h"
#include "Controller\GameController.h"
#include "Utils.h"
#include "SimpleAudioEngine.h"
#include "Effects\LightBunch.h"
#include "Effects\FlowWord.h"

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
}

void Friend::bindSprite(cocos2d::CCSprite *sprite)
{
	Entity::bindSprite(sprite);
	/*��ʼ��Ѫ����*/
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
	mAcceleration = CCPoint(x,y).getLength()/FRIEND_ATTACK_TIME;//��֤�����ٶ���ԭ����һ��
}
void Friend::setController(GameController *controller)
{
	Entity::setController(controller);

	// �����֪ͨcontroller�ĺ�����һ��
	controller->addFriend(this);
}

void Friend::update(float delta)
{
	// չʾ�⻷Ч��
	if(m_activated)
	{
		m_magicTime += delta;
		if(NULL == m_magicSprite)
		{
			m_magicSprite = CCSprite::create("magic.png");
			m_magicSprite->setScale(0.3);
			m_magicSprite->setPosition(CCNode::getPosition());
			CCNode::getParent()->addChild(m_magicSprite, 1);		//����Ӣ������
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

	// ��ͨ����Ч��
	if(m_attacking)
	{
		m_activated = false;
		CCPoint dest = Entity::getTagPosition();
		float ratio = (CCPoint(mxSpeed, mySpeed).getLength() -1.5*delta* mAcceleration)/CCPoint(mxSpeed, mySpeed).getLength();
		//mAcceleration *= (1-10*delta);//���ٶ��𽥱�С
		dest.x += mxSpeed * delta;
		dest.y += mySpeed * delta;
		mxSpeed *= ratio;
		mySpeed *= ratio;

		// �����Ѿ�����λ��
		Entity::setTagPosition(dest.x, dest.y);

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

		// ���Ѿ�����ײֻ�������鼼�ܣ������ǵ���
		Friend *pConflictedFriend = m_controller->conflictWithFriend(this);
		if(pConflictedFriend != NULL)
		{
			pConflictedFriend->attack2();
		}

		// �ȼ����ڵ���������ʱ�����д�͸
		Enermy *pConflictedEnermy = m_controller->conflictWithEnermy(this);
		if(pConflictedEnermy != NULL)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Collide.mp3");
		}
		if(mLevel <= 2 && pConflictedEnermy != NULL)
		{
			if(mLastConflictedEntity == pConflictedEnermy) return;
			mLastConflictedEntity = pConflictedEnermy;

			//�ı�ԭ�������з���
			CCPoint P1 = Entity::getTagPosition();
			CCPoint P2 = pConflictedEnermy->getTagPosition();
			CCPoint normalVec = P1 - P2;
			CCPoint originalVelocity = CCPoint(mxSpeed, mySpeed);
			CCPoint reflectedVelocity;
			reflectedVelocity.x = -2*(mxSpeed*normalVec.x + mySpeed*normalVec.y)*normalVec.x/(normalVec.getLength()*normalVec.getLength()) + originalVelocity.x;
			reflectedVelocity.y = -2*(mxSpeed*normalVec.x + mySpeed*normalVec.y)*normalVec.y/(normalVec.getLength()*normalVec.getLength()) + originalVelocity.y;
			setAttackSpeed(reflectedVelocity.x, reflectedVelocity.y);
			
			m_controller->enermyAttacked(pConflictedEnermy, mAttack1Hurt);
			mAttackCnt++;
			return;
		}
		else if(pConflictedEnermy != NULL)
		{
			if(mLastConflictedEntity == pConflictedEnermy) return;
			mLastConflictedEntity = pConflictedEnermy;
			m_controller->enermyAttacked(pConflictedEnermy, mAttack1Hurt);
			mAttackCnt++;
		}

		CCPoint normalVec;
		bool conflictWithWall = m_controller->conflictWithWall(this, normalVec);
		if(conflictWithWall)
		{
			mLastConflictedEntity = NULL;

			// �Ƚ���λ��У������֤������߽�
			m_controller->normalizePos(this);

			// ��ǽ����ײ��ֱ�ӷ���
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
	mAttackCnt = 0;

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
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_attacking = false;
	m_activated = false;
	m_controller->leaveFromAttacking(this);

	/*��ѪƮ��Ч��*/
	if(mAttackCnt > 1)
	{
		char str[1024];
		sprintf(str, "%d Hits\n", mAttackCnt);
		FlowWord *pFlowWord = FlowWord::create();
		this->getParent()->addChild(pFlowWord);
		pFlowWord->showWord(str, CCPoint(visibleSize.width/2, visibleSize.height/2));
	}
}

void Friend::attack2()
{
	if(mTriggleFlag == false)
	{	
	// ֪ͨcontroller����һ��������
	m_controller->addAttackingFriend();
	switch(mLevel)
	{
	case 1:
		//��ը��Ч
		mParticleSystem = CCParticleExplosion::create();
		mParticleSystem->setDuration(FRIEND_ATTACK_TIME);
		mParticleSystem->setLife(FRIEND_ATTACK_TIME);
		mParticleSystem->setSpeed(100);		// 200��Χ��ȫ������
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
		//��ɢ��Ч
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
		//��������Ч
		LightBunch *pLightBunch = LightBunch::create();
		CCNode::addChild(pLightBunch);
		pLightBunch->show();

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("FriendLightBunch.mp3");
		scheduleOnce(schedule_selector(Friend::attack2End), FRIEND_ATTACK_TIME);
		break;
	}
	mTriggleFlag = true;
	}
}

void Friend::attack2End(float)
{
	// ��Ҫ֪ͨcontroller�Լ��Ĺ����Ѿ������ˣ������Ѿ�����һ�����˺�
	// controller���յ���֪ͨ����ܼ���ѡ����һ��������ѡ��
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
** �ܵ���������ִ��Entity�Ŀ�Ѫ
** Ȼ���жϵ�ǰ״̬�Ƿ�������״̬�������������Լ�Ϊ���ɼ���ͬʱ����������Ч
** ����������Ч�Ĺ������ȴ���һ����Ч��Ȼ�󴴽�һ����ʱ�����ڶ�ʱ����Ĵ����������õ�ǰ���󲻿ɼ�
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
		// TODO: ����������Ч
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
		setHp(100);
		break;
	case 1:
		mAttack1Hurt = 45;
		mAttack2Hurt = 100;
		setHp(450);
		break;
	case 2:
		mAttack1Hurt = 200;
		mAttack2Hurt = 200;
		setHp(700);
		break;
	}
	mLevel++;
}