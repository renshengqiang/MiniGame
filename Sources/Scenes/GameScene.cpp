#include "GameScene.h"
#include "Entity\Friend.h"
#include "Entity\Enermy.h"
#include "Controller\GameController.h"
#include "Scenes\PauseScene.h"
#include "Scenes\CombatResultsScene.h"
#include "UI\Toolbar.h"
#include "UI\Statusbar.h"
#include "Effects\AnimationUtil.h"
#include "Utils.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace cocos2d::extension;
using namespace std;

GameScene::GameScene():
	mBGParent(NULL),
	mBGsprite(NULL),
	mBGsprite2(NULL)
{
}

bool GameScene::init()
{
	initWidget();
	initBackground();
	initPlayer();
	mLevel = 1;
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("FightBGMusic.mp3", true);

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

	CCSprite *showSprite = CCSprite::create("show.png");
	this->addChild(showSprite, 5);
	showSprite->setPosition(ccp(SCREEN_WIDTH/2, WIDGET_HEIGHT/2));

	CCMenuItemImage *pPauseMenuItem = CCMenuItemImage::create(
                                        "stop.png",
                                        "start.png",
                                        this,
										menu_selector(GameScene::onPause));
    
	pPauseMenuItem->setPosition(ccp(visibleSize.width-50, visibleSize.height-50));
	pPauseMenu = CCMenu::create(pPauseMenuItem, NULL);
    pPauseMenu->setPosition(CCPointZero);
    this->addChild(pPauseMenu, 5);
}

void GameScene::onPause(cocos2d::CCObject *pSender)
{
	pPauseMenu->setVisible(false);
	CCRenderTexture *renderTexture = CCRenderTexture::create(SCREEN_WIDTH, SCREEN_HEIGHT);
    renderTexture->begin();
    this->getParent()->visit();
    renderTexture->end();  //这里实际是通过CCRenderTexture保存当前界面（相当于截屏），然后传递给暂停界面，当成背景精灵
	pPauseMenu->setVisible(true);
    CCDirector::sharedDirector()->pushScene(PauseScene::scene(renderTexture,true));
}

void GameScene::initBackground()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	mBGParent = CCNode::create();
	CCLayer::addChild(mBGParent, 0);
	mBGParent->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	mBGsprite = CCSprite::create("GameBG.png");
	mBGsprite->setPosition(ccp(0, 0));
	mBGParent->addChild(mBGsprite, 0);
}

void GameScene::initPlayer()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	
	// 创建Controller
	mGameController = GameController::create();
	CCLayer::addChild(mGameController);

	// 创建2个Friends
	CCPoint pos[3];
	char *friendFileName[3] = {"Hero.png", "Friend1.png", "Friend2.png"};
	for(int i=0; i<3; ++i)
	{
		pos[i].x = visibleSize.width/6*(2*i+1);
		pos[i].y = FRIEND_SIZE +400;
	}

	for(int i=0; i<3; ++i)
	{
		Friend *pFriend = new Friend(friendFileName[i]);
		addFriend(pFriend, pos[i]);
		pFriend->increaseLevel();
		pFriend->setSize(FRIEND_RADIUS);
		pFriend->setController(mGameController);
	}
	mGameController->setAttackingEntity(mFriendVec[0]);
	mFriendVec[1]->increaseLevel();
	mFriendVec[2]->increaseLevel();
	mFriendVec[2]->increaseLevel();


	// 创建二个敌人
	Enermy *pEnermy = new Enermy("Enermy1.png");
	CCPoint epos;
	pEnermy->setHp(200);
	pEnermy->setType(1);
	pEnermy->setAttackHurt(30);
	pEnermy->setSize(ENERMY1_RADIUS);
	pEnermy->setController(mGameController);
	epos.y = visibleSize.height-480; epos.x = visibleSize.width*0.25;
	addEnermy(pEnermy, epos);

	pEnermy = new Enermy("Enermy2.png");
	pEnermy->setHp(200);
	pEnermy->setSize(ENERMY2_RADIUS);
	pEnermy->setAttackHurt(40);
	pEnermy->setType(2);
	pEnermy->setController(mGameController);
	epos.y = visibleSize.height-480; epos.x = visibleSize.width*0.75;
	addEnermy(pEnermy, epos);
}

void GameScene::addFriend(Friend *pFriend, const CCPoint &pos)
{
	CCLayer::addChild(pFriend, 3);
	pFriend->setTagPosition(pos.x, pos.y);
	mFriendVec.push_back(pFriend);
}

void GameScene::addEnermy(Enermy *pEnermy, const CCPoint &pos)
{
	this->addChild(pEnermy, 2);
	pEnermy->setTagPosition(pos.x, pos.y);
	mEnermyVec.push_back(pEnermy);
}

