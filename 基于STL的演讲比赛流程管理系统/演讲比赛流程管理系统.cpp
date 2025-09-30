#include <iostream>
using namespace std;
#include "speechManager.h"

int main()
{
	//创建管理类
	SpeechManager SM;

	//测试选手创建代码
	/*for (map<int, Speaker>::iterator it = SM.m_Speaker.begin(); it != SM.m_Speaker.end(); it++)
	{
		cout << "选手编号: " << it->first << "  姓名:  " << it->second.m_Name << " 分数:  " << it->second.m_Score[0]<<" "<<it->second.m_Score[1]<< endl;
	}*/

	//提供用户选择记录选项
	int choice = 0;

	while (1)
	{
		//展示菜单界面
		SM.Show_Menu();

		//程序功能选择
		cout << "请输入您的功能选择" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:  //开始演讲比赛
			SM.StartSpeech();
			break;
		case 2:  //查看往届记录
			SM.ShowRecord();
			break;
		case 3:  //清空比赛记录
			SM.ClearRecord();
			break;
		case 0:  //退出比赛流程
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