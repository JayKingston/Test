#pragma once

#include <vector>

using namespace std;

#define  MAX_NUM  1000            //定义最大保存数独结果个数

enum E_DIFFICULTY_TYPE		// 难度类型
{
	eType_Easy		= 1,	// 简单 40-45
	eType_Normal,			// 普通 35-40
	eType_Hard,				// 困难 30-35
	eType_Madness,			// 疯狂 25-30
	eType_Hell,				// 地狱 20-25
	eType_Max,
};

// 原理：
// 1、通过CreateSudokuData创建一个数独数据，只保存（挖去洞里的数后）剩余的数，存在m_data和m_user里
// 2、通过CheckTheResult，检查用户的输入是否可行。这里，没有跟1里面创建数独数据时的原始数据进行比较，而是直接对输入的数据，进行一次遍历判定
// 3、通过ComputeResult，计算数独的所有可能解，按照原程序调用的意图，应该是随机取一个结果用于显示
class CSudokuGame
{
public:
	CSudokuGame();
	~CSudokuGame();

	int  m_data[9][9];     //保存原始游戏数据
	int  m_user[9][9];      //保用户输入数据
	vector<vector<vector<int>>> m_vecResults;	// 保存所有可能的结果，针对多种可能解的情况
	int  m_bCompute;     //判断用户是否终止自动计算
	bool  m_bExit;          //标志线程是否终止退出

	void  Initialize();
	bool  CheckInput(const int row, const int col, const int input);   //判断输入的某格数据是否有效
	bool  CheckCell(const int row, const int col);            //判断某一个单元格是否有错
	bool  CheckOriginalData();   //检查原始数据的合法性
	int    GetInputNum(const int row, const int col, vector<int> &integer);          //获取某个单元格所有可输入的整数
	bool  CheckTheResult();      //判断用户最终是否完成了游戏
	bool  ComputeResult(vector<vector<vector<int>>> &results);       //自动计算数独的所有可能解
	bool CallRecurrence(int *data, int count, vector<vector<vector<int>>> &results);   //递归计算，得到所有可能的结果
	bool CallRecurrenceForFirstResult(int *data, int count, int *result);        //递归计算，用以生成数独数据的中间计算过程，只需要获得第一个有效的结果即可
	void  CreateSudokuData(const E_DIFFICULTY_TYPE& eType = eType_Easy);    //自动随机生成数独游戏数据 
	void  CopyToUser();              //将原始数据拷贝到用户数据
};