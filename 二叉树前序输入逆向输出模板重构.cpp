//#pragma once
#ifndef GRP_BINTREE
#define GRP_BINTREE

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

template <typename T>
class GRPStack;

//template <typename T>
//class GRPNode
//{
//	friend class GRPStack<T>;
//protected:
//	T data;
//	GRPNode *before;
//	GRPNode *next;
//	GRPNode() = default;
//	GRPNode(T data, GRPNode *before) :data(data), before(before), next(nullptr) {}
//	~GRPNode() {}
//};


#ifndef GRP_VECTOR
#define GRP_VECTOR
#define DEFAULTSIZE 5

template <typename T>
class GRPVector
{
protected:
	T *data;
	size_t max_size;
	size_t real_size;
public:
	GRPVector();

	void push_back(T input);
	void pop_back();
	size_t size() const;

	T& front();
	T& back();
	T& operator[](int i);

	int find(T which) const;//Ѱ��ĳԪ�أ�������������
};

template <typename T>
GRPVector<T>::GRPVector() : data(new T[DEFAULTSIZE]), max_size(5), real_size(0) {}


template <typename T>
size_t GRPVector<T>::size() const
{
	return real_size;
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
	return (*this)[this->size()];
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

#endif

template <typename T>
class GRPSinNode
{
	friend class GRPStack<T>;
protected:
	T data;
	GRPSinNode *next;
	GRPSinNode() :data(*(new T)), next(nullptr) {}
	GRPSinNode(T data) :data(data), next(nullptr) {}
	GRPSinNode(T data, GRPSinNode *next) :data(data), next(next) {}
	~GRPSinNode() {}
};

template <typename T>
class GRPStack
{
private:
	GRPSinNode<T> *FIRST/*, *current*/;
	size_t stack_size;
public:
	GRPStack();
	~GRPStack();
	void push(T input);
	T pop();
	T& top();
	size_t size() const;
	void show() const;
	bool empty() const;
	void clear();
};

//template <typename T>
//GRPStack<T>::GRPStack()
//{
//	FIRST = current = new GRPNode<T>;
//	stack_size = 0;
//}
//
//template <typename T>
//GRPStack<T>::~GRPStack()
//{
//	GRPNode<T> *kill(FIRST);
//	for (; FIRST != nullptr;)
//	{
//		kill = FIRST;
//		FIRST = FIRST->next;
//		delete kill;
//	}
//}
//
//template <typename T>
//void GRPStack<T>::push(T input)
//{
//	GRPNode<T> *add = new GRPNode<T>(input, current);
//	current->next = add;
//	current = add;
//	++stack_size;
//	return;
//}
//
//template <typename T>
//T GRPStack<T>::pop()
//{
//	GRPNode<T> *p = current;
//	current = current->before;
//	current->next = nullptr;
//	--stack_size;
//	T pop_ret(p->data);
//	delete p;//����delete[]�ͻ᲻�У�����
//	return pop_ret;
//}
//
//template <typename T>
//T GRPStack<T>::top()
//{
//	return current->data;
//}
//
//template <typename T>
//size_t GRPStack<T>::size() const
//{
//	return stack_size;
//}
//
//template <typename T>
//void GRPStack<T>::show() const
//{
//	GRPNode<T> *p(FIRST->next);
//	for (; p != nullptr; p = p->next)
//		cout << p->data << " ";
//	cout << endl;
//	return;
//}
//
//template <typename T>
//bool GRPStack<T>::empty() const
//{
//	return current == FIRST;
//}
//
//template <typename T>
//void GRPStack<T>::clear()
//{
//	while (!this->empty())
//		this->pop();
//	stack_size = 0;
//	return;
//}

#ifndef GRP_STACK
#define GRP_STACK
template <typename T>
GRPStack<T>::GRPStack()
{
	FIRST = new GRPSinNode<T>;
	stack_size = 0;
}

template <typename T>
void GRPStack<T>::push(T input)
{
	FIRST->next = new GRPSinNode<T>(input, FIRST->next);
	++stack_size;
	return;
}

template <typename T>
T GRPStack<T>::pop()
{
	GRPSinNode<T> *p(FIRST->next);
	T ret_data(p->data);
	FIRST->next = p->next;
	delete p;
	--stack_size;
	return ret_data;
}

template <typename T>
size_t GRPStack<T>::size() const
{
	return stack_size;
}

template <typename T>
bool GRPStack<T>::empty() const
{
	return !(FIRST->next);
}

template <typename T>
void GRPStack<T>::clear()
{
	while (!this->empty())
		this->pop();
	stack_size = 0;
	return;
}

template <typename T>
T& GRPStack<T>::top()
{
	return FIRST->next->data;
}

template <typename T>
GRPStack<T>::~GRPStack()
{
	for (GRPSinNode<T> *p(FIRST); p != nullptr;)
	{
		GRPSinNode<T> *kill = p;
		p = p->next;
		delete kill;
	}
}

template <typename T>
void GRPStack<T>::show() const
{
	cout << "==========" << endl << "<TOP>" << endl;
	for (GRPSinNode<T> *p(FIRST->next); p != nullptr; p = p->next)
		cout << p->data << endl;
	cout << "==========" << endl;
	return;
}

#endif


template <typename T>
class GRPBinTree;

template <typename T>
class GRPBinTreeNode
{
	friend class GRPBinTree<T>;
protected:
	T data;
	GRPBinTreeNode *leftChild, *rightChild;
	GRPBinTreeNode() :leftChild(nullptr), rightChild(nullptr) {}
	GRPBinTreeNode(T x, GRPBinTreeNode *left = nullptr, GRPBinTreeNode *right = nullptr) :data(x), leftChild(left), rightChild(right) {}
};

//�������һ���µĽṹ�壬������ջ�м�¼����ʱ��Ľڵ㣬��Ҫ��ע��ʱ�Ѿ����˽����ڵ������������������<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
enum Child { LEFT, RIGHT };

template <typename T>
struct GRPBinTreeBuildNode
{
	GRPBinTreeNode<T> *p;
	Child child;
};
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

template <typename T>
class GRPBinTree
{
protected:
	GRPBinTreeNode<T> *ROOT;//��Ϊ�������ĸ��ڵ�
	T END;//��������ֹͣ�ı�־
	GRPBinTreeNode<T>* parent(GRPBinTreeNode<T> *sub_tree, GRPBinTreeNode<T> *current);//���ظ��ڵ����Ҫ�������Թ�˽�е���

	bool insert(GRPBinTreeNode<T> *&sub_tree, const T &input);//������Ԫ�ص���Ҫʵ�ֺ�������˽�е���
	void show_data_oneline(GRPBinTreeNode<T> *x) const { cout << x->data; }//��ͬһ��������е����ݵ�

	void show_all_postoder_oneline(GRPBinTreeNode<T> *x);

	void find_the_way(GRPVector<T> &store, GRPBinTreeNode<T> *x, int i);
public:
	GRPBinTree() :ROOT(nullptr) {}
	GRPBinTree(T end) :END(end), ROOT(nullptr) {}
	GRPBinTreeNode<T>* parent(GRPBinTreeNode<T> *current) { return (ROOT == nullptr || ROOT == current) ? nullptr : parent(ROOT, current); }
	//�����ǰ�Ľڵ��ǿջ����Ѿ��Ǹ��ڵ㣬��û�и��ڵ㣬�����򷵻ظ��ڵ�

	int insert(const T &input);//������Ԫ��
	bool empty() { return ROOT == nullptr; }//�������Ƿ�Ϊ��

	void show_all_postoder_oneline() { show_all_postoder_oneline(ROOT); }

	void preorder_create(GRPVector<T> &input, T null_node);//ǰ������뽨��һ����������null_node�����˿սڵ�ı�ʾ

	void find_the_way(GRPVector<T> &store) { find_the_way(store, ROOT, 1); }
};

template <typename T>
GRPBinTreeNode<T>* GRPBinTree<T>::parent(GRPBinTreeNode<T>* sub_tree, GRPBinTreeNode<T>* current)
{
	//��sub_tree��ʼ������Ѱ��current�ĸ��ڵ�
	if (sub_tree == nullptr)
		return nullptr;
	else if (sub_tree->leftChild == current || sub_tree->rightChild == current)
		return sub_tree;
	else
	{
		GRPBinTreeNode<T> *p;
		if ((p = parent(sub_tree->leftChild, current)) != nullptr)
			return p;//�ݹ����������в���
		else
			return parent(sub_tree->rightChild, current);//��������Ѱ��
	}
}

template <typename T>
void GRPBinTree<T>::show_all_postoder_oneline(GRPBinTreeNode<T>* x)
{
	if (x != nullptr)
	{
		show_all_postoder_oneline(x->leftChild);
		show_all_postoder_oneline(x->rightChild);//ͨ���ݹ���к������
		show_data_oneline(x);
	}
	return;
}

template <typename T>
void GRPBinTree<T>::preorder_create(GRPVector<T>& input, T null_node)
{
	if (input.size() == 0 || input[0] == null_node)
	{
		ROOT = nullptr;
		return;
	}
	ROOT = new GRPBinTreeNode<T>;
	ROOT->data = input[0];
	//���ڵ�һ���ڵ�ĵ�������
	GRPStack<GRPBinTreeBuildNode<T>> node_stack;
	node_stack.push({ ROOT,LEFT });
	for (int i(1); i < input.size(); ++i)
	{
		if (input[i] != null_node)
		{
			if (node_stack.top().child == LEFT)
			{
				node_stack.top().p->leftChild = new GRPBinTreeNode<T>(input[i]);
				node_stack.top().child = RIGHT;
				node_stack.push({ node_stack.top().p->leftChild,LEFT });
			}
			else
			{
				GRPBinTreeNode<T> *p = node_stack.top().p->rightChild = new GRPBinTreeNode<T>(input[i]);
				node_stack.pop();
				node_stack.push({ p,LEFT });
			}
		}
		else
		{
			if (node_stack.top().child == LEFT)
				node_stack.top().child = RIGHT;
			else
				node_stack.pop();
		}
	}
	return;
}

template <typename T>
void GRPBinTree<T>::find_the_way(GRPVector<T>& store, GRPBinTreeNode<T>* x, int i)
{
	store[i - 1] = x->data;//���ýڵ�������׼��
	//cout << i << endl;
	if (x->leftChild == nullptr && x->rightChild == nullptr)
	{
		//cout << "���Ϊ" << i << endl;
		//cout << "find the end" << endl;
		for (int j(i - 1); j >= 0; --j)
			cout << store[j];
		cout << endl;
		//return;
	}
	else
	{
		if (x->leftChild != nullptr)
		{
			//cout << x->data << "������Ϊ" << x->leftChild->data << endl;
			find_the_way(store, x->leftChild, i + 1);
		}
		if (x->rightChild != nullptr)
		{
			//cout << x->data << "������Ϊ" << x->rightChild->data << endl;
			find_the_way(store, x->rightChild, i + 1);
		}
		//return;
	}
	return;
}


#endif




int main()
{
	GRPBinTree<char> tree;
	string input;
	cin >> input;
	GRPVector<char> output;
	GRPVector<char> input_resave;
	//if (input != "ABCD@@@@@" && input!="ABD@@@CE@@F@@" && input != "ABD@@@C@E@@")
	//cout << input << endl;
	for (auto x : input)
		input_resave.push_back(x);
	for (int i(0); i < input.length(); ++i)
		output.push_back('\0');
	tree.preorder_create(input_resave, '@');
	//tree.show_all_postoder_oneline();
	tree.find_the_way(output);
	return 0;
}