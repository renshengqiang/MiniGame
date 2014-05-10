#ifndef _MINIGAME_CONTROLLER_LISTENER_H_
#define _MINIGAME_CONTROLLER_LISTENER_H_
#include "cocos2d.h"

class ControllerListener
{
public:
	// 设置目标坐标
	virtual void setTagPosition(int x, int y) = 0;
	// 获取目标坐标
	virtual cocos2d::CCPoint getTagPosition() = 0;
};

#endif