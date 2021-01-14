#include<iostream>
using namespace std;

template<class T>
struct binaryTreeNode//二叉树节点 
{
	T element;//数值 
	int leftSize;//以该节点为根的左子树大小 
	binaryTreeNode<T> *leftChild,*rightChild;//左右孩子 
	
	//构造函数 
	binaryTreeNode(){leftChild=rightChild=NULL;leftSize=0;}
	binaryTreeNode(const T& theElement)
	{
		element=theElement;
		leftChild=rightChild=NULL;
		leftSize=0;
	}
	binaryTreeNode(const T& theElement,binaryTreeNode<T> *theLeftChild,binaryTreeNode<T> *theRightChild)
	{
		element=theElement;
		leftChild=theLeftChild;
		rightChild=theRightChild;
		leftSize=0;
	}
};

template<class T>
class indexedBinarySearchTree//索引二叉搜索树 
{
public:
	indexedBinarySearchTree(){root=NULL;treeSize=0;}
	~indexedBinarySearchTree(){eraseAll();}
	
	T* find(const T& theElement)const;//查找 
	void insert(const T& theElement);//插入 
	void erase(const T& theElement);//删除 
	void findIndex(int theIndex)const;//按索引查找 
	void eraseIndex(int theIndex);//按索引删除 
	
	void eraseAll(){postOrder(dispose);root=NULL;}
	void postOrder(void(*theVisit)(binaryTreeNode<T>*)){visit=theVisit;postOrder(root);}//后序遍历 
private:
	binaryTreeNode<T> *root;//根节点 
	int treeSize;//树的大小 
	
	static void (*visit)(binaryTreeNode<T>*);
	static void postOrder(binaryTreeNode<T> *t);//后序遍历 
	static void dispose(binaryTreeNode<T> *t){delete t;}//删除 		
};

template<class T>
void (*indexedBinarySearchTree<T>::visit)(binaryTreeNode<T>*);

template<class T>
void indexedBinarySearchTree<T>::postOrder(binaryTreeNode<T> *t)//后序遍历 
{
	if(t!=NULL)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		indexedBinarySearchTree<T>::visit(t);
	}
}

template<class T>
T* indexedBinarySearchTree<T>::find(const T& theElement)const//查找 
{
	binaryTreeNode<T> *t=root;
	T value=0;//异或值 
	
	while(t!=NULL) 
	{
		value^=t->element;//和比较元素做异或 
		
		if(t->element>theElement)//查找元素在左子树 
		{
			t=t->leftChild;
		}
		else if(t->element<theElement)//查找元素在右子树 
		{
			t=t->rightChild;
		}
		else//找到 
		{
			cout<<value<<endl;
			return &t->element;
		}
	}
	cout<<0<<endl;//未找到 
	return NULL;
}

template<class T>
void indexedBinarySearchTree<T>::insert(const T& theElement)//插入 
{
	binaryTreeNode<T> *t=root;
	T value=0;//异或值 
	
	//查找元素是否存在 
	while(t!=NULL)
	{
		value^=t->element;//和比较元素做异或 
		
		if(t->element>theElement)//元素在左子树 
		{
			t=t->leftChild;
		}
		else if(t->element<theElement)//元素在右子树 
		{
			t=t->rightChild;
		}
		else//元素已存在 
		{
			cout<<0<<endl;
			return;
		}
	}
	cout<<value<<endl;
	
	binaryTreeNode<T> *p=root,*pp=NULL;
	
	while(p!=NULL)
	{
		pp=p;
		
		if(p->element>theElement)//插入到左子树 
		{
			p=p->leftChild;
			pp->leftSize++;
		}
		else//插入到右子树 
		{
			p=p->rightChild;
		}
	}
	
	binaryTreeNode<T> *newNode=new binaryTreeNode<T>(theElement);//插入元素 
	
	if(root!=NULL)
	{
		if(pp->element>theElement)
		{
			pp->leftChild=newNode;
		}
		else
		{
			pp->rightChild=newNode;
		}
	}
	else//插入到根节点 
	{
		root=newNode;
	}
	treeSize++;
}

template<class T>
void indexedBinarySearchTree<T>::erase(const T& theElement)//删除 
{
	T *t=find(theElement);//查找元素是否存在 
	if(t==NULL)//不存在 
	{
		return;
	}
	
	binaryTreeNode<T> *p=root,*pp=NULL;
	
	while(p!=NULL&&p->element!=theElement)
	{
		pp=p;
		
		if(p->element>theElement)//删除元素在左子树 
		{
			p=p->leftChild;
			pp->leftSize--;
		}
		else//删除元素在右子树 
		{
			p=p->rightChild;
		}
	}
	
	if(p->leftChild!=NULL&&p->rightChild!=NULL)//删除元素有两个子树 
	{
		binaryTreeNode<T> *s=p->rightChild,*ps=p;//替换右子树的最小元素 
		
		while(s->leftChild!=NULL)//最左边的节点最小 
		{
			ps=s;
			s->leftSize--;
			s=s->leftChild;
		}
		
		p->element=s->element;//更改删除元素的值 
		p=s;//p移动到替换节点 
		pp=ps;
	}
	
	binaryTreeNode<T> *c;
	
	//只有一个子树 
	if(p->leftChild!=NULL)//只有左子树 
	{
		c=p->leftChild;
	}
	else//只有右子树 
	{
		c=p->rightChild;
	}
	
	if(p==root)//删除根节点 
	{
		root=c;
	}
	else//删除其他节点 
	{
		if(p==pp->leftChild) 
		{
			pp->leftChild=c;
		}
		else 
		{
			pp->rightChild=c;
		}
	}
	treeSize--;
	delete p;
}

template<class T>
void indexedBinarySearchTree<T>::findIndex(int theIndex)const//按索引查找 
{
	theIndex--;//索引=题目所给名次-1 
	binaryTreeNode<T> *t=root;
	T value=0;//异或值 
	
	while(t!=NULL)
	{
		value^=t->element;//和比较元素做异或 
		
		if(t->leftSize>theIndex)//元素在左子树 
		{
			t=t->leftChild;
		}
		else if(t->leftSize<theIndex)//元素在右子树 
		{
			theIndex=theIndex-(t->leftSize+1);//改变索引 
			t=t->rightChild;
		}
		else//找到 
		{
			cout<<value<<endl;
			return;
		}
	}
	cout<<0<<endl;//未找到 
}

template<class T>
void indexedBinarySearchTree<T>::eraseIndex(int theIndex)//按索引删除 
{
	theIndex--;//索引=题目所给名次-1 
	binaryTreeNode<T> *t=root;
	
	while(t!=NULL)
	{
		if(t->leftSize>theIndex)//元素在左子树 
		{
			t=t->leftChild;
		}
		else if(t->leftSize<theIndex)//元素在右子树 
		{
			theIndex=theIndex-(t->leftSize+1);//改变索引 
			t=t->rightChild;
		}
		else//找到 
		{
			erase(t->element);//按元素值删除 
			return;
		}
	}
	cout<<0<<endl;//未找到 
}

int main()
{
	int m;//操作数个数 
	indexedBinarySearchTree<int> tree;
	
	cin>>m;
	for(int i=0;i<m;i++)
	{
		int a,b;
		
		cin>>a>>b;
		switch(a)
		{
			case 0://插入 
				tree.insert(b);
				break;
			case 1://查找 
				tree.find(b);
				break;
			case 2://删除 
				tree.erase(b);
				break;
			case 3://按索引查找 
				tree.findIndex(b);
				break;
			case 4://按索引删除 
				tree.eraseIndex(b);
				break;
		}
	}
	return 0;
}
