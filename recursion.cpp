#include<iostream>
using namespace std;

int value=0;//异或和 
int subset(int k,int m,int a[],int b[])//k:初始值为0，用于计数 m:数组元素个数 a:输入的数组 b:存放0/1序列 
{
	int sum=0;//价值 
	
	//递归的结束条件放在前面 
	if(k==m){//得到一组0/1序列 
		int count=0;//标记元素是数组中的第几个 
		for(int i=0;i<m;i++)
			if(b[i]){//b[i]=1时元素在数组中 
				count++;
				sum+=count*a[i];
			}
	}
	//递归计算0/1序列 
	else{
		b[k]=0;
		subset(k+1,m,a,b);
		b[k]=1;
		subset(k+1,m,a,b);
	}
	value^=sum;
	return value;
}

int main()
{
	int n;
	cin>>n;
	
	int a[n],b[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	cout<<subset(0,n,a,b)<<endl;
	return 0;
}
