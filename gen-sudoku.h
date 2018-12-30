#ifndef GEN_H
#define GEN_H
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<windows.h>
#include<iostream>

#define MAX 9
using namespace std;

class genSudoku
{
	public:
		ofstream outFile;
		int *temp;
		int seed[MAX][MAX] = {{1, 8, 6, 7, 3, 2, 4, 9, 5},
							{3, 9, 2, 1, 4, 5, 6, 7, 8},
							{4, 5, 7, 9, 6, 8, 2, 3, 1},
							{2, 1, 3, 8, 9, 7, 5, 6, 4},
							{6, 4, 5, 3, 2, 1, 7, 8, 9},
							{9, 7, 8, 6, 5, 4, 1, 2, 3},
							{8, 3, 1, 4, 7, 6, 9, 5, 2},
							{5, 6, 9, 2, 1, 3, 8, 4, 7},
							{7, 2, 4, 5, 8, 9, 3, 1, 6}};

		genSudoku();
		~genSudoku();
		void Swap_num(int &one, int &two);//交换数字
		void Swap_row(int a);//轮转交换行
		void Swap_col(int a);//轮转交换列
		void Putout();//数独写入文件
		void Swap_all_num(int list[]);//根据全排列序列交换数独内的所有数字
		void Swap_num_back(int list[]);//撤回交换数字
		void Swap_row_col();//宫内交换行列
		void Perm(int list[], int low, int high);//全排列生成

		void Generate(int need);
	private:
		int list[MAX];
		int count;
		int need;
		double start, end;
};


#endif
