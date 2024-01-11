//#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//#include <omp.h>

#include <stdio.h>
#include <omp.h>

void printArray(int *A, int n)
{
    cout<<"\n";
    for (int i = 0; i < n; i++)
    {
        cout<<A[i]<<" ";
    }
    cout<<"\n";
}


void OMPmerge(int A[], int mid, int low, int high)
{
    int i, j, k, B[100];
    i = low;
    j = mid + 1;
    k = low;
	
    while (i <= mid && j <= high)
    {
        if (A[i] < A[j])
        {
            B[k] = A[i];
            i++;
            k++;
        }
        else
        {
            B[k] = A[j];
            j++;
            k++;
        }
    }
    while (i <= mid)
    {
        B[k] = A[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        B[k] = A[j];
        k++;
        j++;
    }
    for (int i = low; i <= high; i++)
    {
        A[i] = B[i];
    }
    
}





void merge(int A[], int mid, int low, int high)
{
    int i, j, k, B[100];
    i = low;
    j = mid + 1;
    k = low;
    while (i <= mid && j <= high)
    {
        if (A[i] < A[j])
        {
            B[k] = A[i];
            i++;
            k++;
        }
        else
        {
            B[k] = A[j];
            j++;
            k++;
        }
    }
    while (i <= mid)
    {
        B[k] = A[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        B[k] = A[j];
        k++;
        j++;
    }
    for (int i = low; i <= high; i++)
    {
        A[i] = B[i];
    }
    
}





void mergeSort(int A[], int low, int high){
    int mid; 
    if(low<high){
        mid = (low + high) /2;
        mergeSort(A, low, mid);
        mergeSort(A, mid+1, high);
        merge(A, mid, low, high);
    }
}


void OMPmergeSort(int A[], int low, int high){
    int mid; 
    if(low<high){
        mid = (low + high) /2;
        #pragma omp task firstprivate (A, low, high)
        OMPmergeSort(A, low, mid);
        #pragma omp task firstprivate (A, low, high)
        OMPmergeSort(A, mid+1, high);
        #pragma omp taskwait
        OMPmerge(A, mid, low, high);
    }
}



int main()
{

	int n = 7;
	int A[n] = {9, 1, 4, 14, 4, 15, 6};
	int B[n] = {9, 1, 4, 14, 4, 15, 6};	
	printArray(A, n);
	

	clock_t start , end; 
	start = clock();
	
	
	mergeSort(A, 0, 6);
	printArray(A, n);
;
	end = clock();
	
	double cpu_time_used;
	cpu_time_used = ((double) (end - start)) / double(CLOCKS_PER_SEC);
	cout<<"Regular TIME: "<< fixed << cpu_time_used<< setprecision(10) << " sec";
	
	cout<<"\n\n";
	
	start = clock();
	
	
	#pragma omp parallel
	   {
	      #pragma omp single
	      OMPmergeSort(B, 0, 6);
	   }
	printArray(B, n);
;
	end = clock();
	
	cpu_time_used = ((double) (end - start)) / double(CLOCKS_PER_SEC);
	cout<<"Parallel TIME: "<< fixed << cpu_time_used<< setprecision(10) << " sec";
	
	
	return 0;
}
