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
	//ͷ�ļ���Ĵ���
	Map SL_Map;
	Vehicle_List SL_Vehicle_List;
	Passenger_List SL_Passenger_List;
	Allocation SL_Allocation;
	*/

	//��ͼ
	SL_Map.site_acquisition();
	SL_Map.graph_creation();

	//ģ�⣺ÿһ������Ϊһ��
	for (int i = 1; i <= 1440; i++)
	{	
		SL_Passenger_List.Generate_passenger_info();//�����µĳ˿Ͷ���
		SL_Passenger_List.Read_passenger_info();//���µĳ˿Ͷ��������Ӧ��λ��

		SL_Allocation.Str_One();//����ƥ��+��������
		SL_Allocation.Str_Outcome();//����������

		SL_Vehicle_List.Utilize_Car_Info();//������ʼ��
		SL_Passenger_List.Clear_info();//�Գ˿������Ϣ�����
	}
}
//1���������ʵ����������
//2������passenger������
//3�������ٶ��Ƕ���
//4������strOneִ�к�����ݵĸı䣡����αȶ����˵�Ӱ��
//5��strone��strtwo�����𣿣