#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

ofstream outfile;
ifstream infile;
int n=1000000;

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

void printRandoms(int lower, int upper,int count) 
{
    int i;
    for (i = 0; i < count; i++) 
    {
        int num = (rand()%(upper - lower + 1)) + lower;
        outfile << num << " ";
    }
}

int minimum(int arr[],int i,int l,int r)
{
    int smallest=i;

    if(l<=n && arr[l]<arr[i])
        smallest=l;
    if(r<=n && arr[r]<arr[smallest])
        smallest=r;

    return smallest;
}

void heapify_min(int arr[],int i)
{
    int l=left(i);
    int r=right(i);
    int index=minimum(arr,i,l,r);

    if(index!=i)
    {
        swap(&arr[i],&arr[index]);
        heapify_min(arr,index);
    }
}

int heap_extract_min(int arr[])
{
    int min=arr[1];
    arr[1]=arr[n--];
    heapify_min(arr,1);
    return min;
}

void build_min_heap(int arr[])
{
    for(int i=n/2;i>0;i--)
        heapify_min(arr,i);
}
 
int main()
{
    /*
    int lower = 1000000, upper = 4000000, count = 1000000;
    srand(time(0));

    outfile.open("input.txt");
    printRandoms(lower,upper,count);
	outfile.close();
    */

    clock_t begin=clock();

	cout<<"Enter the integer k"<<endl;
	int k;
	cin>>k;

    infile.open("input.txt");
    int arr[1000001];
    for(int i=1;i<=n;i++)
        infile >> arr[i];
    infile.close();

    build_min_heap(arr);

    for(int i=0;i<k;i++)
    {
        int x;
        x=heap_extract_min(arr);
        cout<<x<<" ";
    }

    clock_t end=clock();

    double tym=(double)(end-begin)/CLOCKS_PER_SEC;

    cout<<tym;
 
    return 0;
}