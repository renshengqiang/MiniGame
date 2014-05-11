#include "LoginScene.h"
#include "cocos-ext.h"
#include "GameScene.h"

USING_NS_CC;
using namespace cocos2d::extension;

bool LoginScene::init()
{
	// �ڴ˴�������
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	/*��������ͱ���ͼƬ*/
	CCLabelTTF *title = CCLabelTTF::create("Login", "Arial", 35);
	CCScale9Sprite *pNormalBg = CCScale9Sprite::create("button.png");
	CCScale9Sprite *pLightBg = CCScale9Sprite::create("buttonHighlighted.png");

	/*������ť*/
	CCControlButton *pJumpButton = CCControlButton::create(title, pNormalBg);
	pJumpButton->setPosition(visibleSize.width-80, 50);
	pJumpButton->setBackgroundSpriteForState(pLightBg, CCControlStateHighlighted);

	/*��Ӱ�ť�¼�*/
	pJumpButton->addTargetWithActionForControlEvents(this, cccontrol_selector(LoginScene::login), CCControlEventTouchDown);
	CCLayer::addChild(pJumpButton);
	return true;
}

CCScene* LoginScene::scene()
{
	CCScene *mapScene = CCScene::create();
	LoginScene *layer = LoginScene::create();
	mapScene->addChild(layer);
	return mapScene;
}

void LoginScene::login(CCObject *pSender, CCControlEvent event)
{
	CCScene *pScene = GameScene::scene();
	CCDirector::sharedDirector()->replaceScene(
	CCTransitionSlideInT::create(1.0f, pScene));
}
