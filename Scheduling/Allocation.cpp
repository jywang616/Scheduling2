/*匹配策略一：
1、在满足所有乘客最短路径需求的同时进行拼单
步骤：
1.就经过站点数由大到小排列
2.一辆辆车寻找离车最近的且途径站点最多的订单a（若没有合适站点则循环直至找到最近站点or该轮全部订单结束）
3.由a做匹配项，寻找有无a的子集（终止条件是：1.满4个订单 2.该轮乘客匹配完）
*/

#include <iostream>
#include<vector>
#include<algorithm>
#include "vihicle.h"
#include "utility.h"
#include"Allocation.h"
#include "passenger.h"
#include "map.h"

bool cmp(Quest x, Quest y) {
	vector<vector<int>>Path = SL_Map.Get_Path();
	vector<int>::iterator it;
	int val1 = 0;
	for (it = Path[x.startPos].begin(); it != Path[x.startPos].end(); ++it) {
		if (*it == x.endPos) break;
		else val1++;
	}
	int val2 = 0;
	for (it = Path[y.startPos].begin(); it != Path[y.startPos].end(); ++it) {
		if (*it == y.endPos) break;
		else val2++;
	}
	if (val1 > val2) return true;
	else return false;
}

int is_in_path(Quest cus, Each_Car* car) {
	int flag = 0;
	int count = 0;
	vector<int>::iterator it;
	for (it = car->tobeTravelled.begin(); it != car->tobeTravelled.end(); ++it) {
		if (flag == 0) count++;
		if (*it == cus.startPos) flag = 1;
		if (flag == 1 && (*it) == cus.endPos) return count;
	}
	return -1;
}

bool All_Passenger_Pick() {
	vector<Quest> Passenger_Info = SL_Passenger_List.Read_passenger_info();
	vector<Quest>::iterator it;
	for (it = Passenger_Info.begin(); it != Passenger_Info.end(); ++it) {
		if (it->is_quest == 0) return false;
	}
	return true;
}

bool All_Car_Work() {
	vector<Each_Car*> Car_Info = SL_Vehicle_List.Get_Car_Info();
	vector<Each_Car*>::iterator it;
	for (it = Car_Info.begin(); it != Car_Info.end(); ++it) {
		if ((*it)->determination == 0) return false;
	}
	return true;
}

void Allocation::Str_One() {
	
	//获取车辆和用户的状态
	vector<vector<int>>Path = SL_Map.Get_Path();
	vector<vector<int>> Distance = SL_Map.Get_Distance();//地图信息
	vector<Each_Car*> Car_Info = SL_Vehicle_List.Get_Car_Info();//车辆信息（目前所在地），匹配结束后可以调用回该函数，更改其数据
	vector<Quest> Passenger_Info = SL_Passenger_List.Read_passenger_info();//乘客信息（id，起始点，终点）

	//进行匹配算法
	//排序，从站点大到小排序
	sort(Passenger_Info.begin(), Passenger_Info.end(),cmp);
	/*
	vector<Quest>::iterator it;
	for (it = Passenger_Info.begin(); it != Passenger_Info.end(); ++it)
		cout << *it << " ";
	*/

	//车寻找离车最近的且途径站点最多的订单a（无限循环直到所有乘客都被接到，车第一次接最近的乘客，第二次接第二近的乘客）
	vector<Each_Car*> ::iterator it;
	int count = -2;//作为选择最近点的指针
	int SL_pick_positon = 0;//模拟车辆i接客位置

	while (true) {

		//接客点更改+判断是否所有接客点都遍历了一次
		count++;
		if (count == Path.size()) break;

		//判断是否所有乘客都被接上+所有车都已经接到人
		if (All_Passenger_Pick) break;
		if (All_Car_Work) break;

		//车辆进行匹配
		for (it = Car_Info.begin(); it != Car_Info.end(); ++it) {
			//若车辆未进入工作状态（即上一轮未成功匹配）
			if ((*it)->determination == 0) {

				//获取车辆i接客位置
				if (count == -1) SL_pick_positon = (*it)->current_position;
				else SL_pick_positon = Path[(*it)->current_position][count];//从车的位置开始查找距离车最近的点

				//对所有乘客进行遍历
				for (int i = 0; i < Passenger_Info.size(); ++i) {
					if (Passenger_Info[i].is_quest == 0)//0是乘客未搭载吗？？？
						if ((*it)->determination == 0)//车未搭载乘客？（第一个乘客储存其行进路线）
						{
							if (Passenger_Info[i].startPos == SL_pick_positon) {
								//更新名单--数据更新
								SL_Vehicle_List.Update_Car_Info(*it, Passenger_Info[i].endPos, &Passenger_Info[i]);
								SL_Passenger_List.Update_Passenger_Info(&Passenger_Info[i], Distance[(*it)->current_position][count]);
								//Passenger_Info[i].is_quest = 1;
							}
						}
						else {//接到第一位客人之后，就开始去寻找拼车问题
							//如果乘客startpos在车的tobetravel中，endpos也在
							int point = is_in_path(Passenger_Info[i], *it);
							if (point!=-1) {
								//更新名单--数据更新
								SL_Vehicle_List.Update_Car_Info(*it, Passenger_Info[i].endPos, &Passenger_Info[i]);
								int far_dis = Distance[(*it)->current_position][count] + Distance[SL_pick_positon][point];
								SL_Passenger_List.Update_Passenger_Info(&Passenger_Info[i],far_dis);
								//Passenger_Info[i].is_quest = 1;
							}
						}
					//若刚好满员，跳出
					if ((*it)->capacity == (*it)->custNum) break;
				}
			}
		}
	}


}


