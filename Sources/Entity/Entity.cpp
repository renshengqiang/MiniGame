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
	m_magicSprite(NULL),
	m_magicTime(0),
	m_hpSlider(NULL),
	m_controller(NULL),
	m_activated(false),
	m_attacking(false),
	m_autoAttack(false),
	flag(true)
{
	CCNode::scheduleUpdate();	// ���಻��Ҫ�ٵ����������
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
		m_hpSlider->setValue(m_hp);
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
	/*��ѪƮ��Ч��*/
	FlowWord *pFlowWord = FlowWord::create();
	CCNode::addChild(pFlowWord);
	pFlowWord->showWord(str, m_sprite->getPosition());

	// Ѫ����Ҫ����
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
	if(m_activated)
	{
		m_magicTime += delta;
		if(NULL == m_magicSprite)
		{
			m_magicSprite = CCSprite::create("EnermyMagic.png");
			m_magicSprite->setPosition(CCNode::getPosition());
			CCNode::getParent()->addChild(m_magicSprite, 1);		//����Ӣ������
		}
		else
		{
			m_magicSprite->setRotation(m_magicTime*180);
		}
	}
	else
	{
		if(m_magicSprite != NULL)
		{
			m_magicSprite->getParent()->removeChild(m_magicSprite, true);
			m_magicSprite = NULL;
			m_magicTime = 0;
		}
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