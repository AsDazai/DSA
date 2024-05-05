#include<iostream>
#define max 100
using namespace std;

class mar{
    public:
    int arr[max],temp,n,left,right,large,z;
    void create();
    void hfy(int);
};

void mar::hfy(int i){
    right = 2*i+2;
    left = 2*i+1;
    large = i;
    if(left < n && arr[left] > arr[large]){
        large = left;
    }
    if(right < n && arr[right] > arr[large]){
        large = right;
    }
    if(i!=large){
        temp = arr[i];
        arr[i]=arr[large];
        arr[large]=temp;
        hfy(large);
    }
}

void mar::create(){
    cout<<"enter no. of students : ";
    cin>>n;
    for(int i=0; i<n; i++){
        cout<<"enter marks : ";
        cin>>arr[i];
    }
    for(int i = (n/2)-1; i>=0; i--){
        hfy(i);
    }

    z=n;

    
    for(int i=n-1; i>=0; i--){
        temp = arr[i];
        arr[i] = arr[0];
        arr[0]=temp;
        n--;
        hfy(0);
    }
    cout<<"max"<<arr[z-1];
    cout<<"min"<<arr[0];
}

int main(){
    mar a;
    a.create();
    return 0;
}
