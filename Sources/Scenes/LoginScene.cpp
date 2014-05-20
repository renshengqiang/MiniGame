#include "Scenes\LoginScene.h"
#include "Scenes\ModeSelectScene.h"
using namespace cocos2d;

USING_NS_CC;

CCScene* LoginScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    LoginScene *layer = LoginScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("IntroBGMusic.mp3", true);
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	/*
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(LoginScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
	*/

	 CCMenuItemImage *pEnterItem_WX = CCMenuItemImage::create(
                                        "WXLogin.png",
                                        "WXLoginSelected.png",
                                        this,
                                        menu_selector(LoginScene::changescene));
    
	pEnterItem_WX->setPosition(ccp(origin.x + visibleSize.width/2-150,
                            origin.y + visibleSize.height/2-200));

    // create menu, it's an autorelease object
    CCMenu* pMenu_WX = CCMenu::create(pEnterItem_WX, NULL);
    pMenu_WX->setPosition(CCPointZero);
    this->addChild(pMenu_WX, 1);

	CCMenuItemImage *pEnterItem_QQ = CCMenuItemImage::create(
                                        "QQLogin.png",
                                        "QQLoginSelected.png",
                                        this,
                                        menu_selector(LoginScene::changescene));
    
	pEnterItem_QQ->setPosition(ccp(origin.x + visibleSize.width/2+150,
                            origin.y + visibleSize.height/2-200));
    // create menu, it's an autorelease object
    CCMenu* pMenu_QQ = CCMenu::create(pEnterItem_QQ, NULL);
    pMenu_QQ->setPosition(CCPointZero);
    this->addChild(pMenu_QQ, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("LoginBG.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

    return true;
}


void LoginScene::changescene(CCObject* pSender){
	CCScene * scene2=ModeSelectScene::scene();
	////CCTransitionCrossFade�л���ʽ
	//CCTransitionScene * s1=CCTransitionCrossFade::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s1);

	////CCTransitionFade�л���ʽ
	//CCTransitionScene * s2=CCTransitionFade::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s2);

	////CCTransitionFadeBL�л���ʽ
	//CCTransitionScene * s3=CCTransitionFadeBL::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s3);

	////CCTransitionFadeDown�л���ʽ
	//CCTransitionScene * s4=CCTransitionFadeDown::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s4);

	////CCTransitionFadeTR�л���ʽ
	//CCTransitionScene * s5=CCTransitionFadeTR::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s5);

	////CCTransitionFadeUp�л���ʽ
	//CCTransitionScene * s6=CCTransitionFadeUp::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s6);

	////CCTransitionFlipAngular�л���ʽ
	//CCTransitionScene * s7=CCTransitionFlipAngular::create(2,scene2,kCCTransitionOrientationRightOver);
	//CCDirector::sharedDirector()->replaceScene(s7);

	//CCTransitionFlipX�л���ʽ
	CCTransitionScene * s8=CCTransitionFlipX::create(1,scene2);
	CCDirector::sharedDirector()->replaceScene(s8);

	////CCTransitionFlipY�л���ʽ
	//CCTransitionScene * s9=CCTransitionFlipY::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s9);

	////CCTransitionJumpZoom�л���ʽ
	//CCTransitionScene * s10=CCTransitionJumpZoom::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s10);

	////CCTransitionMoveInB�л���ʽ
	//CCTransitionScene * s11=CCTransitionMoveInB::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s11);

	////CCTransitionMoveInL�л���ʽ
	//CCTransitionScene * s12=CCTransitionMoveInL::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s12);

	////CCTransitionMoveInT�л���ʽ
	//CCTransitionScene * s13=CCTransitionMoveInT::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s13);

	////CCTransitionMoveInR�л���ʽ
	//CCTransitionScene * s14=CCTransitionMoveInR::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s14);

	////CCTransitionPageTurn�л���ʽ
	//CCTransitionScene * s15=CCTransitionPageTurn::create(2,scene2,false);
	//CCDirector::sharedDirector()->replaceScene(s15);

	////CCTransitionProgressHorizontal�л���ʽ
	//CCTransitionScene * s16=CCTransitionProgressHorizontal::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s16);

	////CCTransitionProgressInOut�л���ʽ
	//CCTransitionScene * s17=CCTransitionProgressInOut::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s17);

	////CCTransitionProgressOutIn�л���ʽ
	//CCTransitionScene * s18=CCTransitionProgressOutIn::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s18);

	////CCTransitionProgressRadialCCW�л���ʽ
	//CCTransitionScene * s19=CCTransitionProgressRadialCCW::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s19);

	////CCTransitionProgressRadialCW�л���ʽ
	//CCTransitionScene * s20=CCTransitionProgressRadialCW::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s20);

	////CCTransitionProgressVertical�л���ʽ
	//CCTransitionScene * s21=CCTransitionProgressVertical::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s21);

	////CCTransitionRotoZoom�л���ʽ
	//CCTransitionScene * s22=CCTransitionRotoZoom::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s22);

	////CCTransitionShrinkGrow�л���ʽ
	//CCTransitionScene * s23=CCTransitionShrinkGrow::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s23);

	////CCTransitionSlideInB�л���ʽ
	//CCTransitionScene * s24=CCTransitionSlideInB::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s24);

	////CCTransitionSlideInL�л���ʽ
	//CCTransitionScene * s25=CCTransitionSlideInL::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s25);

	////CCTransitionSlideInR�л���ʽ
	//CCTransitionScene * s26=CCTransitionSlideInR::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s26);

	////CCTransitionSlideInT�л���ʽ
	//CCTransitionScene * s27=CCTransitionSlideInT::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s27);

	////CCTransitionSplitCols�л���ʽ
	//CCTransitionScene * s28=CCTransitionSplitCols::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s28);

	////CCTransitionSplitRows�л���ʽ
	//CCTransitionScene * s29=CCTransitionSplitRows::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s29);

	////CCTransitionTurnOffTiles�л���ʽ
	//CCTransitionScene * s30=CCTransitionTurnOffTiles::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s30);

	////CCTransitionZoomFlipAngular�л���ʽ
	//CCTransitionScene * s31=CCTransitionZoomFlipAngular::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s31);

	////CCTransitionZoomFlipX�л���ʽ
	//CCTransitionScene * s32=CCTransitionZoomFlipX::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s32);

	////CCTransitionZoomFlipY�л���ʽ
	//CCTransitionScene * s33=CCTransitionZoomFlipY::create(2,scene2);
	//CCDirector::sharedDirector()->replaceScene(s33);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ButtonClick.wav");
}


void LoginScene::onEnter(){
    CCLayer::onEnter();
}

void LoginScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
}

void LoginScene::onExit(){
    CCLayer::onExit();
}

void LoginScene::menuCloseCallback(CCObject* pSender)
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
