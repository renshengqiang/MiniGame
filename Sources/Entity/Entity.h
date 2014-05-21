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
	virtual void attack() = 0;		// 释放技能
	virtual void setAttackSpeed(float x, float y){}; // 设置攻击速度，为了方便统一设置，将此函数放在这里

	virtual void setController(GameController *controller);

	// function inheritted from ControllerListener
	virtual void setTagPosition(int x, int y);
	virtual cocos2d::CCPoint getTagPosition();

protected:
	int m_hp;						// 血量
	int m_fullHp;					// 健康状态下的血量
	cocos2d::CCSprite *m_sprite;	// 人物精灵
	cocos2d::CCSprite *m_magicSprite; //进入攻击模式的魔法阵
	float m_magicTime;				// 魔法阵持续时间
	cocos2d::extension::CCControlSlider *m_hpSlider; /*血量条*/
	GameController *m_controller;	// Game控制逻辑
	bool m_activated;				// 当前Entity是否是激活待发射武器的
	bool m_attacking;				// 当前自己是否是攻击者
	bool m_autoAttack;				// 是否是主动攻击对象
	cocos2d::CCParticleSystem *m_particleSystem;	//攻击特效

	bool flag;						// 临时变量，用于对当前活跃对象进行闪烁
};

#endif