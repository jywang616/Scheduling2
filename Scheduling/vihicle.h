#pragma once 

#include<vector>
#include"utility.h"

//一轮内车的信息
class Vehicle_List {
public:
	Vehicle_List();
	~Vehicle_List();
	//更新数据（一轮是指所有汽车都停止的情况），下一轮的初始化
	void Utilize_Car_Info();
	//每一分钟的车辆初始化
	void Update_Car_Info(Each_Car* car, int next_pos, Quest* passenger);
	//配对对配对结果的储存
	std::vector<Each_Car*> Get_Car_Info();
	

private:
	std::vector<Each_Car*> Car_info;//每轮里所有车的信息 一轮完后更新
	//一定要传地址 不然没有办法更新
	int Car_Amount;
}SL_Vehicle_List;


//车12辆 
/*
//每辆车的状态
struct Each_Car {
	//double speed;
	int capacity;//每辆车的乘客容量
	int custNum;//当前车上载的乘客数量
	//int flag;//是否进入下一分钟的接单
	int current_position;//目前在的点
	int determination;//当前订单的目的地
	std::vector<int> tobeTravelled;//到目的地之前会经过的点
	std::vector<int> Pick_Passenger;//所接乘客名单
};
*/