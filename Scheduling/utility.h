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

//ÿ���û�����
struct Quest {
	int id;
	int is_quest;
	int startPos;
	int endPos;
	//double submitTime;
	int WaitingTime;
	std::vector<int> RidingPath;
};
//����waiting time(����ȥ��ʱ��+����ÿһ�ֵ�ʱ�䣩+ ����·��(vector<int>����)��� RidingPath + ������������

//ÿ������״̬
struct Each_Car {
	//double speed;
	int capacity;//ÿ�����ĳ˿�����
	int current_position;//Ŀǰ�ڵĵ�

	int custNum;//��ǰ�����صĳ˿�����
	//int flag;//�Ƿ������һ���ӵĽӵ�
	int determination;//��ǰ������Ŀ�ĵ�(ͬʱҲ��Ϊ�Ƿ��ڶ��������еı�־��
	std::vector<int> tobeTravelled;//��Ŀ�ĵ�֮ǰ�ᾭ���ĵ�
	std::vector<Quest*> Pick_Passenger;//���ӳ˿�����
	
	Each_Car() {
		capacity = 0;
		custNum = 0;
		current_position = 0;
		determination = 0;
		tobeTravelled.clear();
		Pick_Passenger.clear();
	}
};

//������ͬ���Եķ��رȽ�ֵ
struct Outcome {

};

//map��һЩ���м����
struct Son {
	int val = 0;
	int to = 0;
	int next = -1;
};