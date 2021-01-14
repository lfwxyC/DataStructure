#include<iostream>
using namespace std;

template<class T>
class arrayQueue//循环队列类 
{
public:
	arrayQueue(int initialCapacity=10);
	~arrayQueue(){delete[]queue;}
	
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

int main()
{
	int n;
	arrayQueue<int> q;
	
	cin>>n;
	for(int i=0;i<n;i++)
		q.push(i+1);//把1-n插入队列 
		
	while(q.size()>=2)//至少有两张牌时进行操作 
	{
		q.pop();//扔掉第一张牌 
		
		int x=q.front();//获取新的第一张牌的值 
		//把新的第一张牌放到最后 
		q.pop(); 
		q.push(x);
	}
	cout<<q.front()<<endl;//输出最后一张牌 
	q.pop();//清空队列 
	return 0;
}
