#pragma once

#include <vector>

using namespace std;

#define  MAX_NUM  1000            //������󱣴������������

enum E_DIFFICULTY_TYPE		// �Ѷ�����
{
	eType_Easy		= 1,	// �� 40-45
	eType_Normal,			// ��ͨ 35-40
	eType_Hard,				// ���� 30-35
	eType_Madness,			// ��� 25-30
	eType_Hell,				// ���� 20-25
	eType_Max,
};

// ԭ��
// 1��ͨ��CreateSudokuData����һ���������ݣ�ֻ���棨��ȥ���������ʣ�����������m_data��m_user��
// 2��ͨ��CheckTheResult������û��������Ƿ���С����û�и�1���洴����������ʱ��ԭʼ���ݽ��бȽϣ�����ֱ�Ӷ���������ݣ�����һ�α����ж�
// 3��ͨ��ComputeResult���������������п��ܽ⣬����ԭ������õ���ͼ��Ӧ�������ȡһ�����������ʾ
class CSudokuGame
{
public:
	CSudokuGame();
	~CSudokuGame();

	int  m_data[9][9];     //����ԭʼ��Ϸ����
	int  m_user[9][9];      //���û���������
	vector<vector<vector<int>>> m_vecResults;	// �������п��ܵĽ������Զ��ֿ��ܽ�����
	int  m_bCompute;     //�ж��û��Ƿ���ֹ�Զ�����
	bool  m_bExit;          //��־�߳��Ƿ���ֹ�˳�

	void  Initialize();
	bool  CheckInput(const int row, const int col, const int input);   //�ж������ĳ�������Ƿ���Ч
	bool  CheckCell(const int row, const int col);            //�ж�ĳһ����Ԫ���Ƿ��д�
	bool  CheckOriginalData();   //���ԭʼ���ݵĺϷ���
	int    GetInputNum(const int row, const int col, vector<int> &integer);          //��ȡĳ����Ԫ�����п����������
	bool  CheckTheResult();      //�ж��û������Ƿ��������Ϸ
	bool  ComputeResult(vector<vector<vector<int>>> &results);       //�Զ��������������п��ܽ�
	bool CallRecurrence(int *data, int count, vector<vector<vector<int>>> &results);   //�ݹ���㣬�õ����п��ܵĽ��
	bool CallRecurrenceForFirstResult(int *data, int count, int *result);        //�ݹ���㣬���������������ݵ��м������̣�ֻ��Ҫ��õ�һ����Ч�Ľ������
	void  CreateSudokuData(const E_DIFFICULTY_TYPE& eType = eType_Easy);    //�Զ��������������Ϸ���� 
	void  CopyToUser();              //��ԭʼ���ݿ������û�����
};