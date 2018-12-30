#include "pch.h"
#include "solve-sudoku.h"
#include <cstring>
solveSudoku::solveSudoku(char site[])
{
	solveFile.open(site);
	ansFile.open("solve-ans.txt");
	assert(solveFile.is_open());//异常提示
	assert(ansFile.is_open());
}
solveSudoku::~solveSudoku()
{
	solveFile.close();
	ansFile.close();
}
bool solveSudoku::DFS(int z) //深搜找方案
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
char solveSudoku::get_num(int bit)//将按位标记的数字转化为字符形式
{
	char num = '0';
	while(bit)
	{
		num ++;
		bit = bit >> 1;
	}
	return num;
}
bool solveSudoku::readProblems(void)
{
	string s;//存放读入的行
	int cntLine = 0;//记录行号
	int cntZero = 0;//记录待填数字的位置
	memset(bit, 0, sizeof(bit));
	memset(zero, -1, sizeof(zero));
	while(getline(solveFile, s))
	{
		for (int i = 0; i < 2*MAX - 1; i ++)
		{
			if(s[i] == '0')
				zero[cntZero ++] = cntLine*10 + i/2;//读取到待填数字，用二位数的十位表示行号，个位表示列号
			else if (s[i] <= '9' && s[i] >= '1')
				bit[cntLine][i/2] = 1 << (s[i] - '0' - 1);//按位标记存在的数字
		}
		cntLine ++;
		if(cntLine == 9)
		{
			getline(solveFile, s);//读取空行
			return true;
		}
	}
	return false;
}
void solveSudoku::writeAns()//写入答案
{
	char ans[MAX];
	for(int i = 0; i < MAX; i ++)
	{
		for(int j = 0; j < MAX; j ++)
			ans[j] = get_num(bit[i][j]);
		ansFile<<ans[0]<<' '<<ans[1]<<' '<<ans[2]<<' '<<ans[3]<<' '<<ans[4]<<' '<<ans[5]<<' '<<ans[6]<<' '<<ans[7]<<' '<<ans[8]<<endl;
	}
}
void solveSudoku::Solve(void)
{
	if(readProblems())//为了按照要求输出，先读取一个待解数独
	{
		DFS(0);
		writeAns();
	}
	while(readProblems())//后面每个读取的数独前加空行
	{
		ansFile<<'\n';
		DFS(0);
		writeAns();
	}
}
