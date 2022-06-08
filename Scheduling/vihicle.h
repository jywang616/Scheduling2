#pragma once 

#include<vector>
#include"utility.h"

//һ���ڳ�����Ϣ
class Vehicle_List {
public:
	Vehicle_List();
	~Vehicle_List();
	//�������ݣ�һ����ָ����������ֹͣ�����������һ�ֵĳ�ʼ��
	void Utilize_Car_Info();
	//ÿһ���ӵĳ�����ʼ��
	void Update_Car_Info(Each_Car* car, int next_pos, Quest* passenger);
	//��Զ���Խ���Ĵ���
	std::vector<Each_Car*> Get_Car_Info();
	

private:
	std::vector<Each_Car*> Car_info;//ÿ�������г�����Ϣ һ��������
	//һ��Ҫ����ַ ��Ȼû�а취����
	int Car_Amount;
}SL_Vehicle_List;


//��12�� 
/*
//ÿ������״̬
struct Each_Car {
	//double speed;
	int capacity;//ÿ�����ĳ˿�����
	int custNum;//��ǰ�����صĳ˿�����
	//int flag;//�Ƿ������һ���ӵĽӵ�
	int current_position;//Ŀǰ�ڵĵ�
	int determination;//��ǰ������Ŀ�ĵ�
	std::vector<int> tobeTravelled;//��Ŀ�ĵ�֮ǰ�ᾭ���ĵ�
	std::vector<int> Pick_Passenger;//���ӳ˿�����
};
*/