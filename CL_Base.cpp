#include "CL_Base.h"
//���캯��
C_BASE::C_BASE()
{
	TeamID = getTeamId();//��ֵTeamID
	Unit *allUnit = getUnit();
	for (int i = 0, sum = getUnitSize(); i < sum; i++)//��ֵ����ID
	{
		if (allUnit[i].unit_type == __BASE&&allUnit[i].flag == TeamID)
		{
			BaseUnit = &allUnit[i];
			BaseID = allUnit[i].unit_id;
			HPremain = allUnit[i].health_now;
			AttackPower = allUnit[i].attack_now;
			DefensivePower = allUnit[i].defense_now;
			BasePos = allUnit[i].position;
			break;
		}
	}
	InitMeatNum = 20;//Ԥ����������С�������Ϊ20
	InitHaveMeat = 0;
	first = 1;
	SkillCD = 0;//��ʼ����CDΪ0
}

int C_BASE::getID()
{
	return BaseID;
}

void C_BASE::updateHP()
{
	Unit *allUnit = getUnit();
	int sum = getUnitSize();
	for (int i = 0; i < sum; i++)
	{
		if (allUnit[i].unit_id == BaseID)
		{
			HPremain=allUnit[i].health_now;
			return;
		}
	}
}

void C_BASE::updateAttack()
{
	Unit *allUnit = getUnit();
	int sum = getUnitSize();
	for (int i = 0; i < sum; i++)
	{
		if (allUnit[i].unit_id == BaseID)
		{
			AttackPower = allUnit[i].attack_now;
			return;
		}
	}
}

void C_BASE::updateDefense()
{
	Unit *allUnit = getUnit();
	int sum = getUnitSize();
	for (int i = 0; i < sum; i++)
	{
		if (allUnit[i].unit_id == BaseID)
		{
			DefensivePower = allUnit[i].defense_now;
			return;
		}
	}
}

int C_BASE::getHP()
{
	return HPremain;
}

int C_BASE::proMeatBegin()
{
	int MeatID;
	//��ʼ������
	if (IsInitDone()) return -1;
	//����
	produce(BaseID);
	InitHaveMeat++;
	//���������С����ID
	Unit *allUnit = getUnit();
	for (int i = 0, sum = getUnitSize(); i < sum; i++)
	{
		if (allUnit[i].flag == TeamID && allUnit[i].unit_type == MEAT && allUnit[i].position.x == BasePos.x && allUnit[i].position.y == BasePos.y)
		{
			return allUnit[i].unit_id;
		}
	}
	return -1;
}

bool C_BASE::IsInitDone()
{
	if (InitHaveMeat >= InitMeatNum) return true;
	return false;
}

int C_BASE::proMeat()
{
	int MeatID;
	//��ʼ������
	if (IsInitDone()) return -1;
	//����
	produce(BaseID);
	//���������С����ID
	Unit *allUnit = getUnit();
	int sum = getUnitSize();
	for (int i = 0; i < sum; i++)
	{
		if (allUnit[i].flag == TeamID && allUnit[i].unit_type == MEAT && allUnit[i].position.x == BasePos.x && allUnit[i].position.y == BasePos.y)
		{
			return allUnit[i].unit_id;
		}
	}
	return -1;
}

int C_BASE::getAttackPower(int attackID)
{
	Unit *allUnit = getUnit();
	int sum = getUnitSize();
	int attackNum;
	int attackPower;
	for (attackNum = 0; attackNum < sum; attackNum++)
	{
		if (allUnit[attackNum].unit_id == attackID) break;
	}
	//�չ��˺�//Ӧ������
	attackPower = allUnit[attackNum].attack_now*(1-DefensivePower/1000);
	switch (allUnit[attackNum].unit_type)
	{
	case SUPERMAN:
		attackPower *= attack_type[ELEC];
		break;
	case BATTLE_TANK:
		attackPower *= attack_type[ARTILLERY];
		break;
	case NUKE_TANK:
		attackPower *= attack_type[PENETRATING];
		break;
	case UAV:
		attackPower *= attack_type[MACHINEGUN];
		break;
	case EAGLE:
		attackPower *= attack_type[EXPLOSION];
		break;
	}
	return attackPower;
}

int C_BASE::getDefensivePower(int defensiveID)
{
	return DefensivePower;
}

bool C_BASE::getSkillCD()
{
	Unit *allUnit = getUnit();
	int sum = getUnitSize();
	for (int i = 0; i < sum; i++)
	{
		if (allUnit[i].unit_id == BaseID)
		{
			if (allUnit[i].skill_last_release_time1 != 0) return false;
			else return true;
		}
	}
	return false;
}

int C_BASE::WhichToAttack()
{
	//������Χ��Ѫ����͵�
	Unit *allUnit = getUnit();
	int sum = getUnitSize();
	int AHPRemain = 10000;
	int AttackID;
	for (int i = 0; i < sum; i++)
	{
		//�ھ���֮����Ѫ�����
		if (allUnit[i].flag == 1 && allUnit[i].health_now < AHPRemain && ((abs(allUnit[i].position.x - BasePos.x) + abs(allUnit[i].position.y - BasePos.y)) < 12)) 
			AttackID = allUnit[i].unit_id;
	}
	return AttackID;
}

void C_BASE::LaunchAttack(int AttackID)
{
	skill_1(BaseID, AttackID, BasePos);
}

void C_BASE::BaseRun()
{
	if (first)
	{
		getID();
	}
	//����Ѫ��
	updateHP();
	//���¹�����
	updateAttack();
	//���·�����
	updateDefense();
}
