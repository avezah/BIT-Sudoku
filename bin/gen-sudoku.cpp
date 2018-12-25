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
		genSudoku()
		{
			start = GetTickCount();
			for (int i = 0; i < 9; i ++)
				list[i] = i + 1;
			outFile.open("gen-sudoku.txt");
		}
		~genSudoku()
		{
			outFile.close();
			end = GetTickCount();
			cout << "CostTime = "<< end - start << "ms" << endl;
		}
		void Swap(int &one, int &two)
		{
			int temp;
			temp = one;
			one = two;
			two = temp;
		}
		void Putout(int seed[][MAX])
		{
			for (int i = 0; i < MAX; i ++)
			{
				outFile<<seed[i][0]<<' '<<seed[i][1]<<' '<<seed[i][2]<<' '<<seed[i][3]<<' '<<seed[i][4]<<' '<<seed[i][5]<<' '<<seed[i][6]<<' '<<seed[i][7]<<' '<<seed[i][8]<<endl;
			}
			outFile<<endl;
		}
		void Perm(int list[], int low, int high)
		{
			if(low == high)
			{   
				Gen_Perm(list);
			}
			else
			{
				for(int i = low; i <= high; i++)
				{
					Swap(list[i], list[low]);
					Perm(list, low + 1, high);
					Swap(list[i], list[low]);
				}
			}
		}
		void Gen_Perm(int list[])
		{

			int seed[MAX][MAX] = {{1, 8, 6, 7, 3, 2, 4, 9, 5},
								  {3, 9, 2, 1, 4, 5, 6, 7, 8},
								  {4, 5, 7, 9, 6, 8, 2, 3, 1},
								  {2, 1, 3, 8, 9, 7, 5, 6, 4},
								  {6, 4, 5, 3, 2, 1, 7, 8, 9},
								  {9, 7, 8, 6, 5, 4, 1, 2, 3},
								  {8, 3, 1, 4, 7, 6, 9, 5, 2},
								  {5, 6, 9, 2, 1, 3, 8, 4, 7},
								  {7, 2, 4, 5, 8, 9, 3, 1, 6}};
			for(int i = 0; i < MAX; i ++)
				for(int j = 0; j < MAX; j ++)
				{
					seed[i][j] = list[seed[i][j] - 1];
				}
			Putout(seed);
		}
		void Generate()
		{
			Perm(list, 1, 8);
		}
	private:
		int list[MAX];
		double start, end;
		//static int count;
};


int main(void)
{
	genSudoku test;
	test.Generate();
	
}

//void Swap_row(int one, int two)
//{
//	int *temp;
//	temp = seed[one];
//	seed[one] = seed[two];
//	seed[two] = temp;
//}
//void Swap_col(int one, int two)
//{
//	int temp;
//	for (int i = 0; i < MAX; i ++)
//	{
//		temp = seed[i][one];
//		seed[i][one] = seed[i][two];
//		seed[i][two] = temp;
//	}
//}
