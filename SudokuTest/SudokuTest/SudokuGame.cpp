#include "stdafx.h"
#include <time.h>
#include "SudokuGame.h"

CSudokuGame::CSudokuGame()
{
	for(int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)	{ m_data[i][j] = 0;	m_user[i][j] = 0; }
	}
	m_bCompute = false;
}

CSudokuGame::~CSudokuGame()
{
}

void CSudokuGame::Initialize()
{
	for(int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)	{ m_data[i][j] = 0;	m_user[i][j] = 0; }
	}
}

//判断输入是否合法
bool CSudokuGame::CheckInput(const int row, const int col, const int input)
{
	if ( (col >= 9) || (row >= 9) || (col < 0) || (row < 0) )  return false;
	int i = 0, j = 0;
	for( i = 0; i < 9; i++)
	{
		if( (row != i) && m_user[i][col] == input ) return false;
	}
	for( i = 0; i < 9; i++)
	{
		if( (col != i) && m_user[row][i] == input ) return false;
	}
	int t1 = row / 3, t2 = col / 3;
	for( i = t1*3; i < (t1*3+3); i++)
	{
		for( j = t2*3; j < (t2*3+3); j++)
		{
			if( (row != i) && (col != j) && m_user[i][j] == input ) return false;
		}
	}
	return true;
}

//判断某一个单元格是否有错
bool CSudokuGame::CheckCell(const int row, const int col)
{
	if ( (col >= 9) || (row >= 9) || (col < 0) || (row < 0) )  return false;
	int   num = m_user[row][col];
	if ( num < 0 )   return false;
	if ( num == 0 ) return true;
	if ( m_data[row][col] != 0 )  return true;
	int i = 0, j = 0;
	for( i = 0; i < 9; i++)
	{
		if( (row != i) && m_user[i][col] == num ) return false;
	}
	for( i = 0; i < 9; i++)
	{
		if( (col != i) && m_user[row][i] == num ) return false;
	}
	int t1 = row / 3, t2 = col / 3;
	for( i = t1*3; i < (t1*3+3); i++)
	{
		for( j = t2*3; j < (t2*3+3); j++)
		{
			if( (row != i) && (col != j) && m_user[i][j] == num ) return false;
		}
	}
	return true;
}

int CSudokuGame::GetInputNum(const int row, const int col, vector<int> &integer)
{
	if ( (col >= 9) || (row >= 9) || (col < 0) || (row < 0) )  return 0;
	int num = 0;
	integer.clear();
/*	for ( int i = 1; i <= 9; i++ )
	{
		if ( CheckInput(row, col, i) )
		{
			integer.push_back(i);
			num++;
		}
	}*/
	int  line[9];
	memset(line, 1, sizeof(line));
	int i = 0, j = 0, temp;
	for( i = 0; i < 9; i++)
	{
		temp = m_user[i][col];
		if( (row != i) && temp  > 0 )  line[temp-1] = 0;
	}
	for( i = 0; i < 9; i++)
	{
		temp = m_user[row][i];
		if( (col != i) && temp > 0 )  line[temp-1] = 0;
	}
	int t1 = row / 3, t2 = col / 3;
	for( i = t1*3; i < (t1*3+3); i++)
	{
		if ( row == i )  continue;
		for( j = t2*3; j < (t2*3+3); j++)
		{	
			if ( col == j )  continue;
			temp = m_user[i][j];
			if( temp > 0 ) line[temp-1] = 0;
		}
	}
	for ( i = 0; i < 9; i++ )
	{
		if ( line[i] != 0 )
		{
			integer.push_back(i+1);
			num++;
		}
	}
	return num;
}

