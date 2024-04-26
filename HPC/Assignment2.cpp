#include <iostream>
#include <omp.h>
#include <cmath>
#include <iomanip>
using namespace std;

void printArray(int a[], int n)
{
    for(int i=0; i<n; i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

void merge(int a[], int l, int mid, int h)
{
    int i=l, j=mid+1, k=l, b[7];

    while(i<=mid && j<=h)
    {
        if(a[i]<a[j])
        {
            b[k]=a[i];
            i++;
            k++;
        }
        else
        {
            b[k]=a[j];
            j++;
            k++;
        }
    }

    while(i<=mid)
    {
        b[k]=a[i];
        i++;
        k++;
    }

    while(j<=h)
    {
        b[k]=a[j];
        j++;
        k++;
    }

    for(int i=l; i<h; i++)
    {
        a[i]=b[i];
    }
}

void mergeSort(int a[],int l, int h)
{
    int mid;
    if(l<h)
    {
        mid = (l+h)/2;

        mergeSort(a, l, mid);
        mergeSort(a, mid+1, h);

        merge(a,l,mid,h);
    }
}


void parallelMergeSort(int a[],int l, int h)
{
    int mid;
    if(l<h)
    {
        mid = (l+h)/2;
        #pragma omp task firstprivate(a,l,h)
        parallelMergeSort(a, l, mid);
        #pragma omp task firstprivate(a,l,h)
        parallelMergeSort(a, mid+1, h);
        #pragma omp taskwait
        merge(a,l,mid,h);
    }
}

int main()
{
    const int n=7;
    int a[n]={5,3,7,5,2,6,9};

    clock_t start, end;
    double time1, time2;

    start=clock();
    cout<<"\nSequential Merge : ";
    mergeSort(a,0,6);
    printArray(a,n);
    end=clock();

    time1= double(end-start)/double(CLOCKS_PER_SEC);
    cout<<"\nSequential time : "<<fixed<<setprecision(10)<<time1;

    start=clock();
    cout<<"\n\nParallel Merge : ";
    #pragma omp parallel
    {
        #pragma omp single
        {
            parallelMergeSort(a,0,6);
        }
    }
    printArray(a,n);
    end=clock();

    time2= double(end-start)/double(CLOCKS_PER_SEC);
    cout<<"\nParallel time : "<<fixed<<setprecision(10)<<time2;

    cout<<"\n\nSpeedup : "<<time1/time2;


    return 0;
}
