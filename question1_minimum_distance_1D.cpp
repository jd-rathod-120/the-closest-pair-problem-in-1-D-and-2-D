#include<bits/stdc++.h>
using namespace std;
//global variables for keeping track of minimum distance and variables
float mini=INT_MAX,point1,point2; 
//function for finding distance betwwen two elements in array
float distance(float x,float y){
    return (x>y)? (x-y) : (y-x);
}
//function for finding minimum of two elements 
float minimum(float x,float y){
    return (x>y) ? y : x ;
}
//function for finding pair
void find_pair(float x,float y){
    float a=distance(x,y);
    if(a<mini){
        mini=a;    
        point1=x;
        point2=y;
    }
}
//it will find minimum distance from sub array and return the minimum distance by comparing it with previous minimum distance
float sub_check(float sub[],int x,float min){
    sort(sub,sub+x);//for sorting sub array
    for(int i=0;i<x;i++){
        for(int j=i+1; (j<x)&& j<(i+16);j++){
            if(distance(sub[i],sub[j])<min){
                min=distance(sub[i],sub[j]);
                find_pair(sub[i],sub[j]);
                
            }
        }
    }
    return min;
}
//it will find minimum of three points for stoping recursive call
float bruteforce(float arr[],int n){
    float min1=FLT_MAX;
    for(int k=0;k<2;k++){
        for(int l=0;l<2;l++){
            if(k!=l && distance(arr[k],arr[l])<min1){
                min1=distance(arr[k],arr[l]);
                find_pair(arr[k],arr[l]);
                
            }
        }
    }
    return min1;
}
//main function for finding points who have minimum distance recursively 
float closest_pair(float arr[],int n){
    if(n<=3){
        return bruteforce(arr,n);
    }
    //variable which will keep the value of mid of the array
    int mid;
    if(n%2==0){
        mid=n/2;
    }
    else{
        mid=n/2+1;
    }
    //one array will keep the elements which are on the left of mid and another contain right of the mid
    float left[n],right[n];
    for(int i=0;i<mid;i++){
        //transfering the left side of the array
        left[i]=arr[i];
    }
    for(int j=mid;j<n;j++){
        //transfering the right side of the array
        right[j-mid]=arr[j];
    }
    //recursively call for finding minimum 
    float minimum_left=closest_pair(left,mid);
    float minimum_right=closest_pair(right,n-mid);
    //it will contain minimum 
    float min=minimum(minimum_left,minimum_right);
    float sub[n];
    int w=0;
    for(int i=0;i<n;i++){
        if(distance(arr[i],arr[mid-1])<mini){
            sub[w++]=arr[i];
        }
    }
    return sub_check(sub,w,min);
    
}
int main(){
    int n;
    cout<<"ENTER THE NUMBER OF ELEMENTS IN ARRAY:\n";
    cin>>n;
    float arr[n];
    cout<<"ENTER THE ELEMENTS OF ARRAY\n";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    sort(arr,arr+n);
    cout<<"THE MINIMUM DISTANCE IS: "<<closest_pair(arr,n)<<endl;
    cout<<" "<<point1<<"AND"<<" "<<point2;    
    return 0;
}