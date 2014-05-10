#ifndef _MINIGAME_CONTROLLER_LISTENER_H_
#define _MINIGAME_CONTROLLER_LISTENER_H_
#include "cocos2d.h"

class ControllerListener
{
public:
	// ����Ŀ������
	virtual void setTagPosition(int x, int y) = 0;
	// ��ȡĿ������
	virtual cocos2d::CCPoint getTagPosition() = 0;
};

#endif