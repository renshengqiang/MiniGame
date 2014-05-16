#include "GameScene.h"
#include "Entity\Friend.h"
#include "Entity\Enermy.h"
#include "Controller\GameController.h"
#include "Utils.h"

USING_NS_CC;
using namespace cocos2d::extension;
using namespace std;

bool GameScene::init()
{
	initBackground();
	initPlayer();
	//initWidget();
	return true;
}

CCScene* GameScene::scene()
{
	CCScene *mapScene = CCScene::create();
	GameScene *layer = GameScene::create();
	mapScene->addChild(layer);
	return mapScene;
}

void GameScene::initWidget()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	/*创建标题和背景图片*/
	CCLabelTTF *title = CCLabelTTF::create("1", "Arial", 35);
	CCScale9Sprite *pNormalBg = CCScale9Sprite::create("particles.png");
	//CCScale9Sprite *pLightBg = CCScale9Sprite::create("buttonHighlighted.png");

	/*创建按钮*/
	CCControlButton *pJumpButton = CCControlButton::create(title, pNormalBg);
	pJumpButton->setPosition(60, 60);
	//pJumpButton->setBackgroundSpriteForState(pLightBg, CCControlStateHighlighted);

	/*添加按钮事件*/
	//pJumpButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScene::onButtonClicked), CCControlEventTouchDown);
	CCLayer::addChild(pJumpButton);


	title = CCLabelTTF::create("2", "Arial", 35);
	pNormalBg = CCScale9Sprite::create("particles.png");
	pJumpButton = CCControlButton::create(title, pNormalBg);
	pJumpButton->setPosition(180, 60);
	CCLayer::addChild(pJumpButton);

	title = CCLabelTTF::create("3", "Arial", 35);
	pNormalBg = CCScale9Sprite::create("particles.png");
	pJumpButton = CCControlButton::create(title, pNormalBg);
	pJumpButton->setPosition(300, 60);
	CCLayer::addChild(pJumpButton);

	title = CCLabelTTF::create("4", "Arial", 35);
	pNormalBg = CCScale9Sprite::create("particles.png");
	pJumpButton = CCControlButton::create(title, pNormalBg);
	pJumpButton->setPosition(420, 60);
	CCLayer::addChild(pJumpButton);	
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
	pFriend->setAttack2Hurt(ATTACK_HURT);
	pFriend->setController(gameController);
	pFriend->health(2*FULL_HEALTH);
	addFriend(pFriend, CCPoint(SCREEN_WIDTH/6, FRIEND_SIZE));
	//addFriend(pFriend, CCPoint(SCREEN_WIDTH/2, (SCREEN_HEIGHT-WIDGET_SIZE)/2+WIDGET_SIZE));

	// 创建2个Friends
	CCPoint pos[2];
	for(int i=0; i<2; ++i)
	{
		pos[i].x = visibleSize.width/6*(2*i+3);
		pos[i].y = FRIEND_SIZE;
	}

	for(int i=0; i<2; ++i)
	{
		Friend *pFriend = new Friend("Friend.png");
		pFriend->setScale(0.5);
		pFriend->setAttack1Hurt(ATTACK_HURT);
		pFriend->setAttack2Hurt(ATTACK_HURT);
		pFriend->setController(gameController);
		pFriend->health(FULL_HEALTH);
		addFriend(pFriend, pos[i]);
	}

	// 创建二个敌人
	Enermy *pEnermy = new Enermy("Enermy1.png");
	CCPoint epos;
	pEnermy->setScale(0.5);
	pEnermy->setHp(100);
	pEnermy->setAttackHurt(ATTACK_HURT);
	pEnermy->setController(gameController);
	epos.y = SCREEN_HEIGHT-100; epos.x = visibleSize.width*0.25;
	addEnermy(pEnermy, epos);

	pEnermy = new Enermy("Enermy2.png");
	pEnermy->setScale(0.5);
	pEnermy->setHp(100);
	pEnermy->setAttackHurt(ATTACK_HURT);
	pEnermy->setController(gameController);
	epos.y = SCREEN_HEIGHT-100; epos.x = visibleSize.width*0.75;
	addEnermy(pEnermy, epos);
}

void GameScene::addFriend(Friend *pFriend, const CCPoint &pos)
{
	CCLayer::addChild(pFriend, 2);
	pFriend->setTagPosition(pos.x, pos.y);
	mFriendVec.push_back(pFriend);
}

void GameScene::addEnermy(Enermy *pEnermy, const CCPoint &pos)
{
	CCLayer::addChild(pEnermy, 2);
	pEnermy->setTagPosition(pos.x, pos.y);
	mEnermyVec.push_back(pEnermy);
}

void GameScene::onButtonClicked(CCObject *pSender, CCControlEvent event)
{
}