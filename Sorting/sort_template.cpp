#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;

#define arr_size 9

template <class T> void swap(T* a,T* b)
{
	T temp=*a;
	*a=*b;
	*b=temp;
}

template <class T> void printArr(T arr[])
{
	for(int i=0;i<arr_size;i++)
		cout<<arr[i]<<" ";
}

template <class T> void bubbleSort(T arr[],int left,int right)
{
	for(int i=right;i>left;i--)
	{
		for(int j=left;j<=right;j++)
			if(arr[j]>arr[j+1])
				swap(arr[j],arr[j+1]);

		// printArr(arr);
		// cout<<endl;
	}
}

template <class T> void selectionSort(T arr[],int left,int right)
{
	for(int i=left;i<right;i++)
	{
		int minIndex=i;

		for(int j=i+1;j<=right;j++)
			if(arr[j]<arr[minIndex])
				minIndex=j;

		if(i!=minIndex)
			swap(arr[i],arr[minIndex]);

		// printArr(arr);
		// cout<<endl;
	}
}

template <class T> void insertionSort(T arr[],int left,int right)
{
	for(int i=left+1;i<=right;i++)
	{
		T key=arr[i];
		int j=i-1;
		while(j>=0 && arr[j]>key)
		{
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=key;
	}
}

template <class T> void merge(T arr[],int left,int right)
{
	int index1=left;
	int index2=((left+right)/2)+1;
	int tempIndex;

	T temp[right-left+1];

	for(tempIndex=0;tempIndex<=right-left;tempIndex++)
	{
		if(index1<=(left+right)/2)
		{
			if(index2<=right)
			{
				if(arr[index1]>=arr[index2])
				{
					temp[tempIndex]=arr[index2];
					index2++;
				}
				else
				{
					temp[tempIndex]=arr[index1];
					index1++;
				}
			}
			else
			{
				temp[tempIndex]=arr[index1];
				index1++;
			}
		}
		else
		{
			temp[tempIndex]=arr[index2];
			index2++;
		}
	}

	for(int i=0;i<=right-left;i++)
	{
		arr[left+i]=temp[i];
	}

	//printArr(arr);
}

template <class T> void mergeSortTopDown(T arr[],int left,int right)
{
	if(right-left<1)
		return ;

	mergeSortTopDown(arr,left,(left+right)/2);
	mergeSortTopDown(arr,(((left+right)/2)+1),right);

	merge(arr,left,right);
}

template <class T> T partition ( int A[],int start ,int end) 
{
    int i = start + 1;
    int piv = A[start] ;            //make the first element as pivot element.
    for(int j =start + 1; j <= end ; j++ )  {
    /*rearrange the array by putting elements which are less than pivot
       on one side and which are greater that on other. */

          if ( A[ j ] < piv) {
                 swap (A[ i ],A [ j ]);
            i += 1;
        }
   }
   swap ( A[ start ] ,A[ i-1 ] ) ;  //put the pivot element in its proper place.
   return i-1;                      //return the position of the pivot
}

// void quickSort(T arr[],T left,T right)
// {
// 	T pivot=arr[left];


// }

int main()
{
	double arr[arr_size];
	for(int i=0;i<arr_size;i++)
		cin>>arr[i];

	bubbleSort(arr,0,arr_size-1);
	//selectionSort(arr,0,arr_size-1);
	//insertionSort(arr,0,arr_size-1);
	//mergeSortTopDown(arr,0,arr_size-1);
	printArr(arr);

}