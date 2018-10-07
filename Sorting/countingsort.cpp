#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int main()
{
	int max;
	int arr[]={3,5,12,31,11,5,6,3,12,11,9};

	//int size=sizeof(arr)/sizeof(int);
	int size=11;
	max=*max_element(arr,arr+size);

	//cout<<max;

	int aux[max+1]={0};

	for(int i=0;i<size;i++)
		aux[arr[i]]++;

	int j=0;
	int sorted[size];

	for(int i=0;i<=max;i++)
	{
		int k=aux[i];

		while(k--)
		{
			sorted[j]=i;
			j++;
		}

	}

	for(int i=0;i<size;i++)
		cout<<sorted[i]<<" ";


}