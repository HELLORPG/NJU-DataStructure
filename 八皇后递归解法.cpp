#include <iostream>
#include <cmath>

using namespace std;

#define N 8//��ΪN�ʺ������ͨ��Ļ���Ƚ�������

bool JudgeQueen(int row, int*& board);
void Queen(int row, int col, int*& board);

int main()
{
	int first_row(0);
	while (cin >> first_row)
	{
		//����ɹ���һ�лʺ��λ��
		int board[N] = { 0 };
		int *p = board;
		board[0] = first_row;//����һ�е�λ������Ϊ����ֵ
		Queen(1, 1, p);
	}
	return 0;
}

bool JudgeQueen(int row, int*& board)
{
	for (int i = row - 1; i >= 0; --i)
	{
		if (board[i] == board[row] || abs(board[i] - board[row]) == abs(i - row))
			return false;
	}
	//cout << "true" << endl;
	return true;
}

void Queen(int row, int col, int*& board)
{
	//cout << "����" << endl;
	if (row == N)//��ʱ�Ѿ�����
	{
		for (int i = 0; i < N; ++i)
			cout << board[i];
		cout << endl;
		return;
	}
	else
	{
		board[row] = col;
		if (JudgeQueen(row, board))
			Queen(row + 1, 1, board);
		if (col < 8)
			Queen(row, col + 1, board);
	}
	return;
}

