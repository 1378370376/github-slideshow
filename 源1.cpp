#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;
int map[12][12];//为避免边界的特殊处理，故将二维数组四周边界扩展1
int derection[3] = { 0,1,-1 };//方向数组
int calculate(int x, int y)
{
	int counter = 0;//定义变量counter，并初始化为0,
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (map[x + derection[i]][y + derection[j]] == 9)
				counter++;//统计以(x,y)为中心的四周的雷数目
	return counter;
}
void game(int x, int y)
{
	if (calculate(x, y) == 0)
	{
		map[x][y] = 0;
		for (int i = 0; i < 3; i++)
		{//模拟游戏过程，若点到一个空白，则系统自动向外扩展
			for (int j = 0; j < 3; j++)
				if (x + derection[i] <= 9 && y + derection[j] <= 9 && x + derection[i] >= 1 && y + derection[j] >= 1 && !(derection[i] == 0 && derection[j] == 0) && map[x + derection[i]][y + derection[j]] == -1)
					game(x + derection[i], y + derection[j]);//条件比较多，一是不可以让两个方向坐标同时为0，否则递归调用本身！
		}//二是递归不能出界，三要保证不返回调用。
	}
	else
		map[x][y] = calculate(x, y);//若以（x,y）为中心的四周内有雷，则调用calculate函数，统计雷数目并赋值给map（x,y）。

}
void print()
{
	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			if (map[i][j] == -1 || map[i][j] == 9)
				cout << '#';
			else
				cout << map[i][j];
		}
		cout << endl;//将map[i][j]值为-1或9处仍输出为'#'
	}
}
bool check()
{
	int counter = 0;
	for (int i = 1; i < 10; i++)
		for (int j = 1; j < 10; j++)
			if (map[i][j] != -1)
				counter++;
	if (counter == 10)
		return true;
	else
		return false;//检查最终未涉及区域的雷数目是否为10，若是则返回true,反之返回false
}
int main()
{
	int i, j, x, y;
	char ch;
	srand(time(0));//定义时间种子
	do
	{
		memset(map, -1, sizeof(map));//将map全部初始化为-1，以后用-1表示未涉及的区域
		for (i = 0; i < 10;)
		{
			x = rand() % 9 + 1;//调用cstdlib类中的rand（）函数，在时间种子下，实现伪随机数
			y = rand() % 9 + 1;
			if (map[x][y] != 9)
			{
				map[x][y] = 9;
				i++;
			}
		}//实现10个雷的赋值，将雷的赋值为9
		for (i = 1; i < 10; i++)
		{
			for (j = 1; j < 10; j++)
				cout << '#';
			cout << " ";//将所有map[i][j]数组用'#'覆盖
		}
		cout << "Please enter a coordinate:";
		while (cin >> x >> y)//输入x，y
		{
			if (map[x][y] == 9)
			{
				cout << "GAME OVER" << endl;//点中雷之后游戏结束，并且输出雷的位置
				for (i = 1; i < 10; i++)
				{
					for (j = 1; j < 10; j++)
					{
						if (map[i][j] == 9)
							cout << '@';
						else
							cout << '#';
					}
					cout << endl;
				}//游戏结束后将所有map[i][j]值为9的输出'@',其他输出为'#'
				break;
			}
			game(x, y);//调用递归函数，空白处向外扩展，并对map[i][j]根据以（x,y）为中心的四周雷数目进行赋值
			print();
			if (check())//检查游戏是否找出所有雷，若有则输出"YOU WIN"
			{
				cout << "YOU WIN" << endl;
				break;
			}
			cout << " ";
		}
		cout << "Do you want to play again,if ture enter Y,or enter N." << endl;//根据输入指令决定是否循环
		cin >> ch;
		cout << " ";
	} while (ch == 'Y');
	return 0;
}