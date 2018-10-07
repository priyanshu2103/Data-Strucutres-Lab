#include <iostream>
#include <algorithm>
#include <stdlib.h>
using namespace std;

bool seq_validity(int a[],int min,int max,int n,int last)
{
	for(int i=0;i<n;i++)
	{
		if(a[i]>max||a[i]<min)
			return false;
		if(a[i]>last)
			max=a[i]-1;
		if(a[i]<last)
			min=a[i]+1;
	}
	return true;
}

int main()
{
	int n;
	cin>>n;
	cout<<endl;

	int a[n],b[n];

	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		b[i]=a[i];
	}

	sort(b,b+n);


	if(seq_validity(a,b[0],b[n-1],n,a[n-1]))
		cout<<"Valid sequence";
	else
		cout<<"Invalid sequence";

}