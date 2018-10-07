# include <iostream>
# include <cstdlib>
# include <cmath>
# include <stack>

# define N 1000001

using namespace std;

template <class DataType> void swap(DataType *a,DataType *b)
{
	DataType temp=*a;
	*a=*b;
	*b=temp;
}

template <class DataType> void printArray(DataType data[],int left,int right)
{
	cout<<"Array is ";
	for(int i=left;i<=right;i++)
		cout<<data[i]<<" ";
	cout<<endl;
}

template <class DataType> void bubbleSort(DataType data[],int left,int right)
{
	for(int i=right;i>left;i--)
	{
		for(int j=left;j<i;j++)
		{
			if(data[j]>data[j+1])
				swap(&data[j],&data[j+1]);
			//printArray(data,left,right);
		}
	}
}

template <class DataType> void selectionSort(DataType data[],int left,int right)
{
	int minIndex;
	for(int i=left;i<right;i++)
	{
		minIndex=i;
		for(int j=i+1;j<=right;j++)
		{
			if(data[j]<data[minIndex])
			{
				minIndex=j;
			}
		}
		if(minIndex!=i) swap(&data[minIndex],&data[i]);
		printArray(data,left,right);
	}
}

template <class DataType> void stableselectionSort(DataType data[],int left,int right)
{
	int minIndex;
	for(int i=left;i<right;i++)
	{
		minIndex=i;
		for(int j=i+1;j<=right;j++)
		{
			if(data[j]<data[minIndex])
			{
				minIndex=j;
			}
		}
		if(minIndex!=i) 
		{
			//while(minIndex!=i)
			DataType temp=data[minIndex];
			for(int k=minIndex-1;k>=i;k--)
			{
				data[k+1]=data[k];
			}
			data[i]=temp;
		}
		printArray(data,left,right);
	}
}

template <class DataType> void insertionSort(DataType data[],int left,int right)
{
	for(int i=left;i<right;i++)
	{
		int j;
		DataType temp=data[i+1];
		for(j=i;j>=left;j--)
		{
			if(temp<data[j])
			{
				data[j+1]=data[j];
			}
			else 
			{
				break;
			}
		}
		if(j!=i)
		{
			data[j+1]=temp;
		}
	}
}

template <class DataType> void mergeSortTopDown(DataType data[],const int left,const int right)
{
	if(right-left<1) return;
	mergeSortTopDown(data,left,(left+right)/2);
	mergeSortTopDown(data,(left+right)/2+1,right);
	int index1,index2,buffIndex;
	DataType buffer[right-left+1];
	index1=left;
	index2=(left+right)/2+1;
	for(buffIndex=0;buffIndex<right-left+1;buffIndex++)
	{
		if(index1<=(left+right)/2)
		{
			if(index2<=right)
			{
				if(data[index1]<=data[index2])
				{
					buffer[buffIndex]=data[index1];
					index1++;
				}
				else
				{
					buffer[buffIndex]=data[index2];
					index2++;
				}
			}
			else
			{
				buffer[buffIndex]=data[index1];
				index1++;
			}
		}
		else
		{
			buffer[buffIndex]=data[index2];
			index2++;
		}
	}
	for(int i=0;i<right-left+1;i++)
	{
		data[left+i]=buffer[i];
	}
}

template <class DataType> void mergeSortTopDownwithinsertion(DataType data[],const int left,const int right)
{
	if(right-left<1) return;
	if(right-left<=4) 
	{
		insertionSort(data,left,right);
		return;
	}
	mergeSortTopDownwithinsertion(data,left,(left+right)/2);
	mergeSortTopDownwithinsertion(data,(left+right)/2+1,right);
	int index1,index2,buffIndex;
	DataType buffer[right-left+1];
	index1=left;
	index2=(left+right)/2+1;
	for(buffIndex=0;buffIndex<right-left+1;buffIndex++)
	{
		if(index1<=(left+right)/2)
		{
			if(index2<=right)
			{
				if(data[index1]<=data[index2])
				{
					buffer[buffIndex]=data[index1];
					index1++;
				}
				else
				{
					buffer[buffIndex]=data[index2];
					index2++;
				}
			}
			else
			{
				buffer[buffIndex]=data[index1];
				index1++;
			}
		}
		else
		{
			buffer[buffIndex]=data[index2];
			index2++;
		}
	}
	for(int i=0;i<right-left+1;i++)
	{
		data[left+i]=buffer[i];
		cout<<data[left+i]<<"T ";
	}
	cout<<endl;
}

