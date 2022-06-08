#pragma once
#include <iostream>
#include <cstdlib> 
#include <ctime>
#include"map.h"
#include"utility.h"
#include<vector>

//��¼ÿһ���ӳ˿���Ϣ
class Passenger_List {
public:
	Passenger_List();
	~Passenger_List();
	//Ԥ����
	//�������csv�ļ�(һ�������й˿����� �Դ��ڳ�������3-5��
	void Generate_passenger_info();
	//����ÿ���˿͵���Ϣ�������ء�Ŀ�ĵأ�-->��������
	vector<Quest> Read_passenger_info();
	//Felin:
	//����һ���еĸ�����Ϣ
	void Update_Passenger_Info(Quest* Passenger,int dis);
	//���һ���и�����Ϣ
	void Clear_info();


private:
	std::vector<Quest> Passenger_info;//һ�������г˿���Ϣ
	int Sum_Passenger_Num;//һ������������ĳ��Χ�������

}SL_Passenger_List;