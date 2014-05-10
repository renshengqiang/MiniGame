#ifndef _MINIGAME_FLOW_WORD_H_
#define _MINIGAME_FLOW_WORD_H_
#include <cocos2d.h>

class FlowWord :
	public cocos2d::CCNode
{
public:
	FlowWord(void);
	~FlowWord(void);

	CREATE_FUNC(FlowWord);
	bool init();

public:
	void showWord(const char* text, cocos2d::CCPoint pos);

private:
	cocos2d::CCLabelTTF* m_textLab;

	void flowEnd();
};

#endif