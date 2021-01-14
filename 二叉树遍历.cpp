#include<iostream>
using namespace std;

template<class T>
struct binaryTreeNode//二叉树节点 
{
	T element;//数值 
	binaryTreeNode<T> *leftChild,*rightChild;//左右孩子 
	
	//构造函数 
	binaryTreeNode(){leftChild=rightChild=NULL;}
	binaryTreeNode(const T& theElement)
	{
		element=theElement;
		leftChild=rightChild=NULL;
	}
	binaryTreeNode(const T& theElement,binaryTreeNode<T> *theLeftChild,binaryTreeNode<T> *theRightChild)
	{
		element=theElement;
		leftChild=theLeftChild;
		rightChild=theRightChild;
	}
};

template<class E>
class linkedBinaryTree//二叉树 
{
public:
	linkedBinaryTree(){root=NULL;}
	~linkedBinaryTree(){erase();}
	
	void postOrder(void(*theVisit)(binaryTreeNode<E>*)){visit=theVisit;postOrder(root);}//后序遍历 	
	void postOrderOutput(){postOrder(output);cout<<endl;}//后序遍历输出 
	void erase(){postOrder(dispose);root=NULL;}//删除 
	binaryTreeNode<E>* createTree(int preOrder[],int inOrder[],int preBegin,int preEnd,int inBegin,int inEnd);//根据前序和中序建树 
private:
	binaryTreeNode<E> *root;//根节点	
	
	static void (*visit)(binaryTreeNode<E>*);
	static void postOrder(binaryTreeNode<E> *t);//后序遍历 
	static void dispose(binaryTreeNode<E> *t){delete t;}//删除 
	static void output(binaryTreeNode<E> *t){cout<<t->element<<" ";}//输出 
};

template<class E>
void (*linkedBinaryTree<E>::visit)(binaryTreeNode<E>*);

template<class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E> *t)//后序遍历 
{
	if(t!=NULL)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		linkedBinaryTree<E>::visit(t);
	}
}

template<class E>
binaryTreeNode<E>* linkedBinaryTree<E>::createTree(int preOrder[],int inOrder[],int preBegin,int preEnd,int inBegin,int inEnd)//建树 
{
	binaryTreeNode<E> *t=new binaryTreeNode<E>(preOrder[preBegin]);//子树的根节点 
	
	if(preBegin==preEnd&&inBegin==inEnd)//只有一个节点 
	{
		root=t;
		return t;
	}
	
	int i=inBegin;
	
	for(;i<inEnd;i++)//在中序数组中寻找根节点 
		if(inOrder[i]==preOrder[preBegin])
			break;
	
	if(i-inBegin)//中序数组中，根节点之前的元素是其左子树 
		t->leftChild=createTree(preOrder,inOrder,preBegin+1,preBegin+i-inBegin,inBegin,i-1);//递归创建左子树 
	
	if(inEnd-i)//右子树 
		t->rightChild=createTree(preOrder,inOrder,preBegin+i-inBegin+1,preEnd,i+1,inEnd);
	
	root=t;
	return t;
}

int main()
{
	int n; 
	linkedBinaryTree<int> l;
	
	cin>>n;
	int preOrder[n],inOrder[n];//前序和中序数组 
	
	for(int i=0;i<n;i++)
		cin>>preOrder[i];
	
	for(int i=0;i<n;i++)
		cin>>inOrder[i];
	
	l.createTree(preOrder,inOrder,0,n-1,0,n-1);
	l.postOrderOutput();
	return 0;
}
