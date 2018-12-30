// Sudoku.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "solve-sudoku.h"
#include "gen-sudoku.h"
#include <math.h>
int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		cout << "Error-Need order." << endl;
		return 0;
	}
	if (strcmp(argv[1], "-c") == 0)
	{
		if (argc == 2)
		{
			cout << "Error-No numbers!" << endl;
			return 0;
		}
		for (int i = 0; argv[2][i] != '\0'; i++)
			if (argv[2][i] > '9' || argv[2][i] < '0')
			{
				cout << "Error-Please input true numbers!" << endl;
				return 0;
			}
		int num = argv[2][0] - '0';
		for (int i = 1; argv[2][i] != '\0'; i++)
			num = num * 10 + argv[2][i] - '0';
		if (num == 0 || num >= 1e6)
			return 0;
		genSudoku a;
		a.Generate(num);
	}
	else if (strcmp(argv[1], "-s") == 0)
	{
		if (argc == 2)
		{
			cout << "Error-No address!" << endl;
			return 0;
		}
		solveSudoku b(argv[2]);
		b.Solve();
	}
	else cout << "Unknow order!" << endl;

}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
