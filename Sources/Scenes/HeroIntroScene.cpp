#include "Scenes\HeroIntroScene.h"
#include "Scenes\ModeSelectScene.h"
#include "Scenes\GameScene.h"
#include "Scenes\GameLevelSelectScene.h"
using namespace cocos2d;

USING_NS_CC;

CCMenuItemImage *pEnterItem3,*pEnterItem4;
CCSprite *sp_shop,*sp_hero_s,*sp_hero[MAX_Heros];
CCMenu *pMenu3,*pMenu4;

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
                                        "Leveled.png",
                                        "LeveledSelected.png",
                                        this,
                                        0);
    
	pEnterItem_WX->setPosition(ccp(origin.x + visibleSize.width/2-120,
                            origin.y + visibleSize.height/2-300));

    // create menu, it's an autorelease object
    CCMenu* pMenu_WX = CCMenu::create(pEnterItem_WX, NULL);
    pMenu_WX->setPosition(CCPointZero);
    this->addChild(pMenu_WX, 1);

	CCMenuItemImage *pEnterItem_QQ = CCMenuItemImage::create(
                                        "ToStar.png",
                                        "ToStarSelected.png",	
                                        this,
                                        0);
    
	pEnterItem_QQ->setPosition(ccp(origin.x + visibleSize.width/2+120,
                            origin.y + visibleSize.height/2-300));
    // create menu, it's an autorelease object
    CCMenu* pMenu_QQ = CCMenu::create(pEnterItem_QQ, NULL);
    pMenu_QQ->setPosition(CCPointZero);
    this->addChild(pMenu_QQ, 1);

	 CCMenuItemImage *pEnterItem1 = CCMenuItemImage::create(
                                        "Battle.png",
                                        "BattleSelected.png",
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
                                        "ReturnSelected.png",
                                        this,
                                        menu_selector(HeroIntroScene::changescene_return));
    
	pEnterItem2->setPosition(ccp(origin.x + visibleSize.width/2+150,
                            origin.y + visibleSize.height/2-480));

    // create menu, it's an autorelease object
    CCMenu* pMenu2 = CCMenu::create(pEnterItem2, NULL);
    pMenu2->setPosition(CCPointZero);
    this->addChild(pMenu2, 1);

	CCMenuItemImage *pEnterItem7 = CCMenuItemImage::create(
                                        "ShopButton.png",
                                        "ShopButtonSelected.png",
                                        this,
                                        menu_selector(HeroIntroScene::changescene_shop));
    
	pEnterItem7->setPosition(ccp(origin.x + visibleSize.width/2-150,
                            origin.y + visibleSize.height/2-480));

    // create menu, it's an autorelease object
    CCMenu* pMenu7 = CCMenu::create(pEnterItem7, NULL);
    pMenu7->setPosition(CCPointZero);
    this->addChild(pMenu7, 1);

	 pEnterItem3 = CCMenuItemImage::create(
                                        "LeftArrow.png",
                                        "LeftArrow.png",
                                        this,
                                        menu_selector(HeroIntroScene::changescene_left));
    
	pEnterItem3->setPosition(ccp(origin.x + visibleSize.width/2-280,
                            origin.y + visibleSize.height/2));

    // create menu, it's an autorelease object
    pMenu3 = CCMenu::create(pEnterItem3, NULL);
    pMenu3->setPosition(CCPointZero);
    this->addChild(pMenu3, 1);

	pEnterItem4 = CCMenuItemImage::create(
                                        "RightArrow.png",
                                        "RightArrow.png",
                                        this,
                                        menu_selector(HeroIntroScene::changescene_right));
    
	pEnterItem4->setPosition(ccp(origin.x + visibleSize.width/2+280,
                            origin.y + visibleSize.height/2));

    // create menu, it's an autorelease object
    pMenu4 = CCMenu::create(pEnterItem4, NULL);
    pMenu4->setPosition(CCPointZero);
    this->addChild(pMenu4, 1);

    /////////////////////////////
    // 3. add your codes below...
	CCSize mysize=CCDirector::sharedDirector()->getWinSize();
	sp_hero_s = CCSprite::create("Primitve_Hero1.png");
	sp_hero_s->setPosition(ccp(mysize.width/2, mysize.height/2));
	this->addChild(sp_hero_s, 0);

	CCSprite* sp1 = CCSprite::create("Hero1.png");
	sp1->setPosition(ccp(mysize.width/2-154, mysize.height/2+450));
	this->addChild(sp1, 0);

	CCSprite* sp2 = CCSprite::create("Hero2.png");
	sp2->setPosition(ccp(mysize.width/2, mysize.height/2+450));
	this->addChild(sp2, 0);

	CCSprite* sp3 = CCSprite::create("Hero3.png");
	sp3->setPosition(ccp(mysize.width/2+154, mysize.height/2+450));
	this->addChild(sp3, 0);

	CCSprite* sp4 = CCSprite::create("HeroIntro1.png");
	sp4->setPosition(ccp(mysize.width/2, mysize.height/2+20));
	this->addChild(sp4, 0);

    return true;
}


void HeroIntroScene::changescene(CCObject* pSender){
	CCScene * scene2=GameLevelSelectScene::scene();
	CCTransitionScene * s2=CCTransitionFade::create(2,scene2);
	CCDirector::sharedDirector()->replaceScene(s2);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ButtonClick.wav");
}

void HeroIntroScene::changescene_return(CCObject* pSender){
	CCScene * scene=ModeSelectScene::scene();
	CCTransitionScene * s10=CCTransitionFade::create(1,scene);
	CCDirector::sharedDirector()->replaceScene(s10);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ButtonClick.wav");

}

