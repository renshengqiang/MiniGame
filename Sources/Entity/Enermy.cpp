#include "Enermy.h"
#include "Controller\GameController.h"
#include "Effects\Arrow.h"
#include "effects\Missle.h"
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
	mFXSprite = NULL;
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
			Arrow *pArrow = Arrow::create();
			this->addChild(pArrow);
			pArrow->show(this->getPosition(), mAttackedFriend->getPosition());
			mFXSprite = pArrow;
			scheduleOnce(schedule_selector(Enermy::attackEnd), 0.7*ENERMY_ATTACK_TIME);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("EnermyAttack.wav");
		}
		break;
	case 2:
		{
			/*
			mAttackedFriend = m_controller->getOneAttackedFriend();
			CCPoint friendPos = mAttackedFriend->getPosition();
			Missle *pMissle = Missle::create();
			this->addChild(pMissle);
			pMissle->show(this->getPosition(), mAttackedFriend->getPosition());
			mFXSprite = pMissle;
			scheduleOnce(schedule_selector(Enermy::attackEnd), 0.7*ENERMY_ATTACK_TIME);
			*/
			CCPoint pos[15] = {CCPoint(100, 200), CCPoint(300, 250), CCPoint(500, 200), CCPoint(650, 180),
							   CCPoint(200, 400), CCPoint(400, 450), CCPoint(600, 500), 
							   CCPoint(100, 800), CCPoint(300, 900), CCPoint(500, 850), CCPoint(700, 870),
							   CCPoint(200, 1000),CCPoint(400, 1050),CCPoint(550, 1100),CCPoint(300, 1200)};
			mFXSprite = CCSprite::create();
			this->getParent()->addChild(mFXSprite);

			for(int i=0; i<15; ++i)
			{
				CCSprite *pSprite = CCSprite::create("EnermyAttack2_1.png");
				mFXSprite->addChild(pSprite);
				pSprite->setPosition(pos[i]);
				CCAnimation *animation = AnimationUtil::createAnimWithFrameNameAndNum("EnermyAttack2_", 5, 0.16f, 2, CCRectMake(0, 0, 201, 228));
				pSprite->runAction(CCAnimate::create(animation));
			}
			scheduleOnce(schedule_selector(Enermy::attackEnd), 0.7*ENERMY_ATTACK_TIME);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("EnermyAttack.wav");
		}
		break;
	case 3:
		{
		CCPoint pos[15] = {CCPoint(100, 200), CCPoint(300, 250), CCPoint(500, 200), CCPoint(650, 180),
							   CCPoint(200, 400), CCPoint(400, 450), CCPoint(600, 500), 
							   CCPoint(100, 800), CCPoint(300, 900), CCPoint(500, 850), CCPoint(700, 870),
							   CCPoint(200, 1000),CCPoint(400, 1050),CCPoint(550, 1100),CCPoint(300, 1200)};		
		mFXSprite = CCSprite::create();
		this->getParent()->addChild(mFXSprite);

		for(int i=0; i<15; ++i)
		{
			CCSprite *pSprite = CCSprite::create("EnermyAttack3_1.png");
			mFXSprite->addChild(pSprite);
			pSprite->setPosition(pos[i]);
			CCAnimation *animation = AnimationUtil::createAnimWithFrameNameAndNum("EnermyAttack3_", 5, 0.16f, 2, CCRectMake(0, 0, 201, 228));
			pSprite->runAction(CCAnimate::create(animation));
		}
		scheduleOnce(schedule_selector(Enermy::attackEnd), 0.7*ENERMY_ATTACK_TIME);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("BossSkill.mp3");
		}
		break;
	}
}

