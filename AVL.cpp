#pragma once
#include <iostream>
#include <algorithm>

using std::end;
using std::cout;
using std::cin;

#define BinNodePosi(T) BinNode<T>* //���ؽڵ��ָ��
#define stature(p) ((p) ? (p)->height : -1) //���ؽڵ�ĸ߶ȣ�Լ���սڵ�Ϊ-1��
typedef enum { RB_RED, RB_BLACK } RBColor; //�ڵ����ɫ�����ں����

template <typename T>
struct BinNode
{
	T data;//��ֵ
	BinNodePosi(T) parent;
	BinNodePosi(T) left_child;
	BinNodePosi(T) right_child;
	int height;//�߶�
	int npl;//Null Path Length����ʽ�ѣ�Ҳ����ֱ����height���棩
	RBColor color;//���ں��������ɫ

	//���캯��
	BinNode() :parent(nullptr), left_child(nullptr), right_child(nullptr), height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T) rc = nullptr, int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), left_child(lc), right_child(rc), height(h), npl(l), color(c) {}

	//�����ӿ�
	int size(); //ͳ�Ƶ�ǰ�ڵ���������������Ϊ���������Ĺ�ģ
	BinNodePosi(T) insertAsLc(T const&);//��Ϊ��ǰ�ڵ�����Ӳ���ڵ�
	BinNodePosi(T) insertAsRc(T const&);//��Ϊ��ǰ�ڵ���Һ��Ӳ���ڵ�
	BinNodePosi(T) succ(); //ȡ��ǰ�ڵ��ֱ�Ӻ��
	template <typename VST> void travLevel(VST&);//������α���
	template <typename VST> void travPre(VST&);//�����������
	template <typename VST> void travIn(VST&);//�����������
	template <typename VST> void travPost(VST&);//�����������

	//�Ƚ������е�����
	bool operator<(BinNode const& bn) { return data < bn.data; }
	bool operator==(BinNode const& bn) { return data == bn.data; }
};

#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->left_child))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->right_child))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).left_child)
#define HasRChild(x) ((x).right_child)
#define HasChild(x) (HasLChild(x) || HasRChild(x)) //����ӵ��һ������
#define HasBothChild(x) (HasLChild(x) && HasRChild(x)) //ͬʱӵ����������
#define IsLeaf(x) (!HasChild(x))

//����BinNode�����ض���ϵ�Ľڵ��Լ�ָ��
#define sibling(p)/*�ֵ�*/\
	(IsLChild(*(p)) ? (p)->parent->right_child : (p)->parent->left_child)

#define uncle(x) /*����*/\
	(IsLChild(*((x)->parent)) ? (x)->parent->parent->right_child : (x)->parent->parent->left_child)

#define FromParentTo(x)/*���Ի�������丸�׵�����*/\
	(IsRoot(x) ? BinTree<T>::_root : (IsLChild(x) ? (x).parent->left_child : (x).parent->right_child))

template <typename T>
BinNode<T>* BinNode<T>::insertAsLc(T const& e)
{
	return left_child = new BinNode(e, this);
}

template <typename T>
BinNode<T>* BinNode<T>::insertAsRc(T const& e)
{
	return right_child = new BinNode(e, this);
}

template <typename T>
BinNode<T>* BinNode<T>::succ()
{
	BinNodePosi(T) s = this;
	if (right_child)
	{
		s = right_child;
		while (HasLChild(*s))
			s = s->left_child;
	}
	else
	{
		while (IsRChild(*s))
			s = s->parent;
		s = s->parent;
	}
	return s;
}



