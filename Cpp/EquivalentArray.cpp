#include <iostream>
using namespace std;

bool equals(int a[],int b[],int c, int offset){
    
    for(int i =0; i<c;i++){
        int shifted_idx= (i+offset) % c;
        if(a[i]!=b[shifted_idx])return false;
    }
    return true;
}

bool equivalent (int a [], int b [], int c){
    int offset =0;
    for (int i=0; i<c; i++){
        if (a[0]== b[i]) {
            offset=i;
            if(equals(a,b,c,offset))return true;
        }
    }
    return false;
}

int main() {
    cout << boolalpha; // to print bool values as true/false instead of 1/0
    
    int a1[5] = {1, 2, 3, 4, 5};
    int a2[5] = {3, 4, 5, 1, 2};
    cout << equivalent(a1, a2, 5) << endl; // true
    
    int b1[3] = {1, 2, 3};
    int b2[3] = {2, 3, 3};
    cout << equivalent(b1, b2, 3) << endl; // false
    
    int c1[4] = {2, 3, 4, 1};
    int c2[4] = {1, 4, 3, 2};
    cout << equivalent(c1, c2, 4) << endl; // false
    
    int d1[4] = {3, 2, 3, 1};
    int d2[4] = {3, 1, 3, 2};
    cout << equivalent(d1, d2, 4) << endl; // true
    
    int e1[5] = {1, 1, 1, 1, 2};
    int e2[5] = {1, 1, 1, 2, 1};
    cout << equivalent(e1, e2, 5) << endl; // true
    
    return 0;
}


