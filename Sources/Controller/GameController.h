#ifndef _MINIGAME_GAME_CONTROLLER_H_
#define _MINIGAME_GAME_CONTROLLER_H_
#include "cocos2d.h"
#include <vector>

class Entity;
class Friend;
class Enermy;
class GameController : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(GameController);
	virtual bool init();
	virtual void update(float delta);

	void normalizePos(Entity *pEntity);

	void setPlayer(Friend *pPlayer);
	void addFriend(Friend *pFriend);
	void addEnermy(Enermy *pEnermy);

	Friend *conflictWithFriend(Friend *collider);
	Enermy *conflictWithEnermy(Friend *collider);
	bool conflictWithWall(Friend *collider, cocos2d::CCPoint &wallNormal);

	void setAttackingEntity(Entity *pEntity);
	void leaveFromAttacking(Entity *pAttackingEntity);

	void friendsAttacked(int hp);

	// 触屏事件处理函数
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

protected:
	Friend *mPlayer;						// 主角
	std::vector<Friend*> mFriendVec;		// 友军们
	std::vector<Enermy*> mEnermyVec;		// 敌人们
	std::vector<Entity*> mEntityVec;		// 所有参与的Entities
	Entity *mAttackingEntity;				// 当前正在进行攻击的Entity

private:
	int mSpeedX, mSpeedY;
	cocos2d::CCPoint mTouchBeginPos, mTouchEndPos;
	cocos2d::CCSprite *mpArrowSprite;
	bool mIsAttacking;			// 当前是否已经在进行攻击
};

#endif