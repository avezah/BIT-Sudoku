#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <windows.h>
using namespace std;

const int MAX = 9;

class genSudoku
{
	public:
		ofstream outFile;
		int *temp  = new int [MAX]; 
		int seed[MAX][MAX] = {{1, 8, 6, 7, 3, 2, 4, 9, 5},
							{3, 9, 2, 1, 4, 5, 6, 7, 8},
							{4, 5, 7, 9, 6, 8, 2, 3, 1},
							{2, 1, 3, 8, 9, 7, 5, 6, 4},
							{6, 4, 5, 3, 2, 1, 7, 8, 9},
							{9, 7, 8, 6, 5, 4, 1, 2, 3},
							{8, 3, 1, 4, 7, 6, 9, 5, 2},
							{5, 6, 9, 2, 1, 3, 8, 4, 7},
							{7, 2, 4, 5, 8, 9, 3, 1, 6}};
		genSudoku()
		{
			start = GetTickCount();
			need = count = 0;
			for (int i = 0; i < 9; i ++)
				list[i] = i;
			outFile.open("gen-sudoku.txt");
		}
		~genSudoku()
		{
			delete[] temp;
			outFile.close();
			end = GetTickCount();
			cout << "CostTime = "<< end - start << "ms" << endl;
		}
		void Swap_num(int &one, int &two)
		{
			int temp;
			temp = one;
			one = two;
			two = temp;
		}
		void Swap_row(int a)
		{	
			memcpy(temp, seed[a + 2], MAX);
			memcpy(seed[a + 2], seed[a + 1], MAX);
			memcpy(seed[a + 1], seed[a], MAX);
			memcpy(seed[a], temp, MAX);
		}
		void Swap_col(int a)
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
		void Putout()
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
		void Display()
		{
			for (int i = 0; i < MAX; i ++)
			{
				cout<<seed[i][0]<<' '<<seed[i][1]<<' '<<seed[i][2]<<' '<<seed[i][3]<<' '<<seed[i][4]<<' '<<seed[i][5]<<' '<<seed[i][6]<<' '<<seed[i][7]<<' '<<seed[i][8]<<endl;
			}
			cout<<endl;
		}
		void Swap_all_num(int list[])
		{
			for(int i = 0; i < MAX; i ++) 
				for(int j = 0; j < MAX; j ++)
					seed[i][j] = list[seed[i][j] - 1] + 1;
		}
		void Swap_num_back(int list[])
		{
			for(int i = 0; i < MAX; i ++)
				temp[list[i]] = i;
			for(int i = 0; i < MAX; i ++) 
				for(int j = 0; j < MAX; j ++)
					seed[i][j] = temp[seed[i][j] - 1] + 1;
		}
		void Swap_row_col()
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
		void Swap(int list[])
		{
			Swap_all_num(list);
			Swap_row_col();
			Swap_num_back(list);
			
		}
		void Perm(int list[], int low, int high)
		{
			if(low == high)
			{
				Swap(list);
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
		void Generate(int need)
		{
			this->need = need;
			Perm(list, 1, 8);
		}
	private:
		int list[MAX];
		int count;
		int need;
		double start, end;
};

int main(void)
{
	genSudoku test;
	test.Generate(1000000);
}