#include"vihicle.h"
#include"utility.h"
#include"map.h"
#include<vector>
#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>
#include<stdlib.h>
using namespace std;
//车12辆，每辆车的起始位置已知

//未开始模拟前对车辆的初始位置进行读取(capacity,custnum,current-position
Vehicle_List::Vehicle_List() {
	this->Car_Amount = 12;
	Car_info.clear();
	ifstream fp("C:\\Users\\Huilin Yao\\Desktop\\数据结构\\大作业\\Vihicle_Initialization.csv");
	string line;
	getline(fp, line);
	while (getline(fp, line)) {
		istringstream readstr(line);
		Each_Car* temp = new Each_Car();//内部已经做好了初始化
		for (int i = 0; i <= 2; i++) {
			std::string number;
			std::getline(readstr, number, ',');
			if (i == 0) { temp->capacity = atoi(number.c_str());}
			if (i == 1) { temp->custNum= atoi(number.c_str()); }
			if (i == 2) { temp->current_position = atoi(number.c_str()); }
		}
		this->Car_info.push_back(temp);
	}
}

//删除并更新数据（所有车都停止）
void Vehicle_List::Utilize_Car_Info() {
	vector<Each_Car*> ::iterator it;
	for (it = this->Car_info.begin(); it != this->Car_info.end(); it++) {
		(* it)->current_position = (*it)->determination;
		(*it)->tobeTravelled.clear();
		(*it)->Pick_Passenger.clear();
		(*it)->custNum = 0;
		(*it)->determination = 0;
	}
}

//获取起始点（每轮一次）
std::vector<Each_Car*> Vehicle_List::Get_Car_Info() {
	return this->Car_info;
}

//matching的过程中对每一辆车的信息进行更改，从而达到更改整个列表的目的
//更该参数：车辆、custNum、determination、tobeTravel
void Vehicle_List::Update_Car_Info(Each_Car* car,int next_pos,Quest* passenger) {
	//看车辆列表中的数据是否修改
	if (car->custNum == car->capacity) {
		cout << "错误加入！";
			return;
	}
	car->custNum++;
	car->Pick_Passenger.push_back(passenger);

	if (car->determination == 0) {
		car->determination = next_pos;
		vector<vector<int>>Path = SL_Map.Get_Path();
		vector<int>::iterator it;
		for (it = Path[car->current_position].begin(); it != Path[car->current_position].end(); ++it) {
			if (*it == next_pos) {
				car->tobeTravelled.push_back(next_pos);
				break;
			}
			else car->tobeTravelled.push_back(*it);
		}
	}

	return;
}

/*
struct Each_Car {
	//double speed;
	int capacity;//每辆车的乘客容量
	int custNum;//当前车上载的乘客数量
	//int flag;//是否进入下一分钟的接单
	int current_position;//目前在的点
	int determination;//当前订单的目的地
	//std::vector<Node> haveTravelled;
	std::vector<Node> tobeTravelled;//到目的地之前会经过的点
};
*/