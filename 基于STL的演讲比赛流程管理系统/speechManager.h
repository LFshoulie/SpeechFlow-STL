#pragma once
#include <iostream>
using namespace std;
#include "speaker.h"
#include <string>
#include <deque>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <functional>
#include <numeric>
#include <fstream>

//设计演讲管理类
class SpeechManager
{
public:
	//构造函数
	SpeechManager();

	//菜单功能
	void Show_Menu();

	//退出功能
	void ExitSystem();

	//初始化属性
	void InitSpeech();

	//模拟比赛流程
	void StartSpeech();

	//抽签
	void SpeechDraw();

	//比赛
	void SpeechContest();

	//显示比赛成绩
	void ShowScore();

	//保存分数
	void SaveRecord();

	//读取记录
	void LoadRecord();

	//查看记录
	void ShowRecord();

	//创建选手
	void CreateSpeaker();

	//清空记录
	void ClearRecord();

	//析构函数
	~SpeechManager();

	/*成员属性*/
	//比赛选手  容器  初赛12人
	vector<int> v1;

	//第一轮晋级选手  容器  6人
	vector<int> v2;

	//胜利前三名  容器
	vector<int> v_vector;

	//存放编号  以及对应的  具体选手  容器
	map<int, Speaker>m_Speaker;

	//记录比赛轮数
	int m_Index;

	//判断文件是否为空
	bool FileIsEmpty;

	//存放往届记录的容器
	map<int, vector<string>> m_Recod;
};
