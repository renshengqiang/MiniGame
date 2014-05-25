#ifndef __HEROINTROSCENE_SCENE_H__
#define __HEROINTROSCENE_SCENE_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "SimpleAudioEngine.h"

#define MAX_Heros 8
static int SelectedMark=0;

static int ShopSelectedIndex=0;

class HeroIntroScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

	void changescene(CCObject* pSender);
	void changescene_left(CCObject* pSender);
	void changescene_right(CCObject* pSender);
	void changescene_return(CCObject* pSender);
	void changescene_shop(CCObject* pSender);
	//创建3个生命周期函数
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
    
    // implement the "static node()" method manually
    CREATE_FUNC(HeroIntroScene);
};

#endif // __HELLOWORLD_SCENE_H__
