#include <iostream>

using namespace std;

void C(int n, int k, int output[], int length)
{
	int i(0);
	if (length == k)//��ʱ�Ѿ��ǳ��ȴﵽҪ��������
	{
		for (i = 0; i < k; ++i)
		{
			cout << output[i] << " ";
		}
		cout << endl;
		return;//��һ�ε�����Ѿ�������
	}
	else
	{
		//���ʱ����û��������������ʱ��
		//��ʱһ��Ҫ������������һ��Ԫ�ص���һ��λ�ÿ�ʼ������ѭ���Ĵ�������ĩβһ��Ҫ�����㹻��Ԫ�ؽ��з��䡣
		for (i = (length > 0 ? output[length - 1] + 1 : length + 1); i < n + length - k + 2; ++i)
		{
			output[length] = i;
			C(n, k, output, length + 1);
		}
	}
}

int main()
{
	int n, k;
	cin >> n >> k;
	int *output = new int[k];//ѡȡ��ô���Ԫ�ؽ������
	C(n, k, output, 0);
	return 0;
}