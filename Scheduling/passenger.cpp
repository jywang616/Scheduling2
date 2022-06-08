#include"passenger.h"
#include"utility.h"
#include<vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include<string>
using namespace std;

//Felin��
Passenger_List::Passenger_List() {
	this->Sum_Passenger_Num = 0;
	Passenger_info.clear();
}

//Ԥ����
//�������csv�ļ�(һ�������й˿����� �Դ��ڳ�������3-5��
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
//����ÿ���˿͵���Ϣ�������ء�Ŀ�ĵأ�-->��������
vector<Quest> Passenger_List::Read_passenger_info()
{
	FILE* fp;
	vector<Quest> passenger_info;
	Quest Request;
	fopen_s(&fp,"passenger_list.csv", "r");//�ļ�·��(û��ȫ�ģ�
	while (1)
	{
		fscanf_s(fp, "%d,%d,%f,%f", &Request.id, &Request.startPos, &Request.endPos);
		passenger_info.push_back(Request);
		if (feof(fp)) break;
	}
	fclose(fp);
	return passenger_info;
	//Felin: is_quest, WaitingTime, RidingPath��Ҫ����
}

//Felin:
// ����һ���еĸ�����Ϣ
void Passenger_List::Update_Passenger_Info(Quest* Passenger, int dis) {
	Passenger->is_quest = 1;
	//�����˵ľ���+�˽����X�ֵ�ʱ��(�������ٶ��Ƕ��٣���
	Passenger->WaitingTime += dis / 10/*speed*/;

	//��startPos�ߵ�endPos
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

//Felin��
//���һ���и�����Ϣ
void Passenger_List::Clear_info()
{
	ofstream fileout("passenger_list.csv", ios_base::out);//ios::trunc�����ԭ�ļ�����,�ɲ�д,Ĭ�Ͼ�����
	if (!fileout) {
		cout << "Clear successfully!\n";
		exit(0);
	}
	fileout.close();
	//Felin��
	this->Passenger_info.clear();
	this->Sum_Passenger_Num = 0;
}