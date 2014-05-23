#ifndef _MINIGAME_GAME_SCENE_H_
#define _MINIGAME_GAME_SCENE_H_
#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>

class Friend;
class Entity;
class Enermy;
class GameController;
class Toolbar;
class Statusbar;
class GameScene : public cocos2d::CCLayer
{
	friend class GameController;
public:
	GameScene();
	CREATE_FUNC(GameScene);
	virtual bool init();
	static cocos2d::CCScene* scene();

private:
	void initBackground();
	void initPlayer();
	void initWidget();
	void increaseLevel();
	void initLevel2();
	void initLevel3();
	void addFriend(Friend *pFriend, const cocos2d::CCPoint &pos);
	void addEnermy(Enermy *pEnermy, const cocos2d::CCPoint &pos);
	void moveEnd();

private:
	cocos2d::CCNode *mBGParent;		 //背景的父节点
	cocos2d::CCSprite *mBGsprite;	 // 背景
	cocos2d::CCSprite *mBGsprite2;	 // 切换等级背景图片
	std::vector<Friend*> mFriendVec; // 友军
	std::vector<Enermy*> mEnermyVec; // 敌人
	int mLevel;						 // 目前的游戏等级
	GameController *mGameController; // 游戏控制器
	Toolbar *mToolbar;
	Statusbar *mStatusbar;
};


#endif