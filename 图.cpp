#include<queue>
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

class linkedGraph;

template<class T>
class graphChain//图链表 
{
public:
	graphChain(int initialCapacity=10);
	~graphChain();
	
	void insert(const T& theElement);//插入 
	void erase(int theIndex);//按索引删除 
	int indexOf(const T& theElement);//获取索引 
	int size()const{return listSize;}//获取链表长度 
	void eraseElement(int theVertex);//按元素值删除 
	
	friend linkedGraph;
protected:
	chainNode<T> *firstNode;//头结点 
	int listSize;//链表长度 
};

template<class T>
graphChain<T>::graphChain(int initialCapacity)//构造函数 
{
	firstNode=NULL;
	listSize=0;
}

template<class T>
graphChain<T>::~graphChain()//删除链表中的所有结点 
{
	while(firstNode!=NULL)
	{
		chainNode<T> *nextNode=firstNode->next;
		delete firstNode;
		firstNode=nextNode;
	}
}

template<class T>
void graphChain<T>::insert(const T& theElement)//插入 
{
	chainNode<T> *p=firstNode,*pp=NULL;
	
	//按升序插入 
	while(p!=NULL&&theElement>p->element)
	{
		pp=p;
		p=p->next;
	}
	
	if(pp!=NULL)
		pp->next=new chainNode<T>(theElement,pp->next);
	
	else//插入头节点 
		firstNode=new chainNode<T>(theElement,firstNode);
	
	listSize++;
}

template<class T>
void graphChain<T>::erase(int theIndex)//按索引删除 
{
	chainNode<T> *deleteNode;
	
	if(theIndex==0)//删除头结点 
	{
		deleteNode=firstNode;
		firstNode=firstNode->next;
	}
	else//删除其他位置的结点 
	{
		chainNode<T> *p=firstNode;
		for(int i=0;i<theIndex-1;i++)
			p=p->next;
		
		deleteNode=p->next;
		p->next=p->next->next;
	}
	delete deleteNode;
	listSize--;
}

template<class T>
int graphChain<T>::indexOf(const T& theElement)//获取索引 
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
void graphChain<T>::eraseElement(int theVertex)//按元素值删除 
{
	int index=indexOf(theVertex);
	erase(index);
}

template<class T>
class arrayQueue//循环队列类 
{
public:
	arrayQueue(int initialCapacity=10);
	~arrayQueue(){delete[]queue;}
	
	bool empty()const{return queueFront==queueBack;}//判断队列是否为空 
	void push(const T& theElement);//插入到队尾 
	void pop();//删除队首元素 
	int size()const{return (arrayLength+queueBack-queueFront)%arrayLength;}//获取队列长度 
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
			int j=0;//newQueue中的元素从0开始存放 
			
			for(int i=start;i<=queueBack;i++)
			{
				newQueue[j]=queue[i];
				j++;
			}
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

class edge//边 
{
public:
	edge(int i,int j);
	
	int vertex1()const{return v1;}//获取顶点1 
	int vertex2()const{return v2;}//获取顶点2 
private:
	int v1;//顶点1 
	int v2;//顶点2 
};

edge::edge(int i,int j)//构造函数 
{
	v1=i;
	v2=j;
}

class linkedGraph//无向非加权图 
{
protected:
	int n;//顶点数 
	int e;//边数 
	graphChain<int> *aList;//邻接链表 
public:
	linkedGraph(int numberOfVertices=0);
	~linkedGraph();
	
	void insertEdge(edge *theEdge);//插入边 
	void eraseEdge(int i,int j);//删除边 
	int numberOfVertices()const{return n;}//获取顶点个数 
	
	void bfs(int v,int reach[],int label);//bfs
	void dfs(int v,int reach[],int label);//dfs
	void rDfs(int v);//dfs的递归方法 
	
	void findPath(int theSource,int theDestination);//寻找最短路径 
	int labelComponents();//构件标记 
	void outputComponents();//升序输出所有连通子图中最小点的编号
	void outputBfs(int v);//输出bfs序列长度和字典序最小的序列 
	void outputDfs(int v);//输出dfs序列长度和字典序最小的序列 
	
	class myIterator//迭代器 
	{
	public:
		myIterator(chainNode<int> *theNode)//构造函数 
		{
			node=theNode;
		}	
		
