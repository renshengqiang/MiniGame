#include "Effects\AnimationUtil.h"


CCAnimation* AnimationUtil::createAnimWithSingleFrameN( const char* name, float delay, unsigned int iLoops) {
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();

    CCArray* framesArray = CCArray::create();

    CCSpriteFrame* frame = NULL;
    int index = 1;
    do {
        frame = cache->spriteFrameByName(CCString::createWithFormat("%s%d.png", name, index++)->getCString());

        /* 不断地获取CCSpriteFrame对象，直到获取的值为NULL */
        if(frame == NULL) {
            break;
        }

        framesArray->addObject(frame);
    }while(true);

    CCAnimation* animation = CCAnimation::createWithSpriteFrames(framesArray);
    animation->setLoops(iLoops);
    animation->setRestoreOriginalFrame(true);
    animation->setDelayPerUnit(delay);

    return animation;
}

CCAnimation* AnimationUtil::createAnimWithFrameNameAndNum( const char* name, int iNum, float delay, unsigned int iLoops, CCRect rect) {
    CCArray* framesArray = CCArray::create();
    CCSpriteFrame* frame = NULL;
    int index = 1;
    for(int i = 1; i <= iNum; i++)
	{
		frame = CCSpriteFrame::create(CCString::createWithFormat("%s%d.png", name, i)->getCString(), rect);
        if(frame == NULL) 
		{
            break;
        }
        framesArray->addObject(frame);
    }

    CCAnimation* animation = CCAnimation::createWithSpriteFrames(framesArray);
    animation->setLoops(iLoops);
    //animation->setRestoreOriginalFrame(true);
    animation->setDelayPerUnit(delay);

    return animation;
}