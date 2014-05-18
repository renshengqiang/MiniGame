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
	m_particleSystem = NULL;
	mType = 1;
}

void  Enermy::bindSprite(cocos2d::CCSprite *sprite)
{
	Entity::bindSprite(sprite);
	/*��ʼ��Ѫ����*/
	m_hpSlider = CCControlSlider::create(
							CCSprite::create("background.png"),
							CCSprite::create("progress_enermy.png"),
							CCSprite::create("sliderThumb.png"));
	
	m_hpSlider->setPosition(ccp(0,FRIEND_SIZE*0.75));
	m_hpSlider->setTouchEnabled(false);
	m_hpSlider->setMaximumValue(m_fullHp);
	m_hpSlider->setMinimumValue(0);
	m_hpSlider->setValue(m_fullHp);
	Entity::addChild(m_hpSlider, 0);
}

void Enermy::attack()
{
	switch(mType)
	{
	case 1:
		m_particleSystem = CCParticleFlower::create();
		m_particleSystem->setTexture( CCTextureCache::sharedTextureCache()->addImage("stars.png") );
		m_particleSystem->setLifeVar(0);
		m_particleSystem->setLife(ENERMY_ATTACK_TIME);
		m_particleSystem->setSpeed(400);
		m_particleSystem->setSpeedVar(0);
		m_particleSystem->setEmissionRate(10000);
		break;
	case 2:
		m_particleSystem=CCParticleExplosion::create();
		m_particleSystem->setDuration(ENERMY_ATTACK_TIME);
		m_particleSystem->setLife(ENERMY_ATTACK_TIME);
		m_particleSystem->setSpeed(m_particleSystem->getSpeed() * 4);
		m_particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("boss_particle.png"));
		m_particleSystem->setAutoRemoveOnFinish(true);
		m_particleSystem->setPositionType(kCCPositionTypeGrouped);
		break;
	case 3:
		m_particleSystem = new CCParticleSystemQuad();
		m_particleSystem->initWithFile("SpookyPeas.plist");
		break;
	}
	m_particleSystem->setPosition(ccp(0, 0));
	//�����Ч
	this->addChild(m_particleSystem);
	// Ȼ�󴴽�һ����ʱ���񣬱�ը������֪ͨcontroller���Ѿ������˺���Ȼ����һ������ִ��
	scheduleOnce(schedule_selector(Enermy::attackEnd), ENERMY_ATTACK_TIME);
}

void Enermy::underAttack(int hp)
{
	// �ܵ��˺���Ѫ������
	if(m_hp < hp) hp = m_hp;
	Entity::underAttack(hp);

	// �����ܻ�����
	CCActionInterval *shaky3DFX = CCShaky3D::create(0.5, CCSizeMake(15, 10), 5, false);
	CCStopGrid *stopGrid = CCStopGrid::create();
	CCSequence *action = CCSequence::create(shaky3DFX, stopGrid, NULL);
	this->runAction(action);

	if(dead())
	{	
		setVisible(false);
		
		// ����������Ч,����һ����ң����������Ư��
		CCBlink *blinkDieAction = CCBlink::create(1,7);
		CCCallFunc *dieEndAction = CCCallFunc::create(this, callfunc_selector(Enermy::die));
		CCSequence *dieAction = CCSequence::create(blinkDieAction, dieEndAction, NULL);
		this->runAction(dieAction);

		CCSprite *props = CCSprite::create("props.png");
		CCBlink *blinkAction = CCBlink::create(0.2,3);
		CCMoveTo *moveAction = CCMoveTo::create(0.5, ccp(10, SCREEN_HEIGHT-10));
		CCCallFuncND *funcAction = CCCallFuncND::create(this, callfuncND_selector(Enermy::propsMoveEnd),(void *)props);
		CCSequence *propsAction = CCSequence::create(blinkAction, moveAction, funcAction, NULL);
		props->setPosition(this->getPosition()+ccp(0, -FRIEND_SIZE));
		this->getParent()->addChild(props);
		props->runAction(propsAction);
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
	m_particleSystem->getParent()->removeChild(m_particleSystem);
	m_particleSystem = NULL;
}

void Enermy::die()
{
	this->setVisible(false);
}

void Enermy::propsMoveEnd(CCNode *pSender, void *data)
{
	CCSprite *props = static_cast<CCSprite*>(data);
	if(props != NULL)
	{
		props->getParent()->removeChild(props);
	}
}