#include <cstdio>
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;
const int MAX = 9;

class solveSudoku 
{
	public:
		ifstream solveFile;
		ofstream ansFile;
		int zero[MAX*MAX];//记录待填空格的坐标
		int bit[MAX][MAX];//按位记录待填空格每个位置可能的数
		solveSudoku()
		{
			solveFile.open("C:\\Users\\ChenQiang\\Documents\\Code\\sudoku\\bin\\solve-problem.txt");
			ansFile.open("C:\\Users\\ChenQiang\\Documents\\Code\\sudoku\\bin\\solve-ans.txt");
			assert(solveFile.is_open());
			assert(ansFile.is_open());
		}
		~solveSudoku()
		{
			solveFile.close();
			ansFile.close();
		}
		bool DFS(int z) //深搜找方案
		{
			int i = zero[z]/10;//获取行号
			int j = zero[z]%10;//获取列号
			int possible = ((1 << 9) - 1);//记录该位置可能的出现数
			for (int k = 0; k < MAX; k ++)//排除将该位置所在的行列宫中已有的数
				possible &= (~bit[i][k]) & ((~bit[k][j]) & (~bit[i/3*3 + k/3][j/3*3 + k%3]));
			
			while(possible)//仍然存在可能的方案，即possible未被完全置零
			{
				bit[i][j] = possible & (-possible); //该位置将第一个可能出现的数填入，作为一个可能的方案
				possible &= ~bit[i][j]; //从记录中移除已经用过的数
				if(zero[z + 1] != -1 && !DFS(z + 1)) 
					continue; //如果待填空格的坐标没有结束且该方案错误，尝试下一个方案
				else
					return true; //找完最后一个待填位置时，仍有可行的放案，返回存在解
			}
			bit[i][j] = 0; //这种方案下位置可行解为零
			return false; //返回无可行解
		}
		char get_num(int bit)
		{
			char num = '0';
			while(bit)
			{
				num ++;
				bit = bit >> 1;
			}
			return num;
		}
		bool readProblems(void)
		{
			string s;
			int cntLine = 0;
			int cntZero = 0;
			memset(bit, 0, sizeof(bit));
			memset(zero, -1, sizeof(zero));
			while(getline(solveFile, s))
			{
				for (int i = 0; i < 2*MAX - 1; i ++)
				{
					if(s[i] == '0')
						zero[cntZero ++] = cntLine*10 + i/2;
					else if (s[i] <= '9' && s[i] >= '1')
						bit[cntLine][i/2] = 1 << (s[i] - '0' - 1);
				}
				cntLine ++;
				if(cntLine == 9)
				{
					getline(solveFile, s);
					return true;
				}
			}
			return false;
		}
		void writeAns()
		{
			string ans = "";
			char end[3];end[0] = ' ';end[3] = '\0';
			for(int i = 0; i < MAX; i ++)
			{
				ans.append(1, get_num(bit[i][0]));
				for(int j = 1; j < MAX; j ++)
				{
					end[1] = get_num(bit[i][j]);
					ans.append(end);
				}
				ans.append(1, '\n');
			}
			ansFile << ans;
		}
		void Solve(void)
		{
			readProblems();
			DFS(0);
			writeAns();
			while(readProblems())
			{
				ansFile<<'\n';
				DFS(0);
				writeAns();
			}
		}
};
int main()
{
    solveSudoku a;
	a.Solve();
}