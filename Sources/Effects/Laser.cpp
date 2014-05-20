#include "Laser.h"
USING_NS_CC;

bool Laser::init()
{
	CCNode::scheduleUpdate();
	mSprite = CCSprite::create("laser.png"); //10���س���20���ؿ�
	this->addChild(mSprite);
	mRatio = 0;
	return true;
}

void Laser::show(const cocos2d::CCPoint &beginPos, const cocos2d::CCPoint &endPos)
{
	mSpeed = CCPoint(endPos - beginPos).getLength()*0.5;	
	mDelta = (endPos - beginPos)*0.5;
	float angle = mDelta.getAngle(CCPoint(1, 0));
	mSprite->setRotation(angle*180/M_PI);
}

void Laser::update(float delta)
{
	mRatio += delta;
	if(mRatio <= 1.0f)
	{
		//�ȴ���λ��
		CCPoint des = mDelta * mRatio;
		mSprite->setPosition(des);
		//��������
		float scale = mRatio * mSpeed / 200;	//��Ҫԭ���ļ���ͼƬ�ĳ�����10
		mSprite->setScaleX(scale);
	}
}
