#include"passenger.h"
#include"utility.h"
#include<vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include<string>
using namespace std;

//Felin：
Passenger_List::Passenger_List() {
	this->Sum_Passenger_Num = 0;
	Passenger_info.clear();
}

//预处理：
//随机生成csv文件(一轮里所有顾客请求 略大于车辆数量3-5）
void Passenger_List::Generate_passenger_info()
{
	ofstream outFile;
	outFile << "passenger_id" << ',' << "start_position" << ',' << "destination" << endl;
	int passenger_num = 0;
	passenger_num = rand() % (25 - 15 + 1) + 15;
	for (int i = 1; i < passenger_num + 1; )
	{
		int start_position = 0;
		int destination = 0;
		start_position = rand() % (9 - 1 + 1) + 1;
		destination = rand() % (9 - 1 + 1) + 1;
		if (start_position == destination)
		{
			i = i;
			continue;
		}
		else
		{
			outFile.open("passenger_list.csv", ios::out);
			outFile << i << ',' << start_position << ',' << destination << endl;
			i = i + 1;
		}

	}
	outFile.close();
}
//读入每个乘客的信息（出发地、目的地）-->放入请求
vector<Quest> Passenger_List::Read_passenger_info()
{
	FILE* fp;
	vector<Quest> passenger_info;
	Quest Request;
	fopen_s(&fp,"passenger_list.csv", "r");//文件路径(没打全的）
	while (1)
	{
		fscanf_s(fp, "%d,%d,%f,%f", &Request.id, &Request.startPos, &Request.endPos);
		passenger_info.push_back(Request);
		if (feof(fp)) break;
	}
	fclose(fp);
	return passenger_info;
	//Felin: is_quest, WaitingTime, RidingPath需要重置
}

//Felin:
// 更新一轮中的各种信息
void Passenger_List::Update_Passenger_Info(Quest* Passenger, int dis) {
	Passenger->is_quest = 1;
	//车和人的距离+人进入第X轮的时间(车辆的速度是多少？）
	Passenger->WaitingTime += dis / 10/*speed*/;

	//从startPos走到endPos
	Passenger->RidingPath.push_back(Passenger->startPos);
	vector<vector<int>>Path = SL_Map.Get_Path();
	for (int i = 0; i < Path[Passenger->startPos].size(); ++i) {
		if (Path[Passenger->startPos][i] == Passenger->endPos) {
			Passenger->RidingPath.push_back(Passenger->endPos);
			break;
		}
		Passenger->RidingPath.push_back(Path[Passenger->startPos][i]);
	}	
}

//Felin：
//清除一轮中各种信息
void Passenger_List::Clear_info()
{
	ofstream fileout("passenger_list.csv", ios_base::out);//ios::trunc是清除原文件内容,可不写,默认就是它
	if (!fileout) {
		cout << "Clear successfully!\n";
		exit(0);
	}
	fileout.close();
	//Felin：
	this->Passenger_info.clear();
	this->Sum_Passenger_Num = 0;
}