template <class DataType> void iterativemergeSortBottomUp(DataType data[],const int left,const int right)
{
	if(right-left<1) return;
	int size=right-left+1;
	int count=0;
	while(size>0)
	{
		size=size/2;
		count++;
	}
	//cout<<count;
	for(int i=2;i<=pow(2,count);i=i*2)
	{
		for(int j=left;j<=right;j+=i)
		{
			int index1,index2,buffIndex;
			DataType buffer[i];
			int r;
			if(j+i-1<=right)
			{ 
				index1=j;
				r=j+i-1;
				index2=(j+r)/2+1;
			}
			else
			{
				index1=j;
				r=right;
				index2=(j+j+i-1)/2+1;
				if(index2>r) continue;				
			}
			for(buffIndex=0;buffIndex<r-j+1;buffIndex++)
			{
				if(index1<=(j+j+i-1)/2)
				{
					if(index2<=r)
					{
						if(data[index1]<=data[index2])
						{
							buffer[buffIndex]=data[index1];
							index1++;
						}
						else
						{
							buffer[buffIndex]=data[index2];
							index2++;
						}
					}
					else
					{
						buffer[buffIndex]=data[index1];
						index1++;
					}
				}
				else
				{
					buffer[buffIndex]=data[index2];
					index2++;
				}
			}
			for(int k=0;k<r-j+1;k++)
			{
				data[j+k]=buffer[k];
			}
		}
	}
}

template <class DataType> int pivotpos(DataType data[],int left,int right)
{
	int lptr,rptr;
	lptr=left+1;
	rptr=right;
	for(lptr;lptr<=rptr;lptr++)
	{
		if(data[lptr]>data[left])
		{
			while(data[rptr]>data[left])
			{
				rptr--;
			}
			if(rptr<lptr) break;
			swap(&data[lptr],&data[rptr]);
			//printArray(data,left,right);
		}
	}
	swap(&data[lptr-1],&data[left]);
	//printArray(data,left,right);
	return(lptr-1);
}

template <class DataType> int rightmostpivotpos(DataType data[],int left,int right)
{
	int lptr,rptr;
	lptr=left-1;
	//rptr=right-1;
	for(int i=left;i<right;i++)
	{
		if(data[i]<=data[right])
		{
			if(++lptr!=i) swap(&data[lptr],&data[i]);
			//printArray(data,left,right);
		}
	}
	swap(&data[lptr+1],&data[right]);
	//printArray(data,left,right);
	return(lptr+1);
}

template <class DataType> int randompivotpos(DataType data[],int left,int right)
{
	int ran=rand()%(right-left)+left;
	cout<<"random pivot is "<<data[ran]<<"with pivot pos "<<ran<<endl;
	swap(&data[ran],&data[right]);
	int lptr=left-1;
	//rptr=right-1;
	for(int i=left;i<right;i++)
	{
		if(data[i]<=data[right])
		{
			if(++lptr!=i) swap(&data[lptr],&data[i]);
			//printArray(data,left,right);
		}
	}
	swap(&data[lptr+1],&data[right]);
	//printArray(data,left,right);
	return(lptr+1);
}

template <class DataType> int stablepivotpos(DataType data[],int left,int right)
{

	cout<<"pivot is "<<data[right]<<" with position "<<right<<endl;
	int lptr,rptr;
	lptr=left-1;
	//rptr=right-1;
	for(int i=left;i<right;i++)
	{
		if(data[i]<=data[right])
		{
			lptr++;
			DataType temp=data[i];
			for(int k=i;k>lptr;k--)
			{
				data[k]=data[k-1];
			}
			data[lptr]=temp;
			//swap(&data[lptr],&data[i]);
			//printArray(data,left,right);
		}
	}

	DataType temp=data[right];
	for(int i=right;i>lptr+1;i--)
	{
		data[i]=data[i-1];
	}
	data[lptr+1]=temp;
	//swap(&data[lptr+1],&data[right]);
	//printArray(data,left,right);
	return(lptr+1);
}

template <class DataType> void multipivotpos(DataType data[],int left,int right,int *p1,int *p2)
{
	//cout<<"pivot is "<<data[right]<<" with position "<<right<<endl;
	/*int lptr,rptr;
	



	lptr=left+1;
	rptr=right;
	for(lptr;lptr<=rptr;lptr++)
	{
		if(data[lptr]>data[left])
		{
			while(data[rptr]>data[left])
			{
				rptr--;
			}
			if(rptr<lptr) break;
			swap(&data[lptr],&data[rptr]);
			cout<<"LL\n";
			printArray(data,left,right);
		}
	}
	swap(&data[lptr-1],&data[left]);
	cout<<"LL\n";
	printArray(data,left,right);
	*p2=lptr-1;


lptr=left-1;
	//rptr=right-1;
	for(int i=left;i<right;i++)
	{
		if(data[i]<=data[right])
		{
			lptr++;
			DataType temp=data[i];
			for(int k=i;k>lptr;k--)
			{
				data[k]=data[k-1];
			}
			data[lptr]=temp;
			//swap(&data[lptr],&data[i]);
			cout<<"RR\n";
			printArray(data,left,right);
		}
	}

	DataType temp=data[right];
	for(int i=right;i>lptr+1;i--)
	{
		data[i]=data[i-1];
	}
	data[lptr+1]=temp;
	//swap(&data[lptr+1],&data[right]);
	cout<<"RR\n";
	printArray(data,left,right);
	*p1=lptr+1;*/
	//if(data[left]>data[right]) swap(&data[left],&data[right]);
	int lptr,rptr;
	lptr=left+1;
	rptr=right-1;
	for(int i=left+1;i<=rptr;i++)
	{
		if(data[i]<data[left])
		{		
			//lptr++;
			swap(&data[i],&data[lptr]);
			lptr++;
			//swap(&data[lptr],&data[i]);
		}
		else if(data[i]>=data[right])
		{
			while(data[rptr]>data[right]&&i<rptr)
			rptr--;
			swap(&data[i],&data[rptr]);
			rptr--;
			if(data[i]<data[left])
			{
				//lptr++;
				swap(&data[i],&data[lptr]);
				lptr++;
			}
		}
	}
	swap(&data[lptr-1],&data[left]);
	swap(&data[rptr+1],&data[right]);
	*p1=lptr-1;
	*p2=rptr+1;
}

