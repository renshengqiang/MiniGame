#ifndef _MINIGAME_FLOW_WORD2_H_
#define _MINIGAME_FLOW_WORD2_H_
#include <cocos2d.h>

class FlowWord2 :
	public cocos2d::CCNode
{
public:
	FlowWord2(void);
	~FlowWord2(void);

	CREATE_FUNC(FlowWord2);
	bool init();

public:
	void showWord(const char* text, cocos2d::CCPoint pos);

private:
	cocos2d::CCLabelTTF* m_textLab;

	void flowEnd();
};

#endif