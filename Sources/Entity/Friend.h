#ifndef _MINIGAME_FRIEND_H_
#define _MINIGAME_FRIEND_H_
#include "Entity.h"

class Friend : public Entity
{
public:
	Friend(const char *fileName);

	void bindSprite(cocos2d::CCSprite *sprite);

	void setAttack1Hurt(float hurt) { mAttack1Hurt = hurt;}
	void setAttack2Hurt(float hurt) { mAttack2Hurt = hurt;}
	void setSpeed(float x, float y) { mxSpeed = x; mySpeed = y; }
	virtual void setController(GameController *controller);
	void update(float delta);
	
	void attack1();	//��ͨ����
	void attack2(); //���鼼��

private:
	bool mAttacking;		// ��ǰ�Լ��Ƿ��ǻ�Ծ����
	float mxSpeed, mySpeed; // �ƶ�������x,y���������ϵ��ٶ�
	float mAttackTimeLeft;	// �ƶ�����ʣ���ʱ��
	float mAttack1Hurt;		//��һ�ּ��ܵĹ�����
	float mAttack2Hurt;		//���鼼�ܵĹ�����
	Entity *mLastConflictedEntity;//�ϴγ�ͻ����
};

#endif