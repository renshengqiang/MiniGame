#include "Friend.h"
#include "Enermy.h"
#include "Controller\GameController.h"
#include "Utils.h"

USING_NS_CC;
using namespace cocos2d::extension;

Friend::Friend(const char *fileName)
{
	mAttackTimeLeft = 0;
	mxSpeed = 0;
	mySpeed = 0;
	mLastConflictedEntity = NULL;

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

	// �����֪ͨcontroller�ĺ�����һ��
	controller->addFriend(this);
}

void Friend::update(float delta)
{
	Entity::update(delta);

	if(m_attacking)
	{
		CCPoint dest = Entity::getTagPosition();
		dest.x += mxSpeed * delta;
		dest.y += mySpeed * delta;
		Entity::setTagPosition(dest.x, dest.y);

		mAttackTimeLeft -= delta;

		if(NULL == m_controller) 
		{
			m_attacking = false;
			return;
		}

		if(mAttackTimeLeft <= 0)
		{
			m_attacking = false;
			m_activated = false;
			m_controller->leaveFromAttacking(this);
		}

		Friend *pConflictedFriend = m_controller->conflictWithFriend(this);
		if(pConflictedFriend != NULL)
		{
			//�򵥸ı�ԭ�����еķ����µ������ǣ�����Ѿ������غ�����һֱ����Χ������ת���������
			//�������֮һ�Ǽ�¼��һ�γ�ͻ�Ķ�������γ�ͻ�Ķ�����ͬ�򲻽��з���ı�
			if(mLastConflictedEntity == pConflictedFriend) return;
			mLastConflictedEntity = pConflictedFriend;

			//�ı�ԭ�����˶�����
			CCPoint P1 = Entity::getTagPosition();
			CCPoint P2 = pConflictedFriend->getTagPosition();
			CCPoint normalVec = P1 - P2;
			CCPoint originalVelocity = CCPoint(mxSpeed, mySpeed);
			CCPoint reflectedVelocity;
			reflectedVelocity.x = -2*(mxSpeed*normalVec.x + mySpeed*normalVec.y)*normalVec.x/(normalVec.getLength()*normalVec.getLength()) + originalVelocity.x;
			reflectedVelocity.y = -2*(mxSpeed*normalVec.x + mySpeed*normalVec.y)*normalVec.y/(normalVec.getLength()*normalVec.getLength()) + originalVelocity.y;
			setAttackSpeed(reflectedVelocity.x, reflectedVelocity.y);

			//TODO: �������ѵ����鼼��
			//pConflictedFriend->attack2();
			//m_controller->addAttackingFriend(pConflictedFriend);

			return;
		}
		
		Enermy *pConflictedEnermy = m_controller->conflictWithEnermy(this);
		if(pConflictedEnermy != NULL)
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
			
			// TODO:������Ҫ�жϵ�ǰ�������ּ���
			pConflictedEnermy->underAttack(mAttack1Hurt);

			return;
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
	mAttackTimeLeft = 2;
	mLastConflictedEntity = NULL;
}

void Friend::attack2()
{
	//TODO:�ڶ��ּ���
}