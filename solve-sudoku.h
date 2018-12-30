#include <cstdio>
#include <iostream>
#include <cstring>
#include <fstream>
#include <cassert>
#include <string>

using namespace std;
const int MAX = 9;

class solveSudoku
{
	public:
		ifstream solveFile;
		ofstream ansFile;
		int zero[MAX*MAX];
		int bit[MAX][MAX];
		solveSudoku(char site[]);
		~solveSudoku();
		bool DFS(int z);
		char get_num(int bit);
		bool readProblems(void);
		void writeAns();
		void Solve(void);
};

