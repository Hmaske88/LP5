#include <iostream>
#include <omp.h>
using namespace std;

int minVal(int arr[], int n)
{
    int minval=arr[0]
    #pragma omp parallel for reduction(min : minval)
    ;for(int i=0; i<n; i++)
    {
        if(arr[i]<minval) minval=arr[i];
    }
    return minval;
}

int maxVal(int arr[], int n)
{
    int maxval=arr[0]
    #pragma omp parallel for reduction(max : maxval) 
    ;for(int i=0; i<n; i++)
    {
        if(arr[i]>maxval) maxval=arr[i];
    }
    return maxval;
}

int sum(int arr[], int n)
{
    int sum=0;
    #pragma omp parallel for reduction(+ : sum) 
    ;for(int i=0; i<n; i++)
    {
        sum+=arr[i];
    }
    return sum;
}

int average(int arr[],int n)
{
    return double(sum(arr,n))/n;
}

int main()
{
    int n=5;
    int arr[]={1,2,3,4,5};
    cout<<"Minimum Value : "<<minVal(arr,n)<<"\n";
    cout<<"Maximum Value : "<<maxVal(arr,n)<<"\n";
    cout<<"Sum : "<<sum(arr,n)<<"\n";
    cout<<"Average : "<<average(arr,n)<<"\n";

    return 0;
}
