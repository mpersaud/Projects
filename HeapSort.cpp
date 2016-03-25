//
//  HeapSort.cpp
//  test
//
//  Created by Michael Persaud on 2/19/16.
//  Copyright © 2016 home. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;

class heapSort{
private:
    int *heap;
    int length;
    
public:
    heapSort(int size){
        
        heap= new int[size+1];
        heap[0]=0;
        length=size+1;
        for (int i =0; i<length;i++){
            heap[i]=0;
        }
        
    }
    
    ~heapSort(){
        delete []heap;
    }
    
    bool isHeapEmpty(){
        if(heap[0]==0)return true;
        else return false;
    }
    
    bool isHeapFull(){
        if(heap[0]==length)return true;
        else return false;
    }
    
    void buildHeap(string filename,string outfilename){
        
        
        //reopening file
        ifstream inFile;
        ofstream outFile;
        outFile.open(outfilename);
        int input;
        inFile.open(filename);
        if (inFile.is_open())
        {
            while (inFile>> input)
            {
                
                //inserting and restoring the partial order tree property
                insertOneDataItem(input);
                bubbleUp();
                printHeap(outFile);
                
            }
            
        }
        outFile.close();
        inFile.close();
        
    }
    
    void insertOneDataItem(int data){
        if(isHeapFull()) return;
        int lastindex= heap[0]; //finds the last
        heap[lastindex+1]=data; // adds to last+1
        heap[0]++; //increment size
    }
    
    void bubbleUp(){
        
        int currentindex = heap[0]; // to start at last
        int parentindex= heap[0]/2; // finding the parent
        int root = 1; //index of root
        
        while(heap[currentindex]<heap[parentindex]&& currentindex !=root){
            
            //used to swap
            int temp;
            temp=heap[currentindex];
            heap[currentindex]=heap[parentindex];
            heap[parentindex]=temp;
            
            //updating to move up the tree
            currentindex=parentindex;
            parentindex = parentindex/2;
        }
        
    }
    
    void deleteHeap(string outfilename1, string outfilename2){
        
        //opening the output files
        ofstream outFile;
        ofstream outFile2;
        outFile.open(outfilename1,ios::app);
        outFile2.open(outfilename2);
        
        
        //continue while there iselements
        while(!isHeapEmpty()) {
            
            //delete the root
            deleteRoot(outFile2);
            heap[1]= heap[heap[0]];
            heap[heap[0]] = -1;
            heap[0]--;
            bubbleDown();
            printHeap(outFile);
        }
       
        //outFile.close();
        outFile2.close();
        
    }
    
    void deleteRoot(ofstream &outFile2){
       
        //uses -1 as a sign for deletion
        
        if(isHeapFull()) return;
        //sends root to output file
        outFile2<< heap[1]<< " ";
        heap[1]=-1;
    }
    void bubbleDown(){
        
        //starts at root and finds its children
        int currentindex = 1;
        int leftchildindex = currentindex * 2;
        int rightchildindex = (currentindex* 2) +1;
        
        //min bettween the children
        int minIndex;
        
        if (heap[leftchildindex] <= heap[rightchildindex])
            minIndex = leftchildindex;
        else
            minIndex = rightchildindex;
        
        //while there is a minium and still in the ree
        while ((heap[minIndex]< heap[currentindex]) && (minIndex<=heap[0])){
            
            //swap values
            int temp;
            temp=heap[minIndex];
            heap[minIndex]=heap[currentindex];
            heap[currentindex]=temp;
            
            //update the min and children
            currentindex=minIndex;
            leftchildindex = minIndex * 2;
            rightchildindex = (minIndex * 2) +1;
            if (heap[rightchildindex]>=length||heap[leftchildindex]>=length){
                return;
            }
            if (heap[leftchildindex] <= heap[rightchildindex])
                minIndex = leftchildindex;
            else
                minIndex = rightchildindex;
        }
            
    
    }
    
    void printHeap(ofstream &outFile){
        
        //prints the first 10 items including size
        for(int i =0;i<10;i++){
            if(heap[i]==-1)continue;
            outFile<<heap[i] << " ";
            
        }
        outFile<<endl;
    }
    
};



int main(int argc, char* argv[]){
    
    ifstream inFile;
   
    string filename(argv[1]);
    string outfilename1(argv[2]);
   string outfilename2(argv[3]);
    inFile.open(filename);
  
    int count =0;
    
    int input;
   
    
    if (inFile.is_open())
    {
        while (inFile>> input)
        {
            
            count++;
            
        }
    }

    else cout << "Unable to open file"<<endl;
    
    cout<< '\n';
    inFile.close();
    

    heapSort HA = heapSort(count);
    
    HA.buildHeap(filename,outfilename1);
    HA.deleteHeap(outfilename1,outfilename2);
    
 
}