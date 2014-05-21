#ifndef _MINIGAME_ENTITY_H_
#define _MINIGAME_ENTITY_H_
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Controller/ControllerListener.h"

class GameController;
class CCParticleSystem;
class Entity : public cocos2d::CCNode, public ControllerListener
{
public:
	Entity();
	void bindSprite(cocos2d::CCSprite *sprite);

	void update(float delta);

	bool isActive(){ return m_activated; }
	void setActive(bool active);

	bool isAuto() { return m_autoAttack; }
	bool dead() { return m_hp<=0; }
	void setHp(int hp);
	void health(int hp);
	int getHp(){ return m_hp;}
	int getFullHp() { return m_fullHp; }
	virtual void underAttack(int hp);
	virtual void attack() = 0;		// �ͷż���
	virtual void setAttackSpeed(float x, float y){}; // ���ù����ٶȣ�Ϊ�˷���ͳһ���ã����˺�����������

	virtual void setController(GameController *controller);

	// function inheritted from ControllerListener
	virtual void setTagPosition(int x, int y);
	virtual cocos2d::CCPoint getTagPosition();

protected:
	int m_hp;						// Ѫ��
	int m_fullHp;					// ����״̬�µ�Ѫ��
	cocos2d::CCSprite *m_sprite;	// ���ﾫ��
	cocos2d::CCSprite *m_magicSprite; //���빥��ģʽ��ħ����
	float m_magicTime;				// ħ�������ʱ��
	cocos2d::extension::CCControlSlider *m_hpSlider; /*Ѫ����*/
	GameController *m_controller;	// Game�����߼�
	bool m_activated;				// ��ǰEntity�Ƿ��Ǽ��������������
	bool m_attacking;				// ��ǰ�Լ��Ƿ��ǹ�����
	bool m_autoAttack;				// �Ƿ���������������
	cocos2d::CCParticleSystem *m_particleSystem;	//������Ч

	bool flag;						// ��ʱ���������ڶԵ�ǰ��Ծ���������˸
};

#endif