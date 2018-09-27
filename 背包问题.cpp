#include <iostream>
#include <algorithm>
using namespace std;
int InPack(int w[], int n, int s, int &num)//���һ���Ǳ���ĿǰΪֹ�Ĵ�С
{
	if (s == 0)//��ʱ�Ѿ�װ�����ոպ�
		return 1;//��ʱ�Ƿ���ɹ���
	else if (s < 0 || (s > 0 && n <= 0))//��ʱ�����Ǳ���������ߣ��Ѿ�û������Ʒ
		return 0;
	else if (InPack(w, n - 1, s - w[n - 1], num) == 1)
		++num;
	return InPack(w, n - 1, s, num);
}
int main()
{
	int n(0), s(0);
	while (cin >> s >> n)
	{
		int num(0);
		int *weight = new int[n];//��̬����
		for (int i = 0; i < n; ++i)
			cin >> weight[i];
		sort(weight, weight + n);
		InPack(weight, n, s, num);
		cout << num << endl;
	}
	return 0;
}