/* A worst case O(nLogn) implementation of quicksort */
#include<cstring> 
#include<iostream> 
#include<algorithm> 
#include<climits> 
using namespace std; 
  
// Following functions are taken from http://goo.gl/ih05BF 
int partition(int arr[], int l, int r, int k); 
int kthSmallest(int arr[], int l, int r, int k); 
  
/* A O(nLogn) time complexity function for sorting arr[l..h] */
void quickSort(int arr[], int l, int h) 
{ 
    if (l < h) 
    { 
        // Find size of current subarray 
        int n = h-l+1; 
  
        // Find median of arr[]. 
        int med = kthSmallest(arr, l, h, n/2); 
  
        // Partition the array around median 
        int p = partition(arr, l, h, med); 
  
        // Recur for left and right of partition 
        quickSort(arr, l, p - 1); 
        quickSort(arr, p + 1, h); 
    } 
} 
  
// A simple function to find median of arr[].  This is called 
// only for an array of size 5 in this program. 
int findMedian(int arr[], int n) 
{ 
    sort(arr, arr+n);  // Sort the array 
    return arr[n/2];   // Return middle element 
} 
  
// Returns k'th smallest element in arr[l..r] in worst case 
// linear time. ASSUMPTION: ALL ELEMENTS IN ARR[] ARE DISTINCT 
int kthSmallest(int arr[], int l, int r, int k) 
{ 
    // If k is smaller than number of elements in array 
    if (k > 0 && k <= r - l + 1) 
    { 
        int n = r-l+1; // Number of elements in arr[l..r] 
  
        // Divide arr[] in groups of size 5, calculate median 
        // of every group and store it in median[] array. 
        int i, median[(n+4)/5]; // There will be floor((n+4)/5) groups; 
        for (i=0; i<n/5; i++) 
            median[i] = findMedian(arr+l+i*5, 5); 
        if (i*5 < n) //For last group with less than 5 elements 
        { 
            median[i] = findMedian(arr+l+i*5, n%5); 
            i++; 
        } 
  
        // Find median of all medians using recursive call. 
        // If median[] has only one element, then no need 
        // of recursive call 
        int medOfMed = (i == 1)? median[i-1]: 
                                 kthSmallest(median, 0, i-1, i/2); 
  
        // Partition the array around a random element and 
        // get position of pivot element in sorted array 
        int pos = partition(arr, l, r, medOfMed); 
  
        // If position is same as k 
        if (pos-l == k-1) 
            return arr[pos]; 
        if (pos-l > k-1)  // If position is more, recur for left 
            return kthSmallest(arr, l, pos-1, k); 
  
        // Else recur for right subarray 
        return kthSmallest(arr, pos+1, r, k-pos+l-1); 
    } 
  
    // If k is more than number of elements in array 
    return INT_MAX; 
} 
  
void swap(int *a, int *b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 
  
// It searches for x in arr[l..r], and partitions the array 
// around x. 
int partition(int arr[], int l, int r, int x) 
{ 
    // Search for x in arr[l..r] and move it to end 
    int i; 
    for (i=l; i<r; i++) 
        if (arr[i] == x) 
           break; 
    swap(&arr[i], &arr[r]); 
  
    // Standard partition algorithm 
    i = l; 
    for (int j = l; j <= r - 1; j++) 
    { 
        if (arr[j] <= x) 
        { 
            swap(&arr[i], &arr[j]); 
            i++; 
        } 
    } 
    swap(&arr[i], &arr[r]); 
    return i; 
} 
  
/* Function to print an array */
void printArray(int arr[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        cout << arr[i] << " "; 
    cout << endl; 
} 
  
// Driver program to test above functions 
int main() 
{ 
    int arr[] = {1000, 10, 7, 8, 9, 30, 900, 1, 5, 6, 20}; 
    int n = sizeof(arr)/sizeof(arr[0]); 
    quickSort(arr, 0, n-1); 
    cout << "Sorted array is\n"; 
    printArray(arr, n); 
    return 0; 
} 