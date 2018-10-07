#include <iostream>
#include <cstdlib>

#define insize 8

using namespace std;


template <class DataType>void swapElements(DataType &v1, DataType &v2){

	DataType temp = v1;
	v1=v2;
	v2=temp;
}


template <class DataType> void printArray(DataType data[]){

	cout<<  "Array is ";
	for(int i=0; i<insize; i++){
		cout<<" "<<data[i];
	}
	cout<<endl;
}


template <class DataType> void bubbleSort(DataType data[]){

	int i, j;

	for(i=(insize-1); i>0; i--){

		for(j=0; j<i; j++){

			if(data[j]>data[j+1]){

				swapElements(data[j],data[j+1]);
				//printArray(data);
			}
		}
	}

}



template <class DataType> void mergeSortTopDown(DataType data[], const int left, const int right){

	if((right-left)<1){
		return;
	}

	//printArray(data);
	cout<<"Sorting from "<<left<<"  to "<<right<<endl;
	mergeSortTopDown(data, left, (left+right)/2);
	mergeSortTopDown(data, ((left+right)/2)+1, right);

	DataType buffer[(right-left)+1];

	int index1=left, index2=((left+right)/2)+1, buffIndex;

	for(buffIndex=0; buffIndex<=(right-left); buffIndex++){

		if(index1<=(left+right)/2){
			if(index2<=right){
				if(data[index1]<=data[index2]){
					buffer[buffIndex]=data[index1];
					index1++;
				}else{
					buffer[buffIndex]=data[index2];
					index2++;
				}

			}else{
					buffer[buffIndex]=data[index1];
					index1++;
			}

		}else{

			buffer[buffIndex]=data[index2];
			index2++;
		}
	}

	for(int i=0; i<=right-left; i++){
		data[left+i]=buffer[i];
	}
	cout<<"Finished Sorting from "<<left<<"  to "<<right<<endl;
	//printArray(data);
}

template <class DataType> int partitionNoCount(DataType data[], int left, int right){

		DataType temp = data[left];
		int leftPtr, rightPtr;




		for(leftPtr=left+1, rightPtr=right; leftPtr<=rightPtr; leftPtr++){

			if(data[leftPtr]>data[left]){
				while(data[rightPtr]>data[left]){
					rightPtr--;
				}
				if(rightPtr<leftPtr){
					break;
				}
				swapElements(data[leftPtr], data[rightPtr]);
			}
		}
		swapElements(data[left], data[leftPtr-1]);

		return(leftPtr-1);

}




template <class DataType> int partition(DataType data[], int left, int right){

		DataType temp = data[left];
		int leftPtr, rightPtr;
		int lessEqCount=0, greaterCount=0;

		for(int i=left+1; i<=right; i++){
			if(data[i]<=temp){
				lessEqCount++;
			}else{
				greaterCount++;
			}
		}


		if(lessEqCount==0){
			return(left);
		}
		if(greaterCount==0){
			swapElements(data[left], data[right]);
			return(right);
		}

		int pivotPos=left+lessEqCount;
		swapElements(data[left], data[pivotPos]);

		for(leftPtr=left, rightPtr=right; leftPtr<pivotPos; leftPtr++){

			if(data[leftPtr]>data[pivotPos]){
				while(data[rightPtr]>data[pivotPos]){
					rightPtr--;
				}
				swapElements(data[leftPtr], data[rightPtr]);
			}
		}
		return(pivotPos);
}


template <class DataType> void quickSort(DataType data[], int left, int right){
	cout<<"Sorting from "<<left<<" to "<<right<<endl;
	if(right<=left){
		cout<<"Trivial Case: Finished Sorting from "<<left<<" to "<<right<<endl;
		return;
	}

	int pivotPos = partitionNoCount(data, left, right);
	cout<<"Pivot value "<<data[pivotPos]<<"  Pivot position "<<pivotPos<<endl;
	//printArray(data);


	if(((pivotPos-1)-left)>1){
		quickSort(data, left, pivotPos-1);
	}

	if((right-(pivotPos+1))>1){
		quickSort(data, pivotPos+1, right);
	}

	cout<<"Finished Sorting from "<<left<<" to "<<right<<endl;
	//printArray(data);
}

template <class DataType> void selectionSort(DataType data[]){
	int i,j;
	int minIndex;

	for(i=0; i<insize-1; i++){
		minIndex=i;
		for(j=i+1; j<insize; j++){

			if(data[j]<data[minIndex]){
				minIndex=j;
			}
		}

		if(minIndex!=i){
			swapElements(data[i], data[minIndex]);
			//printArray(data);
		}

	}

}



template <class DataType> void insertionSort(DataType data[]){

	int i,j;

	for(i=1; i<insize; i++){
		DataType temp=data[i];
		for(j=i-1; j>=0; j--){

			if(data[j]>temp){
				data[j+1]=data[j];
				printArray(data);
			}else{

				break;
			}
		}
		cout<<"i is "<<i<<" j is "<<j<<endl<<endl;
		if(j!=(i-1)){
			data[j+1]=temp;
			//printArray(data);
		}
	}
}








int main(){

	float input[]= {12.3, 6, 4, 9,14,43,42,3};
	printArray(input);
	//bubbleSort(input);
	//selectionSort(input);
	//insertionSort(input);
	//quickSort(input,0,insize-1);
	mergeSortTopDown(input,0,insize-1);
	printArray(input);

	return(0);
}
