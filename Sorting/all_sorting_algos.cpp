/+// 5 4 3 3 9 12 4 6 10 --> the testcase
#include <bits/stdc++.h>
using namespace std;

int size;

ofstream outfile;
ifstream infile;

void swap(int* a,int* b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

void print(int arr[])
{
	for(int i=0;i<size;i++)
		cout<<arr[i]<<" ";
}

// stable sort giving partial output
void bubbleSort(int arr[],int left,int right)
{
	for(int i=right;i>left;i--){

		for(int j=left;j<i;j++)
			if(arr[j]>arr[j+1])
				swap(&arr[j],&arr[j+1]);
		
		// print(arr);
		// cout<<endl;

	}
}

//unstable sort giving partial output
void selectionSort_swap(int arr[],int left,int right)
{
	for(int i=left;i<right;i++)
	{
		int minIndex=i;

		for(int j=i+1;j<=right;j++)
			if(arr[j]<arr[minIndex])
				minIndex=j;

		if(minIndex!=i)
			swap(&arr[i],&arr[minIndex]);

		//print(arr);
		//cout<<endl;
	}
}

// stable sort giving partial output
void selectionSort_shift(int arr[],int left,int right)
{
	for(int i=left;i<right;i++)
	{   
		int minIndex=i;

		for(int j=i+1;j<=right;j++)
			if(arr[j]<arr[minIndex])
				minIndex=j;

		while(minIndex>i)
		{
			swap(&arr[minIndex],&arr[minIndex-1]);
			minIndex--;
		}

		// print(arr);
		// cout<<endl;
	}
}

// stable giving partial output
void insertionSort(int arr[],int left,int right)
{
	for(int i=left+1;i<=right;i++)
	{
		int j=i-1;
		int temp=arr[i];

		while(j>=left && arr[j]>temp)
		{
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=temp;

		// print(arr);
		// cout<<endl;
	}
}

void merge(int arr[],int left,int mid,int right)
{
	int buffer[right-left+1];

	int i=left;
	int j=mid+1;
	int k=0;

	for(int temp=left;temp<=right;temp++)
	{
		if(i>mid)
			buffer[k++]=arr[j++];

		else if(j>right)
			buffer[k++]=arr[i++];

		else if(arr[i]<arr[j])
			buffer[k++]=arr[i++];

		else
			buffer[k++]=arr[j++];
	}

	for(int i=0;i<=right-left;i++)
		arr[left+i]=buffer[i];

}

// stable but not giving partial output
void mergeSortTopDown(int arr[],int left,int right)
{
	if(left>=right)
		return ;

	int mid=(left+right)/2;
	mergeSortTopDown(arr,left,mid);
	mergeSortTopDown(arr,mid+1,right);

	merge(arr,left,mid,right);
	// print(arr);
	// cout<<endl;

}

void mergeSortWithInsertion(int arr[],int left,int right)
{

	if(left>=right)
		return ;

	if(right-left<=3)
		return insertionSort(arr,left,right);

	int mid=(left+right)/2;
	mergeSortTopDown(arr,left,mid);
	mergeSortTopDown(arr,mid+1,right);

	merge(arr,left,mid,right);
	// print(arr);
	// cout<<endl;
}

void mergeSortBottomUp(int arr[],int left,int right)
{

	// if input size is odd we need to consider curr_size as n also, but it even, we can manage in curr_size<n-1 also
	for(int curr_size=1;curr_size<=size;curr_size=curr_size*2)
	{
		for(int leftmost=left;leftmost<right;leftmost+=2*curr_size)
		{
			int mid=leftmost+curr_size-1;
			int right_end=min(leftmost+2*curr_size-1,size-1);

			merge(arr,leftmost,mid,right_end);
		}
	}
}

int partition_taking_rightMost(int arr[],int left,int right)
{
	int pivot=arr[right];
	int i=left-1;

	for(int j=left;j<right;j++)
	{
		if(arr[j]<=pivot){
			i++;
			swap(&arr[i],&arr[j]);
		}
	}
	
	swap(&arr[i+1],&arr[right]);
	return i+1;
}

int partition_taking_leftMost(int arr[],int left,int right)
{
	int pivot=arr[left];
	int i=left+1;

	for(int j=left+1;j<=right;j++)
	{
		if(arr[j]<pivot)
		{
			swap(&arr[i],&arr[j]);
			i++;
		}
	}
	swap(&arr[i-1],&arr[left]);
	return i-1;
}

int partition_taking_random(int arr[],int left,int right)
{
	// randomisation part
	int randNum = rand()%(right-left) + left;
	swap(&arr[right],&arr[randNum]);
	
	return partition_taking_rightMost(arr,left,right);

}

// unstable version of quicksort
void quickSortUnstable(int arr[],int left,int right)
{

	if(right-left<1)
		return ;

	int pivot=partition_taking_random(arr,left,right);

	if((pivot-1)-left>1)
		quickSortUnstable(arr,left,pivot-1);

	if(right-(pivot+1)>1)
		quickSortUnstable(arr,pivot+1,right);
	
	return ;

}

void quicksortWithInsertion(int arr[],int left,int right)
{

	if(right-left<1)
		return ;

	if(right-left<=3)
		return insertionSort(arr,0,size-1);

	int pivot=partition_taking_random(arr,left,right);

	if((pivot-1)-left>1)
		quickSortUnstable(arr,left,pivot-1);

	if(right-(pivot+1)>1)
		quickSortUnstable(arr,pivot+1,right);
	
	return ;
}

int stablePartition(int arr[],int left,int right)
{
	int pivot=arr[right];
	int lptr=left-1;

	// used shifting instead of swapping
	for(int i=left;i<right;i++)
	{
		if(arr[i]<=pivot)
		{
			lptr++;
			int temp=arr[i];
			for(int k=i;k>lptr;k--)
			{
				arr[k]=arr[k-1];
			}	
			arr[lptr]=temp;
		}
	}
	int temp=arr[right];

	for(int k=right;k>lptr+1;k--)
		arr[k]=arr[k-1];

	arr[lptr+1]=temp;
	return lptr+1;

}

void quicksortStable(int arr[],int left,int right)
{
	if(right-left<1)
		return ;

	int pivot=stablePartition(arr,left,right);
	quicksortStable(arr,left,pivot-1);
	quicksortStable(arr,pivot+1,right);
}

int triPartition(int arr[],int left,int right,int* leftPiv,int* rightPiv)
{
	int lptr,rptr;
	lptr=left+1;
	rptr=right-1;
	for(int i=left+1;i<=rptr;i++)
	{
		if(arr[i]<arr[left])
		{		
			//lptr++;
			swap(&arr[i],&arr[lptr]);
			lptr++;
			//swap(&data[lptr],&data[i]);
		}
		else if(arr[i]>=arr[right])
		{
			while(arr[rptr]>arr[right]&&i<rptr)
			rptr--;
			swap(&arr[i],&arr[rptr]);
			rptr--;
			if(arr[i]<arr[left])
			{
				//lptr++;
				swap(&arr[i],&arr[lptr]);
				lptr++;
			}
		}
	}
	swap(&arr[lptr-1],&arr[left]);
	swap(&arr[rptr+1],&arr[right]);
	*leftPiv=lptr-1;
	*rightPiv=rptr+1;
}

void quickSortwithLogn(int arr[], int low, int high) 
{ 
    while (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition_taking_random(arr, low, high); 
  
        // If left part is smaller, then recur for left 
        // part and handle right part iteratively 
        if (pi - low < high - pi) 
        { 
            quickSortwithLogn(arr, low, pi - 1); 
            low = pi + 1; 
        } 
  
        // Else recur for right part 
        else
        { 
            quickSortwithLogn(arr, pi + 1, high); 
            high = pi - 1; 
        } 
    } 
} 

void quicksort_2pivots(int arr[],int left,int right)
{
	if(right-left<1)
		return ;

	int leftPiv,rightPiv;

	if(arr[left]>arr[right])
		swap(&arr[left],&arr[right]);

	triPartition(arr,left,right,&leftPiv,&rightPiv);

	if(rightPiv<leftPiv)
		swap(&leftPiv,&rightPiv);

	quicksort_2pivots(arr,left,leftPiv-1);
	quicksort_2pivots(arr,leftPiv+1,rightPiv-1);
	quicksort_2pivots(arr,rightPiv+1,right);

}

void quickSort_stack(int arr[],int left,int right)
{
	stack<int> s;
	s.push(left);
	s.push(right);
	while(!s.empty())
	{
		int r=s.top();
		s.pop();
		int l=s.top();
		s.pop();
		int pivot=partition_taking_random(arr,l,r);
		if(pivot-1>l)
		{
			s.push(l);
			s.push(pivot-1);
		}
		if(pivot+1<r)
		{
			s.push(pivot+1);
			s.push(r);
		}
	}
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

int main()
{

	 //int lower = 1000000, upper = 4000000, count = 100000;
	 // this is for making input.txt, which I have already made, again making will cause overlapping
    //srand(time(0));

    /*
    outfile.open("input.txt");
    printRandoms(lower,upper,count);
	outfile.close();
    */

	clock_t begin=clock();

	cout<<"Enter array size"<<endl;
	cin>>size;
	cout<<"Enter array elements: "<<endl;
	int arr[size];

	for(int i=0;i<size;i++)
		cin>>arr[i];

	//bubbleSort(arr,0,size-1);
	//selectionSort_swap(arr,0,size-1);
	//selectionSort_shift(arr,0,size-1);
	//insertionSort(arr,0,size-1);
	//mergeSortTopDown(arr,0,size-1);
	//mergeSortBottomUp(arr,0,size-1);
	//quickSortUnstable(arr,0,size-1);
	//mergeSortWithInsertion(arr,0,size-1);
	//quicksortWithInsertion(arr,0,size-1);
	//quicksortStable(arr,0,size-1);
	//quickSortwithLogn(arr,0,size-1);
	//quicksort_2pivots(arr,0,size-1);
	//quickSort_stack(arr,0,size-1);

	cout<<"The sorted order is: "<<endl;

	print(arr);
	cout<<endl;
	clock_t end=clock();

    double tym=(double)(end-begin)/CLOCKS_PER_SEC;

    cout<<"The time taken is "<<tym<<"s"<<endl;

}