		int next()//返回下一个顶点 
		{
			if(node!=NULL)
			{
				int theElement=node->element;
				node=node->next;
				
				return theElement;
			}
			
			else//不存在 
				return 0;
		}
	protected:
		chainNode<int> *node;
	};
	myIterator* iterator(int theVertex){return new myIterator(aList[theVertex].firstNode);}
private:
	int *reach;//标记顶点是否被访问 
	int label;//构件个数 
	int length;//序列长度 
	int *c;//标记构件 
	int *bfsArray;//bfs序列 
	int *dfsArray;//dfs序列 
};

linkedGraph::linkedGraph(int numberOfVertices)//构造函数 
{
	n=numberOfVertices;
	e=0;
	
	aList=new graphChain<int>[n+1];
	c=new int[n+1];
	bfsArray=new int[n+1];
	dfsArray=new int[n+1];
	reach=new int[n+1];
}

linkedGraph::~linkedGraph()//析构函数 
{
	delete[]aList;
	delete[]c;
	delete[]bfsArray;
	delete[]dfsArray;
	delete[]reach;
}

void linkedGraph::insertEdge(edge *theEdge)//插入边 
{
	int v1=theEdge->vertex1();
	int v2=theEdge->vertex2();
	
	if(aList[v1].indexOf(v2)==-1)
	{
		aList[v1].insert(v2);
		aList[v2].insert(v1);
		e++;
	}
}

void linkedGraph::eraseEdge(int i,int j)//删除边 
{
	if(i>=1&&j>=1&&i<=n&&j<=n)
	{
		aList[i].eraseElement(j);
		aList[j].eraseElement(i);
		e--;
	}
}

void linkedGraph::bfs(int v,int reach[],int label)//bfs
{
	arrayQueue<int> q;
	
	reach[v]=label;//到达顶点v 
	length=1;//初始序列长度 
	bfsArray[1]=v; 
	q.push(v);
	
	while(!q.empty())
	{
		int w=q.front();
		q.pop();
		
		for(chainNode<int>* u=aList[w].firstNode;u!=NULL;u=u->next)
			if(reach[u->element]==0)//顶点u未被访问 
			{
				q.push(u->element);
				reach[u->element]=label;
				length++;
				bfsArray[length]=u->element;
			}
	}
}

void linkedGraph::dfs(int v,int reach[],int label)//dfs
{
	this->reach=reach;
	this->label=label;
	length=0;
	rDfs(v);
}

void linkedGraph::rDfs(int v)//dfs的递归实现 
{
	reach[v]=label;
	length++;
	dfsArray[length]=v;
	myIterator *iv=iterator(v);
	int u;
	
	while((u=iv->next())!=0)
		if(reach[u]==0)
			rDfs(u);      
	
	delete iv;
}

void linkedGraph::findPath(int theSource,int theDestination)//寻找最短路径 
{
	arrayQueue<int> q;
	int *size=new int[n+1];//bfs层次大小 
	int index=2,count=0;
	bool find=false;//标记是否找到 
	
	for(int i=1;i<=n;i++)
		reach[i]=0;
	
	reach[theSource]=label;
	q.push(theSource);
	size[1]=1;//第一层只有theSource一个顶点 
	
	for(int i=2;i<=n;i++)
		size[i]=0;
	
	while(!q.empty())
	{
		int w=q.front();
		q.pop();
		count++;//记录每一层已访问的顶点个数 
		
		if(w==theDestination)//找到终点 
		{
			cout<<index-2<<endl;
			find=true;
			break;
		}
		
		for(chainNode<int>* u=aList[w].firstNode;u!=NULL;u=u->next)
			if(reach[u->element]==0)
			{
				q.push(u->element);
				reach[u->element]=label;
				size[index]++;//计算每一层的全部顶点个数 
			}
		
		if(count==size[index-1])//进入下一层 
		{
			count=0;
			index++;
		}
	}
	
	if(!find)//路径不存在 
		cout<<-1<<endl;
}

int linkedGraph::labelComponents()//标记构件 
{
	int n=numberOfVertices();
	
	for(int i=1;i<=n;i++)
		c[i]=0;
	
	label=0;
	
	for(int i=1;i<=n;i++)
		if(c[i]==0)
		{
			label++;
			bfs(i,c,label);
		}
	
	return label;
}

void linkedGraph::outputComponents()//升序输出所有连通子图中最小点的编号
{
	int count=1;
	
	for(int i=1;i<=n;i++)
		if(c[i]==count)
		{
			cout<<i<<" ";
			if(count==label) 
			{
				cout<<endl;
				break;
			}
			count++;
		}
}

void linkedGraph::outputBfs(int v)//输出bfs序列长度和字典序最小的序列 
{
	for(int i=1;i<=n;i++)
		reach[i]=0;
	
	bfs(v,reach,1);
	cout<<length<<endl;//输出bfs序列长度 
	
	for(int i=1;i<=length;i++)
		cout<<bfsArray[i]<<" ";//输出bfs序列 
	
	cout<<endl;
}

void linkedGraph::outputDfs(int v)//输出dfs序列长度和字典序最小的序列 
{
	for(int i=0;i<=n;i++)
		reach[i]=0;
	
	dfs(v,reach,1);
	cout<<length<<endl;
	
	for(int i=1;i<=length;i++)
		cout<<dfsArray[i]<<" ";
	
	cout<<endl;
}

int main()
{
	int n,m,s,t;//顶点个数，操作个数，起点，终点 
	
	cin>>n>>m>>s>>t;
	linkedGraph graph(n);
	
	for(int i=0;i<m;i++)
	{
		int opt,u,v;
		
		cin>>opt>>u>>v;
		edge *theEdge=new edge(u,v);
		
		if(opt==0)//插入边 
		{
			graph.insertEdge(theEdge);
		}
		else//删除边 
		{
			graph.eraseEdge(u,v);
		}
		delete theEdge;
	}
	
	cout<<graph.labelComponents()<<endl;
	graph.outputComponents();
	graph.outputDfs(s);
	graph.outputBfs(t);
	graph.findPath(s,t);
	return 0;
}
