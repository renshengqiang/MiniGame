#include "GameScene.h"
#include "Entity\Friend.h"
#include "Entity\Enermy.h"
#include "Controller\GameController.h"

USING_NS_CC;
using namespace std;

bool GameScene::init()
{
	initBackground();
	initPlayer();
	return true;
}

CCScene* GameScene::scene()
{
	CCScene *mapScene = CCScene::create();
	GameScene *layer = GameScene::create();
	mapScene->addChild(layer);
	return mapScene;
}

void GameScene::initBackground()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	mBGsprite = CCSprite::create("GameBG.png");
	mBGsprite->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	CCLayer::addChild(mBGsprite, 0);
}

void GameScene::initPlayer()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	
	// 创建Controller
	GameController *gameController = GameController::create();
	CCLayer::addChild(gameController);

	// 创建Friend
	CCPoint pos[4];
	for(int i=0; i<3; ++i)
	{
		pos[i].x = visibleSize.width/6*(2*i+1);
		pos[i].y = 100;
	}

	for(int i=0; i<3; ++i)
	{
		Friend *pFriend = new Friend("Friend.png");
		pFriend->setScale(0.5);
		pFriend->setController(gameController);
		pFriend->health(100);
		addFriend(pFriend, pos[i]);
		if(0 == i)
		{
			pFriend->setActive(true);
			gameController->setAttackingFriend(pFriend);
		}
	}

	// 创建二个敌人
	Enermy *pEnermy = new Enermy("Friend.png");
	CCPoint epos;
	pEnermy->setScale(0.5);
	pEnermy->setHp(100);
	pEnermy->setController(gameController);
	epos.y = 400; epos.x = visibleSize.width*0.25;
	addEnermy(pEnermy, epos);

	pEnermy = new Enermy("Friend.png");
	pEnermy->setScale(0.5);
	pEnermy->setHp(100);
	pEnermy->setController(gameController);
	epos.y = 400; epos.x = visibleSize.width*0.75;
	addEnermy(pEnermy, epos);
}

void GameScene::addFriend(Friend *pFriend, const CCPoint &pos)
{
	CCLayer::addChild(pFriend);
	pFriend->setTagPosition(pos.x, pos.y);
	mFriendVec.push_back(pFriend);
}

void GameScene::addEnermy(Enermy *pEnermy, const CCPoint &pos)
{
	CCLayer::addChild(pEnermy);
	pEnermy->setTagPosition(pos.x, pos.y);
	mEnermyVec.push_back(pEnermy);
}