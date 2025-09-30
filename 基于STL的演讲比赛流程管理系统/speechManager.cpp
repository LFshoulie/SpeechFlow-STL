#include "speechManager.h"

//���캯��
SpeechManager::SpeechManager()
{
	//��ʼ������
	this->InitSpeech();

	//����ѡ��
	this->CreateSpeaker();

	//��ȡ��¼
	this->LoadRecord();
}

//�˵�����
void SpeechManager::Show_Menu()
{
	cout << "*********************************************" << endl;
	cout << "*********      ��ӭ�μ��ݽ�����     *********" << endl;
	cout << "*********    ��1������ʼ�ݽ�����    *********" << endl;
	cout << "*********    ��2�����鿴�����¼    *********" << endl;
	cout << "*********    ��3������ձ�����¼    *********" << endl;
	cout << "*********    ��0�����˳���������    *********" << endl;
	cout << "*********************************************" << endl;
	cout << endl;
}

//�˳�����
void SpeechManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);  //�˳�����
}


//��ʼ������
void SpeechManager::InitSpeech()
{
	//�����ÿ�
	this->v1.clear();
	this->v2.clear();
	this->v_vector.clear();
	this->m_Speaker.clear();
	this->m_Recod.clear();

	//��ʼ����������
	this->m_Index = 1;
}

//����ѡ��
void SpeechManager::CreateSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		//��������ѡ��
		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		//����ѡ�ֱ��  �������� v1��
		this->v1.push_back(i+1001);

		//ѡ�ֱ�� �Լ���Ӧѡ��  ����map������
		this->m_Speaker.insert(make_pair(i + 1001, sp));
	}
}

//��ǩ
void SpeechManager::SpeechDraw()
{
	//����ʱ������
	srand((unsigned int)time(NULL));

	cout << "-------------------------" << endl;
	cout << "��<<" << this->m_Index << ">>�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-------------------------" << endl;

	cout << "\n��ǩ���ݽ�˳������" << endl;
	if (this->m_Index == 1)  //��һ��
	{
		//ϴ��
		random_shuffle(v1.begin(), v1.end());
		
		//��ӡϴ�ƺ�Ľ��
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else    //�ڶ���
	{
		//ϴ��
		random_shuffle(v2.begin(), v2.end());

		//��ӡϴ�ƺ�Ľ��
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

//����
void SpeechManager::SpeechContest()
{
	//����ʱ������
	srand((unsigned int)time(NULL));

	cout << "-------------------------" ;
	cout << "��<<" << this->m_Index << ">>�ֱ�����ʽ��ʼ" ;
	cout << "---------------------" << endl;

	multimap<double, int, greater<double>> groupScore;  //��ʱ����  �������  value ѡ�ֱ��

	int num = 0;  //��¼��Ա����6��Ϊһ��

	vector<int> v_Src;  //��������Ա����
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//�������в���ѡ��
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;

		//��ί���
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;   //600~10000
			d.push_back(score);
		}

		sort(d.begin(), d.end(),greater<double>());       //����
		d.pop_front();                                    //ȥ����߷�
		d.pop_back();                                     //ȥ����ͷ�
	
		double temp = 0;
		double sum = accumulate(d.begin(), d.end(),temp);
		double avg = sum / d.size();

		//ÿ����ƽ����
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
	
		//6��һ�飬����ʱ��������
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "-------------------------" << endl;
			cout << "��<<" << num / 6 << ">>С���������" << endl;
			cout << "-------------------------" << endl;

			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "���: " << it->second
					<< "\t����: " << this->m_Speaker[it->second].m_Name
					<< "\t�ɼ�: " << this->m_Speaker[it->second].m_Score[this->m_Index-1] << endl;
			}

			//ȡǰ����
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
	cout << "��<<" << this->m_Index << ">>�ֱ������" ;
	cout << "-------------------------" << endl;
	system("pause");

}

//��ʾ�����ɼ�
void SpeechManager::ShowScore()
{
	cout << "-------------------------";
	cout << "��<<" << this->m_Index << ">>�ֽ���ѡ����Ϣ����";
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
		cout << "���: " << *it
			<< "\t����: " << m_Speaker[*it].m_Name
			<< "\t�ɼ�: " << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->Show_Menu();
}

//�������
void  SpeechManager::SaveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	//��ÿ��������д���ļ���
	for (vector<int>::iterator it = v_vector.begin(); it != v_vector.end(); it++)
	{
		ofs << *it << ","
			<< m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	
	//�ر��ļ�
	ofs.close();

	cout << "��¼�ѱ���" << endl;

	//�����ļ�Ϊ��״̬
	this->FileIsEmpty = false;
}

//ģ���������
void SpeechManager::StartSpeech()
{
	//��һ�ֱ���
	//1����ǩ
	this->SpeechDraw();

	//2������
	this->SpeechContest();
	
	//3����ʾ�������
	this->ShowScore();


	//�ڶ��ֱ���
	this->m_Index++;
	//1����ǩ
	this->SpeechDraw();

	//2������
	this->SpeechContest();

	//3����ʾ�������
	this->ShowScore();
	
	//�������
	this->SaveRecord();

	//���ñ���  ��ȡ��¼
	//��ʼ������
	this->InitSpeech();

	//����ѡ��
	this->CreateSpeaker();

	//��ȡ��¼
	this->LoadRecord();

	cout << "����������" << endl;
	system("pause");
	system("cls");

}

//��ȡ��¼
void SpeechManager::LoadRecord()
{
	ifstream ifs;
	ifs.open("speech.csv", ios::in);

	if (!ifs.is_open())
	{
		this->FileIsEmpty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		this->FileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->FileIsEmpty = false;

	ifs.putback(ch);   //����ȡ�ĵ����ַ��Ż�ȥ

	string data;
	int Index = 0;

	while (ifs >> data)
	{
		vector<string> v;

		int pos = -1;
		int start = 0;

		while (1)
		{
			pos = data.find(",", start);  //��0��ʼ����
			if (pos == -1)
			{
				break;  //�Ҳ���break����
			}
			
			/*�ҵ��ˣ����зָ����1  ��ʼλ��  ������2  ��ȡ����*/
			string tmp = data.substr(start, pos - start);

			v.push_back(tmp);
			start = pos + 1;
		}

		this->m_Recod.insert(make_pair(Index, v));
		Index++;
	}
	ifs.close();
}

//�鿴��¼
void SpeechManager::ShowRecord()
{
	if (this->FileIsEmpty)
	{
		cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Recod.size(); i++)
		{
			cout << "-------------��" << i + 1 << "��-------------" << endl
				<< "�ھ����:  " << this->m_Recod[i][0] << "\t�÷�:  " << this->m_Recod[i][1] << endl
				<< "�Ǿ����:  " << this->m_Recod[i][2] << "\t�÷�:  " << this->m_Recod[i][3] << endl
				<< "�������:  " << this->m_Recod[i][4] << "\t�÷�:  " << this->m_Recod[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}

//��ռ�¼
void SpeechManager::ClearRecord()
{
	cout << "ȷ�������" << endl;
	cout << "1,ȷ��" << endl;
	cout << "2,����" << endl;
	
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		ofs.open("speech.csv", ios::trunc);
		ofs.close();

		//��ʼ������
		this->InitSpeech();

		//����ѡ��
		this->CreateSpeaker();

		//��ȡ��¼
		this->LoadRecord();

		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}

//��������
SpeechManager::~SpeechManager()
{

}