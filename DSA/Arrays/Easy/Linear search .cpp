#include<bits/stdc++.h>
using namespace std; 

int search(int arr[] , int n , int num){
    for(int i=0; i<n;i++){
        arr[i]==num;
        return i;

    }

    return -1;
}

int main(){

int arr=[1,2,3,4,5,67];
int num=67;
int n=sizeof(arr)/sizeof(arr[0]);
int value = search(arr,n,num);




}