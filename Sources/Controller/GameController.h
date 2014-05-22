#ifndef _MINIGAME_GAME_CONTROLLER_H_
#define _MINIGAME_GAME_CONTROLLER_H_
#include "cocos2d.h"
#include <vector>

class Entity;
class Friend;
class Enermy;
class Toolbar;
class GameController : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(GameController);
	virtual bool init();
	virtual void update(float delta);

	void normalizePos(Entity *pEntity);

	void addFriend(Friend *pFriend);
	void addEnermy(Enermy *pEnermy);

	Friend *getOneAttackedFriend();
	Friend *conflictWithFriend(Friend *collider);
	Enermy *conflictWithEnermy(Friend *collider);
	bool conflictWithWall(Friend *collider, cocos2d::CCPoint &wallNormal);

	void setAttackingEntity(Entity *pEntity);
	void leaveFromAttacking(Entity *pAttackingEntity);
	void addAttackingFriend();
	void removeAttackingFriend();
	void addAttackedEnermy();
	void removeAttackedEnermy();

	void friendsAttacked(Friend *pFriend,int hp);
	void enermyAttacked(Enermy *pEnermy, int hp);
	void enermyAttackedByLaser(Friend *pFriend, int hp);
	void enermyAttacked(Friend *pFriend, float dis, int hp);

	void clearEnermy();
	void resetNewLevel();

	void setToolbar(Toolbar *pToolbar) { mToolbar = pToolbar; }
	// �����¼�������
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

protected:
	std::vector<Friend*> mFriendVec;		// �Ѿ���
	std::vector<Enermy*> mEnermyVec;		// ������
	std::vector<Entity*> mEntityVec;		// ���в����Entities
	Entity *mAttackingEntity;				// ��ǰ���ڽ��й�����Entity
	int mAttackingFriendCnt;				// ���ڹ������Ѿ�����
	int mAttackedEnermyCnt;				// �����ܹ����ĵо�����

private:
	int mSpeedX, mSpeedY;
	cocos2d::CCPoint mTouchBeginPos, mTouchEndPos;
	cocos2d::CCSprite *mpArrowSprite;
	bool mIsAttacking;			// ��ǰ�Ƿ��Ѿ��ڽ��й���
	bool mIsFingerDown;			// ���ڽ�ֹ��㴥��
	Toolbar *mToolbar;			// ������
};

#endif