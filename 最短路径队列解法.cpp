#include <iostream>
#include <algorithm>

using namespace std;

struct FindTheWay
{
	int row;
	int col;
	int distance;
	FindTheWay *next;
};

struct Map
{
	char data;
	bool flag;
};

struct Distance
{
	int sum;
	Distance *next;
};

int FindWay(FindTheWay *FINDHEAD, Distance *DISHEAD, Map **map, int n, int m);
bool Empty(FindTheWay *HEAD);

int main()
{
	int n(0), m(0);
	cin >> n >> m;
	Map **map = new Map*[n];
	for (int i(0); i < n; ++i)
		map[i] = new Map[m];
	for (int i(0); i < n; ++i)
	{
		for (int j(0); j < m; ++j)
		{
			char input;
			cin >> input;
			map[i][j].data = input;
			map[i][j].flag = true;//true����û�з���
		}
	}
	//�������еĵ�ͼ��ʶ
	//������ջʵ�֣�����ʹ����������㷨�������еĻ�����õķ����ǹ�������㷨
	//��������㷨���������������²���
	FindTheWay *FINDHEAD = new FindTheWay{ -1,-1,-1,nullptr };
	Distance *DISHEAD = new Distance{ -1,nullptr };
	cout << FindWay(FINDHEAD, DISHEAD, map, n, m) << endl;
	return 0;
}

int FindWay(FindTheWay* FINDHEAD, Distance* DISHEAD, Map** map, int n, int m)
{
	FindTheWay *findtail = FINDHEAD;
	Distance *distail = DISHEAD;
	int begin_row(0), begin_col(0);
	int end_row(0), end_col(0);
	for (int i(0); i < n; ++i)
	{
		for (int j(0); j < m; ++j)
		{
			if (map[i][j].data == 'x')
				map[i][j].flag = false;
			else if (map[i][j].data == 'd')
			{
				end_row = i;
				end_col = j;
			}
			else if (map[i][j].data == 'z')
			{
				begin_row = i;
				begin_col = j;
			}
		}
	}

	map[begin_row][begin_col].flag = false;
	FindTheWay *begin = new FindTheWay{ begin_row, begin_col, 0, nullptr };
	FINDHEAD->next = begin;//�ṩ�˵�һ���ڵ㣬�����ڷ���ͨʽ������м���
	findtail = begin;
	FINDHEAD = begin;//��ʱ��ͷ��β����ͬһ��λ��

	while (!Empty(FINDHEAD))
	{
		if (FINDHEAD->col == end_col && FINDHEAD->row == end_row)//��ʱ�ǵ������յ�
		{
			Distance *dis_p = new Distance{ FINDHEAD->distance, nullptr };
			//cout << "dis_p"<<dis_p << endl;
			distail->next = dis_p;
			distail = distail->next;
			FindTheWay *findkill = FINDHEAD;
			FINDHEAD = FINDHEAD->next;
			delete findkill;
		}
		//���û�е����յ㣬��Ӧ�ñ�����Χ������
		else
		{
			map[FINDHEAD->row][FINDHEAD->col].flag = false;//�����һλ�Ѿ�����
			if (FINDHEAD->row - 1 >= 0 && map[FINDHEAD->row - 1][FINDHEAD->col].flag)
			{
				FindTheWay *find_p = new FindTheWay{ FINDHEAD->row - 1, FINDHEAD->col, FINDHEAD->distance + 1,nullptr };
				findtail->next = find_p;
				findtail = findtail->next;
			}
			if (FINDHEAD->row + 1 < n && map[FINDHEAD->row + 1][FINDHEAD->col].flag)
			{
				FindTheWay *find_p = new FindTheWay{ FINDHEAD->row + 1, FINDHEAD->col, FINDHEAD->distance + 1,nullptr };
				findtail->next = find_p;
				findtail = findtail->next;
			}
			if (FINDHEAD->col - 1 >= 0 && map[FINDHEAD->row][FINDHEAD->col - 1].flag)
			{
				FindTheWay *find_p = new FindTheWay{ FINDHEAD->row, FINDHEAD->col - 1, FINDHEAD->distance + 1,nullptr };
				findtail->next = find_p;
				findtail = findtail->next;
			}
			if (FINDHEAD->col + 1 >= 0 && map[FINDHEAD->row][FINDHEAD->col + 1].flag)
			{
				FindTheWay *find_p = new FindTheWay{ FINDHEAD->row, FINDHEAD->col + 1, FINDHEAD->distance + 1,nullptr };
				findtail->next = find_p;
				findtail = findtail->next;
			}
			FindTheWay *findkill = FINDHEAD;
			FINDHEAD = FINDHEAD->next;
			delete findkill;
		}	
	}
	//cout << "?";
	//cout << DISHEAD << endl;
	//cout << p << endl;
	Distance *p = DISHEAD->next;
	
	int mindis = 100000000;
	if (p == nullptr)
		mindis = -1;
	else
	{
		for (;p != nullptr; p = p->next)
		{
			//mindis > p->sum ? mindis = p->sum : mindis = mindis;

			if (mindis > p->sum)
				mindis = p->sum;
		}
	}
	return mindis;
}

bool Empty(FindTheWay* HEAD)
{
	bool flag(false);
	(HEAD == nullptr) ? (flag = true) : (flag = false);
	return flag;
}