template <typename T>
class BinTree
{
protected:
	int _size;
	BinNodePosi(T) _root;//��Ϊ���ڵ�
	//virtual int updateHeight(BinNodePosi(T) x);//���½ڵ�x�ĸ߶�
	//void updateHeightAbove(BinNodePosi(T) x);//���½ڵ�x�Լ������ȵĸ߶�

public:
	BinTree() :_size(0), _root(nullptr) {}
	//virtual ~BinTree() { if (_size > 0) remove(_root); }//��������
	int size() const { return _size; }//��ģ
	BinNodePosi(T) root() const { return _root; }
	BinNodePosi(T) insertAsRoot(T const& e);//������ڵ�
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &t);//T��Ϊx������������
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &t);//T��Ϊx������������
	//int remove(BinNodePosi(T) x);//ɾ����λ��xΪ���ڵ�����������ظ�����ԭ�ȵĹ�ģ
	BinTree<T>* secede(BinNodePosi(T) x);//������x�ӵ�ǰ����ժ����������ת��Ϊһ�ö�������

	static int updateHeight(BinNodePosi(T) x);//���½ڵ�x�ĸ߶�
	static void updateHeightAbove(BinNodePosi(T) x);//���½ڵ�x�Լ������ȵĸ߶�

	template <typename VST>//������
	void travLevel(VST& visit) { if (_root) _root->travLevel(visit); }//��α���
	template <typename VST>
	void travPre(VST& visit) { if (_root) _root->travPre(visit); }
	template <typename VST>
	void travIn(VST& visit) { if (_root) _root->travIn(visit); }
	template <typename VST>
	void travPost(VST& visit) { if (_root) _root->travPost(visit); }//��������

	bool operator<(BinTree<T> const& t)
	{
		return _root && t._root && /*need to add*/ 1;
	}
	bool operator==(BinTree<T> const& t)
	{
		return _root && t._root && (_root == t._root);
	}
};

template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + std::max(stature(x->left_child), stature(x->right_child));
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while (x)
	{
		updateHeight(x);
		x = x->parent;
	}
	return;
}



template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)
{
	_size = 1;
	return _root = new BinNode<T>(e);
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e)
{
	++_size;
	x->insertAsLc(e);
	updateHeightAbove(x);
	return x->left_child;
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)
{
	++_size;
	x->insertAsRc(e);
	updateHeightAbove(x);
	return x->right_child;
}

//Binary Search Tree == BST
//����������

template <typename T>
class BST : public BinTree<T>
{
protected:
	BinNode<T>* _hot;//�����С��ڵ�ĸ���
	//BinNodePosi(T) connect34(BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));//���ա�3+4����ͨʽ�ṹ���������ڵ��Լ��Ŀ�����
	BinNodePosi(T) rotateAt(BinNodePosi(T) v);//��x���丸�ס��游��ͳһ��ת����
public:
	BinNodePosi(T) connect34(BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));//���ա�3+4����ͨʽ�ṹ���������ڵ��Լ��Ŀ�����
	virtual BinNodePosi(T)& search(const T& e);//����
	virtual BinNodePosi(T) insert(const T& e);//����
	//virtual bool remove(const T& e);//ɾ��
	//static BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot);
};

template <typename T>
static BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot)
{
	if (!v || (e == v->data))
		return v;
	hot = v;//���µ�ǰ�Ľڵ㣬����֮������н���ĸ��׽ڵ�
	return searchIn(((e < v->data) ? v->left_child : v->right_child), e, hot);
}

template <typename T>
BinNodePosi(T)& BST<T>::search(const T& e)
{
	return searchIn(BinTree<T>::_root, e, _hot = nullptr);//��_hot���и�ֵ�ĸ��£�������Ϊ�ս�����һ���Ĳ���
}

template <typename T>
BinNode<T>* BST<T>::insert(const T& e)
{
	BinNodePosi(T)& x = search(e);
	if (x)
		return x;//���Ŀ���Ѿ����ڣ�����Ҫ��һ��������
	x = new BinNode<T>(e, _hot);
	++BinTree<T>::_size;
	BinTree<T>::updateHeightAbove(x);
	
	return x;
}


template <typename T>
class ALV : public BST<T>
{
public:
	void show();
	BinNode<T>* insert(const T& e);
	//bool remove(const T& e);
};

#define Balanced(x) (stature((x).left_child) == stature((x).right_child))//����ƽ������
#define BalFac(x) (stature((x).left_child) - stature((x).right_child))//ƽ������
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))//AVL��ƽ������

#define tallerChild(x)(\
	stature((x)->left_child) > stature((x)->right_child) ? (x)->left_child : (\
	stature((x)->left_child) < stature((x)->right_child) ? (x)->right_child : (\
	IsLChild(*(x)) ? (x)->left_child : (x)->right_child\
	)\
	)\
)

