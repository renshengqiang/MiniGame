#include "Enermy.h"
#include "Controller\GameController.h"
#include "Utils.h"

USING_NS_CC;
using namespace cocos2d::extension;
Enermy::Enermy(const char *fileName)
{
	CCSprite *sprite = CCSprite::create(fileName);

	bindSprite(sprite);
	m_autoAttack = true;
}

void  Enermy::bindSprite(cocos2d::CCSprite *sprite)
{
	Entity::bindSprite(sprite);
	/*��ʼ��Ѫ����*/
	m_hpSlider = CCControlSlider::create(
							CCSprite::create("background.png"),
							CCSprite::create("progress_enermy.png"),
							CCSprite::create("sliderThumb.png"));
	
	m_hpSlider->setPosition(ccp(0,FRIEND_SIZE));
	m_hpSlider->setTouchEnabled(false);
	m_hpSlider->setMaximumValue(m_fullHp);
	m_hpSlider->setMinimumValue(0);
	m_hpSlider->setValue(m_fullHp);
	Entity::addChild(m_hpSlider, 0);
}

void Enermy::attack()
{
	//TODO: ����һ������һ��ʱ���ı�ը����Ч��
	////����CCParticleExplosion��Ч
	CCParticleSystem * p1=CCParticleExplosion::create();
	p1->setDuration(ENERMY_ATTACK_TIME);
	p1->setLife(ENERMY_ATTACK_TIME);
	p1->setSpeed(p1->getSpeed() * 4);
	//������Ч��ͼ
	p1->setTexture(CCTextureCache::sharedTextureCache()->addImage("particles.png"));
	//�����Զ��ͷ�
	p1->setAutoRemoveOnFinish(true);
	//�����ƶ�����
	p1->setPositionType(kCCPositionTypeGrouped);
	//����λ��
	p1->setPosition(ccp(0, 0));
	//�����Ч
	this->addChild(p1);
	// Ȼ�󴴽�һ����ʱ���񣬱�ը������֪ͨcontroller���Ѿ������˺���Ȼ����һ������ִ��
	scheduleOnce(schedule_selector(Enermy::attackEnd), ENERMY_ATTACK_TIME);
}

void Enermy::underAttack(int hp)
{
	if(m_hp < hp) hp = m_hp;
	Entity::underAttack(hp);

	if(dead())
	{
		scheduleOnce(schedule_selector(Enermy::die), DIE_TIME);
		// TODO: ����������Ч
	}
	
}

void Enermy::setController(GameController *controller)
{
	Entity::setController(controller);
	controller->addEnermy(this);
}

void Enermy::attackEnd(float)
{
	// ֪ͨcontroller������ѡ�ֽ���һ���˺�
	// TODO:�Ż��˺���ʽ
	m_activated = false;
	m_controller->friendsAttacked(mAttackHurt);
	m_controller->leaveFromAttacking(this);
}

void Enermy::die(float)
{
	setVisible(false);
}