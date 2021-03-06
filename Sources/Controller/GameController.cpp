#include "GameController.h"
#include "Entity\Friend.h"
#include "Entity\Enermy.h"
#include "Scenes\GameScene.h"
#include "Scenes\CombatResultsScene.h"
#include "Scenes\CombatFailedScene.h"
//#include "UI\Toolbar.h"
//#include "UI\Statusbar.h"
#include "Utils.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

float _calcRatio(cocos2d::CCPoint delta)
{
	float max = FRIEND_RADIUS*4;
	return delta.getLength()/max > 1 ? 1 : delta.getLength()/max;
}

bool GameController::init()
{

	CCLayer::setTouchEnabled(true);		// 设置允许触摸
	CCLayer::scheduleUpdate();			// 调用update函数

	mAttackingEntity = NULL;
	mIsAttacking = false;
	mAttackingFriendCnt = 0;
	mAttackedEnermyCnt = 0;
	mpArrowSprite = NULL;
	mIsFingerDown = false;
	//mToolbar = NULL;
	//mStatusbar = NULL;
	return true;
}

void GameController::update(float delta)
{

}

/*
** 规范化pEntity的坐标，使其在屏幕范围内 
*/
void GameController::normalizePos(Entity *pEntity)
{
	CCPoint pos = pEntity->getTagPosition();
	int size = pEntity->getSize();
	
	if(pos.x < size)
	{
		pos.x = size;
	}
	else if( pos.x > SCREEN_WIDTH - size)
	{
		pos.x = SCREEN_WIDTH - size;
	}

	if(pos.y < size + WIDGET_HEIGHT)
	{
		pos.y = size + WIDGET_HEIGHT;
	}
	else if(pos.y > SCREEN_HEIGHT - size)
	{
		pos.y = SCREEN_HEIGHT - size;
	}
	pEntity->setTagPosition(pos.x, pos.y);
}

/*
** 加入一个友军
*/
void GameController::addFriend(Friend *pFriend)
{
	mFriendVec.push_back(pFriend);
	mEntityVec.push_back(pFriend);
}

/*
** 加入一个怪物敌人
*/
void GameController::addEnermy(Enermy *pEnermy)
{
	mEnermyVec.push_back(pEnermy);
	mEntityVec.push_back(pEnermy);
}

/*
** 获取一个受攻击的友军
** 可以确定肯定可以获取一个友军
*/
Friend *GameController::getOneAttackedFriend()
{
	cc_timeval psv;
	CCTime::gettimeofdayCocos2d( &psv, NULL );
	unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000;
	unsigned int index = tsrans%3;
	
	if(mFriendVec[index]->dead() == true) index = (index+1)%3;
	if(mFriendVec[index]->dead() == true) index = (index+1)%3;
	return mFriendVec[index];
}

/*
**判断collider是否和场景中的其他友军有冲突，有冲突则返回友军的指针，否则返回NULL
*/
Friend *GameController::conflictWithFriend(Friend *collider)
{
	CCPoint pos = collider->getTagPosition();

	for(int i=0; i<mFriendVec.size(); ++i)
	{
		if(mFriendVec[i] == collider) continue;
		if(mFriendVec[i]->dead()) continue;
		CCPoint pos2 = mFriendVec[i]->getTagPosition();
		CCPoint dist = pos2 - pos;
		if(ccpLength(dist) <= FRIEND_RADIUS*2)
			return mFriendVec[i];
	}

	return NULL;
}

/*
** 判断collider是否和场景中的怪物敌人有碰撞发生，如果有则返回该敌人，否则返回NULL
*/
Enermy *GameController::conflictWithEnermy(Friend *collider)
{
	static bool flag = false;
	CCPoint pos = collider->getTagPosition();

	for(int i=0; i<mEnermyVec.size(); ++i)
	{
		if(mEnermyVec[i]->dead()) continue;
	
		CCPoint pos2 = mEnermyVec[i]->getTagPosition();
		CCPoint dist = pos2 - pos;

		if( ccpLength(dist) <= collider->getSize() + mEnermyVec[i]->getSize() )
		{
			return mEnermyVec[i];
		}
	}
	if(flag == false)
	{
		for(int i=0; i<mEnermyVec.size(); ++i)
		{
			CCPoint pos = mEnermyVec[i]->getTagPosition();
		}
		flag = true;
	}
	return NULL;
}

/*
** 判断collider是否和当前场景的墙壁有所碰撞，返回true则表示发生了碰撞，否则表示没有碰撞
** 发生碰撞则在wallNormall中返回墙壁的法线向量
*/
bool GameController::conflictWithWall(Friend *collider, cocos2d::CCPoint &wallNormal)
{
	bool ret = true;
	CCPoint pos = collider->getTagPosition();
	if(pos.x < collider->getSize())
	{
		wallNormal.x = 1;
		wallNormal.y = 0;
	}
	else if(pos.y < collider->getSize()+WIDGET_HEIGHT)
	{
		wallNormal.x = 0;
		wallNormal.y = 1;
	}
	else if(pos.x > SCREEN_WIDTH - collider->getSize())
	{
		wallNormal.x = -1;
		wallNormal.y = 0;
	}
	else if(pos.y > SCREEN_HEIGHT - collider->getSize())
	{
		wallNormal.x = 0;
		wallNormal.y = -1;
	}
	else
		ret = false;

	return ret;
}

