#include "Scenes\CombatResultsScene.h"
#include "Scenes\ModeSelectScene.h"
#include "Scenes\GameLevelSelectScene.h"
#include "Utils.h"
using namespace cocos2d;

USING_NS_CC;

CCScene* CombatResultsScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    CombatResultsScene *layer = CombatResultsScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CombatResultsScene::init()
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
                                        "Continue.png",
                                        "ContinueSelected.png",
                                        this,
                                        menu_selector(CombatResultsScene::changescene));
    
	pEnterItem_WX->setPosition(ccp(origin.x + visibleSize.width/2-130,
                            origin.y + visibleSize.height/2-100));

    // create menu, it's an autorelease object
    CCMenu* pMenu_WX = CCMenu::create(pEnterItem_WX, NULL);
    pMenu_WX->setPosition(CCPointZero);
    this->addChild(pMenu_WX, 1);

	CCMenuItemImage *pEnterItem_SH = CCMenuItemImage::create(
                                        "Share.png",
                                        "ShareSelected.png",
                                        this,
                                        0);
    
	pEnterItem_SH->setPosition(ccp(origin.x + visibleSize.width/2+130,
                            origin.y + visibleSize.height/2-100));

    // create menu, it's an autorelease object
    CCMenu* pMenu_SH = CCMenu::create(pEnterItem_SH, NULL);
    pMenu_SH->setPosition(CCPointZero);
    this->addChild(pMenu_SH, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("BattleResultSuccess.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);


	//CCSprite* pSprite1 = CCSprite::create("show.png");

 //   pSprite1->setPosition(ccp(SCREEN_WIDTH/2, WIDGET_HEIGHT/2));

 //   this->addChild(pSprite1, 0);

    return true;
}


void CombatResultsScene::changescene(CCObject* pSender){
	//新建一个GameLevelSelectScene的scene
	CCScene * scene2=GameLevelSelectScene::scene();
	CCTransitionScene * s8=CCTransitionFade::create(2,scene2);
	CCDirector::sharedDirector()->replaceScene(s8);
}


void CombatResultsScene::onEnter(){
    CCLayer::onEnter();
}

void CombatResultsScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
}

void CombatResultsScene::onExit(){
    CCLayer::onExit();
}

void CombatResultsScene::menuCloseCallback(CCObject* pSender)
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
