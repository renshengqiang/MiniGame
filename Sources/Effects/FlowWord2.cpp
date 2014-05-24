#include "FlowWord2.h"
USING_NS_CC;

FlowWord2::FlowWord2(void)
{
}


FlowWord2::~FlowWord2(void)
{
}

bool FlowWord2::init() 
{
	m_textLab = CCLabelTTF::create("", "Arial", 80);
	m_textLab->setColor(ccc3(255, 255, 0));
	m_textLab->setAnchorPoint(ccp(0.5, 0.5));
	m_textLab->setVisible(false);

	this->addChild(m_textLab);
	return true;
}

void FlowWord2::showWord( const char* text, CCPoint pos ) 
{
	m_textLab->setString(text);
	m_textLab->setPosition(pos);
	m_textLab->setVisible(true);

	/* 组合两个动作，放大后缩小 */
	CCActionInterval* scaleSmall = CCScaleTo::create(0.8f, 0.5f, 0.5f);

	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(FlowWord2::flowEnd));

	CCActionInterval* actions = CCSequence::create(scaleSmall, callFunc, NULL);

	m_textLab->runAction(actions);
}

void FlowWord2::flowEnd() {
	/* 动作结束，从父节点中删除自身 */
	m_textLab->setVisible(false);
	m_textLab->removeFromParentAndCleanup(true);
}