void GameController::setAttackingEntity(Entity *pEntity)
{
	mAttackingEntity = pEntity;
	mAttackingEntity->setActive(true);

	// 新一轮攻击开始，触发标志位复位
	for(int i=0; i<mFriendVec.size(); ++i)
	{
		mFriendVec[i]->setTiggleFlag(false);
	}
}

/*
** pAttackingEntity当前的攻击过程结束
** 此过程的判断较为复杂：
1. 若主角死亡，则游戏结束；
2. 如果所有的敌人死亡，则胜利，进入下一个场景（关卡）；
3. 否则选择下一个Entity进行下一轮的攻击；
4. 如果下一个攻击的对象是怪物，则进行自动攻击
5. 设置友情技能的标志位为false
*/
void GameController::leaveFromAttacking(Entity *pAttackingEntity)
{
	if(mAttackingFriendCnt > 0) return;

	//选择下一个Entity进入攻击状态
	if(NULL != pAttackingEntity)
	{
		int index = 0;
		for(int i=0; i<mEntityVec.size(); ++i)
		{
			if(pAttackingEntity == mEntityVec[i]) 
			{
				index = i;
				break;
			}
		}
		index = (index+1)%mEntityVec.size();

		while(mEntityVec[index]->dead()) index=(index+1)%mEntityVec.size();
		mAttackingEntity = mEntityVec[index];
	}

	if(mAttackedEnermyCnt > 0) return;

	// 1 游戏结束
	bool endFlag = true;
	for(int i=0; i<mFriendVec.size(); ++i)
	{
		if(mFriendVec[i]->dead() == false)
		{
			endFlag = false;
			break;
		}
	}
	if(true == endFlag)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("GameFail.mp3");

		CCScene *pScene = CombatFailedScene::scene();
		CCDirector::sharedDirector()->replaceScene(pScene);
		return;
	}


	// 2 进入下一个关卡
	bool isAllEnermyDead = true;
	for(int i=0; i<mEnermyVec.size(); ++i)
	{
		if(mEnermyVec[i]->dead() == false)
		{
			isAllEnermyDead = false;
			break;
		}
	}

	if(true == isAllEnermyDead)
	{
		GameScene *pParentScene = dynamic_cast<GameScene*>(getParent());

		if(NULL != pParentScene)
		{
			pParentScene->increaseLevel();
			// 设置toolbar上显示的是新一轮攻击的Entity的情况
			int index = 0;
			for(index=0; index<mFriendVec.size(); ++index)
			{
				if(mFriendVec[index] != NULL) break;
			}
			//mToolbar->setEntity(mFriendVec[index]);
			return;
		}
	}

	//mToolbar->setEntity(mAttackingEntity);

	// 设置为激活状态，如果是自动攻击对象则进行自动攻击
	mAttackingEntity->setActive(true);
	if(mAttackingEntity->isAuto())
	{
		mIsAttacking = true;
		mAttackingEntity->attack();
	}
	else
	{
		mIsAttacking = false;
	}
	
	// 新一轮攻击开始，触发标志位复位
	for(int i=0; i<mFriendVec.size(); ++i)
	{
		mFriendVec[i]->setTiggleFlag(false);
	}
}

void  GameController::addAttackingFriend()
{
	++mAttackingFriendCnt;
}

void  GameController::removeAttackingFriend()
{
	--mAttackingFriendCnt;
	leaveFromAttacking(mAttackingEntity);
}

void GameController::addAttackedEnermy()
{
	++mAttackedEnermyCnt;

}