void Enermy::underAttack(int hp)
{
	// 受到伤害，血量减少
	if(m_hp < hp) hp = m_hp;
	Entity::underAttack(hp);

	m_controller->addAttackedEnermy();

	if(dead())
	{	
		if(mType <= 2)
		{
			// Enermy死亡特效
			mFXSprite = CCSprite::create("EnermyDie1.png");
			mFXSprite->setScale(3.0f);
			this->getParent()->addChild(mFXSprite, 5);
			mFXSprite->setPosition(this->getPosition());
			CCAnimation *animation = AnimationUtil::createAnimWithFrameNameAndNum("EnermyDie", 10, 0.1f, 1, CCRectMake(0, 0, 100, 105));
			mFXSprite->runAction(CCAnimate::create(animation));
			scheduleOnce(schedule_selector(Enermy::die), 1);
		}
		else
		{
			// Boss死亡特效
			mFXSprite = CCSprite::create("BossDie1.png");
			this->getParent()->addChild(mFXSprite, 5);
			mFXSprite->setScale(2.0f);
			mFXSprite->setPosition(this->getPosition());
			CCAnimation *animation = AnimationUtil::createAnimWithFrameNameAndNum("BossDie", 10, 0.1f, 1, CCRectMake(0, 0, 323, 360));
			mFXSprite->runAction(CCAnimate::create(animation));
			scheduleOnce(schedule_selector(Enermy::die), 1);
		}
	}
	else
	{
		// 播放受击动画
		CCActionInterval *shaky3DFX = CCShaky3D::create(0.5, CCSizeMake(15, 10), 5, false);
		CCStopGrid *stopGrid = CCStopGrid::create();
		CCCallFunc *pCallFunc = CCCallFunc::create(this, callfunc_selector(Enermy::underAttackEnd));
		CCSequence *action = CCSequence::create(shaky3DFX, stopGrid, pCallFunc, NULL);
		this->runAction(action);
	}
}

void Enermy::underAttackEnd()
{
	m_controller->removeAttackedEnermy(this);
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
	m_activated = false;
	mFXSprite->removeFromParentAndCleanup(true);
	mFXSprite = NULL;
	// 通知controller对所有选手进行一次伤害
	if(mType <= 1)
	{
		m_controller->friendsAttacked(mAttackedFriend, mAttackHurt);
	}
	else
	{
		m_controller->friendsAttacked(NULL, mAttackHurt);
	}
	scheduleOnce(schedule_selector(Enermy::attackEndEnd), 0.3*ENERMY_ATTACK_TIME);
}

void Enermy::attackEndEnd(float)
{
	m_controller->leaveFromAttacking(this);
}

void Enermy::die(float)
{
	setVisible(false);

	if( mFXSprite != NULL )
	{
		mFXSprite->removeFromParentAndCleanup(true);
		mFXSprite = NULL;
	}

	// 播放掉金币特效
	mpJinbiSprite = CCSprite::create("jinbi1.png");
	mpJinbiSprite->setScale(1.5);
	this->getParent()->addChild(mpJinbiSprite);
	mpJinbiSprite->setPosition(this->getPosition());
	CCAnimation *animation = AnimationUtil::createAnimWithFrameNameAndNum("jinbi", 10, 0.2f, 1, CCRectMake(0, 0, 250, 250));
	mpJinbiSprite->runAction(CCAnimate::create(animation));
	scheduleOnce(schedule_selector(Enermy::dieEnd), 2);

	
	if(mType > 2)
	{
		// 生成一个科技残片飘向道具栏
		CCSprite *props = CCSprite::create("props.png");
		CCBlink *blinkAction = CCBlink::create(0.2,3);
		CCMoveTo *moveAction = CCMoveTo::create(0.3, ccp(SCREEN_WIDTH - 10, 10));
		CCCallFuncND *funcAction = CCCallFuncND::create(this, callfuncND_selector(Enermy::propsMoveEnd),(void *)props);
		CCSequence *propsAction = CCSequence::create(blinkAction, moveAction, funcAction, NULL);
		props->setPosition(this->getPosition()+ccp(0, -FRIEND_SIZE));
		this->getParent()->addChild(props);
		props->runAction(propsAction);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("BossDie.wav");
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("EnermyDie.wav");
	}
}

void Enermy::dieEnd(float)
{
	this->setVisible(false);
	if(mpJinbiSprite)
	{
		mpJinbiSprite->removeFromParentAndCleanup(true);
	}

	// 通知controller以进行下一步的攻击
	m_controller->removeAttackedEnermy(this);
}

void Enermy::propsMoveEnd(CCNode *pSender, void *data)
{
	CCSprite *props = static_cast<CCSprite*>(data);
	if(props != NULL)
	{
		props->getParent()->removeChild(props);
	}
}