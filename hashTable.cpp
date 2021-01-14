#include<iostream>
using namespace std;

template<class T>
class hashTable//散列表 
{
public:
	hashTable(int theDivisor=11);
	~hashTable(){delete[]table;}
	
	void find(const T&)const;//查找 
	void insert(const T&);//插入 
	void erase(const T&);//删除 
protected:
	int search(const T&)const;//返回元素在桶中的位置 
	T *table;//散列表 
	int divisor;//除数 
};

template<class T>
hashTable<T>::hashTable(int theDivisor)//构造函数 
{
	divisor=theDivisor;
	table=new T[divisor];
	
	for(int i=0;i<divisor;i++)//初始化散列表，将桶全部置空 
		table[i]=-1;
}

template<class T>
int hashTable<T>::search(const T& x)const//返回元素在桶中的位置 
{
	int i=x%divisor;//元素应该在的位置 
	int j=i;
	
	do
	{
		if(table[j]==-1||table[j]==x)//该位置为空或该元素已存在
			return j;
			 
		j=(j+1)%divisor;
	}while(j!=i);
	
	return j;//散列表已满 
}

template<class T>
void hashTable<T>::insert(const T& x)//插入 
{
	int i=search(x);
	
	if(table[i]==-1||table[i]!=x)//该位置为空或散列表已满 
	{
		table[i]=x;
		cout<<i<<endl;
	}
	else //元素已存在 
		cout<<"Existed"<<endl;
}

template<class T>
void hashTable<T>::find(const T& x)const//查找 
{
	int i=search(x);
	
	if(table[i]==-1||table[i]!=x)//元素不存在 
		cout<<-1<<endl;
	
	else
		cout<<i<<endl;
}

template<class T>
void hashTable<T>::erase(const T& x)//删除 
{
	int i=search(x);
	
	if(table[i]==-1||table[i]!=x)//元素不存在 
		cout<<"Not Found"<<endl;
	
	else
	{
		int j=(i+1)%divisor;
		int move=i;
		int count=0;//计算元素移动次数 
		table[i]=-1;//删除元素 
		
		while(j!=i&&table[j]!=-1)//遇到删除元素或遇到空桶时停止循环 
		{
			if(move<j)//未成环 
			{
				if(table[j]%divisor<=move||table[j]%divisor>j)
				{
					table[move]=table[j];//移动元素 
					table[j]=-1;
					move=j;
					count++;
				}
			}
			else//形成环 
			{
				if(table[j]%divisor<=move&&table[j]%divisor>j)
				{
					table[move]=table[j];
					table[j]=-1;
					move=j;
					count++;
				}
			}
			j=(j+1)%divisor;
		}
		cout<<count<<endl;
	}
}

int main()
{
	int D,m;//除数，操作个数 
	
	cin>>D>>m;
	hashTable<int> h(D);
	
	for(int i=0;i<m;i++)
	{
		int opt,x;//操作类型，操作数 
		
		cin>>opt>>x;
		switch(opt)
		{
			case 0://插入 
				h.insert(x);
				break;
			case 1://查找 
				h.find(x);
				break;
			case 2://删除 
				h.erase(x);
				break;
			default:
				break;
		}
	}
	return 0;
}
