// SudokuTest.cpp : �������̨Ӧ�ó������ڵ㡣
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
	cout << "����������ʱ " << dwEndTime - dwBeginTime << " ����\n";
	cout << "�Ѷ�Ϊ��";
	switch (nType) {
	case eType_Easy:
		cout << "��";
		break;
	case eType_Normal:
		cout << "��ͨ";
		break;
	case eType_Hard:
		cout << "����";
		break;
	case eType_Madness:
		cout << "���";
		break;
	case eType_Hell:
		cout << "����";
		break;
	default:
		cout << "��";
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
	cout << "��������" << nCount << "��Ԫ��" << "\n";
	return 0;
}

