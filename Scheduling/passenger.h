#pragma once
#include <iostream>
#include <cstdlib> 
#include <ctime>
#include"map.h"
#include"utility.h"
#include<vector>

//记录每一分钟乘客信息
class Passenger_List {
public:
	Passenger_List();
	~Passenger_List();
	//预处理：
	//随机生成csv文件(一轮里所有顾客请求 略大于车辆数量3-5）
	void Generate_passenger_info();
	//读入每个乘客的信息（出发地、目的地）-->放入请求
	vector<Quest> Read_passenger_info();
	//Felin:
	//更新一轮中的各种信息
	void Update_Passenger_Info(Quest* Passenger,int dis);
	//清除一轮中各种信息
	void Clear_info();


private:
	std::vector<Quest> Passenger_info;//一轮里所有乘客信息
	int Sum_Passenger_Num;//一轮里（随机数生成某范围里的数）

}SL_Passenger_List;