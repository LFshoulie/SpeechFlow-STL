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

//����ݽ�������
class SpeechManager
{
public:
	//���캯��
	SpeechManager();

	//�˵�����
	void Show_Menu();

	//�˳�����
	void ExitSystem();

	//��ʼ������
	void InitSpeech();

	//ģ���������
	void StartSpeech();

	//��ǩ
	void SpeechDraw();

	//����
	void SpeechContest();

	//��ʾ�����ɼ�
	void ShowScore();

	//�������
	void SaveRecord();

	//��ȡ��¼
	void LoadRecord();

	//�鿴��¼
	void ShowRecord();

	//����ѡ��
	void CreateSpeaker();

	//��ռ�¼
	void ClearRecord();

	//��������
	~SpeechManager();

	/*��Ա����*/
	//����ѡ��  ����  ����12��
	vector<int> v1;

	//��һ�ֽ���ѡ��  ����  6��
	vector<int> v2;

	//ʤ��ǰ����  ����
	vector<int> v_vector;

	//��ű��  �Լ���Ӧ��  ����ѡ��  ����
	map<int, Speaker>m_Speaker;

	//��¼��������
	int m_Index;

	//�ж��ļ��Ƿ�Ϊ��
	bool FileIsEmpty;

	//��������¼������
	map<int, vector<string>> m_Recod;
};
