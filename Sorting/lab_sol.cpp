#include<bits/stdc++.h>
using namespace std;


template <class DataType> void swap(DataType *a,DataType *b)
{
    DataType t=*a;
    *a=*b;
    *b=t;
}

template <class DataType> void print_array(DataType a[],int n)
{
    for(int i=0;i<n;i++){cout<<a[i]<<" "<<endl;}
}

template <class DataType> void kway_merge_sort(DataType a[],int n,int k,int num_of_itre)
{
    priority_queue <DataType> q;
    int i,l;
    int number=0;
    if(num_of_itre<0)
    {
        for(int size=1;size<=n;size*=k)
        {
            for(int i=0;i<n;i+=k*size)
            {
                for(int j=i;j<=min(i+k*size-1,n-1);j++){q.push(a[j]);}
                l=min(i+k*size-1,n-1);
                while(!q.empty()){a[l--]=q.top();q.pop();}
            }
        }
    }
    else if(num_of_itre>=0)
    {
        for(int size=1;size<=n;size*=k)
        {
            number++;
            if(number>num_of_itre){return ;}
            for(int i=0;i<n;i+=k*size)
            {
                for(int j=i;j<=min(i+k*size-1,n-1);j++){q.push(a[j]);}
                l=min(i+k*size-1,n-1);
                while(!q.empty()){a[l--]=q.top();q.pop();}
            
            }
        }
    }
}

int main()
{
    int k;
    cin>>k;
    int num_of_itre;
    cin>>num_of_itre;
    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    kway_merge_sort(a,n,k,num_of_itre);
    print_array(a,n);
}