void HeroIntroScene::changescene_shop(CCObject* pSender){
	ShopSelectedIndex++;
	int s_index=ShopSelectedIndex%2;
	CCSize mysize=CCDirector::sharedDirector()->getWinSize();
	switch(s_index)
	{
		case 0:
		{
			this->removeChild(sp_shop,0);
			CCSize visibleSize1 = CCDirector::sharedDirector()->getVisibleSize();
			CCPoint origin1 = CCDirector::sharedDirector()->getVisibleOrigin();
			
			pEnterItem3 = CCMenuItemImage::create(
                                        "LeftArrow.png",
                                        "LeftArrow.png",
                                        this,
                                        menu_selector(HeroIntroScene::changescene_left));
    
			pEnterItem3->setPosition(ccp(origin1.x + visibleSize1.width/2-280,
									origin1.y + visibleSize1.height/2));

			pMenu3 = CCMenu::create(pEnterItem3, NULL);
			pMenu3->setPosition(CCPointZero);
			this->addChild(pMenu3, 1);

			pEnterItem4 = CCMenuItemImage::create(
												"RightArrow.png",
												"RightArrow.png",
												this,
												menu_selector(HeroIntroScene::changescene_right));
    
			pEnterItem4->setPosition(ccp(origin1.x + visibleSize1.width/2+280,
									origin1.y + visibleSize1.height/2));

			pMenu4 = CCMenu::create(pEnterItem4, NULL);
			pMenu4->setPosition(CCPointZero);
			this->addChild(pMenu4, 1);

			sp_hero_s = CCSprite::create("Primitve_Hero1.png");
			sp_hero_s->setPosition(ccp(mysize.width/2, mysize.height/2+40));
			this->addChild(sp_hero_s, 0);
			break;
		}
		case 1:
		{
			for(int i=0;i<MAX_Heros;i++)
			{
				this->removeChild(sp_hero[i],0);
			}
			this->removeChild(sp_hero_s,0);
			this->removeChild(pMenu3,0);
			this->removeChild(pMenu4,0);
			sp_shop = CCSprite::create("shop.png");
			sp_shop->setPosition(ccp(mysize.width/2, mysize.height/2+60));
			this->addChild(sp_shop, 0);
			break;
		}
		default:break;
	}
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ButtonClick.wav");

}

void HeroIntroScene::changescene_left(CCObject* pSender){
	SelectedMark--;
	int m=abs(SelectedMark%MAX_Heros);
	CCSize mysize=CCDirector::sharedDirector()->getWinSize();
	for(int i=0;i<MAX_Heros;i++)
	{
		this->removeChild(sp_hero[i],0);
	}
	switch(m){
	case 0:
		{
			sp_hero[0] = CCSprite::create("Primitve_Hero1.png");
			sp_hero[0]->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp_hero[0], 2);
			break;
		}
	case 1:
		{
			sp_hero[1] = CCSprite::create("Human_Hero1.png");
			sp_hero[1]->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp_hero[1], 2);
			break;
		}
	case 2:
		{
			sp_hero[2] = CCSprite::create("Human_Hero2.png");
			sp_hero[2]->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp_hero[2], 2);
			break;
		}
	case 3:
		{
			sp_hero[3] = CCSprite::create("Super_Hero1.png");
			sp_hero[3]->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp_hero[3], 2);
			break;
		}
	case 4:
		{
			sp_hero[4] = CCSprite::create("Super_Hero2.png");
			sp_hero[4]->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp_hero[4], 2);
			break;
		}
	case 5:
		{
			sp_hero[5] = CCSprite::create("Super_Hero3.png");
			sp_hero[5]->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp_hero[5], 2);
			break;
		}
	case 6:
		{
			sp_hero[6] = CCSprite::create("Shenmo_Hero1.png");
			sp_hero[6]->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp_hero[6], 2);
			break;
		}
	case 7:
		{
			sp_hero[7] = CCSprite::create("Shenmo_Hero2.png");
			sp_hero[7]->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp_hero[7], 2);
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
	for(int i=0;i<MAX_Heros;i++)
	{
		this->removeChild(sp_hero[i],0);
	}
	switch(m){
	case 0:
		{
			sp_hero[0] = CCSprite::create("Primitve_Hero1.png");
			sp_hero[0]->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp_hero[0], 2);
			break;
		}
	case 1:
		{
			sp_hero[1] = CCSprite::create("Human_Hero1.png");
			sp_hero[1]->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp_hero[1], 2);
			break;
		}
	case 2:
		{
			sp_hero[2] = CCSprite::create("Human_Hero2.png");
			sp_hero[2]->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp_hero[2], 2);
			break;
		}
	case 3:
		{
			sp_hero[3] = CCSprite::create("Super_Hero1.png");
			sp_hero[3]->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp_hero[3], 2);
			break;
		}
	case 4:
		{
			sp_hero[4] = CCSprite::create("Super_Hero2.png");
			sp_hero[4]->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp_hero[4], 2);
			break;
		}
	case 5:
		{
			sp_hero[5] = CCSprite::create("Super_Hero3.png");
			sp_hero[5]->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp_hero[5], 2);
			break;
		}
	case 6:
		{
			sp_hero[6] = CCSprite::create("Shenmo_Hero1.png");
			sp_hero[6]->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp_hero[6], 2);
			break;
		}
	case 7:
		{
			sp_hero[7] = CCSprite::create("Shenmo_Hero2.png");
			sp_hero[7]->setPosition(ccp(mysize.width/2, mysize.height/2+20));
			this->addChild(sp_hero[7], 2);
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
