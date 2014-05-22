#include "Scenes\HeroIntroScene.h"
#include "Scenes\ModeSelectScene.h"
#include "Scenes\GameScene.h"
using namespace cocos2d;

USING_NS_CC;

CCScene* HeroIntroScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HeroIntroScene *layer = HeroIntroScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HeroIntroScene::init()
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
                                        "Upgrade.png",
                                        "UpgradeSel.png",
                                        this,
                                        0);
    
	pEnterItem_WX->setPosition(ccp(origin.x + visibleSize.width/2-120,
                            origin.y + visibleSize.height/2-300));

    // create menu, it's an autorelease object
    CCMenu* pMenu_WX = CCMenu::create(pEnterItem_WX, NULL);
    pMenu_WX->setPosition(CCPointZero);
    this->addChild(pMenu_WX, 1);

	CCMenuItemImage *pEnterItem_QQ = CCMenuItemImage::create(
                                        "Evolution.png",
                                        "EvolutionSel.png",	
                                        this,
                                        0);
    
	pEnterItem_QQ->setPosition(ccp(origin.x + visibleSize.width/2+120,
                            origin.y + visibleSize.height/2-300));
    // create menu, it's an autorelease object
    CCMenu* pMenu_QQ = CCMenu::create(pEnterItem_QQ, NULL);
    pMenu_QQ->setPosition(CCPointZero);
    this->addChild(pMenu_QQ, 1);

	 CCMenuItemImage *pEnterItem1 = CCMenuItemImage::create(
                                        "Fight.png",
                                        "FightSel.png",
                                        this,
                                        menu_selector(HeroIntroScene::changescene));
    
	pEnterItem1->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2-390));

    // create menu, it's an autorelease object
    CCMenu* pMenu1 = CCMenu::create(pEnterItem1, NULL);
    pMenu1->setPosition(CCPointZero);
    this->addChild(pMenu1, 1);

	CCMenuItemImage *pEnterItem2 = CCMenuItemImage::create(
                                        "Return.png",
                                        "ReturnSel.png",
                                        this,
                                        menu_selector(HeroIntroScene::changescene_return));
    
	pEnterItem2->setPosition(ccp(origin.x + visibleSize.width/2+220,
                            origin.y + visibleSize.height/2-480));

    // create menu, it's an autorelease object
    CCMenu* pMenu2 = CCMenu::create(pEnterItem2, NULL);
    pMenu2->setPosition(CCPointZero);
    this->addChild(pMenu2, 1);

	 CCMenuItemImage *pEnterItem3 = CCMenuItemImage::create(
                                        "LeftArrow.png",
                                        "LeftArrow.png",
                                        this,
                                        menu_selector(HeroIntroScene::changescene_left));
    
	pEnterItem3->setPosition(ccp(origin.x + visibleSize.width/2-280,
                            origin.y + visibleSize.height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu3 = CCMenu::create(pEnterItem3, NULL);
    pMenu3->setPosition(CCPointZero);
    this->addChild(pMenu3, 1);

	CCMenuItemImage *pEnterItem4 = CCMenuItemImage::create(
                                        "RightArrow.png",
                                        "RightArrow.png",
                                        this,
                                        menu_selector(HeroIntroScene::changescene_right));
    
	pEnterItem4->setPosition(ccp(origin.x + visibleSize.width/2+280,
                            origin.y + visibleSize.height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu4 = CCMenu::create(pEnterItem4, NULL);
    pMenu4->setPosition(CCPointZero);
    this->addChild(pMenu4, 1);

    /////////////////////////////
    // 3. add your codes below...
	CCSize mysize=CCDirector::sharedDirector()->getWinSize();
	CCSprite* sp = CCSprite::create("HeroIntroBG.png");
	sp->setPosition(ccp(mysize.width/2, mysize.height/2));
	//设置不同颜色区分
	sp->setColor(ccc3(100,100,100));
	this->addChild(sp, 0);

	CCSprite* sp5 = CCSprite::create("Widget1_1.png");
	sp5->setPosition(ccp(mysize.width/2-154, mysize.height/2+400));
	this->addChild(sp5, 0);

	CCSprite* sp6 = CCSprite::create("Widget1_2.png");
	sp6->setPosition(ccp(mysize.width/2, mysize.height/2+400));
	this->addChild(sp6, 0);

	CCSprite* sp7 = CCSprite::create("Widget1_3.png");
	sp7->setPosition(ccp(mysize.width/2+154, mysize.height/2+400));
	this->addChild(sp7, 0);

	CCSprite* sp8 = CCSprite::create("CMPrimitive.png");
	sp8->setPosition(ccp(mysize.width/2, mysize.height/2+20));
	this->addChild(sp8, 0);

    return true;
}


void HeroIntroScene::changescene(CCObject* pSender){
	CCScene * scene2=GameScene::scene();
	CCTransitionScene * s2=CCTransitionFade::create(2,scene2);
	CCDirector::sharedDirector()->replaceScene(s2);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ButtonClick.wav");
}

void HeroIntroScene::changescene_return(CCObject* pSender){
	CCScene * scene=ModeSelectScene::scene();
	CCTransitionScene * s10=CCTransitionJumpZoom::create(1,scene);
	CCDirector::sharedDirector()->replaceScene(s10);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ButtonClick.wav");

}

void HeroIntroScene::changescene_left(CCObject* pSender){
	SelectedMark--;
	int m=abs(SelectedMark%MAX_Heros);
	CCSize mysize=CCDirector::sharedDirector()->getWinSize();
	switch(m){
	case 0:
		{
			CCSprite* sp1 = CCSprite::create("CMPrimitive1.png");
			sp1->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp1, 2);
			break;
		}
	case 1:
		{
			CCSprite* sp2 = CCSprite::create("Science2.png");
			sp2->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp2, 2);
			break;
		}
	case 2:
		{
			CCSprite* sp3 = CCSprite::create("Sivel3.png");
			sp3->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp3, 2);
			break;
		}
	case 3:
		{
			CCSprite* sp4 = CCSprite::create("Bird4.png");
			sp4->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp4, 2);
			break;
		}
	default:break;
	}
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ButtonClick.wav");
}

void HeroIntroScene::changescene_right(CCObject* pSender){
	SelectedMark++;
	int m=abs(SelectedMark%MAX_Heros);
	CCSize mysize=CCDirector::sharedDirector()->getWinSize();
	switch(m){
	case 0:
		{
			CCSprite* sp1 = CCSprite::create("CMPrimitive1.png");
			sp1->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp1, 2);
			break;
		}
	case 1:
		{
			CCSprite* sp2 = CCSprite::create("Science2.png");
			sp2->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp2, 2);
			break;
		}
	case 2:
		{
			CCSprite* sp3 = CCSprite::create("Sivel3.png");
			sp3->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp3, 2);
			break;
		}
	case 3:
		{
			CCSprite* sp4 = CCSprite::create("Bird4.png");
			sp4->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp4, 2);
			break;
		}
	default:break;
	}
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ButtonClick.wav");
}

void HeroIntroScene::onEnter(){
    CCLayer::onEnter();
}

void HeroIntroScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
}

void HeroIntroScene::onExit(){
    CCLayer::onExit();
}

void HeroIntroScene::menuCloseCallback(CCObject* pSender)
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
