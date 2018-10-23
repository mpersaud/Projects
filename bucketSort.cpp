//
//  bucketSort.cpp
//  test
//
//  Created by Michael Persaud on 3/4/16.
//  Copyright © 2016 home. All rights reserved.
//




#include <iostream>
#include <fstream>

using namespace std;

class bucketSort{
private:
    
    
public:
    int minData;
    int maxData;
    int offSet;
    int bucketSize;
    int * bucketAry;
    
    //contstructor
    bucketSort(int size, int min, int max, int offset){
        bucketSize = size;
        bucketAry = new int[size];
        for (int i =0;i<bucketSize;i++){
            bucketAry[i]=0;
        }
        minData=min;
        maxData=max;
        offSet=offset;
        
    }
    
    
    void printBucketAry(ofstream &outFile2){
        for (int i =0;i<=18;i++){
            if(i>=10){
                outFile2<<i<<"  ";
                continue;
            }
            outFile2<<i<<"   ";
            
        }
        outFile2<<endl;
        for (int i =0;i<=18;i++){
            outFile2<<bucketAry[i]<<"   ";
        }
    }
    void printSortedData(ofstream &outFile){
        
        for (int i=0;i<bucketSize;i++){
            int index=i;
            while(bucketAry[index]!=0){
                outFile<<i+offSet<<endl;
                bucketAry[index]--;
            }
        }
        
    }
    
    int getIndex(int data){
        
        return data-offSet;
    }
};

void findMinMax(int &min, int &max, int input){
 
    if (input < min )min=input;
    else if (input > max ) max = input;
    else return;
        
};

int main(int argc, char* argv[]){
    
    
    string filename(argv[1]);
    string outfilename1(argv[2]);
    string outfilename2(argv[3]);
    
    ifstream inFile;
    ofstream outFile;
    ofstream outFile2;
    inFile.open(filename);
    
    int input;
    inFile>>input;
    int min=input;
    int max=input;
    while (inFile>>input){
       
        findMinMax(min,max,input);
      
    }
    inFile.close();

    int size= max-min+1;
    
    bucketSort BS = bucketSort(size,min,max,min);
    inFile.open(filename);
    outFile.open(outfilename1);
    outFile2.open(outfilename2);
    
    while (inFile>>input){
     
        int index = BS.getIndex(input);
        BS.bucketAry[index]++;
        outFile2<< input <<" " << index<<endl;
        
    }
    
    BS.printBucketAry(outFile2);
    BS.printSortedData(outFile);
    
    inFile.close();
    outFile.close();
    outFile2.close();
    cout<<"Program: Success"<<endl;
    return 0;
}
