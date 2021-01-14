#include<iostream>
using namespace std;

template<class T>
class mySort
{
public:
	mySort(T a[],int n);
	~mySort(){delete []p;}
	void rank();//名次排序
	void selectionSort();//及时终止的选择排序
	void bubbleSort();//及时终止的冒泡排序
	void insertSort();//插入排序 
	void output();//输出排好序的数组 
private:
	T *p;//指向排序数组  
	int n;//数组长度		
};

template<class T>
mySort<T>::mySort(T a[],int n):n(n)//构造函数 
{
	p=new T [n];
	
	for(int i=0;i<n;i++)
	{
		p[i]=a[i];
	} 
}

template<class T>
void mySort<T>::rank()//名次排序
{
	T *r=new T[n];//创建计算名次的数组 
	
	//初始化r
	for(int i=0;i<n;i++)
		r[i]=0;
		
	//计算名次 
	for(int i=1;i<n;i++)
		for(int j=0;j<i;j++)
		{
			if(p[i]>=p[j])//p[i]与其左边的元素比较 
				r[i]++;
			else
				r[j]++;
		}
			
	T *u=new T[n];//创建附加数组
		 
	//按名次排序 
	for(int i=0;i<n;i++)
		u[r[i]]=p[i];
	for(int i=0;i<n;i++)
		p[i]=u[i];
		
	delete []r;
}

template<class T>
void mySort<T>::selectionSort()//及时终止的选择排序
{
	bool sorted=false;//初始时未排好序 
	
	for(int i=n;(i>1)&&(!sorted);i--)//若数组已经排好序则循环停止 
	{
		int indexOfMax=0;
		sorted=true;//假设已经排好序 
		
		for(int j=1;j<i;j++)
		{
			if(p[indexOfMax]<p[j])//若每一个元素均小于其后一个，则数组有序 
				indexOfMax=j;
			else
				sorted=false;
		}
		swap(p[indexOfMax],p[i-1]); 
	}	
}

template<class T>
void mySort<T>::bubbleSort()//及时终止的冒泡排序
{
	bool swapped=true;
	
	for(int i=0;(i<n-1)&&(swapped);i++)
	{
		swapped=false;//初始时没有进行交换 
		
		for(int j=0;j<n-i-1;j++)
			if(p[j]>p[j+1])
			{
				swap(p[j],p[j+1]);
				swapped=true;
			}	
	}		
}

template<class T>
void mySort<T>::insertSort()//插入排序
{
	for(int i=1;i<n;i++)
	{
		T t=p[i];
		int j;
		
		for(j=i-1;j>=0&&t<p[j];j--)//从后往前找，当元素比t小时停止 
			p[j+1]=p[j];
		p[j+1]=t;		
	}	
}

template<class T>
void mySort<T>::output()//输出排好序的数组
{
	for(int i=0;i<n;i++)
		cout<<p[i]<<" ";
	cout<<endl;
}

int main()
{
	int n;
	cin>>n;
	
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
		
	mySort<int> s(a,n);
	s.bubbleSort();
	s.output();
	return 0;
}
