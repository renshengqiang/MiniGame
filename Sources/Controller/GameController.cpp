#include "GameController.h"
#include "Entity\Friend.h"
#include "Entity\Enermy.h"
#include "Utils.h"

USING_NS_CC;

bool GameController::init()
{

	CCLayer::setTouchEnabled(true);		// 设置允许触摸
	CCLayer::scheduleUpdate();			// 调用update函数

	mAttackingEntity = NULL;
	mIsAttacking = false;
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
	
	if(pos.x < FRIEND_SIZE/2)
	{
		pos.x = FRIEND_SIZE/2;
	}
	else if( pos.x > SCREEN_WIDTH - FRIEND_SIZE/2)
	{
		pos.x = SCREEN_WIDTH - FRIEND_SIZE/2;
	}

	if(pos.y < FRIEND_SIZE/2)
	{
		pos.y = FRIEND_SIZE/2;
	}
	else if(pos.y > SCREEN_HEIGHT - FRIEND_SIZE/2)
	{
		pos.y = SCREEN_HEIGHT - FRIEND_SIZE/2;
	}
	pEntity->setTagPosition(pos.x, pos.y);
}

/*
** 设置游戏的主角
*/
void GameController::setPlayer(Friend *pPlayer)
{
	mPlayer = pPlayer;
	mAttackingEntity = pPlayer;
	pPlayer->setActive(true);
	mEntityVec.push_back(pPlayer);
}

/*
** 加入一个友军
*/
void GameController::addFriend(Friend *pFriend)
{
	if(pFriend != mPlayer)
	{
		mFriendVec.push_back(pFriend);
		mEntityVec.push_back(pFriend);
	}
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
**判断collider是否和场景中的其他友军有冲突，有冲突则返回友军的指针，否则返回NULL
*/
Friend *GameController::conflictWithFriend(Friend *collider)
{
	CCPoint pos = collider->getTagPosition();

	for(int i=0; i<mFriendVec.size(); ++i)
	{
		if(mFriendVec[i] == collider) continue;
		CCPoint pos2 = mFriendVec[i]->getTagPosition();
		CCPoint dist = pos2 - pos;
		if(ccpLength(dist) <= FRIEND_SIZE)
			return mFriendVec[i];
	}
	return NULL;
}

/*
** 判断collider是否和场景中的怪物敌人有碰撞发生，如果有则返回该敌人的坐标，否则返回NULL
*/
Enermy *GameController::conflictWithEnermy(Friend *collider)
{
	CCPoint pos = collider->getTagPosition();

	for(int i=0; i<mEnermyVec.size(); ++i)
	{
		CCPoint pos2 = mEnermyVec[i]->getTagPosition();
		CCPoint dist = pos2 - pos;
		if(ccpLength(dist) <= FRIEND_SIZE)
			return mEnermyVec[i];
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
	if(pos.x < FRIEND_SIZE/2)
	{
		wallNormal.x = 1;
		wallNormal.y = 0;
	}
	else if(pos.y < FRIEND_SIZE/2)
	{
		wallNormal.x = 0;
		wallNormal.y = 1;
	}
	else if(pos.x > SCREEN_WIDTH - FRIEND_SIZE/2)
	{
		wallNormal.x = -1;
		wallNormal.y = 0;
	}
	else if(pos.y > SCREEN_HEIGHT - FRIEND_SIZE/2)
	{
		wallNormal.x = 0;
		wallNormal.y = -1;
	}
	else
		ret = false;

	return ret;
}

/*
** pAttackingEntity当前的攻击过程结束
** 此过程的判断较为复杂：
1. 若主角死亡，则游戏结束；
2. 如果所有的敌人死亡，则胜利，进入下一个场景（关卡）；
3. 否则选择下一个Entity进行下一轮的攻击；
4. 如果下一个攻击的对象是怪物，则进行自动攻击
*/
void GameController::leaveFromAttacking(Entity *pAttackingEntity)
{
	// 1 游戏结束
	// 2 进入下一个关卡
	// 3 选择下一个Entity进入攻击状态
	int index = 0;
	for(int i=0; i<mEntityVec.size(); ++i)
	{
		if(pAttackingEntity == mEntityVec[i]) index = i;
	}
	index = (index+1)%mEntityVec.size();

	while(mEntityVec[index]->dead()) index=(index+1)%mEntityVec.size();
	mAttackingEntity = mEntityVec[index];

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
}

/*
** 怪物发动攻击，主角和友军会同时受到攻击
** 1. 如果主角死亡，则游戏结束；
** 2. 如果其他友军死亡则播放死亡特效，然后将其隐藏；
*/
void  GameController::friendsAttacked(int hp)
{
	// 1
	// 2
	for(int i=0; i<mFriendVec.size(); ++i)
	{
		if(mFriendVec[i]->dead() == false)
		{
			mFriendVec[i]->underAttack(hp);
			// TODO: 判断是否造成死亡，死亡则将其隐藏
		}
	}
}

/*
** 触摸开始事件的处理，如果是自己或者友军在进行攻击，则创建一个箭头表示攻击方向
*/
bool GameController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(mIsAttacking) return true;

	mTouchBeginPos = mAttackingEntity->getTagPosition();
	//TODO: 判断当前是哪个选手在进行攻击，并且创建箭头
	//mpArrowSprite = CCSprite::create("arrow.jpg");
	//CCLayer::addChild(mpArrowSprite);
	//mpArrowSprite->setPosition(CCPoint(100, 100));

	return true;
}

/*
** 发生移动则旋转箭头
*/
void GameController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if(mIsAttacking) return;

	// 获取坐标
	CCPoint touchPos = pTouch->getLocationInView();
	touchPos = CCDirector::sharedDirector()->convertToGL(touchPos);

	//TODO:改变箭头方向 
}

void GameController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if(mIsAttacking) return;

	// 获取单击的坐标
	CCPoint touchPos = pTouch->getLocationInView();
	touchPos = CCDirector::sharedDirector()->convertToGL(touchPos);
	mTouchEndPos = touchPos;

	CCPoint dir = mTouchEndPos - mTouchBeginPos;
	dir = dir.normalize();
	dir.x *= ATTACK_SPEED;
	dir.y *= ATTACK_SPEED;
	mAttackingEntity->setAttackSpeed(dir.x, dir.y);
	mAttackingEntity->attack();

	mIsAttacking = true;
}

void GameController::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}
