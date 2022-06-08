#include<vector>
#include<iostream>
#include"map.h"
#include"passenger.h"
#include"vihicle.h"
#include"Allocation.h"
#include"utility.h"
using namespace std;


int main() {
	/*
	//头文件类的创建
	Map SL_Map;
	Vehicle_List SL_Vehicle_List;
	Passenger_List SL_Passenger_List;
	Allocation SL_Allocation;
	*/

	//建图
	SL_Map.site_acquisition();
	SL_Map.graph_creation();

	//模拟：每一分钟作为一轮
	for (int i = 1; i <= 1440; i++)
	{	
		SL_Passenger_List.Generate_passenger_info();//生成新的乘客订单
		SL_Passenger_List.Read_passenger_info();//将新的乘客订单放入对应的位置

		SL_Allocation.Str_One();//进行匹配+更新数据
		SL_Allocation.Str_Outcome();//输出结果数据

		SL_Vehicle_List.Utilize_Car_Info();//车辆初始化
		SL_Passenger_List.Clear_info();//对乘客相关信息的清除
	}
}
//1、关于类的实例化的问题
//2、关于passenger的问题
//3、车辆速度是多少
//4、考虑strOne执行后对数据的改变！！如何比对两人的影响
//5、strone和strtwo的区别？？