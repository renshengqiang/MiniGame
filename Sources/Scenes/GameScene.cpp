#include "GameScene.h"
#include "Entity\Friend.h"
#include "Entity\Enermy.h"
#include "Controller\GameController.h"
#include "Utils.h"

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

	// 创建主角
	Friend *pFriend = new Friend("Friend.png");
	gameController->setPlayer(pFriend);
	pFriend->setScale(0.5f);
	pFriend->setAttack1Hurt(2*ATTACK_HURT);
	pFriend->setController(gameController);
	pFriend->health(2*FULL_HEALTH);
	addFriend(pFriend, CCPoint(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));

	// 创建2个Friends
	CCPoint pos[2];
	for(int i=0; i<2; ++i)
	{
		pos[i].x = visibleSize.width/4*(2*i+1);
		pos[i].y = 100;
	}

	for(int i=0; i<2; ++i)
	{
		Friend *pFriend = new Friend("Friend.png");
		pFriend->setScale(0.5);
		pFriend->setAttack1Hurt(ATTACK_HURT);
		pFriend->setController(gameController);
		pFriend->health(FULL_HEALTH);
		addFriend(pFriend, pos[i]);
	}

	// 创建二个敌人
	Enermy *pEnermy = new Enermy("Friend.png");
	CCPoint epos;
	pEnermy->setScale(0.5);
	pEnermy->setHp(100);
	pEnermy->setAttackHurt(ATTACK_HURT);
	pEnermy->setController(gameController);
	epos.y = SCREEN_HEIGHT-100; epos.x = visibleSize.width*0.25;
	addEnermy(pEnermy, epos);

	pEnermy = new Enermy("Friend.png");
	pEnermy->setScale(0.5);
	pEnermy->setHp(100);
	pEnermy->setAttackHurt(ATTACK_HURT);
	pEnermy->setController(gameController);
	epos.y = SCREEN_HEIGHT-100; epos.x = visibleSize.width*0.75;
	addEnermy(pEnermy, epos);
}

void GameScene::addFriend(Friend *pFriend, const CCPoint &pos)
{
	CCLayer::addChild(pFriend, 1);
	pFriend->setTagPosition(pos.x, pos.y);
	mFriendVec.push_back(pFriend);
}

void GameScene::addEnermy(Enermy *pEnermy, const CCPoint &pos)
{
	CCLayer::addChild(pEnermy, 1);
	pEnermy->setTagPosition(pos.x, pos.y);
	mEnermyVec.push_back(pEnermy);
}