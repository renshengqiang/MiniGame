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
	/*初始化血量条*/
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
	//TODO: 创建一个具有一定时长的爆炸粒子效果
	////创建CCParticleExplosion特效
	CCParticleSystem * p1=CCParticleExplosion::create();
	p1->setDuration(ENERMY_ATTACK_TIME);
	p1->setLife(ENERMY_ATTACK_TIME);
	p1->setSpeed(p1->getSpeed() * 4);
	//设置特效贴图
	p1->setTexture(CCTextureCache::sharedTextureCache()->addImage("particles.png"));
	//设置自动释放
	p1->setAutoRemoveOnFinish(true);
	//设置移动类型
	p1->setPositionType(kCCPositionTypeGrouped);
	//设置位置
	p1->setPosition(ccp(0, 0));
	//添加特效
	this->addChild(p1);
	// 然后创建一个定时任务，爆炸结束后通知controller对友军进行伤害，然后到下一个继续执行
	scheduleOnce(schedule_selector(Enermy::attackEnd), ENERMY_ATTACK_TIME);
}

void Enermy::underAttack(int hp)
{
	if(m_hp < hp) hp = m_hp;
	Entity::underAttack(hp);

	if(dead())
	{
		scheduleOnce(schedule_selector(Enermy::die), DIE_TIME);
		// TODO: 播放死亡特效
	}
	
}

void Enermy::setController(GameController *controller)
{
	Entity::setController(controller);
	controller->addEnermy(this);
}

void Enermy::attackEnd(float)
{
	// 通知controller对所有选手进行一次伤害
	// TODO:优化伤害方式
	m_activated = false;
	m_controller->friendsAttacked(mAttackHurt);
	m_controller->leaveFromAttacking(this);
}

void Enermy::die(float)
{
	setVisible(false);
}