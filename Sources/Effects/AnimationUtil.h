#ifndef __ANIMATION_UTIL_H__
#define __ANIMATION_UTIL_H__

#include "cocos2d.h"

using namespace cocos2d;

class AnimationUtil {
public:
    /* 根据文件名字前缀创建动画对象 */
    static CCAnimation* createAnimWithSingleFrameN(const char* name, float delay, unsigned int iLoops);

    /* 根据文件名字前缀创建动画对象，指定动画图片数量 */
    static CCAnimation* createAnimWithFrameNameAndNum( const char* name, int iNum, float delay, unsigned int iLoops, CCRect rect);

};

#endif