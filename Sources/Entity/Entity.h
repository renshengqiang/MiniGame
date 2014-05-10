#ifndef _MINIGAME_ENTITY_H_
#define _MINIGAME_ENTITY_H_
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Controller/ControllerListener.h"

class GameController;
class Entity : public cocos2d::CCNode, public ControllerListener
{
public:
	Entity();
	void bindSprite(cocos2d::CCSprite *sprite);

	void update(float delta);

	bool isActive(){ return m_activated; }
	void setActive(bool active);

	void setHp(int hp);
	void health(int hp);
	virtual void underAttack(int hp);

	virtual void setController(GameController *controller);

	// function inheritted from ControllerListener
	virtual void setTagPosition(int x, int y);
	virtual cocos2d::CCPoint getTagPosition();

protected:
	int m_hp;						// Ѫ��
	int m_fullHp;					// ����״̬�µ�Ѫ��
	cocos2d::CCSprite *m_sprite;	// ���ﾫ��
	cocos2d::extension::CCControlSlider *m_hpSlider; /*Ѫ����*/
	GameController *m_controller;	// Game�����߼�
	bool m_activated;				// ��ǰEntity�Ƿ��Ǽ��������������
};

#endif