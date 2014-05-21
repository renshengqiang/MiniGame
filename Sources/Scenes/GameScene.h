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

	void onButton1(CCObject *pSender);
	void onButton2(CCObject *pSender);
	void onButton3(CCObject *pSender);
	void onButton4(CCObject *pSender);
private:
	cocos2d::CCNode *mBGParent;		 //�����ĸ��ڵ�
	cocos2d::CCSprite *mBGsprite;	 // ����
	cocos2d::CCSprite *mBGsprite2;	 // �л��ȼ�����ͼƬ
	std::vector<Friend*> mFriendVec; // �Ѿ�
	std::vector<Enermy*> mEnermyVec; // ����
	int mLevel;						 // Ŀǰ����Ϸ�ȼ�
	GameController *mGameController; // ��Ϸ������
	Toolbar *mToolbar;
};


#endif