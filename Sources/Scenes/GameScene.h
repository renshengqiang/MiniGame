#ifndef _MINIGAME_GAME_SCENE_H_
#define _MINIGAME_GAME_SCENE_H_
#include "cocos2d.h"
#include <vector>

class Friend;
class Enermy;
class GameScene : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(GameScene);
	virtual bool init();
	static cocos2d::CCScene* scene();

private:
	void initBackground();
	void initPlayer();
	void addFriend(Friend *pFriend, const cocos2d::CCPoint &pos);
	void addEnermy(Enermy *pEnermy, const cocos2d::CCPoint &pos);
private:
	cocos2d::CCSprite *mBGsprite;	 // ±³¾°
	std::vector<Friend*> mFriendVec; // ÓÑ¾ü
	std::vector<Enermy*> mEnermyVec; // µÐÈË
};


#endif