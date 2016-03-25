#include <iostream>
#include <fstream>

using namespace std;

class Image {
public:
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int ** imgAry;
    
    
    void makeImgAry(){
        
        imgAry = new int*[numRows];
        for(int i = 0; i < numRows; i++){
            imgAry[i] = new int[numCols]();
            
        }
    }
    
    void loadImage(string filename){
        ifstream inFile;
        inFile.open(filename);
        
        int input;
        
        //in order to skip header
        int count=0;
        while (count<4){
            inFile>>input;
            count++;
        }
        
        for (int i =0;i<numRows;i++){
            // cout<<endl;
            for (int j=0;j<numCols;j++){
                inFile>>imgAry[i][j];
                //cout<<imgAry[i][j]<<" ";
            }
        }
        //cout<<endl<<endl;
        inFile.close();
        
    }
    
    Image(int rows, int cols,int min,int max){
        numRows=rows;
        numCols=cols;
        minVal=min;
        maxVal=max;
        
    }
    
};


class QuadTreeNode {
    
public:
    
    friend class QuadTree;
    friend class Image;
    
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int Color;
    int rowOffset;
    int colOffset;
    
    QuadTreeNode* NW_kid;
    QuadTreeNode* SW_kid;
    QuadTreeNode* NE_kid;
    QuadTreeNode* SE_kid;
    
    QuadTreeNode(int rows, int cols, int min, int max, int rowOff, int ColOff,Image* img){
        
        numRows=rows;
        numCols=cols;
        minVal=min;
        maxVal=max;
        rowOffset= rowOff;
        colOffset=ColOff;
        computeColor(img);
        NW_kid=NULL;
        SW_kid=NULL;
        NE_kid=NULL;
        SE_kid=NULL;
    }
    
    QuadTreeNode(int rows, int cols, int min, int max, int rowOff, int ColOff){
        
        numRows=rows;
        numCols=cols;
        minVal=min;
        maxVal=max;
        rowOffset= rowOff;
        colOffset=ColOff;
        
        
    }
    
    QuadTreeNode(){
        
    }
    
    
    ~QuadTreeNode(){
        delete NW_kid;
        delete SW_kid;
        delete NE_kid;
        delete SE_kid;
        
    }
    
    void printNode(ofstream &outFile){
        
        if (NW_kid==NULL)   outFile<<Color<<" "<<numRows<<" "<< numCols<<" "<<minVal<<" "<<maxVal<<" "<<rowOffset<<" "<<colOffset<<" "<<"NULL"<<" "<<"NULL"<<" "<< "NULL"<<" "<<"NULL"<<" "<<endl;
        
        else outFile<<Color<<" "<<numRows<<" "<< numCols<<" "<<minVal<<" "<<maxVal<<" "<<rowOffset<<" "<<colOffset<<" "<<NW_kid->Color<<" "<<SW_kid->Color<<" "<<SE_kid->Color<<" "<<NE_kid->Color<<" "<<endl;
        
    }
    
    void computeNWOffsets(QuadTreeNode* parentNode){
        rowOffset = parentNode->rowOffset;
        colOffset = parentNode->colOffset;
        
    }
    void computeSWOffsets(QuadTreeNode* parentNode){
        rowOffset = parentNode->rowOffset+ (parentNode->numRows/2);
        colOffset = parentNode->colOffset;
        
    }
    void computeSEOffsets(QuadTreeNode* parentNode){
        rowOffset = parentNode->rowOffset+ (parentNode->numRows/2);
        colOffset = parentNode->colOffset + (parentNode->numCols/2);
        
    }
    void computeNEOffsets(QuadTreeNode* parentNode){
        rowOffset = parentNode->rowOffset;
        colOffset = parentNode->colOffset + (parentNode->numCols/2);
        
    }
    
    void computenumRowsCols(QuadTreeNode* parentNode){
        numRows=parentNode->numRows/2;
        numCols= parentNode->numCols/2;
        
    }
    
    void computeColor(Image* img){
        
        int val = img->imgAry[rowOffset][colOffset];
        for (int i = rowOffset; i <rowOffset + numRows;i++){
            for (int j = colOffset;j<colOffset + numCols;j++){
                
                if(val != img->imgAry[i][j]){
                    Color = 2;
                    minVal=0;
                    maxVal=1;
                    return;
                }
            }
        }
        Color = val;
        minVal=val;
        maxVal =val;
        return;
        
    }
    
    
    /*  void computeMinMaxValue(QuadTreeNode* parenttNode){
     
     }
     */
    
};


class QuadTree {
    
public:
    QuadTreeNode* rootNode;
    
    QuadTree(QuadTreeNode* root){
        rootNode=root;
    }
    
    void buildQuadTree(QuadTreeNode* treeNode,Image* img){
        
        if(treeNode == NULL)return;
        
        
        else if( treeNode->Color!=2 )return;
        
        else {
            
            treeNode->NW_kid= new QuadTreeNode();
            treeNode->NW_kid->computenumRowsCols(treeNode);
            treeNode->NW_kid->computeNWOffsets(treeNode);
            treeNode->NW_kid->computeColor(img);
            buildQuadTree(treeNode->NW_kid,img);
            
            treeNode->SW_kid= new QuadTreeNode();
            treeNode->SW_kid->computenumRowsCols(treeNode);
            treeNode->SW_kid->computeSWOffsets(treeNode);
            treeNode->SW_kid->computeColor(img);
            buildQuadTree(treeNode->SW_kid,img);
            
            treeNode->SE_kid= new QuadTreeNode();
            treeNode->SE_kid->computenumRowsCols(treeNode);
            treeNode->SE_kid->computeSEOffsets(treeNode);
            treeNode->SE_kid->computeColor(img);
            buildQuadTree(treeNode->SE_kid,img);
            
            treeNode->NE_kid= new QuadTreeNode();
            treeNode->NE_kid->computenumRowsCols(treeNode);
            treeNode->NE_kid->computeNEOffsets(treeNode);
            treeNode->NE_kid->computeColor(img);
            buildQuadTree(treeNode->NE_kid,img);
            
        }
        
    }
    
    void printQuadTree(QuadTreeNode *treeNode,ofstream &outFile){
        
        if(treeNode == NULL)return;
        
        else {
            
            treeNode->printNode(outFile);
            printQuadTree(treeNode->NW_kid,outFile);
            printQuadTree(treeNode->SW_kid,outFile);
            printQuadTree(treeNode->SE_kid,outFile);
            printQuadTree(treeNode->NE_kid,outFile);
            
        }
    }
    
};

int main(int argc, char * argv[]) {
    
    string filename(argv[1]);
    string outfile1(argv[2]);
    string outfile2(argv[3]);
    
    ifstream inFile;
    ofstream outFile;
    ofstream outFile2;
    inFile.open(filename);
    outFile.open(outfile1);
    outFile2.open(outfile2);
    
    int input;
    inFile>>input;
    int numRows=input;
    inFile>>input;
    int numCols=input;
    inFile>>input;
    int minVal=input;
    inFile>>input;
    int maxVal=input;
    inFile.close();
    
    Image* img  = new Image(numRows,numCols,minVal,maxVal);
    img->makeImgAry();
    img->loadImage(filename);
    
    QuadTreeNode * rootNode = new QuadTreeNode(numRows,numCols,minVal,maxVal,0,0,img);
    QuadTree* QT = new QuadTree(rootNode);
    QT->buildQuadTree(rootNode,img);
    QT->printQuadTree(rootNode,outFile);
    outFile.close();
    outFile2.close();
    return 0;
    
}