template <typename T>
BinNode<T>* ALV<T>::insert(const T& e)
{
	BinNode<T>*& x = BST<T>::search(e);
	if (x)
		return x;
	BinNode<T>* xx = x = new BinNode<T>(e, BST<T>::_hot);
	for (BinNode<T>* g = BST<T>::_hot; g; g = g->parent)//�ӵ����Ͻ��е���
	{
		/*
		if (!AvlBalanced(*g))
		{
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
			break;//g�ָ�ƽ��֮�󣬾ֲ������߶ȱ�Ȼ��ԭ������������ˣ��ʵ������漴������
		}
		*/
		if (!AvlBalanced(*g))
		{
			//cout<<this->search(25)<<" can i find?"<<std::endl;
			//FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
			if (g->parent == nullptr)
				BinTree<T>::_root = rotateAt(tallerChild(tallerChild(g)));
			else if (IsLChild(*g))
				g->parent->left_child = rotateAt(tallerChild(tallerChild(g)));
			else
				g->parent->right_child = rotateAt(tallerChild(tallerChild(g)));
			//cout<<this->search(25)<<" can i find?"<<std::endl;
			break;//g�ָ�ƽ��֮�󣬾ֲ������߶ȱ�Ȼ��ԭ������������ˣ��ʵ������漴������
		}
		//�˶κ�����ͨ����Linux�Լ�OJ���ԵĲ��֣���֪��Ϊʲô
		else
		{
			BinTree<T>::updateHeight(g);//���¸߶�
		}
	}//��������ֻ��һ��
	//cout << "insert " << xx->data<< std::endl;
	return xx;
}

template <typename T>
BinNodePosi(T) connect34(BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c, BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3)
{
	a->left_child = T0;
	if (T0)
		T0->parent = a;
	a->right_child = T1;
	if (T1)
		T1->parent = a;
	BinTree<T>::updateHeight(a);

	c->left_child = T2;
	if (T2)
		T2->parent = c;
	c->right_child = T3;
	if (T3)
		T3->parent = c;
	BinTree<T>::updateHeight(c);

	b->left_child = a;
	a->parent = b;
	b->right_child = c;
	c->parent = b;
	BinTree<T>::updateHeight(b);
	return b;//�������Ľڵ�
}

template <typename T>
BinNodePosi(T) rotateAt(BinNodePosi(T) v)
{
	BinNode<T>* p = v->parent;
	BinNode<T>* g = p->parent;//�ҵ����ף��游�ڵ㣬֮��Ҫ�����������������

	if (IsLChild(*p))
	{
		if (IsLChild(*v))
		{
			p->parent = g->parent;//���Ͻ�������
			cout << "1" << std::endl;
			return connect34(v, p, g, v->left_child, v->right_child, p->right_child, g->right_child);
			//cout << "1" << std::endl;
		}
		else
		{
			v->parent = g->parent;
			cout << "2" << std::endl;
			return connect34(p, v, g, p->left_child, v->left_child, v->right_child, g->right_child);
		}
	}

	else
	{
		if (IsRChild(*v))
		{
			p->parent = g->parent;
			cout << "3" << std::endl;
			return connect34(g, p, v, g->left_child, p->left_child, v->left_child, v->right_child);
		}
		else
		{
			v->parent = g->parent;
			cout << "4" << std::endl;
			return connect34(g, v, p, g->left_child, v->left_child, v->right_child, p->right_child);
		}
	}
}
template <typename T>
void visit_root(BinNode<T>* x)
{
	//cout << "what";
	if (x)
	{
		cout << x->data << " ";
		visit_root(x->left_child);
		visit_root(x->right_child);
	}
	return;
}

template <typename T>
void ALV<T>::show()
{
	//cout << BinTree<T>::_root << std::endl;
	//cout << "what" << std::endl;
	visit_root(BinTree<T>::_root);
	return;
}




int main()
{
	ALV<int> tree;
	int n(0);
	cin >> n;
	int input;
	/*64 71 62 25 11 23 27 83 70*/
	for (int i(0); i < n; ++i)
	{
		cin >> input;
		tree.insert(input);
		//cout << input << " ";
	}
	tree.show();
	//cout << "--" << tree.search(25) << std::endl;
	return 0;
}