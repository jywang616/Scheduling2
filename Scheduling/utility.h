#pragma once
/*
struct Node
{
	double x;
	double y;
};

struct Edge
{
	Node startNode;
	Node endNote;
	double length;
};

struct Position {
	Edge edge;
	double acc;
};
*/

//每个用户请求
struct Quest {
	int id;
	int is_quest;
	int startPos;
	int endPos;
	//double submitTime;
	int WaitingTime;
	std::vector<int> RidingPath;
};
//新添：waiting time(车过去的时间+进入每一轮的时间）+ 行走路线(vector<int>类型)最好 RidingPath + 被哪辆车接走

//每辆车的状态
struct Each_Car {
	//double speed;
	int capacity;//每辆车的乘客容量
	int current_position;//目前在的点

	int custNum;//当前车上载的乘客数量
	//int flag;//是否进入下一分钟的接单
	int determination;//当前订单的目的地(同时也作为是否在订单进行中的标志）
	std::vector<int> tobeTravelled;//到目的地之前会经过的点
	std::vector<Quest*> Pick_Passenger;//所接乘客名单
	
	Each_Car() {
		capacity = 0;
		custNum = 0;
		current_position = 0;
		determination = 0;
		tobeTravelled.clear();
		Pick_Passenger.clear();
	}
};

//两个不同策略的返回比较值
struct Outcome {

};

//map的一些个中间变量
struct Son {
	int val = 0;
	int to = 0;
	int next = -1;
};