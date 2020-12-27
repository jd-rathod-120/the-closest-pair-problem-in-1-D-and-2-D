//programm for finding two points with minimum distances
#include<bits/stdc++.h>
using namespace std;
//it will contain minimum distance
float mini=FLT_MAX;


//class of variable x and y
class point{
    public:
        float x,y;
};
//for storing variables between whom has minimum distance
point point1;
point point2;
//function for finding distance
float distance(point a,point b){
    return (sqrt(((a.x-b.x)*(a.x-b.x))+((a.y-b.y)*(a.y-b.y))));//distance pq=sqrt((Px-Qx)^2+(Py-Qy)^2)
};
//for sorting x coordinate
int sort_x(const void* a,const void* b){
    point *a1=(point *)a;
    point *b1=(point *)b;
    return (a1->x - b1->x);
}
//for sorting y coordinate
int sort_y(const void* a,const void* b){
    point *a1=(point *)a;
    point *b1=(point *)b;
    return (a1->y - b1->y);
}
//for finding minimum of two variables 
float minimum(float a,float b){
    return (a<b) ? a : b;
}
//function for finding pair and storing them in global variables
void find_pair(point a,point b){
    float temp=distance(a,b);
    if(temp<mini){
        mini=temp;
        point1.x = a.x;
        point1.y = a.y;
        point2.x = b.x;
        point2.y = b.y;
        
    }
}
//for breaking recurssion means it will work as base case of function closest_pair
float bruteforce(point arr[],float n){
    float min= INT_MAX;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(distance(arr[i],arr[j])<min){
                min = distance(arr[i],arr[j]);
                find_pair(arr[i],arr[j]);
                
            }
        }
    }
    return min;
}
//function for finding minimum distance in sub array and comaring it to the actual minimum
float sub_pair(point sub[ ],int n,float min){
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n && ((sub[j].y-sub[i].y)<min);j++){
            if(distance(sub[j],sub[i])<min){
                min=distance(sub[i],sub[j]);
                find_pair(sub[i],sub[j]);
            }
        }
    }
    return min;
}
//main function for finding pair with minimum distance
float closest_pair(point arr_x[ ],point arr_y[ ],int n){
    //base case 
    if(n<=3){
        return bruteforce(arr_x,n);
    }
    int mid=n/2;
    point arr_mid = arr_x[mid];
    //arr_left array will contain elements on the left of mid and arr_right will contain elements on the right side of mid
    point arr_left[mid];
    point arr_right[mid];
    int left=0,right=0;
    for(int i=0;i<n;i++){
        if(left<mid && arr_y[i].x <= arr_mid.x){
            arr_left[left++]=arr_y[i];
        }
        else{
            arr_right[right++]=arr_y[i];
        }
    }
    //recursively call 
    float distance_left=closest_pair(arr_x,arr_left,mid);
    float distance_right=closest_pair(arr_x,arr_right,n-mid);
    //from both distance left and right it will contain minimum 
    float min1=minimum(distance_left,distance_right);
     point sub[mid];
     int k=0;    
     for(int j=0;j<n;j++){
         if(abs(arr_y[j].x-arr_mid.x)<min1){
             sub[k++]=arr_y[j];
         }
     }
     //function call for finding if any pair exist in sub array with minimum distance
     return sub_pair(sub,k,min1);
}
int main(){
    cout<<"NUMBER OF ELEMENTS YOU WANT TO ENTER:\n";
    int n;
    cin>>n;
    point arr[n];
    cout<<"ENTER ELEMENT:\n";
    for(int i=0;i<n;i++){
        cin>>arr[i].x;
        cin>>arr[i].y;
    }
    point arra_x[n];
    point arra_y[n];
    for(int j=0;j<n;j++){
        arra_x[j]=arr[j];
        arra_y[j]=arr[j];
    }
    qsort(arra_x,n,sizeof(point),sort_x);
    qsort(arra_y,n,sizeof(point),sort_y);
    cout<<"MINIMUM DISTANCE: "<<closest_pair(arra_x,arra_y,n)<<endl;
    cout<<"("<<point1.x<<" "<<point1.y<<")"<<endl;
    cout<<"("<<point2.x<<" "<<point2.y<<")"<<endl;
    
    
    
    return 0;
}