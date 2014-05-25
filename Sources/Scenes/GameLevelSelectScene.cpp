#include "Scenes\GameLevelSelectScene.h"
#include "Scenes\ModeSelectScene.h"
#include "Scenes\GameScene.h"
#include "Scenes\HeroIntroScene.h"
using namespace cocos2d;

USING_NS_CC;

CCScene* GameLevelSelectScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameLevelSelectScene *layer = GameLevelSelectScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLevelSelectScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

	 CCMenuItemImage *pEnterItem_WX = CCMenuItemImage::create(
                                        "Yes.png",
                                        "YesSelected.png",
                                        this,
                                        menu_selector(GameLevelSelectScene::changescene));
    
	pEnterItem_WX->setPosition(ccp(origin.x + visibleSize.width/2-200,
                            origin.y + visibleSize.height/2-470));

    // create menu, it's an autorelease object
    CCMenu* pMenu_WX = CCMenu::create(pEnterItem_WX, NULL);
    pMenu_WX->setPosition(CCPointZero);
    this->addChild(pMenu_WX, 1);

	CCMenuItemImage *pEnterItem_QQ = CCMenuItemImage::create(
                                        "Return.png",
                                        "ReturnSelected.png",
                                        this,
                                        menu_selector(GameLevelSelectScene::changescene2HeroSelect));
    
	pEnterItem_QQ->setPosition(ccp(origin.x + visibleSize.width/2+200,
                            origin.y + visibleSize.height/2-470));
    // create menu, it's an autorelease object
    CCMenu* pMenu_QQ = CCMenu::create(pEnterItem_QQ, NULL);
    pMenu_QQ->setPosition(CCPointZero);
    this->addChild(pMenu_QQ, 1);

	CCMenuItemImage *pEnterItem_G = CCMenuItemImage::create(
                                        "guanka3.png",
                                        "guanka3.png",
                                        this,
                                       0);
    
	pEnterItem_G->setPosition(ccp(origin.x + visibleSize.width/2+265,
                            origin.y + visibleSize.height/2-20));
    // create menu, it's an autorelease object
    CCMenu* pMenu_G = CCMenu::create(pEnterItem_G, NULL);
    pMenu_G->setPosition(CCPointZero);
    this->addChild(pMenu_G, 1);

    /////////////////////////////
    // 3. add your codes below...

	
    // add "HelloWorld" splash screen"

	CCSize mysize=CCDirector::sharedDirector()->getWinSize();
	
	CCSprite* sp = CCSprite::create("FriendsRankBG.png");
	sp->setPosition(ccp(mysize.width/2, mysize.height/2));
	//设置不同颜色区分
	sp->setColor(ccc3(100,100,100));
	this->addChild(sp, 0);

	CCSprite* sp1 = CCSprite::create("FriendsRank.png");
	sp1->setPosition(ccp(mysize.width/2-120, mysize.height/2+180));
	this->addChild(sp1, 2);


	CCSprite* sp2 = CCSprite::create("xuanguan_new.png");
	sp2->setPosition(ccp(mysize.width/2+80, mysize.height/2+100));
	this->addChild(sp2, 2);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("IntroBGMusic.mp3", true);

    return true;
}


void GameLevelSelectScene::changescene(CCObject* pSender){
	//新建一个GameScene的scene
	CCScene * scene2=GameScene::scene();
	CCTransitionScene * s3=CCTransitionFade::create(1,scene2);
	CCDirector::sharedDirector()->replaceScene(s3);
}

void GameLevelSelectScene::changescene2HeroSelect(CCObject* pSender){
	//新建一个HeroIntroScene的scene
	CCScene * scene2=HeroIntroScene::scene();
	CCTransitionScene * s3=CCTransitionFade::create(1,scene2);
	CCDirector::sharedDirector()->replaceScene(s3);
}

void GameLevelSelectScene::onEnter(){
    CCLayer::onEnter();
}

void GameLevelSelectScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
}

void GameLevelSelectScene::onExit(){
    CCLayer::onExit();
}

void GameLevelSelectScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
