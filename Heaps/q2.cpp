#include <iostream>
#include <stdlib.h>
#include <string>
#define MAX_SIZE 1000
using namespace std;

int heap_size;
int dup_heap_size;


int parent(int i)
{
	return i/2;
}

int left(int i)
{
	return 2*i;
}

int right(int i)
{
	return (2*i+1);
}

void swap(int* a,int* b)
{
	int t=*a;
	*a=*b;
	*b=t;
	return ;
}

int minimum(int arr[],int i,int l,int r,int n)
{
    int smallest=i;

    if(l<=n && arr[l]<arr[i])
        smallest=l;
    if(r<=n && arr[r]<arr[smallest])
        smallest=r;

    return smallest;
}

void heapify_min(int arr[],int i,int n)
{
    int l=left(i);
    int r=right(i);
    int index=minimum(arr,i,l,r,n);

    if(index!=i)
    {
        swap(&arr[i],&arr[index]);
        heapify_min(arr,index,n);
    }
}

void heap_extract_min(int arr[],int n)
{
    arr[1]=arr[n--];
    heapify_min(arr,1,n);
}

void build_min_heap(int arr[],int n)
{
    for(int i=n/2;i>0;i--)
        heapify_min(arr,i,n);
    return ;
}

int main()
{
	cout<<"Enter number of arguments in input function"<<endl;
	int n;
	cin>>n;

	int arr[n+1];

	int lines_in_output=0;

	string ans1[100];
	int ans2[100];

	for(int i=0;i<100;i++)
		ans1[i]="";

	for(int i=0;i<100;i++)
		ans2[i]=-200;


	for(int i=0;i<n;i++)
	{
		string a;
		int b;
		cin>>a;
		static int j=0;
		static int k=1;
		if(a=="insert")
		{
			cin>>b;
			j++;
			arr[j]=b;
			build_min_heap(arr,j);
			ans1[k]=a;
			ans2[k]=b;
			k++;
			lines_in_output++;
		}
		else if(a=="removeMin")
		{
			heap_extract_min(arr,j);
			j--;
			ans1[k]=a;
			k++;
			lines_in_output++;
		}
		else if(a=="getMin")
		{
			cin>>b;
			//if(b<arr[1])
			//{
				while(j>0)
				{
					heap_extract_min(arr,j);
					j--;	
					lines_in_output++;
					ans1[k]="removeMin";
					k++;
				}
				ans1[k]="insert";
				ans2[k]=b;
				k++;
				lines_in_output++;
			}
			/*else
			{
				while(j>0)
				{
					int a=arr[1];
					if(a!=b)
					{
						heap_extract_min(arr,j);
						j--;
						lines_in_output++;
						ans1[k]="removeMin";
						k++;
					}
					else
					{

					}
				}
			}*/
			ans1[k]="getMin";
			ans2[k]=b;
			k++;
			lines_in_output++;
		}
	}

	int size=0;

	for(int i=1;i<100;i++)
	{
		if(ans1[i]!="") size++;
	}

	cout<<lines_in_output<<endl;

	for(int i=1;i<=size;i++)
	{
		if(ans2[i]==-200)
		{
			cout<<ans1[i]<<endl;
		}
		else
		{
			cout<<ans1[i]<<" "<<ans2[i]<<endl;
		}
	}

}