bool CSudokuGame::CheckOriginalData()
{
	int count = 0;
	int i = 0, j = 0;
	for ( i = 0; i < 9; i++ )
	{
		for ( j = 0; j < 9; j++ )
		{
			if ( m_data[i][j] != 0 )  count++;
		}
	}
	//假如有效数据（1位正整数）不足9个，则被认为游戏数据非法
	if ( count < 10 )   return false;
	//检查原始游戏数据是否满足数独游戏规则
	for( i =0; i < 9; i++)
	{
		for( j = 0; j < 9; j++)
		{
			if( m_user[i][j] != 0 )
			{
				if( !CheckInput(i, j, m_user[i][j]) )  return false;
			}
		}
	}
	return true;
}

//检查用户是否正确完成游戏
bool CSudokuGame::CheckTheResult()
{
	int i = 0, j = 0;
	for( i =0; i < 9; i++)
	{
		for( j = 0; j < 9; j++)
		{
			if( m_user[i][j] == 0 ) return false;
			else
			{
				if( !CheckInput(i, j, m_user[i][j]) )  return false;
			}
		}
	}
	return true;
}

//递归计算数独结果
bool CSudokuGame::CallRecurrence(int *data, int count, vector<vector<vector<int>>> &results)
{
	if ( !m_bCompute )    return false;
	if ( results.size() >= MAX_NUM )  return true;
	if ( count == 81 )
	{
		memcpy(m_user, data, sizeof(m_user));
		//if ( CheckTheResult() )
		//{
			vector<vector<int>> result;
			result.clear();
			result.resize(9);
			for ( int i = 0; i < 9; i++ )
			{
				for ( int j = 0; j < 9; j++ )
				{
					result[i].push_back(m_user[i][j]);
				}
			}
			results.push_back(result);
			return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	}
	int a[9][9];
	memcpy(a, data, sizeof(a));
	unsigned int num = 10;
	int row = 0, col = 0;
	vector<int>  mayInput;

	// 通过GetInputNum取得某个格子填数的可能性，从最小解入手
	for ( int i = 0; i < 9; i++ )
	{
		for ( int j = 0; j < 9; j++ )
		{
			if ( a[i][j] == 0 )
			{
				vector<int> integer;
				memcpy(m_user, a, sizeof(m_user));
				GetInputNum(i, j, integer);
				if ( integer.empty() )   return false;
				if ( num > integer.size() )
				{
					num = integer.size();
					row = i;
					col = j;
					mayInput = integer;
				}
			}
		}
	}
	bool bOK = false;

	// 遍历最小解，递归直到找到可行解
	for (unsigned int i = 0; i < mayInput.size(); i++ )
	{
		a[row][col] = mayInput[i];
		if ( CallRecurrence( (int *)a, count+1, results ) )  bOK = true;
	}
	return bOK;
}

//自动计算数独的所有可能解
bool CSudokuGame::ComputeResult(vector<vector<vector<int>>> &results)
{
	m_bExit = false;
	results.clear();
	int  data[9][9];
	memcpy(data, m_data, sizeof(m_data)); 
	int count = 0;
	for ( int i = 0; i < 9; i++ )
	{
		for ( int j = 0; j < 9; j++ )
		{
			if ( m_data[i][j] > 0 )  count++;
		}
	}
	if ( CallRecurrence((int *)data, count, results) )
	{
		m_bExit = true;
		return true;
	}
	else
	{
		m_bExit = true;
		return false;
	}
}

//递归计算，用以生成数独数据的中间计算过程，只需要获得第一个有效的结果即可
bool CSudokuGame::CallRecurrenceForFirstResult(int *data, int count, int *result)
{
	int a[9][9];
	memcpy(a, data, sizeof(a));
	if ( count == 81 )
	{
		memcpy(result, a, sizeof(a));
		return  true;
	}
	unsigned int num = 10;
	int row = 0, col = 0;
	vector<int>  mayInput;
	for ( int i = 0; i < 9; i++ )
	{
		for ( int j = 0; j < 9; j++ )
		{
			if ( a[i][j] == 0 )
			{
				vector<int> integer;
				memcpy(m_user, a, sizeof(m_user));
				GetInputNum(i, j, integer);
				if ( integer.empty() )   return false;
				if ( num > integer.size() )
				{
					num = integer.size();
					row = i;
					col = j;
					mayInput = integer;
				}
			}
		}
	}
	for (unsigned int i = 0; i < mayInput.size(); i++ )
	{
		a[row][col] = mayInput[i];
		if ( CallRecurrenceForFirstResult( (int *)a, count+1, result) )  return true;
	}
	return  false;
}

