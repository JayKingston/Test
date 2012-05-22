// SudokuTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <MMSystem.h>
#include "SudokuGame.h"
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	CSudokuGame objSudokuGame;
	objSudokuGame.Initialize();

	srand( (unsigned) time(NULL) );
	int nType = rand() % eType_Max;
	DWORD dwBeginTime = ::timeGetTime();
	objSudokuGame.CreateSudokuData((E_DIFFICULTY_TYPE)nType);
	DWORD dwEndTime = ::timeGetTime();
	cout << "创建数独耗时 " << dwEndTime - dwBeginTime << " 毫秒\n";
	cout << "难度为：";
	switch (nType) {
	case eType_Easy:
		cout << "简单";
		break;
	case eType_Normal:
		cout << "普通";
		break;
	case eType_Hard:
		cout << "困难";
		break;
	case eType_Madness:
		cout << "疯狂";
		break;
	case eType_Hell:
		cout << "地狱";
		break;
	default:
		cout << "简单";
		break;
	}
	cout << "\n";
	int i = 0;
	int nCount = 0;
	for (; i < 9; ++i) {
		int j = 0;
		for (; j < 9; ++j) {
			if (objSudokuGame.m_data[i][j] > 0) {
				++nCount;
				cout << objSudokuGame.m_data[i][j] << " ";
			} else {
				cout << "* ";
			}
		}
		cout << "\n";
	}
	cout << "此数独有" << nCount << "个元素" << "\n";
	return 0;
}

