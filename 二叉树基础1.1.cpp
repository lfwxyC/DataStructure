#include<iostream>
using namespace std;

template<class T>
class arrayQueue//循环队列类 
{
public:
	arrayQueue(int initialCapacity=10);
	~arrayQueue(){delete[]queue;}
	
	bool empty(){return queueFront==queueBack;}
	void push(const T& theElement);//插入到队尾 
	void pop();//删除队首元素 
	T& front()const{return queue[(queueFront+1)%arrayLength];}//获取队首元素 
private:
	int queueFront;//指向队首元素逆时针的下一个 
	int queueBack;//指向队尾元素 
	int arrayLength;//数组容量 
	T *queue;//指向队列的数组 
};

template<class T>
arrayQueue<T>::arrayQueue(int initialCapacity)//构造函数 
{
	arrayLength=initialCapacity;
	queue=new T[arrayLength];
	queueFront=queueBack=0;//从1开始存放元素 
}

template<class T>
void arrayQueue<T>::push(const T& theElement)//插入 
{
	if(queueFront==(queueBack+1)%arrayLength)//数组已满，倍增数组长度 
	{
		T *newQueue=new T[arrayLength*2];
		int start=(queueFront+1)%arrayLength;//指向队首元素 
		
		if(start<2)//未形成环 
		{ 
			for(int i=start;i<=queueBack;i++)
				newQueue[i]=queue[i];
		} 
		else//形成环，分开复制 
		{
			int j=0;//记录newQueue数组中元素的位置 
			
			for(int i=start;i<arrayLength;i++)
			{
				newQueue[j]=queue[i];
				j++;
			}
			for(int i=0;i<=queueBack;i++)
			{
				newQueue[j]=queue[i];
				j++;
			}
		}
		queueFront=arrayLength*2-1;//新数组从0开始存放元素 
		queueBack=arrayLength-2; 
		arrayLength*=2;
		delete[]queue;
		queue=newQueue;
	}
	
	queueBack=(queueBack+1)%arrayLength;
	queue[queueBack]=theElement;
}

template<class T>
void arrayQueue<T>::pop()//删除 
{
	queueFront=(queueFront+1)%arrayLength; 
	queue[queueFront].~T();
}

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
	linkedBinaryTree(){root=NULL;treeSize=0;}
	~linkedBinaryTree(){erase();}
	
	void postOrder(void(*theVisit)(binaryTreeNode<E>*)){visit=theVisit;postOrder(root);}//后序遍历 
	void levelOrder();//层次遍历输出 
	void erase(){postOrder(dispose);root=NULL;}//删除 
	void createTree();//创建树 
	void size();//输出各子树大小 
	void height();//输出各子树高度 
private:
	binaryTreeNode<E> *root;//根节点 
	int treeSize;//节点个数 
	int *sizeArray;//存放各子树大小 
	int *heightArray;//存放各子树高度 
	
	static void (*visit)(binaryTreeNode<E>*);
	static void postOrder(binaryTreeNode<E> *t);//后序遍历 
	static void dispose(binaryTreeNode<E> *t){delete t;}//删除 
	static int size(binaryTreeNode<E> *t);//计算子树大小 
	static int height(binaryTreeNode<E> *t);//计算子树高度 
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
void linkedBinaryTree<E>::levelOrder()//层次遍历输出 
{
	arrayQueue<binaryTreeNode<E>*> q;//存放节点 
	binaryTreeNode<E> *t=root;
	
	while(t!=NULL)
	{
		cout<<t->element<<" ";//输出节点 
		
		if(t->leftChild!=NULL)
		{
			q.push(t->leftChild);
		}
		if(t->rightChild!=NULL)
		{
			q.push(t->rightChild);
		}
		
		t=q.front();
		
		if(q.empty())
		{
			break;
		}
		q.pop();
	}
	cout<<endl;
}

template<class E>
void linkedBinaryTree<E>::createTree()//创建树 
{
	int n;//节点个数 
	
	cin>>n;
	root=new binaryTreeNode<E>(1);//根节点为1 
	binaryTreeNode<E>* a[n*2];//按编号存放节点 
	a[0]=root;//根节点放入数组 
	treeSize++;
	
	for(int i=0;i<n;i++)
	{
		E left,right;//左右孩子的数值 
		cin>>left>>right;
		
		binaryTreeNode<E> *t=a[i];
		
		if(left!=-1)
		{
			binaryTreeNode<E> *leftChild=new binaryTreeNode<E>(left);
			
			t->leftChild=leftChild;
			a[left-1]=leftChild;
			treeSize++;
		}
		if(right!=-1)
		{
			binaryTreeNode<E> *rightChild=new binaryTreeNode<E>(right);
			
			t->rightChild=rightChild;
			a[right-1]=rightChild;
			treeSize++;
		}
	}
}

template<class E>
void linkedBinaryTree<E>::size()//输出各子树大小 
{
	sizeArray=new int[treeSize];
	arrayQueue<binaryTreeNode<E>*> q;
	binaryTreeNode<E> *t=root;
	
	while(t!=NULL)
	{
		sizeArray[t->element-1]=size(t);//计算以该节点为根的子树大小，放入编号对应的数组位置 
	
		if(t->leftChild!=NULL)
		{
			q.push(t->leftChild);
		}
		if(t->rightChild!=NULL)
		{
			q.push(t->rightChild);
		}
		
		t=q.front();
		
		if(q.empty())
		{
			break;
		}
		q.pop();
	}
	
	for(int i=0;i<treeSize;i++)//按编号输出各子树大小 
	{
		cout<<sizeArray[i]<<" ";
	}
	cout<<endl;
	delete[]sizeArray;
}

template<class E>
int linkedBinaryTree<E>::size(binaryTreeNode<E> *t)//递归计算各子树大小 
{
	if(t==NULL)//没有节点 
	{
		return 0;
	}
	return size(t->leftChild)+size(t->rightChild)+1;//左孩子个数+右孩子个数+根节点 
}

template<class E>
void linkedBinaryTree<E>::height()//输出各子树高度 
{
	heightArray=new int[treeSize];
	arrayQueue<binaryTreeNode<E>*> q;
	binaryTreeNode<E> *t=root;
	
	while(t!=NULL)
	{
		heightArray[t->element-1]=height(t);
	
		if(t->leftChild!=NULL)
		{
			q.push(t->leftChild);
		}
		if(t->rightChild!=NULL)
		{
			q.push(t->rightChild);
		}
		
		t=q.front();
		
		if(q.empty())
		{
			break;
		}
		q.pop();
	}
	
	for(int i=0;i<treeSize;i++)
	{
		cout<<heightArray[i]<<" ";
	}
	cout<<endl;
	delete[]heightArray;
}

template<class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E> *t)//计算子树高度 
{
	if(t==NULL)//没有节点 
	{
		return 0;
	}
	
	int hl=height(t->leftChild);//左子树高度 
	int hr=height(t->rightChild);//右子树高度 
	
	if(hl>hr)
	{
		return ++hl;
	}
	else
	{
		return ++hr;
	}
}

int main()
{
	linkedBinaryTree<int> l;
	
	l.createTree();
	l.levelOrder();
	l.size();
	l.height();
	return 0;
}