void GameController::removeAttackedEnermy(Enermy *pEnermy)
{
	--mAttackedEnermyCnt;
	leaveFromAttacking(NULL);

	//if(pEnermy->dead() && mStatusbar)
	//{
	//	mStatusbar->addBuff1(pEnermy->getBuff1());
	//	mStatusbar->addBuff2(pEnermy->getBuff2());
	//}
}
/*
** 怪物发动攻击，主角和友军会同时受到攻击
** 1. 如果主角死亡，则游戏结束；
** 2. 如果其他友军死亡则播放死亡特效，然后将其隐藏；
*/
void  GameController::friendsAttacked(Friend *pFriend, int hp)
{
	// 对友军执行伤害动作
	if(pFriend != NULL)
	{
		pFriend->underAttack(hp);
	}
	else
	{
		for(int i=0; i<mFriendVec.size(); ++i)
		{
			if(mFriendVec[i]->dead() == false)
			{
				mFriendVec[i]->underAttack(hp);
			}
		}
	}
	
	bool endFlag = true;
	for(int i=0; i<mFriendVec.size(); ++i)
	{
		if(mEnermyVec[i]->dead() == false)
		{
			endFlag = false;
			break;
		}
	}
	if(true == endFlag)
	{
		CCScene *pScene = CombatResultsScene::scene();
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

/*
** 如果pEnermy不为空，则调用pEnermy的underAttack方法受到攻击
** 如果pEnermy为空，则对所有的pEnermy调用underAttack方法
*/
void GameController::enermyAttacked(Enermy *pEnermy, int hp)
{
	if(pEnermy != NULL && pEnermy->dead() == false)
	{
		pEnermy->underAttack(hp);
	}
	else
	{
		for(unsigned i=0; i<mEnermyVec.size(); ++i)
		{
			if(mEnermyVec[i]->dead() == false)
			{
				mEnermyVec[i]->underAttack(hp);
			}
		}
	}
}

/*
** 友军激光攻击：需要判断有哪几个Enermy受到伤害
*/
void GameController::enermyAttackedByLaser(Friend *pFriend, int hp)
{
	CCPoint fPos = pFriend->getPosition();

	for(unsigned i=0; i<mEnermyVec.size(); ++i)
	{
		if(mEnermyVec[i]->dead() == false)
		{
			CCPoint ePos = mEnermyVec[i]->getPosition();
			if(abs(fPos.x - ePos.x) <= FRIEND_SIZE || abs(fPos.y - ePos.y) <= FRIEND_SIZE)
			{
				mEnermyVec[i]->underAttack(hp);
			}
		}
	}
}

void GameController::enermyAttacked(Friend *pFriend, float dis, int hp)
{
	CCPoint fPos = pFriend->getPosition();
	for(unsigned i=0; i<mEnermyVec.size(); ++i)
	{
		if(mEnermyVec[i]->dead() == false)
		{
			CCPoint ePos = mEnermyVec[i]->getPosition();
			CCPoint delta  = ePos - fPos;
			float d = delta.getLength();

			if(d <= dis)
			{
				mEnermyVec[i]->underAttack(hp);
			}
		}
	}
}
/*
** 清除当前局的所有Enermy
*/
void GameController::clearEnermy()
{
	mEnermyVec.clear();
}

/*
** 重置新关卡
*/
void GameController::resetNewLevel()
{
	for(int i=0; i<mFriendVec.size(); ++i)
	{
		if(mFriendVec[i]->dead() == false)
		{
			mAttackingEntity = mFriendVec[i];
		}
	}

	mAttackingEntity->setActive(true);
	mIsAttacking = false;

	// 新一轮攻击开始，触发标志位复位
	for(int i=0; i<mFriendVec.size(); ++i)
	{
		mFriendVec[i]->setTiggleFlag(false);
		mFriendVec[i]->setActive(false);
	}
}

/*
** 触摸开始事件的处理，如果是自己或者友军在进行攻击，则创建一个箭头表示攻击方向
*/
bool GameController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	if(mIsAttacking) return true;
	if(mIsFingerDown) return true;
	// 获取坐标
	CCPoint touchPos = pTouch->getLocationInView();
	touchPos = CCDirector::sharedDirector()->convertToGL(touchPos);
	mTouchBeginPos = touchPos;

	if(mTouchBeginPos.y < WIDGET_HEIGHT) return true;
	if(mTouchBeginPos.y >= visibleSize.height - WIDGET_HEIGHT) return true;
	mpArrowSprite = CCSprite::create("arrow.png");
	//mpArrowSprite->setScaleX(2.0f);
	CCLayer::addChild(mpArrowSprite);
	mpArrowSprite->setPosition(mAttackingEntity->getTagPosition());

	mIsFingerDown = true;
	return true;
}

/*
** 发生移动则旋转箭头
*/
void GameController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if(mIsAttacking) return;
	if(mpArrowSprite == NULL) return;

	// 获取坐标
	CCPoint touchPos = pTouch->getLocationInView();
	touchPos = CCDirector::sharedDirector()->convertToGL(touchPos);
	mTouchEndPos = touchPos;

	CCPoint delta = mTouchBeginPos - touchPos;
	float angle = delta.getAngle(CCPoint(1,0));
	float ratio = _calcRatio(delta);
	if(mpArrowSprite)
	{
		mpArrowSprite->setRotation(angle*180/M_PI);
		mpArrowSprite->setScaleX(2*ratio+1);
	}
}

void GameController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if(mIsAttacking) return;
	if(mpArrowSprite == NULL) return;

	Friend *pAttackingFriend = dynamic_cast<Friend*>(mAttackingEntity);
	if(pAttackingFriend == NULL) return;

	// 释放箭头
	if(mpArrowSprite != NULL)
	{
		mpArrowSprite->getParent()->removeChild(mpArrowSprite, true);
		mpArrowSprite = NULL;
	}

	CCPoint dir = mTouchBeginPos - mTouchEndPos;
	float ratio = _calcRatio(dir);
	dir = dir.normalize();
	pAttackingFriend->setAttackSpeed(dir.x*ATTACK_SPEED*ratio,dir.y*ATTACK_SPEED*ratio);
	pAttackingFriend->setAttackTime(FRIEND_ATTACK_TIME);
	pAttackingFriend->attack();

	mIsAttacking = true;
	mIsFingerDown = false;
}

void GameController::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}
