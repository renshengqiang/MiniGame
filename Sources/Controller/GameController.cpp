#include "GameController.h"
#include "Entity\Friend.h"
#include "Entity\Enermy.h"
#include "Scenes\WinScene.h"
#include "Scenes\GameScene.h"
#include "Utils.h"

USING_NS_CC;

bool GameController::init()
{

	CCLayer::setTouchEnabled(true);		// ����������
	CCLayer::scheduleUpdate();			// ����update����

	mAttackingEntity = NULL;
	mIsAttacking = false;
	mAttackingFriendCnt = 0;
	mpArrowSprite = NULL;
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

	if(pos.y < FRIEND_SIZE/2 + WIDGET_HEIGHT)
	{
		pos.y = FRIEND_SIZE/2 + WIDGET_HEIGHT;
	}
	else if(pos.y > SCREEN_HEIGHT - FRIEND_SIZE/2)
	{
		pos.y = SCREEN_HEIGHT - FRIEND_SIZE/2;
	}
	pEntity->setTagPosition(pos.x, pos.y);
}

/*
** ����һ���Ѿ�
*/
void GameController::addFriend(Friend *pFriend)
{
	mFriendVec.push_back(pFriend);
	mEntityVec.push_back(pFriend);
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
		if(mFriendVec[i]->dead()) continue;
		CCPoint pos2 = mFriendVec[i]->getTagPosition();
		CCPoint dist = pos2 - pos;
		if(ccpLength(dist) <= FRIEND_SIZE)
			return mFriendVec[i];
	}

	return NULL;
}

/*
** �ж�collider�Ƿ�ͳ����еĹ����������ײ������������򷵻ظõ��ˣ����򷵻�NULL
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

		if(ccpLength(dist) <= FRIEND_SIZE)
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
	else if(pos.y < FRIEND_SIZE/2+WIDGET_HEIGHT)
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

void GameController::setAttackingEntity(Entity *pEntity)
{
	mAttackingEntity = pEntity;
	mAttackingEntity->setActive(true);

	// ��һ�ֹ�����ʼ��������־λ��λ
	for(int i=0; i<mFriendVec.size(); ++i)
	{
		mFriendVec[i]->setTiggleFlag(false);
	}
}

/*
** pAttackingEntity��ǰ�Ĺ������̽���
** �˹��̵��жϽ�Ϊ���ӣ�
1. ����������������Ϸ������
2. ������еĵ�����������ʤ����������һ���������ؿ�����
3. ����ѡ����һ��Entity������һ�ֵĹ�����
4. �����һ�������Ķ����ǹ��������Զ�����
5. �������鼼�ܵı�־λΪfalse
*/
void GameController::leaveFromAttacking(Entity *pAttackingEntity)
{
	if(mAttackingFriendCnt > 0) return;

	// 1 ��Ϸ����
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
	}


	// 2 ������һ���ؿ�
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
			return;
		}
	}

	// 3 ѡ����һ��Entity���빥��״̬
	int index = 0;
	for(int i=0; i<mEntityVec.size(); ++i)
	{
		if(pAttackingEntity == mEntityVec[i]) index = i;
	}
	index = (index+1)%mEntityVec.size();

	while(mEntityVec[index]->dead()) index=(index+1)%mEntityVec.size();
	mAttackingEntity = mEntityVec[index];

	// ����Ϊ����״̬��������Զ���������������Զ�����
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
	
	// ��һ�ֹ�����ʼ��������־λ��λ
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
/*
** ���﷢�����������Ǻ��Ѿ���ͬʱ�ܵ�����
** 1. �����������������Ϸ������
** 2. ��������Ѿ������򲥷�������Ч��Ȼ�������أ�
*/
void  GameController::friendsAttacked(int hp)
{
	// ���Ѿ�ִ���˺�����
	for(int i=0; i<mFriendVec.size(); ++i)
	{
		if(mFriendVec[i]->dead() == false)
		{
			mFriendVec[i]->underAttack(hp);
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
		// TODO:����Ҫ�ж������Ƿ��Ѿ�������������������ֱ�ӵ��ý�������
	}
}

/*
** ���pEnermy��Ϊ�գ������pEnermy��underAttack�����ܵ�����
** ���pEnermyΪ�գ�������е�pEnermy����underAttack����
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
** �����ǰ�ֵ�����Enermy
*/
void GameController::clearEnermy()
{
	mEnermyVec.clear();
}

/*
** �����¹ؿ�
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

	// ��һ�ֹ�����ʼ��������־λ��λ
	for(int i=0; i<mFriendVec.size(); ++i)
	{
		mFriendVec[i]->setTiggleFlag(false);
		mFriendVec[i]->setActive(false);
	}
}

/*
** ������ʼ�¼��Ĵ���������Լ������Ѿ��ڽ��й������򴴽�һ����ͷ��ʾ��������
*/
bool GameController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(mIsAttacking) return true;
	// ��ȡ����
	CCPoint touchPos = pTouch->getLocationInView();
	touchPos = CCDirector::sharedDirector()->convertToGL(touchPos);
	mTouchBeginPos = touchPos;

	if(mTouchBeginPos.y < WIDGET_HEIGHT) return true;
	//TODO: �жϵ�ǰ���ĸ�ѡ���ڽ��й��������Ҵ�����ͷ
	mpArrowSprite = CCSprite::create("arrow.png");
	//mpArrowSprite->setScaleX(2.0f);
	CCLayer::addChild(mpArrowSprite);
	mpArrowSprite->setPosition(mAttackingEntity->getTagPosition());

	return true;
}

float _calcRatio(CCPoint delta)
{
	CCPoint max = CCPoint(SCREEN_WIDTH, SCREEN_HEIGHT);
	return delta.getLength()/max.getLength();
}

/*
** �����ƶ�����ת��ͷ
*/
void GameController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if(mIsAttacking) return;
	if(mpArrowSprite == NULL) return;

	// ��ȡ����
	CCPoint touchPos = pTouch->getLocationInView();
	touchPos = CCDirector::sharedDirector()->convertToGL(touchPos);
	mTouchEndPos = touchPos;

	//TODO:�ı��ͷ���� 
	CCPoint delta = mTouchBeginPos - touchPos;
	float angle = delta.getAngle(CCPoint(1,0));
	float ratio = _calcRatio(delta);
	if(mpArrowSprite)
	{
		mpArrowSprite->setRotation(angle*180/M_PI);
		mpArrowSprite->setScaleX(3*ratio+1);
	}
}

void GameController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if(mIsAttacking) return;
	if(mpArrowSprite == NULL) return;

	Friend *pAttackingFriend = dynamic_cast<Friend*>(mAttackingEntity);
	if(pAttackingFriend == NULL) return;

	// �ͷż�ͷ
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
}

void GameController::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}