//输出结果（结束了一轮）
//遍历车：每辆车的乘客容量+所接乘客名单（*QUEST）+目的地之前会经过的点
//对应的车遍历乘客：乘客id+乘客的行走路线+乘客等候时间
void Allocation::Str_Outcome() {
	vector<Each_Car*> Car_Info = SL_Vehicle_List.Get_Car_Info();//车辆信息（目前所在地），匹配结束后可以调用回该函数，更改其数据
	for (int i = 0; i < Car_Info.size(); ++i) {
		cout << "第" << i << "辆车在第" << "X" << "分钟的行驶数据: "<<endl;
		cout << "乘客数量：" << Car_Info[i]->custNum<<endl;
		vector<Quest*>::iterator it;
		for (it = Car_Info[i]->Pick_Passenger.begin(); it != Car_Info[i]->Pick_Passenger.end(); ++it) {
			cout << "乘客id：" << (*it)->id << "waiting time: " << (*it)->WaitingTime << "行走路线：";
			for (int i = 0; i < (*it)->RidingPath.size()-1; ++i) {
				cout << (*it)->RidingPath[i] << "-->";
			}
			cout << (*it)->endPos << endl;
		}
	}
	cout << endl << endl;
	//通过哪些信息进行比较
	//车和人为主体都输出一遍模拟过程
}

/*
核心算法：
1、第一层循环（乘客全部接上or车辆全部运行or所有接客点均遍历一次-->跳出）->设定该轮每辆车的接客点i（最近点、第二近点、第三近点）
2、第二层循环（对所有车辆进行遍历）
	->判断车i是否接客（未接客）
		获取车辆i的接客位置SL_pick_position;
	3、第三层循环（对乘客进行遍历）
		->判断乘客j是否被搭载（未搭载）
			->判断车i是否接客（未接客）
				->判断乘客j的startpos与车辆i的SL_pick_position是否相等（相等）
					车辆参数更新（车的终点、车的行驶路径、车的搭载人id）
					乘客参数更新（已上车）//是否需要增加更多参数
			->判断车i是否接客（已接客--拼车）
				-> 判断乘客i的startpos和endpos是否在车i的tobetravell中（在--可拼车）
					车辆参数更新（车的搭载人id)
					乘客参数更新（已上车）
			->判断车i是否满员，若满员，跳出第三层循环
Q：
1、轮：每一分钟一次（乘客全部接上or车辆全部运行or所有接客点均遍历一次）
【未接到的乘客进入下一轮->等待时间+1，已完成订单的车也进入下一轮）
2、乘客参数信息太少（waittime-车到人、pos-乘客所经过的站点、gotime-大概行驶时间）
*/


/*策略二：做动态规划*/
