#include "Entity.h"
#include "Controller/GameController.h"
#include "Utils.h"
#include "Effects\FlowWord.h"

USING_NS_CC;
using namespace cocos2d::extension;
	
Entity::Entity():
	m_hp(0),
	m_fullHp(100),
	m_sprite(NULL),
	m_hpSlider(NULL),
	m_controller(NULL),
	m_activated(false),
	m_attacking(false),
	m_autoAttack(false),
	flag(true)
{
	CCNode::scheduleUpdate();	// 子类不需要再调用这个函数
}

void Entity::bindSprite(CCSprite *sprite)
{
	m_sprite = sprite;
	CCNode::addChild(m_sprite);

}

void Entity::setHp(int hp)
{
	m_fullHp = hp;
	m_hp = hp;
	if(m_hpSlider != NULL)
	{
		m_hpSlider->setMaximumValue(hp);
	}
}

void Entity::health(int hp)
{
	m_hp += hp;
	if(m_hp > m_fullHp) m_hp = m_fullHp;
	if(m_hpSlider != NULL)
	{
		m_hpSlider->setValue(m_hp);
	}
}

void Entity::underAttack(int hp)
{
	char str[100];
	m_hp -= hp;
		
	sprintf(str, "-%d\n", hp);
	/*扣血飘字效果*/
	FlowWord *pFlowWord = FlowWord::create();
	CCNode::addChild(pFlowWord);
	pFlowWord->showWord(str, m_sprite->getPosition());

	// TODO:血量条要进行更新
	if(m_hpSlider != NULL)
	{
		m_hpSlider->setValue(m_hp);
	}
}

void Entity::setActive(bool active)
{
	m_activated = active;
}

void Entity::update(float delta)
{
	if(m_activated)		// 随机晃动一个距离
	{
		if(!flag)
			CCNode::setScale(0.48, 0.48);
		else
			CCNode::setScale(0.5, 0.5);
		flag = !flag;
	}
	else
	{
		CCNode::setScale(0.5, 0.5);
	}
}

void Entity::setController(GameController *controller)
{
	m_controller = controller;
}

void Entity::setTagPosition(int x, int y)
{
	CCNode::setPosition(x, y);
}

CCPoint Entity::getTagPosition()
{
	return CCNode::getPosition();
}