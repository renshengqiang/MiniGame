#ifndef __ANIMATION_UTIL_H__
#define __ANIMATION_UTIL_H__

#include "cocos2d.h"

using namespace cocos2d;

class AnimationUtil {
public:
    /* �����ļ�����ǰ׺������������ */
    static CCAnimation* createAnimWithSingleFrameN(const char* name, float delay, unsigned int iLoops);

    /* �����ļ�����ǰ׺������������ָ������ͼƬ���� */
    static CCAnimation* createAnimWithFrameNameAndNum( const char* name, int iNum, float delay, unsigned int iLoops, CCRect rect);

};

#endif