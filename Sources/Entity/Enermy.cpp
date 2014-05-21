#include "Enermy.h"
#include "Controller\GameController.h"
#include "Effects\Laser.h"
#include "Utils.h"
#include "Friend.h"
#include "SimpleAudioEngine.h"
#include "Effects\AnimationUtil.h"

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
	/*初始化血量条*/
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
		{
			mAttackedFriend = m_controller->getOneAttackedFriend();
			CCPoint friendPos = mAttackedFriend->getPosition();
			Laser *pLaser = Laser::create();
			this->addChild(pLaser);
			pLaser->show(this->getPosition(), mAttackedFriend->getPosition());
			mFXSprite = pLaser;
			scheduleOnce(schedule_selector(Enermy::attackEnd), ENERMY_ATTACK_TIME);
			//scheduleOnce(schedule_selector(Enermy::attackTempEnd), 0.3*ENERMY_ATTACK_TIME);
		}
		break;
	case 2:
		m_particleSystem = CCParticleFlower::create();
		m_particleSystem->setTexture( CCTextureCache::sharedTextureCache()->addImage("stars.png"));
		m_particleSystem->setLifeVar(0);
		m_particleSystem->setLife(ENERMY_ATTACK_TIME);
		m_particleSystem->setSpeed(400);
		m_particleSystem->setSpeedVar(0);
		m_particleSystem->setEmissionRate(10000);
		m_particleSystem->setPosition(ccp(0, 0));
		this->addChild(m_particleSystem);
		scheduleOnce(schedule_selector(Enermy::attackEnd), ENERMY_ATTACK_TIME);
		break;
	case 3:
		m_particleSystem = CCParticleExplosion::create();
		m_particleSystem->setDuration(ENERMY_ATTACK_TIME);
		m_particleSystem->setLife(ENERMY_ATTACK_TIME);
		CCLog("speed %f\n", m_particleSystem->getSpeed());
		m_particleSystem->setSpeed(m_particleSystem->getSpeed() * 4);
		m_particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
		m_particleSystem->setAutoRemoveOnFinish(true);
		m_particleSystem->setPositionType(kCCPositionTypeGrouped);
		m_particleSystem->setPosition(ccp(0, 0));
		this->addChild(m_particleSystem);
		scheduleOnce(schedule_selector(Enermy::attackEnd), ENERMY_ATTACK_TIME);

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("BossSkill.mp3");
		break;
	}
}

void Enermy::underAttack(int hp)
{
	// 受到伤害，血量减少
	if(m_hp < hp) hp = m_hp;
	Entity::underAttack(hp);

	// 播放受击动画
	CCActionInterval *shaky3DFX = CCShaky3D::create(0.5, CCSizeMake(15, 10), 5, false);
	CCStopGrid *stopGrid = CCStopGrid::create();
	CCSequence *action = CCSequence::create(shaky3DFX, stopGrid, NULL);
	this->runAction(action);

	if(dead())
	{	
		setVisible(false);
		
		// 播放死亡特效,生成一个金币，并向道具栏漂移
		CCBlink *blinkDieAction = CCBlink::create(1,7);
		CCCallFunc *dieEndAction = CCCallFunc::create(this, callfunc_selector(Enermy::die));
		CCSequence *dieAction = CCSequence::create(blinkDieAction, dieEndAction, NULL);
		this->runAction(dieAction);

/* TODO: 测试爆炸效果
		CCSprite *pRunsp = CCSprite::create("Bomb01.png");
		this->addChild(pRunsp);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Boomb0.plist", "Boomb0.png");
		CCAnimation *animation  = AnimationUtil::createAnimWithFrameNameAndNum("Boomb0", 16, 0.1f, -1);
		pRunsp->runAction(CCAnimate::create(animation));
*/
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

void Enermy::attackTempEnd(float)
{
	mFXSprite = CCSprite::create("laser.png");
	this->getParent()->addChild(mFXSprite);
	mAttackedFriend = m_controller->getOneAttackedFriend();
	CCPoint friendPos = mAttackedFriend->getPosition();
	CCPoint pos = getPosition();
	CCPoint centerPos = (friendPos + pos)*0.5;
	mFXSprite->setPosition(centerPos);
	mFXSprite->setScaleX(10);
	CCPoint delta = friendPos - pos;
	float angle = delta.getAngle(CCPoint(1,0));
	if(mFXSprite)
	{
		mFXSprite->setRotation(angle*180/M_PI);
	}
	scheduleOnce(schedule_selector(Enermy::attackEnd), 0.7*ENERMY_ATTACK_TIME);
}

void Enermy::attackEnd(float)
{
	// 通知controller对所有选手进行一次伤害
	if(1 == mType)
	{
		mFXSprite->getParent()->removeChild(mFXSprite);
		m_controller->friendsAttacked(mAttackedFriend, mAttackHurt);
		m_controller->leaveFromAttacking(this);
	}
	else
	{
		m_activated = false;
		m_controller->friendsAttacked(NULL, mAttackHurt);
		m_controller->leaveFromAttacking(this);
		m_particleSystem->getParent()->removeChild(m_particleSystem);
		m_particleSystem = NULL;
	}
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