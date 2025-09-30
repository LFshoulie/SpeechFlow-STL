#include "speechManager.h"

//构造函数
SpeechManager::SpeechManager()
{
	//初始化属性
	this->InitSpeech();

	//创建选手
	this->CreateSpeaker();

	//读取记录
	this->LoadRecord();
}

//菜单功能
void SpeechManager::Show_Menu()
{
	cout << "*********************************************" << endl;
	cout << "*********      欢迎参加演讲比赛     *********" << endl;
	cout << "*********    【1】，开始演讲比赛    *********" << endl;
	cout << "*********    【2】，查看往届记录    *********" << endl;
	cout << "*********    【3】，清空比赛记录    *********" << endl;
	cout << "*********    【0】，退出比赛程序    *********" << endl;
	cout << "*********************************************" << endl;
	cout << endl;
}

//退出功能
void SpeechManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);  //退出程序
}


//初始化属性
void SpeechManager::InitSpeech()
{
	//容器置空
	this->v1.clear();
	this->v2.clear();
	this->v_vector.clear();
	this->m_Speaker.clear();
	this->m_Recod.clear();

	//初始化比赛轮数
	this->m_Index = 1;
}

//创建选手
void SpeechManager::CreateSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		//创建具体选手
		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		//创建选手编号  放入容器 v1中
		this->v1.push_back(i+1001);

		//选手编号 以及对应选手  放入map容器中
		this->m_Speaker.insert(make_pair(i + 1001, sp));
	}
}

//抽签
void SpeechManager::SpeechDraw()
{
	//包含时间种子
	srand((unsigned int)time(NULL));

	cout << "-------------------------" << endl;
	cout << "第<<" << this->m_Index << ">>轮比赛选手正在抽签" << endl;
	cout << "-------------------------" << endl;

	cout << "\n抽签后演讲顺序如下" << endl;
	if (this->m_Index == 1)  //第一轮
	{
		//洗牌
		random_shuffle(v1.begin(), v1.end());
		
		//打印洗牌后的结果
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else    //第二轮
	{
		//洗牌
		random_shuffle(v2.begin(), v2.end());

		//打印洗牌后的结果
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-------------------------" << endl;
	system("pause");
	cout << endl;
}

//比赛
void SpeechManager::SpeechContest()
{
	//包含时间种子
	srand((unsigned int)time(NULL));

	cout << "-------------------------" ;
	cout << "第<<" << this->m_Index << ">>轮比赛正式开始" ;
	cout << "---------------------" << endl;

	multimap<double, int, greater<double>> groupScore;  //临时容器  保存分数  value 选手编号

	int num = 0;  //记录人员数，6个为一组

	vector<int> v_Src;  //比赛的人员容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//遍历所有参赛选手
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;

		//评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;   //600~10000
			d.push_back(score);
		}

		sort(d.begin(), d.end(),greater<double>());       //排序
		d.pop_front();                                    //去掉最高分
		d.pop_back();                                     //去掉最低分
	
		double temp = 0;
		double sum = accumulate(d.begin(), d.end(),temp);
		double avg = sum / d.size();

		//每个人平均分
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
	
		//6人一组，用临时容器保存
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "-------------------------" << endl;
			cout << "第<<" << num / 6 << ">>小组比赛名次" << endl;
			cout << "-------------------------" << endl;

			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号: " << it->second
					<< "\t姓名: " << this->m_Speaker[it->second].m_Name
					<< "\t成绩: " << this->m_Speaker[it->second].m_Score[this->m_Index-1] << endl;
			}

			//取前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count<3;it++,count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					v_vector.push_back((*it).second);
				}
			}

			groupScore.clear();
			cout << endl;
		}
	}

	cout << "-------------------------";
	cout << "第<<" << this->m_Index << ">>轮比赛完毕" ;
	cout << "-------------------------" << endl;
	system("pause");

}

//显示比赛成绩
void SpeechManager::ShowScore()
{
	cout << "-------------------------";
	cout << "第<<" << this->m_Index << ">>轮晋级选手信息如下";
	cout << "-----------------" << endl;

	vector<int> v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = v_vector;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "编号: " << *it
			<< "\t姓名: " << m_Speaker[*it].m_Name
			<< "\t成绩: " << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->Show_Menu();
}

//保存分数
void  SpeechManager::SaveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	//将每个人数据写入文件中
	for (vector<int>::iterator it = v_vector.begin(); it != v_vector.end(); it++)
	{
		ofs << *it << ","
			<< m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	
	//关闭文件
	ofs.close();

	cout << "记录已保存" << endl;

	//更改文件为空状态
	this->FileIsEmpty = false;
}

//模拟比赛流程
void SpeechManager::StartSpeech()
{
	//第一轮比赛
	//1，抽签
	this->SpeechDraw();

	//2，比赛
	this->SpeechContest();
	
	//3，显示晋级结果
	this->ShowScore();


	//第二轮比赛
	this->m_Index++;
	//1，抽签
	this->SpeechDraw();

	//2，比赛
	this->SpeechContest();

	//3，显示晋级结果
	this->ShowScore();
	
	//保存分数
	this->SaveRecord();

	//重置比赛  获取记录
	//初始化属性
	this->InitSpeech();

	//创建选手
	this->CreateSpeaker();

	//读取记录
	this->LoadRecord();

	cout << "本届比赛完毕" << endl;
	system("pause");
	system("cls");

}

//读取记录
void SpeechManager::LoadRecord()
{
	ifstream ifs;
	ifs.open("speech.csv", ios::in);

	if (!ifs.is_open())
	{
		this->FileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		this->FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->FileIsEmpty = false;

	ifs.putback(ch);   //将读取的单个字符放回去

	string data;
	int Index = 0;

	while (ifs >> data)
	{
		vector<string> v;

		int pos = -1;
		int start = 0;

		while (1)
		{
			pos = data.find(",", start);  //从0开始查找
			if (pos == -1)
			{
				break;  //找不到break返回
			}
			
			/*找到了，进行分割，参数1  起始位置  ，参数2  截取长度*/
			string tmp = data.substr(start, pos - start);

			v.push_back(tmp);
			start = pos + 1;
		}

		this->m_Recod.insert(make_pair(Index, v));
		Index++;
	}
	ifs.close();
}

//查看记录
void SpeechManager::ShowRecord()
{
	if (this->FileIsEmpty)
	{
		cout << "文件不存在或文件为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Recod.size(); i++)
		{
			cout << "-------------第" << i + 1 << "届-------------" << endl
				<< "冠军编号:  " << this->m_Recod[i][0] << "\t得分:  " << this->m_Recod[i][1] << endl
				<< "亚军编号:  " << this->m_Recod[i][2] << "\t得分:  " << this->m_Recod[i][3] << endl
				<< "季军编号:  " << this->m_Recod[i][4] << "\t得分:  " << this->m_Recod[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}

//清空记录
void SpeechManager::ClearRecord()
{
	cout << "确认清楚？" << endl;
	cout << "1,确认" << endl;
	cout << "2,返回" << endl;
	
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		ofs.open("speech.csv", ios::trunc);
		ofs.close();

		//初始化属性
		this->InitSpeech();

		//创建选手
		this->CreateSpeaker();

		//读取记录
		this->LoadRecord();

		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}

//析构函数
SpeechManager::~SpeechManager()
{

}