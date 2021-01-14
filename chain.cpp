#include<iostream>
using namespace std;

template<class T>
struct chainNode//链表结点 
{
	T element;//元素值 
	chainNode *next;//指向下一个结点 
	
	chainNode(const T& element,chainNode<T> *next)//构造函数 
	{
		this->element=element;
		this->next=next;
	}
};

template<class T>
class chain
{
public:
	chain(int initialCapacity=10);
	~chain();
	
	void insert(int theIndex,const T& theElement);	
	void erase(const T& theElement);
	void reverse();//原地逆置链表
	int indexOf(const T& theElement);
	int output();//输出索引与元素的异或和
	
	class iterator;//链表迭代器 
	iterator begin(){return iterator(firstNode);}
	iterator end(){return iterator(NULL);} 
protected:
	chainNode<T> *firstNode;//头结点 
	int listSize;//链表长度 
};

template<class T>
class chain<T>::iterator
{
public:
	typedef bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;
	
	iterator(chainNode<T> *theNode=NULL){node=theNode;}
	
	T& operator*()const{return node->element;}
	T* operator->()const{return &node->element;}
	
	iterator& operator++()
		{node=node->next;return *this;}
	iterator operator++(int)
		{iterator old=*this;
		node=node->next;
		return old;}
	
	bool operator!=(const iterator right)const
		{return node!=right.node;}
	bool operator==(const iterator right)const
		{return node==right.node;}
protected:
	chainNode<T> *node;
};

template<class T>
chain<T>::chain(int initialCapacity)
{
	firstNode=NULL;
	listSize=0;
}

template<class T>
chain<T>::~chain()//删除链表中的所有结点 
{
	while(firstNode!=NULL)
	{
		chainNode<T> *nextNode=firstNode->next;
		delete firstNode;
		firstNode=nextNode;
	}
}

template<class T>
void chain<T>::insert(int theIndex,const T& theElement) 
{
	if(theIndex==0)//插入头结点 
		firstNode=new chainNode<T>(theElement,firstNode);
	else//插入其他位置的结点 
	{
		chainNode<T> *p=firstNode;
		
		for(int i=0;i<theIndex-1;i++)
			p=p->next;
		p->next=new chainNode<T>(theElement,p->next);
	}
	listSize++;
}

template<class T>
void chain<T>::erase(const T& theElement)
{
	chainNode<T> *deleteNode;
	int theIndex=indexOf(theElement);
	
	if(theIndex==-1)
	{
		cout<<-1<<endl;
		return ;
	}
	else if(theIndex==0)//删除头结点 
	{
		deleteNode=firstNode;
		firstNode=firstNode->next;
	}
	else//删除其他位置的结点 
	{
		chainNode<T> *p=firstNode->next;
		for(int i=0;i<theIndex-1;i++)
			p=p->next;
		
		deleteNode=p->next;
		p->next=p->next->next;
	}
	listSize--;
	delete deleteNode;
}

template<class T>
void chain<T>::reverse()
{
	chainNode<T> *p=firstNode;
	chainNode<T> *q=p->next;
	chainNode<T> *r=q->next;
	
	while(r!=NULL)
	{
		q->next=p;//让当前结点指向其前一个结点 
		//三个结点向后移动一个 
		p=q;
		q=r;
		r=r->next;
	}
	q->next=p;
	p=q;
	firstNode->next=NULL;//头结点变成尾结点 
	firstNode=p; 
}

template<class T>
int chain<T>::indexOf(const T& theElement)
{
	int index=0;
	chainNode<T> *p=firstNode;
	
	while(p!=NULL&&p->element!=theElement)
	{
		p=p->next;
		index++;
	}
	if(p==NULL)//若未找到则返回-1 
		return -1;
	else
		return index;
}

template<class T>
int chain<T>::output()
{
	int sum=0,index=0;//sum:异或值之和，index:索引 
	
	for(iterator p=begin();p!=end();p++)
	{
		sum+=index^*p;
		index++;
	}
	return sum;
}

int main()
{
	int N,Q,theElement;
	chain<int> c;
	
	cin>>N>>Q;
	for(int i=0;i<N;i++)
	{
		cin>>theElement;
		c.insert(i,theElement);
	}
	for(int i=0;i<Q;i++)
	{
		int m;
		
		cin>>m;
		switch(m)
		{
			case 1:
				{
					int theIndex,theElement;
				
					cin>>theIndex>>theElement;
					c.insert(theIndex,theElement);
					break;
				}
			case 2:
				{
					int theElement;
				
					cin>>theElement;
					c.erase(theElement);
					break;
				}
			case 3:
				c.reverse();
				break;
			case 4:
				{
					int theElement;
					
					cin>>theElement;
					cout<<c.indexOf(theElement)<<endl;
					break;
				}
			case 5:
				cout<<c.output()<<endl;
				break;
		}
	}
	return 0;
}
