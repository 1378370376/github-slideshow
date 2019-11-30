#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;
int map[12][12];//Ϊ����߽�����⴦���ʽ���ά�������ܱ߽���չ1
int derection[3] = { 0,1,-1 };//��������
int calculate(int x, int y)
{
	int counter = 0;//�������counter������ʼ��Ϊ0,
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (map[x + derection[i]][y + derection[j]] == 9)
				counter++;//ͳ����(x,y)Ϊ���ĵ����ܵ�����Ŀ
	return counter;
}
void game(int x, int y)
{
	if (calculate(x, y) == 0)
	{
		map[x][y] = 0;
		for (int i = 0; i < 3; i++)
		{//ģ����Ϸ���̣����㵽һ���հף���ϵͳ�Զ�������չ
			for (int j = 0; j < 3; j++)
				if (x + derection[i] <= 9 && y + derection[j] <= 9 && x + derection[i] >= 1 && y + derection[j] >= 1 && !(derection[i] == 0 && derection[j] == 0) && map[x + derection[i]][y + derection[j]] == -1)
					game(x + derection[i], y + derection[j]);//�����Ƚ϶࣬һ�ǲ�������������������ͬʱΪ0������ݹ���ñ���
		}//���ǵݹ鲻�ܳ��磬��Ҫ��֤�����ص��á�
	}
	else
		map[x][y] = calculate(x, y);//���ԣ�x,y��Ϊ���ĵ����������ף������calculate������ͳ������Ŀ����ֵ��map��x,y����

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
		cout << endl;//��map[i][j]ֵΪ-1��9�������Ϊ'#'
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
		return false;//�������δ�漰���������Ŀ�Ƿ�Ϊ10�������򷵻�true,��֮����false
}
int main()
{
	int i, j, x, y;
	char ch;
	srand(time(0));//����ʱ������
	do
	{
		memset(map, -1, sizeof(map));//��mapȫ����ʼ��Ϊ-1���Ժ���-1��ʾδ�漰������
		for (i = 0; i < 10;)
		{
			x = rand() % 9 + 1;//����cstdlib���е�rand������������ʱ�������£�ʵ��α�����
			y = rand() % 9 + 1;
			if (map[x][y] != 9)
			{
				map[x][y] = 9;
				i++;
			}
		}//ʵ��10���׵ĸ�ֵ�����׵ĸ�ֵΪ9
		for (i = 1; i < 10; i++)
		{
			for (j = 1; j < 10; j++)
				cout << '#';
			cout << " ";//������map[i][j]������'#'����
		}
		cout << "Please enter a coordinate:";
		while (cin >> x >> y)//����x��y
		{
			if (map[x][y] == 9)
			{
				cout << "GAME OVER" << endl;//������֮����Ϸ��������������׵�λ��
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
				}//��Ϸ����������map[i][j]ֵΪ9�����'@',�������Ϊ'#'
				break;
			}
			game(x, y);//���õݹ麯�����հ״�������չ������map[i][j]�����ԣ�x,y��Ϊ���ĵ���������Ŀ���и�ֵ
			print();
			if (check())//�����Ϸ�Ƿ��ҳ������ף����������"YOU WIN"
			{
				cout << "YOU WIN" << endl;
				break;
			}
			cout << " ";
		}
		cout << "Do you want to play again,if ture enter Y,or enter N." << endl;//��������ָ������Ƿ�ѭ��
		cin >> ch;
		cout << " ";
	} while (ch == 'Y');
	return 0;
}