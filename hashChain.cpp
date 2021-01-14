#include<iostream>
using namespace std;

template<class T>
struct node//链表节点 
{
	T element;//值 
	node *next;//指针 
	
	//构造函数 
	node(){}
	node(const T& theElement,node<T> *theNext)
	{
		element=theElement;
		next=theNext;
	}
};

template<class T>
class sortedChain//有序链表 
{
public:
	sortedChain();
	~sortedChain(){}
	
	void find(const T& x)const;//查找 
	void insert(const T& x);//插入 
	void erase(const T& x);	//删除 
	int getSize()const{return size;}//获取链表长度 
protected:
	node<T> *firstNode;//头节点 
	int size;//链表长度 
};

template<class T>
sortedChain<T>::sortedChain()//构造函数 
{
	firstNode=NULL;
	size=0;
}

template<class T>
void sortedChain<T>::find(const T& x)const//查找 
{
	node<T> *currentNode=firstNode;
	
	while(currentNode!=NULL&&currentNode->element!=x)
		currentNode=currentNode->next;
	
	if(currentNode!=NULL)//找到了 
		cout<<size<<endl;
	
	else//未找到 
		cout<<"Not Found"<<endl;
} 

template<class T>
void sortedChain<T>::insert(const T& x)//插入 
{
	node<T> *p=firstNode,*tp=NULL;//tp用于记录p的位置 
	
	while(p!=NULL&&p->element<x)
	{
		tp=p;
		p=p->next;
	}
	
	if(p!=NULL&&p->element==x)//元素已存在 
	{
		cout<<"Existed"<<endl;
		return;
	}
	
	//元素不存在 
	node<T> *newNode=new node<T>(x,p);
	
	if(tp==NULL)//插入头节点 
		firstNode=newNode;
	
	else//插入其他节点 
		tp->next=newNode;
	
	size++;
}

template<class T>
void sortedChain<T>::erase(const T& x)//删除 
{
	node<T> *p=firstNode,*tp=NULL;//tp用于记录p的位置 
	
	while(p!=NULL&&p->element<x)
	{
		tp=p;
		p=p->next;
	}
	
	if(p!=NULL&&p->element==x)//元素存在 
	{
		if(tp==NULL)//删除头节点 
			firstNode=p->next;
		
		else//删除其他节点 
			tp->next=p->next;
		
		delete p;
		size--;
		cout<<size<<endl;
	}
	
	else//元素不存在 
		cout<<"Delete Failed"<<endl;
}

template<class T>
class hashChains//链表散列 
{
public:
	hashChains(int theDivisor=11);
	~hashChains(){delete[]table;}
	
	void find(const T& x)const{table[x%divisor].find(x);}//查找 
	void insert(const T& x){table[x%divisor].insert(x);}//插入 
	void erase(const T& x){table[x%divisor].erase(x);}//删除 
protected:
	sortedChain<T> *table;//散列表 
	int divisor;//除数 
};

template<class T>
hashChains<T>::hashChains(int theDivisor)//构造函数 
{
	divisor=theDivisor;
	table=new sortedChain<T>[divisor];
}

int main()
{
	int D,m;
	
	cin>>D>>m;
	hashChains<int> h(D);
	
	for(int i=0;i<m;i++)
	{
		int opt,x;
		
		cin>>opt>>x;
		switch(opt)
		{
			case 0:
				h.insert(x);
				break;
			case 1:
				h.find(x);
				break;
			case 2:
				h.erase(x);
				break;
		}
	}
	return 0;
}
