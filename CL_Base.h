#ifndef CL_BASE_H
#define CL_BASE_H
#include "teamstyle18-my-1.h"
class C_BASE
{
private:
	int TeamID;//����ID
	int BaseID;//����ID
	int HPremain;//ʣ��Ѫ��
	int AttackPower;//������
	int DefensivePower;//������
	int SkillCD;//�չ�ʣ��CD
	int InitMeatNum;//������Ҫ����С�������
	int InitHaveMeat;//�����Ѿ�������С�������
	Unit *BaseUnit;//ָ����ص�ָ��
	const double attack_type[5] = { 0.25,0.75,1,1,1 };
	Position BasePos;
	int first;//��һ�غ�
public:
	C_BASE();//���캯��
public:
	//���ػ���ID;
	int getID();
	//����Ѫ��
	void updateHP();
	//���¹�����
	void updateAttack();
	//���·�����
	void updateDefense();
	//����Ѫ��
	int getHP();
	//���ֽ���С����,ִ��n�Σ�ÿ�η��������ɵ�С�����ID
	int proMeatBegin();
	//�Ƿ��ʼ������
	bool IsInitDone();
	//��;����С����,����С�����ID
	int proMeat();
	//���㹥����,����Ϊ��������ID
	int getAttackPower(int attackID);
	//���������������Ϊ�������صĶ���ID
	int getDefensivePower(int defensiveID);
	//�Ƿ�����������
	bool getSkillCD();

	//������Ϊ
	//����Ҫ�����Ķ���ID
	int WhichToAttack();
	//��������
	void LaunchAttack(int AttackID);

	//ÿ�غ�Ӧ�õ��õĺ�������
	void BaseRun();
};
#endif // !CL_BASE_H

