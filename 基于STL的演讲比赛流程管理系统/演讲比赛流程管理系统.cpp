#include <iostream>
using namespace std;
#include "speechManager.h"

int main()
{
	//����������
	SpeechManager SM;

	//����ѡ�ִ�������
	/*for (map<int, Speaker>::iterator it = SM.m_Speaker.begin(); it != SM.m_Speaker.end(); it++)
	{
		cout << "ѡ�ֱ��: " << it->first << "  ����:  " << it->second.m_Name << " ����:  " << it->second.m_Score[0]<<" "<<it->second.m_Score[1]<< endl;
	}*/

	//�ṩ�û�ѡ���¼ѡ��
	int choice = 0;

	while (1)
	{
		//չʾ�˵�����
		SM.Show_Menu();

		//������ѡ��
		cout << "���������Ĺ���ѡ��" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:  //��ʼ�ݽ�����
			SM.StartSpeech();
			break;
		case 2:  //�鿴�����¼
			SM.ShowRecord();
			break;
		case 3:  //��ձ�����¼
			SM.ClearRecord();
			break;
		case 0:  //�˳���������
			SM.ExitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}