#include "Scenes\LoginScene.h"
#include "Scenes\ModeSelectScene.h"
#include "Scenes\HeroIntroScene.h"
#include "Scenes\GameScene.h"

USING_NS_CC;

CCScene* ModeSelectScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ModeSelectScene *layer = ModeSelectScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ModeSelectScene::init()
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
                                        "InfMode.png",
                                        "InfModeSel.png",
                                        this,
                                        menu_selector(ModeSelectScene::changescene));
    
	pEnterItem_WX->setPosition(ccp(origin.x + visibleSize.width/2-120,
                            origin.y + visibleSize.height/2-200));

    // create menu, it's an autorelease object
    CCMenu* pMenu_WX = CCMenu::create(pEnterItem_WX, NULL);
    pMenu_WX->setPosition(CCPointZero);
    this->addChild(pMenu_WX, 1);

	CCMenuItemImage *pEnterItem_QQ = CCMenuItemImage::create(
                                        "StoryMode.png",
                                        "StoryModeSel.png",
                                        this,
                                        menu_selector(ModeSelectScene::changescene));
    
	pEnterItem_QQ->setPosition(ccp(origin.x + visibleSize.width/2+120,
                            origin.y + visibleSize.height/2-200));
    // create menu, it's an autorelease object
    CCMenu* pMenu_QQ = CCMenu::create(pEnterItem_QQ, NULL);
    pMenu_QQ->setPosition(CCPointZero);
    this->addChild(pMenu_QQ, 1);


    /////////////////////////////
    // 3. add your codes below...

	
	CCSize mysize=CCDirector::sharedDirector()->getWinSize();
	CCSprite* sp = CCSprite::create("ModelSelect.png");
	sp->setPosition(ccp(mysize.width/2, mysize.height/2));
	//设置不同颜色区分
	sp->setColor(ccc3(100,100,100));
	this->addChild(sp, 0);

	CCSprite* sp1 = CCSprite::create("Primitve.png");
	sp1->setPosition(ccp(mysize.width/2-154, mysize.height/2+200));
	this->addChild(sp1, 2);

	CCSprite* sp2 = CCSprite::create("Modern.png");
	sp2->setPosition(ccp(mysize.width/2, mysize.height/2+200));
	this->addChild(sp2, 2);

	CCSprite* sp3 = CCSprite::create("ScieneFiction.png");
	sp3->setPosition(ccp(mysize.width/2+154, mysize.height/2+200));
	this->addChild(sp3, 2);

	CCSprite* sp4 = CCSprite::create("HeroChi.png");
	sp4->setPosition(ccp(mysize.width/2, mysize.height/2));
	this->addChild(sp4, 2);
    
    return true;
}


void ModeSelectScene::changescene(CCObject * obj){
	CCScene * scene1=HeroIntroScene::scene();
	CCTransitionScene * ss=CCTransitionCrossFade::create(1,scene1);
	CCDirector::sharedDirector()->replaceScene(ss);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ButtonClick.wav");
}

void ModeSelectScene::onEnter(){
    CCLayer::onEnter();
}

void ModeSelectScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
}

void ModeSelectScene::onExit(){
    CCLayer::onExit();
}

void ModeSelectScene::menuCloseCallback(CCObject* pSender)
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
