#include "WinScene.h"
#include "cocos-ext.h"
#include "GameScene.h"

USING_NS_CC;
using namespace cocos2d::extension;

bool WinScene::init()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	/*创建标题和背景图片*/
	CCLabelTTF *title = CCLabelTTF::create("Exit", "Arial", 35);
	CCScale9Sprite *pNormalBg = CCScale9Sprite::create("button.png");
	CCScale9Sprite *pLightBg = CCScale9Sprite::create("buttonHighlighted.png");

	/*创建按钮*/
	CCControlButton *pJumpButton = CCControlButton::create(title, pNormalBg);
	pJumpButton->setPosition(visibleSize.width/2 - 60, visibleSize.height/2);
	pJumpButton->setBackgroundSpriteForState(pLightBg, CCControlStateHighlighted);

	/*添加按钮事件*/
	pJumpButton->addTargetWithActionForControlEvents(this, cccontrol_selector(WinScene::onExit), CCControlEventTouchDown);
	CCLayer::addChild(pJumpButton);
	
	/*创建标题和背景图片*/
	title = CCLabelTTF::create("Resume", "Arial", 35);
	pNormalBg = CCScale9Sprite::create("button.png");
	pLightBg = CCScale9Sprite::create("buttonHighlighted.png");

	/*创建按钮*/
	pJumpButton = CCControlButton::create(title, pNormalBg);
	pJumpButton->setPosition(visibleSize.width/2 + 60, visibleSize.height/2);
	pJumpButton->setBackgroundSpriteForState(pLightBg, CCControlStateHighlighted);

	/*添加按钮事件*/
	pJumpButton->addTargetWithActionForControlEvents(this, cccontrol_selector(WinScene::onResume), CCControlEventTouchDown);
	CCLayer::addChild(pJumpButton);

	return true;
}

CCScene* WinScene::scene()
{
	CCScene *mapScene = CCScene::create();
	WinScene *layer = WinScene::create();
	mapScene->addChild(layer);
	return mapScene;
}

void WinScene::onExit(CCObject *pSender, CCControlEvent event)
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

void WinScene::onResume(CCObject *pSender, CCControlEvent event)
{

}