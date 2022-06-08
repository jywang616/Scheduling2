/*ƥ�����һ��
1�����������г˿����·�������ͬʱ����ƴ��
���裺
1.�;���վ�����ɴ�С����
2.һ������Ѱ���복�������;��վ�����Ķ���a����û�к���վ����ѭ��ֱ���ҵ����վ��or����ȫ������������
3.��a��ƥ���Ѱ������a���Ӽ�����ֹ�����ǣ�1.��4������ 2.���ֳ˿�ƥ���꣩
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
	
	//��ȡ�������û���״̬
	vector<vector<int>>Path = SL_Map.Get_Path();
	vector<vector<int>> Distance = SL_Map.Get_Distance();//��ͼ��Ϣ
	vector<Each_Car*> Car_Info = SL_Vehicle_List.Get_Car_Info();//������Ϣ��Ŀǰ���ڵأ���ƥ���������Ե��ûظú���������������
	vector<Quest> Passenger_Info = SL_Passenger_List.Read_passenger_info();//�˿���Ϣ��id����ʼ�㣬�յ㣩

	//����ƥ���㷨
	//���򣬴�վ���С����
	sort(Passenger_Info.begin(), Passenger_Info.end(),cmp);
	/*
	vector<Quest>::iterator it;
	for (it = Passenger_Info.begin(); it != Passenger_Info.end(); ++it)
		cout << *it << " ";
	*/

	//��Ѱ���복�������;��վ�����Ķ���a������ѭ��ֱ�����г˿Ͷ����ӵ�������һ�ν�����ĳ˿ͣ��ڶ��νӵڶ����ĳ˿ͣ�
	vector<Each_Car*> ::iterator it;
	int count = -2;//��Ϊѡ��������ָ��
	int SL_pick_positon = 0;//ģ�⳵��i�ӿ�λ��

	while (true) {

		//�ӿ͵����+�ж��Ƿ����нӿ͵㶼������һ��
		count++;
		if (count == Path.size()) break;

		//�ж��Ƿ����г˿Ͷ�������+���г����Ѿ��ӵ���
		if (All_Passenger_Pick) break;
		if (All_Car_Work) break;

		//��������ƥ��
		for (it = Car_Info.begin(); it != Car_Info.end(); ++it) {
			//������δ���빤��״̬������һ��δ�ɹ�ƥ�䣩
			if ((*it)->determination == 0) {

				//��ȡ����i�ӿ�λ��
				if (count == -1) SL_pick_positon = (*it)->current_position;
				else SL_pick_positon = Path[(*it)->current_position][count];//�ӳ���λ�ÿ�ʼ���Ҿ��복����ĵ�

				//�����г˿ͽ��б���
				for (int i = 0; i < Passenger_Info.size(); ++i) {
					if (Passenger_Info[i].is_quest == 0)//0�ǳ˿�δ�����𣿣���
						if ((*it)->determination == 0)//��δ���س˿ͣ�����һ���˿ʹ������н�·�ߣ�
						{
							if (Passenger_Info[i].startPos == SL_pick_positon) {
								//��������--���ݸ���
								SL_Vehicle_List.Update_Car_Info(*it, Passenger_Info[i].endPos, &Passenger_Info[i]);
								SL_Passenger_List.Update_Passenger_Info(&Passenger_Info[i], Distance[(*it)->current_position][count]);
								//Passenger_Info[i].is_quest = 1;
							}
						}
						else {//�ӵ���һλ����֮�󣬾Ϳ�ʼȥѰ��ƴ������
							//����˿�startpos�ڳ���tobetravel�У�endposҲ��
							int point = is_in_path(Passenger_Info[i], *it);
							if (point!=-1) {
								//��������--���ݸ���
								SL_Vehicle_List.Update_Car_Info(*it, Passenger_Info[i].endPos, &Passenger_Info[i]);
								int far_dis = Distance[(*it)->current_position][count] + Distance[SL_pick_positon][point];
								SL_Passenger_List.Update_Passenger_Info(&Passenger_Info[i],far_dis);
								//Passenger_Info[i].is_quest = 1;
							}
						}
					//���պ���Ա������
					if ((*it)->capacity == (*it)->custNum) break;
				}
			}
		}
	}


}


//��������������һ�֣�
//��������ÿ�����ĳ˿�����+���ӳ˿�������*QUEST��+Ŀ�ĵ�֮ǰ�ᾭ���ĵ�
//��Ӧ�ĳ������˿ͣ��˿�id+�˿͵�����·��+�˿͵Ⱥ�ʱ��
void Allocation::Str_Outcome() {
	vector<Each_Car*> Car_Info = SL_Vehicle_List.Get_Car_Info();//������Ϣ��Ŀǰ���ڵأ���ƥ���������Ե��ûظú���������������
	for (int i = 0; i < Car_Info.size(); ++i) {
		cout << "��" << i << "�����ڵ�" << "X" << "���ӵ���ʻ����: "<<endl;
		cout << "�˿�������" << Car_Info[i]->custNum<<endl;
		vector<Quest*>::iterator it;
		for (it = Car_Info[i]->Pick_Passenger.begin(); it != Car_Info[i]->Pick_Passenger.end(); ++it) {
			cout << "�˿�id��" << (*it)->id << "waiting time: " << (*it)->WaitingTime << "����·�ߣ�";
			for (int i = 0; i < (*it)->RidingPath.size()-1; ++i) {
				cout << (*it)->RidingPath[i] << "-->";
			}
			cout << (*it)->endPos << endl;
		}
	}
	cout << endl << endl;
	//ͨ����Щ��Ϣ���бȽ�
	//������Ϊ���嶼���һ��ģ�����
}

/*
�����㷨��
1����һ��ѭ�����˿�ȫ������or����ȫ������or���нӿ͵������һ��-->������->�趨����ÿ�����Ľӿ͵�i������㡢�ڶ����㡢�������㣩
2���ڶ���ѭ���������г������б�����
	->�жϳ�i�Ƿ�ӿͣ�δ�ӿͣ�
		��ȡ����i�Ľӿ�λ��SL_pick_position;
	3��������ѭ�����Գ˿ͽ��б�����
		->�жϳ˿�j�Ƿ񱻴��أ�δ���أ�
			->�жϳ�i�Ƿ�ӿͣ�δ�ӿͣ�
				->�жϳ˿�j��startpos�복��i��SL_pick_position�Ƿ���ȣ���ȣ�
					�����������£������յ㡢������ʻ·�������Ĵ�����id��
					�˿Ͳ������£����ϳ���//�Ƿ���Ҫ���Ӹ������
			->�жϳ�i�Ƿ�ӿͣ��ѽӿ�--ƴ����
				-> �жϳ˿�i��startpos��endpos�Ƿ��ڳ�i��tobetravell�У���--��ƴ����
					�����������£����Ĵ�����id)
					�˿Ͳ������£����ϳ���
			->�жϳ�i�Ƿ���Ա������Ա������������ѭ��
Q��
1���֣�ÿһ����һ�Σ��˿�ȫ������or����ȫ������or���нӿ͵������һ�Σ�
��δ�ӵ��ĳ˿ͽ�����һ��->�ȴ�ʱ��+1������ɶ����ĳ�Ҳ������һ�֣�
2���˿Ͳ�����Ϣ̫�٣�waittime-�����ˡ�pos-�˿���������վ�㡢gotime-�����ʻʱ�䣩
*/


/*���Զ�������̬�滮*/