void GameScene::increaseLevel()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	if(1 == mLevel)			//从一级升到二级
	{
		mBGsprite2 = CCSprite::create("GameBG.png");
		mBGParent->addChild(mBGsprite2, 0);
		mBGsprite2->setPosition(ccp(0, visibleSize.height));
		initLevel2();
		CCMoveBy *pMoveTo = CCMoveBy::create(2.0f, ccp(0, -visibleSize.height));
		CCCallFunc *pCallFunc = CCCallFunc::create(this, callfunc_selector(GameScene::moveEnd));
		CCSequence *pAction = CCSequence::create(pMoveTo, pCallFunc, NULL);
		mBGParent->runAction(pAction);
		mLevel = 2;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("BeginAttack.wav");
	}
	else if(2 == mLevel)
	{
		mBGsprite2 = CCSprite::create("GameBG.png");
		mBGParent->addChild(mBGsprite2, 0);
		mBGsprite2->setPosition(ccp(0, 2*visibleSize.height));

		initLevel3();
		CCMoveBy *pMoveTo = CCMoveBy::create(2.0f, ccp(0, -visibleSize.height));
		CCCallFunc *pCallFunc = CCCallFunc::create(this, callfunc_selector(GameScene::moveEnd));
		CCSequence *pAction = CCSequence::create(pMoveTo, pCallFunc, NULL);
		mBGParent->runAction(pAction);
		mLevel = 3;

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("BossAccur.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("BossBGMusic.wav", true);
	}
	else
	{
		CCScene *pScene = CombatResultsScene::scene();
		CCDirector::sharedDirector()->replaceScene(pScene);
		
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("GameSuccess.mp3", true);
	}

	int i;
	for(i=0; i<mFriendVec.size(); ++i)
	{
		if(mFriendVec[i]->dead() == false)
			break;
	}
	mGameController->setAttackingEntity(mFriendVec[i]);
}

void GameScene::initLevel2()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	// 通知contrller清理Enermy
	mGameController->clearEnermy();

	// 自己清理Enermy
	for(unsigned i=0; i<mEnermyVec.size(); ++i)
	{
		mEnermyVec[i]->getParent()->removeChild(mEnermyVec[i]);
	}
	mEnermyVec.clear();

	// 创建新的Enermy
	Enermy *pEnermy = new Enermy("Enermy1.png");
	CCPoint epos;
	pEnermy->setHp(800);
	pEnermy->setAttackHurt(30);
	pEnermy->setType(1);
	pEnermy->setSize(ENERMY1_RADIUS);
	pEnermy->setController(mGameController);
	epos.y = 2*visibleSize.height-480; epos.x = visibleSize.width*(1.0/6);
	addEnermy(pEnermy, epos);
	CCMoveBy *pMoveTo1 = CCMoveBy::create(2.0f, ccp(0, -visibleSize.height));
	pEnermy->runAction(pMoveTo1);

	pEnermy = new Enermy("Enermy2.png");
	pEnermy->setHp(800);
	pEnermy->setAttackHurt(60);
	pEnermy->setType(2);
	pEnermy->setSize(ENERMY2_RADIUS);
	pEnermy->setController(mGameController);
	epos.y = 2*visibleSize.height-670; epos.x = visibleSize.width*(3.0/6);
	addEnermy(pEnermy, epos);
	CCMoveBy *pMoveTo2 = CCMoveBy::create(2.0f, ccp(0, -visibleSize.height));
	pEnermy->runAction(pMoveTo2);

	pEnermy = new Enermy("Enermy1.png");
	pEnermy->setHp(800);
	pEnermy->setAttackHurt(30);
	pEnermy->setType(1);
	pEnermy->setSize(ENERMY1_RADIUS);
	pEnermy->setController(mGameController);
	epos.y = 2*visibleSize.height-480; epos.x = visibleSize.width*(5.0/6);
	addEnermy(pEnermy, epos);
	CCMoveBy *pMoveTo3 = CCMoveBy::create(2.0f, ccp(0, -visibleSize.height));
	pEnermy->runAction(pMoveTo3);

	// 设置从Player重新开始
	mGameController->resetNewLevel();
}

void GameScene::initLevel3()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	// 通知contrller清理Enermy
	mGameController->clearEnermy();

	// 自己清理Enermy
	for(unsigned i=0; i<mEnermyVec.size(); ++i)
	{
		mEnermyVec[i]->getParent()->removeChild(mEnermyVec[i]);
	}
	mEnermyVec.clear();

	
	CCPoint epos;
	Enermy *pEnermy = new Enermy("Boss.png");
	pEnermy->setHp(2000);
	pEnermy->setAttackHurt(100);
	pEnermy->setType(3);
	pEnermy->setSize(BOSS_RADIUS);
	pEnermy->setController(mGameController);
	epos.y = 2*visibleSize.height-480; epos.x = visibleSize.width*(3.0/6);
	addEnermy(pEnermy, epos);
	CCMoveBy *pMoveTo = CCMoveBy::create(2.0f, ccp(0, -visibleSize.height));
	pEnermy->runAction(pMoveTo);

	// 设置从Player重新开始
	mGameController->resetNewLevel();
}

void GameScene::moveEnd()
{
	//删除原来的背景
	if(mBGsprite)
	{
		mBGsprite->removeFromParentAndCleanup(true);
		mBGsprite = mBGsprite2;
		mBGsprite2 = NULL;
	}
}