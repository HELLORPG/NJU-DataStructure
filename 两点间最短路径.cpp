#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::min;

#define N 100
#define NOWAY 100000//����Ǳ�ʾû����һ��
#define GRP_VECTOR_DEFAULTSIZE 5

template <typename T>
class GRPVector
{
protected:
	T *data;
	size_t max_size;
	size_t real_size;
public:
	GRPVector();
	~GRPVector();

	void push_back(T input);
	void pop_back();
	size_t size() const;
	bool empty() const;
	void clear();

	T& front();
	T& back();
	T& operator[](int i);

	void insert(int i, const T &add);
	void erase(int i);

	int find(T which) const;//Ѱ��ĳԪ�أ�������������

	GRPVector& operator=(const GRPVector& copy);
};

template <typename T>
GRPVector<T>::GRPVector() : data(new T[GRP_VECTOR_DEFAULTSIZE]), max_size(GRP_VECTOR_DEFAULTSIZE), real_size(0) {}

template <typename T>
GRPVector<T>::~GRPVector()
{
	delete data;//����̬����黹
}


template <typename T>
size_t GRPVector<T>::size() const
{
	return real_size;
}

template <typename T>
bool GRPVector<T>::empty() const
{
	return real_size == 0;
}

template <typename T>
void GRPVector<T>::clear()
{
	real_size = 0;
	return;
}



template <typename T>
void GRPVector<T>::push_back(T input)
{
	if (real_size == max_size)
	{
		T *old = data;
		data = new T[2 * max_size];//��һ������һ��������
		for (size_t i(0); i < max_size; ++i)
		{
			data[i] = old[i];
		}
		max_size *= 2;//�����ݷ���
	}
	//�����費��Ҫ���ݣ������Ĺ�����һ����
	data[real_size] = input;
	++real_size;
	return;
}

template <typename T>
void GRPVector<T>::pop_back()
{
	//�����û�д�����ɿ����Զ����ٳ��ȵĹ���
	--real_size;//ֱ�ӽ����ı�ʶ��ǰ���ɣ������ӾͿ��Ա������
	return;
}

template <typename T>
T& GRPVector<T>::operator[](int i)
{
	//cout << -static_cast<int>(real_size) << endl;
	//cout << (i >= -static_cast<int>(real_size)) << endl;
	if ((i < static_cast<int>(real_size)) && (i >= -static_cast<int>(real_size)))
	{
		if (i >= 0)
			return data[i];
		else
			return data[this->size() + i];
	}

	else
	{
		cout << "This GRPVector's size is " << real_size << endl;
		cout << "You should not read the place [" << i << "]" << endl;
		exit(-1);
	}
}

template <typename T>
T& GRPVector<T>::front()
{
	return (*this)[0];
}

template <typename T>
T& GRPVector<T>::back()
{
	return (*this)[this->size() - 1];
}

template <typename T>
void GRPVector<T>::insert(int i, const T& add)
{
	if (i < real_size)
	{
		this->push_back(this->back());//�����һλ�����������һ�Σ�����չ
		for (int j(i); j < real_size - 1; ++j)
		{
			(*this)[j + 1] = (*this)[j];
		}
		(*this)[i] = add;
	}
	else
	{
		cout << "GRPVector���ܳ���Ϊ" << real_size << "��������[" << i << "]������Ԫ��" << endl;
	}
	return;
}

template <typename T>
void GRPVector<T>::erase(int i)
{
	if (i < real_size)
	{
		for (int j(i); j < real_size - 1; ++j)
		{
			(*this)[j] = (*this)[j + 1];
		}
		this->pop_back();
	}
	else
	{
		cout << "GRPVector���ܳ���Ϊ" << real_size << "��������ɾ��[" << i << "]Ԫ��" << endl;
	}
	return;
}


template <typename T>
int GRPVector<T>::find(T which) const
{
	for (int i(0); i < real_size; ++i)
	{
		if (data[i] == which)
			return i;
	}
	return -1;//��Ϊ�޴�Ԫ�صı�־
}



template <typename T>
GRPVector<T>& GRPVector<T>::operator=(const GRPVector& copy)
{
	this->clear();
	for (int i(0); i < copy.size(); ++i)
	{
		this->push_back(copy[i]);
	}
	return *this;
}

struct Node
{
	int data = NOWAY;
	int father = 0;
};




int main()
{
	int n, begin, end;
	cin >> n >> begin >> end;
	//�ֱ�����˶���������㣬�ص�

	int data[N][N] = { 0 };
	for (int i(0); i < n; ++i)
	{
		for (int j(0); j < n; ++j)
		{
			cin >> data[i][j];
		}
	}
	//����������ֻ��n*n����������Ч��

	Node *way = new Node[n];
	int *sign = new int[n];//������ǵ�ǰ�Ľڵ��Ƿ񱻼�¼��
	for (int i(0); i < n; ++i)
	{
		sign[i] = 0;
	}
	sign[begin] = 1;//ֻ�����Ŀǰ�����ʹ���

	//way[begin].data = 0;//�����0�ĳ���
	//����ĵ��·�����ȶ��� NOWAY
	for (int i(0); i < n; ++i)
	{
		if (i == begin)
			way[i].data = 0;
		else
		{
			way[i].data = data[begin][i];//ֱ�Ӽ�ʹbegin��end�ľ���
			way[i].father = begin;
		}
	}

	/*for (int i(0); i < n; ++i)
	{
		cout << way[i].data << " " << way[i].father << endl;
	}*/

	for (int time(0); time < n - 1; ++time)//һ����n-1��
	{
		int now_min = NOWAY;
		int now_we_are(-1);
		for (int i = 0; i < n; ++i)
		{
			if (sign[i] == 0 && way[i].data < now_min)
			{
				now_min = way[i].data;
				now_we_are = i;
			}
			//cout << "?" << endl;
		}
		if (now_we_are == -1)
			break;
		sign[now_we_are] = 1;//��Ƿ��ʵ�λ��
		//cout << now_we_are << "-<" << endl;

		for (int k = 0; k < n; ++k)
		{
			if (data[now_we_are][k] < NOWAY)
			{
				if (way[k].data > way[now_we_are].data + data[now_we_are][k])
				{
					way[k].data = way[now_we_are].data + data[now_we_are][k];
					way[k].father = now_we_are;
				}
			}
		}
	}

	if (way[end].data == NOWAY)
		cout << "2^32-1" << endl;
	else
	{
		int point = end;
		GRPVector<int> output;
		while (point != begin)
		{
			output.push_back(way[point].father);
			point = way[point].father;
		}
		cout << way[end].data << endl;
		while(!output.empty())
		{
			cout << output.back() << "->";
			output.pop_back();
		}
		cout << end << endl;
	}

	return 0;
}