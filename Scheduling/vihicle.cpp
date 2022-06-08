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
//��12����ÿ��������ʼλ����֪

//δ��ʼģ��ǰ�Գ����ĳ�ʼλ�ý��ж�ȡ(capacity,custnum,current-position
Vehicle_List::Vehicle_List() {
	this->Car_Amount = 12;
	Car_info.clear();
	ifstream fp("C:\\Users\\Huilin Yao\\Desktop\\���ݽṹ\\����ҵ\\Vihicle_Initialization.csv");
	string line;
	getline(fp, line);
	while (getline(fp, line)) {
		istringstream readstr(line);
		Each_Car* temp = new Each_Car();//�ڲ��Ѿ������˳�ʼ��
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

//ɾ�����������ݣ����г���ֹͣ��
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

//��ȡ��ʼ�㣨ÿ��һ�Σ�
std::vector<Each_Car*> Vehicle_List::Get_Car_Info() {
	return this->Car_info;
}

//matching�Ĺ����ж�ÿһ��������Ϣ���и��ģ��Ӷ��ﵽ���������б��Ŀ��
//���ò�����������custNum��determination��tobeTravel
void Vehicle_List::Update_Car_Info(Each_Car* car,int next_pos,Quest* passenger) {
	//�������б��е������Ƿ��޸�
	if (car->custNum == car->capacity) {
		cout << "������룡";
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
	int capacity;//ÿ�����ĳ˿�����
	int custNum;//��ǰ�����صĳ˿�����
	//int flag;//�Ƿ������һ���ӵĽӵ�
	int current_position;//Ŀǰ�ڵĵ�
	int determination;//��ǰ������Ŀ�ĵ�
	//std::vector<Node> haveTravelled;
	std::vector<Node> tobeTravelled;//��Ŀ�ĵ�֮ǰ�ᾭ���ĵ�
};
*/