template <class DataType> void quickSort(DataType data[],int left,int right)
{
	if(right-left<1) return;
	int pivot=pivotpos(data,left,right);
	printArray(data,left,right);
	quickSort(data,left,pivot-1);
	quickSort(data,pivot+1,right);
}

template <class DataType> void rightpivotquickSort(DataType data[],int left,int right)
{
	if(right-left<1) return;
	int pivot=rightmostpivotpos(data,left,right);
	printArray(data,left,right);
	rightpivotquickSort(data,left,pivot-1);
	rightpivotquickSort(data,pivot+1,right);
}

template <class DataType> void randomquickSort(DataType data[],int left,int right)
{
	if(right-left<1) return;
	int pivot=randompivotpos(data,left,right);
	printArray(data,left,right);
	randomquickSort(data,left,pivot-1);
	randomquickSort(data,pivot+1,right);
}

template <class DataType> void quickSortwithinsertion(DataType data[],int left,int right)
{
	if(right-left<1) return;
	if(right-left<=4) 
	{
		insertionSort(data,left,right);
		return;
	}
	int pivot=pivotpos(data,left,right);
	printArray(data,left,right);
	quickSortwithinsertion(data,left,pivot-1);
	quickSortwithinsertion(data,pivot+1,right);
}

template <class DataType> void stablequickSort(DataType data[],int left,int right)
{
	if(right-left<1) return;
	int pivot=stablepivotpos(data,left,right);
	printArray(data,left,right);
	stablequickSort(data,left,pivot-1);
	stablequickSort(data,pivot+1,right);
}

template <class DataType> void multipivotquickSort(DataType data[],int left,int right)
{
	if(right-left<1) return;
	int p1,p2;
	if(data[left]>data[right]) swap(&data[left],&data[right]);
	multipivotpos(data,left,right,&p1,&p2);
	printArray(data,left,right);
	if(p2<p1) swap(&p1,&p2);
	multipivotquickSort(data,left,p1-1);
	multipivotquickSort(data,p1+1,p2-1);
	multipivotquickSort(data,p2+1,right);
}

template <class DataType> void iterativequicksort(DataType data[],int left,int right)
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
		int p=pivotpos(data,l,r);
		if(p-1>l)
		{
			s.push(l);
			s.push(p-1);
		}
		if(p+1<r)
		{
			s.push(p+1);
			s.push(r);
		}
	}
}

int main()
{
	int input[N];
	int n;
	cout<<"Enter no of inputs\n";
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>input[i];//=rand()%100;
	}
	cout<<"Initially the ";
	printArray(input,0,n-1);

	/*bubbleSort(input,0,n-1);
	cout<<"After bubble sort ";
	printArray(input,0,n-1);
	*/

	/*selectionSort(input,0,n-1);
	cout<<"After selection sort ";
	printArray(input,0,n-1);
	*/

	/*insertionSort(input,0,n-1);
	cout<<"After insertion sort ";
	printArray(input,0,n-1);
	*/

	/*mergeSortTopDown(input,0,n-1);
	cout<<"After merge sort top down ";
	printArray(input,0,n-1);
	*/

	/*iterativemergeSortBottomUp(input,0,n-1);
	cout<<"After merge sort bottom up ";
	printArray(input,0,n-1);
	*/

	/*quickSort(input,0,n-1);
	cout<<"After quick sort ";
	printArray(input,0,n-1);
	*/

	/*stableselectionSort(input,0,n-1);
	cout<<"After stable selection sort ";
	printArray(input,0,n-1);
	*/

	/*rightpivotquickSort(input,0,n-1);
	cout<<"After right pivot quick sort ";
	printArray(input,0,n-1);
	*/

	/*randomquickSort(input,0,n-1);
	cout<<"After random quick sort ";
	printArray(input,0,n-1);
	*/

	/*quickSortwithinsertion(input,0,n-1);
	cout<<"After quick sort with insertion ";
	printArray(input,0,n-1);
	*/

	/*mergeSortTopDownwithinsertion(input,0,n-1);
	cout<<"After merge sort with insertion ";
	printArray(input,0,n-1);
	*/

	/*stablequickSort(input,0,n-1);
	cout<<"After stable quick sort ";
	printArray(input,0,n-1);
	*/

	/*iterativequicksort(input,0,n-1);
	cout<<"After iterative quick sort ";
	printArray(input,0,n-1);
	*/

	/*multipivotquickSort(input,0,n-1);
	cout<<"After multipivot quick sort ";
	printArray(input,0,n-1);
	*/
	
	return 0;
} 