//自动随机生成数独游戏数据
void CSudokuGame::CreateSudokuData(const E_DIFFICULTY_TYPE& eType)
{
	int  data[9][9];
	memset(data, 0, sizeof(data));
	srand( (unsigned) time(NULL) );

	int nRandEx = 0;
	switch (eType) {
	case eType_Easy:
		nRandEx = 40;
		break;
	case eType_Normal:
		nRandEx = 35;
		break;
	case eType_Hard:
		nRandEx = 30;
		break;
	case eType_Madness:
		nRandEx = 25;
		break;
	case eType_Hell:
		nRandEx = 20;
		break;
	default:
		nRandEx = 40;
		break;
	}
	int num = (rand() % 5) + nRandEx;    //随机产生20-41个原始数据
	int possible[9], i1, i2, temp;

	// 先存1-9，备后面使用
	for ( int i = 0; i < 9; i++ )    possible[i] = i+1;

	// 做20次循环，打乱possible里存的数字的顺序
	for ( int i = 0; i < 20; i++ )
	{
		i1 = rand() % 9;
		i2 = rand() % 9;
		temp = possible[i1];
		possible[i1] = possible[i2];
		possible[i2] = temp;
	}

	bool  bNon = true;
	int  count = 9;

	int row, col;
	while ( bNon )
	{
		// 每行都随机放一个不同的数
		for ( int i = 0; i < 9; i++ )
		{
			col = rand() % 9;
			data[i][col] = possible[i];
		}

		// 获取第一个得到的解，作为初始数据（PS：如果bNon一直为true，则进入死循环。但是，由于只预设了9个数，切都是互异的，所以，必定能找到可行解）
		if ( CallRecurrenceForFirstResult((int *)data, count, (int *)data)  ) 
		{
			bNon = false; 
			break; 
		}
	}

	//随机挖去81-num个的洞
	for (int  i = 0; i < (81-num); i++ )
	{
		row = rand() % 9;
		col = rand() % 9;
		while( data[row][col] == 0 )
		{
			row = rand() % 9;
			col = rand() % 9;
		}
		data[row][col] = 0;
	}
/*	int  row = rand() % 9;
	int  col = rand() % 9;
	int  val = (rand() % 9) + 1;
	data[row][col] = val;
	for ( int i = 2; i < num; i++ )
	{
		bool  bNon = true;
		while( bNon )
		{
			row = rand() % 9;
			col = rand() % 9;
			while( data[row][col] != 0 )
			{
				row = rand() % 9;
				col = rand() % 9;
			}
			memcpy(m_user, data, sizeof(data));
			vector<int>  integer;
			GetInputNum(row, col, integer);
			int size = integer.size();
			for ( int j = 0; j < 3; j++ )
			{
				int  p1 = rand() % size;
				int  p2 = rand() % size;
				int  temp = integer[p1];
				integer[p1] = integer[p2];
				integer[p2] = temp;
			}
			for ( int j = 0; j < size; j++ )
			{
				int val = integer[j];
				data[row][col] = val;
				int count = i;
				if ( CallRecurrence((int *)data, count)  ) 
				{
					bNon = false; 
					break; 
				}
				else  data[row][col] = 0;
			}
		}
	}*/
	memcpy(m_data, data, sizeof(data));
	memcpy(m_user, data, sizeof(data)); 
}

void CSudokuGame::CopyToUser()
{
	for(int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)	m_user[i][j] = m_data[i][j]; 
	}
}