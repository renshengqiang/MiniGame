#include "GameController.h"
#include "Entity\Friend.h"
#include "Entity\Enermy.h"
#include "Utils.h"

USING_NS_CC;

bool GameController::init()
{

	CCLayer::setTouchEnabled(true);		// ����������
	CCLayer::scheduleUpdate();			// ����update����

	mAttackingEntity = NULL;
	mIsAttacking = false;
	return true;
}

void GameController::update(float delta)
{

}

/*
** �淶��pEntity�����꣬ʹ������Ļ��Χ�� 
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
** ������Ϸ������
*/
void GameController::setPlayer(Friend *pPlayer)
{
	mPlayer = pPlayer;
	mAttackingEntity = pPlayer;
	pPlayer->setActive(true);
	mEntityVec.push_back(pPlayer);
}

/*
** ����һ���Ѿ�
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
** ����һ���������
*/
void GameController::addEnermy(Enermy *pEnermy)
{
	mEnermyVec.push_back(pEnermy);
	mEntityVec.push_back(pEnermy);
}

/*
**�ж�collider�Ƿ�ͳ����е������Ѿ��г�ͻ���г�ͻ�򷵻��Ѿ���ָ�룬���򷵻�NULL
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
** �ж�collider�Ƿ�ͳ����еĹ����������ײ������������򷵻ظõ��˵����꣬���򷵻�NULL
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
** �ж�collider�Ƿ�͵�ǰ������ǽ��������ײ������true���ʾ��������ײ�������ʾû����ײ
** ������ײ����wallNormall�з���ǽ�ڵķ�������
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
** pAttackingEntity��ǰ�Ĺ������̽���
** �˹��̵��жϽ�Ϊ���ӣ�
1. ����������������Ϸ������
2. ������еĵ�����������ʤ����������һ���������ؿ�����
3. ����ѡ����һ��Entity������һ�ֵĹ�����
4. �����һ�������Ķ����ǹ��������Զ�����
*/
void GameController::leaveFromAttacking(Entity *pAttackingEntity)
{
	// 1 ��Ϸ����
	// 2 ������һ���ؿ�
	// 3 ѡ����һ��Entity���빥��״̬
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
** ���﷢�����������Ǻ��Ѿ���ͬʱ�ܵ�����
** 1. �����������������Ϸ������
** 2. ��������Ѿ������򲥷�������Ч��Ȼ�������أ�
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
			// TODO: �ж��Ƿ����������������������
		}
	}
}

/*
** ������ʼ�¼��Ĵ���������Լ������Ѿ��ڽ��й������򴴽�һ����ͷ��ʾ��������
*/
bool GameController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(mIsAttacking) return true;

	mTouchBeginPos = mAttackingEntity->getTagPosition();
	//TODO: �жϵ�ǰ���ĸ�ѡ���ڽ��й��������Ҵ�����ͷ
	//mpArrowSprite = CCSprite::create("arrow.jpg");
	//CCLayer::addChild(mpArrowSprite);
	//mpArrowSprite->setPosition(CCPoint(100, 100));

	return true;
}

/*
** �����ƶ�����ת��ͷ
*/
void GameController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if(mIsAttacking) return;

	// ��ȡ����
	CCPoint touchPos = pTouch->getLocationInView();
	touchPos = CCDirector::sharedDirector()->convertToGL(touchPos);

	//TODO:�ı��ͷ���� 
}

void GameController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if(mIsAttacking) return;

	// ��ȡ����������
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
