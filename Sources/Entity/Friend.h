#ifndef _MINIGAME_FRIEND_H_
#define _MINIGAME_FRIEND_H_
#include "Entity.h"

class CCParticleSystem;
class Friend : public Entity
{
public:
	Friend(const char *fileName);

	void bindSprite(cocos2d::CCSprite *sprite);

	void setAttack1Hurt(float hurt) { mAttack1Hurt = hurt;}
	void setAttack2Hurt(float hurt) { mAttack2Hurt = hurt;}
	void setAttackSpeed(float x, float y);
	void setTiggleFlag(bool flag) { mTriggleFlag = flag; }
	void setAttackTime(float time) { mAttackTimeLeft = time; }
	virtual void setController(GameController *controller);

	void update(float delta);
	
	virtual void attack();	//��ͨ����
	void attackEnd();		// �����ͷŽ���
	void attack2();			//���鼼��
	void attack2End(float); //���鼼���ͷŽ���
	virtual void underAttack(int hp);

	void die(float delta);

	void increaseLevel();
	
private:
	float mxSpeed, mySpeed; // �ƶ�������x,y���������ϵ��ٶ�
	float mAcceleration;	//���ٶ�
	float mAttackTimeLeft;	// �ƶ�����ʣ���ʱ��
	float mAttack1Hurt;		//��һ�ּ��ܵĹ�����
	float mAttack2Hurt;		//���鼼�ܵĹ�����
	Entity *mLastConflictedEntity;//�ϴγ�ͻ����
	bool mTriggleFlag;		// �Ƿ��Ѿ���������
	cocos2d::CCParticleSystem *mParticleSystem; // ���鼼������ϵͳ
	int	mLevel;				// Ӣ�۵ȼ�
	cocos2d::CCSprite*	mWeapon[3];		// ������������Ч��
};

#endif