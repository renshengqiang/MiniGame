#include "PauseScene.h"
#include "cocos-ext.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace cocos2d::extension;

bool PauseScene::init()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	
	CCMenuItemImage *pPauseMenuItem = CCMenuItemImage::create(
                                        "start.png",
                                        "pause.png",
                                        this,
										menu_selector(PauseScene::onResume));
    
	pPauseMenuItem->setPosition(ccp(visibleSize.width-50, visibleSize.height-50));
	CCMenu* pPauseMenu = CCMenu::create(pPauseMenuItem, NULL);
    pPauseMenu->setPosition(CCPointZero);
    this->addChild(pPauseMenu, 5);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();

	return true;
}

CCScene* PauseScene::scene(CCRenderTexture *renderTexture, bool isFlip)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCScene *mapScene = CCScene::create();

	CCSprite *_spr = CCSprite::createWithTexture(renderTexture->getSprite()->getTexture());
	_spr->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	_spr->setFlipY(isFlip);
	_spr->setColor(ccGRAY);
	mapScene->addChild(_spr);

	PauseScene *layer = PauseScene::create();
	mapScene->addChild(layer);
	return mapScene;
}

void PauseScene::onResume(CCObject *pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	CCDirector::sharedDirector()->popScene();
}