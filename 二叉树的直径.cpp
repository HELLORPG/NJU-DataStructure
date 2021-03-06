//#pragma once
/*
题目描述：
求一颗二叉树的直径，即二叉树中相距最远的两个节点之间的距离。

输入：
输入包括两行。 
第一行为一个整数，表示二叉树对应字符串的长度。 
第二行为二叉树对应字符串。 

输出：
输出一个整数，表示二叉树的直径长。

样例输入：
15
XABD@@@CE@@F@@@

样例输出：
4
*/
#ifndef GRP_BINTREE
#define GRP_BINTREE

#include <iostream>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::max;

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

	int find(T which) const;//寻找某元素，返回它的索引
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
		data = new T[2 * max_size];//开一个扩容一倍的数组
		for (size_t i(0); i < max_size; ++i)
		{
			data[i] = old[i];
		}
		max_size *= 2;//将扩容反馈
	}
	//无论需不需要扩容，后续的过程是一样的
	data[real_size] = input;
	++real_size;
	return;
}

template <typename T>
void GRPVector<T>::pop_back()
{
	//现如今没有打算完成可以自动减少长度的功能
	--real_size;//直接将最后的标识向前即可，这样子就可以避免访问
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
	return -1;//作为无此元素的标志
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
//	delete p;//换成delete[]就会不行，待解
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

//这里加入一个新的结构体，用于在栈中记录创建时候的节点，需要标注此时已经到了建立节点的左子树还是右子树<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
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
	GRPBinTreeNode<T> *ROOT;//作为二叉树的根节点
	T END;//数据输入停止的标志
	GRPBinTreeNode<T>* parent(GRPBinTreeNode<T> *sub_tree, GRPBinTreeNode<T> *current);//返回父节点的主要函数，以供私有调用

	bool insert(GRPBinTreeNode<T> *&sub_tree, const T &input);//插入新元素的主要实现函数，供私有调用
	int height(GRPBinTreeNode<T> *sub_tree);//返回子树的高度

	void show_data_oneline(GRPBinTreeNode<T> *x) const { cout << x->data; }//在同一行输出所有的数据点

	void show_all_postoder_oneline(GRPBinTreeNode<T> *x);

	int diameter(GRPBinTreeNode<T> *sub_tree, int &res);//计算二叉树的直径
public:
	GRPBinTree() :ROOT(nullptr) {}
	GRPBinTree(T end) :END(end), ROOT(nullptr) {}
	GRPBinTreeNode<T>* parent(GRPBinTreeNode<T> *current) { return (ROOT == nullptr || ROOT == current) ? nullptr : parent(ROOT, current); }
	//如果当前的节点是空或者已经是根节点，则没有父节点，否则则返回父节点

	int insert(const T &input);//插入新元素
	bool empty() { return ROOT == nullptr; }//二叉树是否为空
	int height() { return height(ROOT); }//直接求出树的高度

	
	int diameter();//计算直径的递归函数

	void show_all_postoder_oneline() { show_all_postoder_oneline(ROOT); }

	void preorder_create(GRPVector<T> &input, T null_node);//前序的输入建立一个二叉树，null_node代表了空节点的表示
};

template <typename T>
GRPBinTreeNode<T>* GRPBinTree<T>::parent(GRPBinTreeNode<T>* sub_tree, GRPBinTreeNode<T>* current)
{
	//从sub_tree开始，向下寻找current的父节点
	if (sub_tree == nullptr)
		return nullptr;
	else if (sub_tree->leftChild == current || sub_tree->rightChild == current)
		return sub_tree;
	else
	{
		GRPBinTreeNode<T> *p;
		if ((p = parent(sub_tree->leftChild, current)) != nullptr)
			return p;//递归左子树进行查找
		else
			return parent(sub_tree->rightChild, current);//在右子树寻找
	}
}

template <typename T>
int GRPBinTree<T>::height(GRPBinTreeNode<T>* sub_tree)
{
	if (sub_tree == nullptr)
		return 0;
	else
	{
		return max(height(sub_tree->leftChild), height(sub_tree->rightChild));
	}
}


template <typename T>
void GRPBinTree<T>::show_all_postoder_oneline(GRPBinTreeNode<T>* x)
{
	if (x != nullptr)
	{
		show_all_postoder_oneline(x->leftChild);
		show_all_postoder_oneline(x->rightChild);//通过递归进行后序遍历
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
	//对于第一个节点的单独讨论
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
int GRPBinTree<T>::diameter()
{
	int res(0);
	diameter(ROOT, res);
	return res;
}

template <typename T>
int GRPBinTree<T>::diameter(GRPBinTreeNode<T> *sub_tree, int& res)
{
	if (sub_tree == nullptr)
		return 0;
	else
	{
		int left_height = diameter(sub_tree->leftChild, res);
		int right_height = diameter(sub_tree->rightChild, res);
		res = max(res, left_height + right_height);
		return max(left_height, right_height) + 1;
	}
}



#endif


int main()
{
	size_t input_size(0);
	string input;
	cin >> input_size >> input;
	//输入所需要的数据，对于我自己来说，第一个数据是没有用的
	GRPVector<char> input_resave;
	for (auto x : input)
	{
		input_resave.push_back(x);
	}

	GRPBinTree<char> my_tree;
	my_tree.preorder_create(input_resave, '@');

	cout << my_tree.diameter() << endl;

	return 0;
}
