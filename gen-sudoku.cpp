#include "pch.h"
#include "gen-sudoku.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <Windows.h>

using namespace std;

genSudoku::genSudoku()
{
	start = GetTickCount();
	temp  = new int [MAX];
	need = count = 0;
	for (int i = 0; i < 9; i ++)
	list[i] = i;
	outFile.open("gen-sudoku.txt");
}
genSudoku::~genSudoku()
{
	delete[] temp;
	outFile.close();
	end = GetTickCount();
	cout << "CostTime = "<< end - start << "ms" << endl;
}
void genSudoku::Swap_num(int &one, int &two)
{
	int temp;
	temp = one;
	one = two;
	two = temp;
}
void genSudoku::Swap_row(int a)//轮转交换行
{
	memcpy(temp, seed[a + 2], MAX);
	memcpy(seed[a + 2], seed[a + 1], MAX);
	memcpy(seed[a + 1], seed[a], MAX);
	memcpy(seed[a], temp, MAX);
}
void genSudoku::Swap_col(int a)//轮转交换列
{
	int temp;
	for (int i = 0; i < MAX; i ++)
	{
		temp = seed[i][a + 2];
		seed[i][a + 2] = seed[i][a + 1];
		seed[i][a + 1] = seed[i][a];
		seed[i][a] = temp;
	}
}
void genSudoku::Putout()//数独写入文件
{
	for (int i = 0; i < MAX; i ++)
	{
		outFile<<seed[i][0]<<' '<<seed[i][1]<<' '<<seed[i][2]<<' '<<seed[i][3]<<' '<<seed[i][4]<<' '<<seed[i][5]<<' '<<seed[i][6]<<' '<<seed[i][7]<<' '<<seed[i][8]<<endl;
	}
	count ++;
	if(count == need)
	{
		this->~genSudoku();
		exit(0);
	}
	outFile<<endl;

}
void genSudoku::Swap_all_num(int list[])//根据全排列序列交换数独内的所有数字
{
	for(int i = 0; i < MAX; i ++)
		for(int j = 0; j < MAX; j ++)
			seed[i][j] = list[seed[i][j] - 1] + 1;
}
void genSudoku::Swap_num_back(int list[])//撤回交换数字
{
	for(int i = 0; i < MAX; i ++)
		temp[list[i]] = i;
	for(int i = 0; i < MAX; i ++)
		for(int j = 0; j < MAX; j ++)
			seed[i][j] = temp[seed[i][j] - 1] + 1;
}
void genSudoku::Swap_row_col(void)//宫内交换行列
{
	for(int i = 1; i <= 2; i ++)
		for(int j = 0; j < 3; j ++)
		{
			Swap_row(i*3);
			for(int a = 1; a <= 2; a ++)
				for(int b = 0; b < 3; b ++)
				{
					Swap_col(a*3);
					Putout();
					
				}
		}

}
void genSudoku::Perm(int list[], int low, int high)//全排列生成
{
	if(low == high)
	{
		Swap_all_num(list);
		Swap_row_col();
		Swap_num_back(list);
	}
	else
	{
		for (int i = low; i <= high; i++)
		{
			Swap_num(list[i], list[low]);
			Perm(list, low + 1, high);
			Swap_num(list[i], list[low]);
		}
	}
}
void genSudoku::Generate(int need)
{
	this->need = need;
	Perm(list, 1, 8);
}


