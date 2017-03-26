#pragma once
#include<vector>
using namespace std;
#include"teamstyle18-my-1.h"
struct information
{
	information(){}



	bool my_teamid;
	Unit*my_base = nullptr;
	Unit*my_nuke_tank = nullptr;
	Unit*my_eagle = nullptr;
	Unit*my_superman = nullptr;
	Unit*my_meat = nullptr;

	vector<Unit*> my_unit_list;
	int my_unit_size = 0;

	vector<Unit*> my_building_list;
	int my_building_size = 0;

	int my_money = 0;
	int my_tech = 0;
	int my_people = 0;


	bool en_teamid;
	Unit*en_base = nullptr;
	Unit*en_nuke_tank = nullptr;
	Unit*en_eagle = nullptr;
	Unit*en_superman = nullptr;
	Unit*en_meat = nullptr;

	vector<Unit*> en_unit_list;
	int en_unit_size = 0;

	vector<Unit*> en_building_list;
	int en_building_size = 0;

	int en_money = 0;
	int en_tech = 0;
	int en_people = 0;

//中立信息表

	vector<Unit*> neutral_building;
};
extern information info;

void basic_information_initialize(bool TEAMID)
{
	if (TEAMID == info.my_teamid)
	{
		info.my_money = getResourse().money_2;
		info.my_tech = getResourse().tech_2;
		info.my_people = getResourse().remain_people_2;
		info.en_money = getResourse().money_1;
		info.en_tech = getResourse().tech_1;
		info.en_people = getResourse().remain_people_1;
	}
	else
	{
		info.my_money = getResourse().money_1;
		info.my_tech = getResourse().tech_1;
		info.my_people = getResourse().remain_people_1;
		info.en_money = getResourse().money_2;
		info.en_tech = getResourse().tech_2;
		info.en_people = getResourse().remain_people_2;
	}
}
void unit_info_initialize()
{
	Unit*temp = move(getUnit());
	int size = getUnitSize();
	for (int iter = 0; iter != size; ++iter)
	{
		//初始化己方单位表，将单位加至地图
		if ((temp + iter)->flag - 1 == info.my_teamid)
		{
			if ((temp + iter)->unit_type == BUILDING)
			{
				info.my_building_list.push_back(temp + iter);
				++info.my_building_size;
				map.at((temp + iter)->position).pos_my_building = temp + iter;
			}
			else if ((temp + iter)->unit_type == BASE)
			{
				info.my_base = temp + iter;
				map.at((temp + iter)->position).pos_my_building = temp + iter;
			}
			else
			{
				info.my_unit_list.push_back(temp + iter);
				++info.my_unit_size;
				map.at((temp + iter)->position).pos_my_unit.push_back(temp + iter);
			}
			if ((temp + iter)->type_name == NUKE_TANK)//初始化特殊己方单位
			{
				info.my_nuke_tank = temp + iter;
				map.at((temp + iter)->position).pos_my_unit.push_back(temp + iter);
			}
			else if ((temp + iter)->type_name == EAGLE)
			{
				info.my_eagle = temp + iter;
				map.at((temp + iter)->position).pos_my_unit.push_back(temp + iter);
			}
			else if ((temp + iter)->type_name == SUPERMAN)
			{
				info.my_superman = temp + iter;
				map.at((temp + iter)->position).pos_my_unit.push_back(temp + iter);
			}
			else if ((temp + iter)->type_name == MEAT)
			{
				info.my_meat = temp + iter;
				map.at((temp + iter)->position).pos_my_unit.push_back(temp + iter);
			}
		}
		//初始化敌方单位表，将单位加至地图
		else if ((temp + iter)->flag - 1 == info.en_teamid)
		{
			if ((temp + iter)->unit_type == BUILDING)
			{
				info.en_building_list.push_back(temp + iter);
				++info.en_building_size;
				map.at((temp + iter)->position).pos_en_building = temp + iter;
			}
			else if ((temp + iter)->unit_type == BASE)
			{
				info.en_base = temp + iter;
				map.at((temp + iter)->position).pos_en_building = temp + iter;
			}
			else
			{
				info.en_unit_list.push_back(temp + iter);
				++info.en_unit_size;
				map.at((temp + iter)->position).pos_en_unit.push_back(temp + iter);
			}
			if ((temp + iter)->type_name == NUKE_TANK)//初始化特殊敌方单位
			{
				info.en_nuke_tank = temp + iter;
				map.at((temp + iter)->position).pos_en_unit.push_back(temp + iter);
			}
			else if ((temp + iter)->type_name == EAGLE)
			{
				info.en_eagle = temp + iter;
				map.at((temp + iter)->position).pos_en_unit.push_back(temp + iter);
			}
			else if ((temp + iter)->type_name == SUPERMAN)
			{
				info.en_superman = temp + iter;
				map.at((temp + iter)->position).pos_en_unit.push_back(temp + iter);
			}
			else if ((temp + iter)->type_name == MEAT)
			{
				info.en_meat = temp + iter;
				map.at((temp + iter)->position).pos_en_unit.push_back(temp + iter);
			}
		}
		//初始化中立建筑表，将单位加至地图
		else
		{
			info.neutral_building.push_back(temp + iter);
			map.at((temp + iter)->position).pos_neutral_building = temp + iter;
		}
	}
}
struct map_info//战场地图信息表
{
	struct pos_info
	{
		pos_info(Position&pos) :pos(pos){}
		pos_info(){}
		Position pos;
		vector<Unit*> pos_my_unit;
		Unit* pos_my_building = nullptr;
		vector<Unit*> pos_en_unit;
		Unit* pos_en_building = nullptr;
		Unit* pos_neutral_building = nullptr;

		void in_range(int range, void func(Position&),Position&param)
		{
			if (range >= 1)
			{
				for (int y = -range+1; y != range; ++y)
				{
					for (int x = -range + 1; x != range; ++x)
					{
						if (abs(x) + abs(y) <= range)
						{
							func(Position(param.x + x, param.y + y));
						}
					}
				}
			}
			else
			{
				return;
			}
		}
	};
	map_info()
	{
		for (int iter1 = 0; iter1 != 100; ++iter1)
		{
			for (int iter2 = 0; iter2 != 100; ++iter2)
			{
				map[iter1 + 10 * iter2].pos.x = iter1;
				map[iter1 + 10 * iter2].pos.y = iter2;
			}
		}
	}
	pos_info&at(Position&pos)
	{
		if (pos.x >= 0 && pos.x <= 99 && pos.y >= 0 && pos.y <= 99)
		{
			return map[pos.x + pos.y * 100];
		}
		else
		{
			return none_position;
		}
	}
	pos_info*map = new pos_info[10000];
	pos_info&none_position = *new pos_info(Position(-1,-1));
};
extern map_info map;

void initialize()
{
	extern information info;
	extern map_info map;
	info.my_teamid = getTeamId();
	info.en_teamid = !info.my_teamid;
	basic_information_initialize(info.my_teamid);
	basic_information_initialize(info.en_teamid);
	unit_info_initialize();
}
