import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Scanner;


public class HeapSort {
	private int length;
	
	private int[] heap;
	
	public HeapSort(int size){
		heap = new int[size+1];
		heap[0]=0;
		length=size+1;
		for (int i =0; i <length;i++){
			heap[0]=0;
		}
	}
	
	 boolean isHeapEmpty(){
	        if(heap[0]==0)return true;
	        else return false;
	    }
	    
	 boolean isHeapFull(){
	        if(heap[0]==length)return true;
	        else return false;
	    }
	
	 void insertOneDataItem(int data){
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
	 
	 void buildHeap(String filename, String outfilename){
		 
	        
	      Scanner s=null;  
		 try {
	            s = new Scanner(new BufferedReader(new FileReader(filename)));
	            
	            while (s.hasNext()) {
	            	
	            	insertOneDataItem(s.nextInt());
	            	bubbleUp();
	            	printHeap(outfilename);
	            }
	        } catch (Exception e) {
	        	System.out.print(e);
	        }
		 
	       s.close(); 
	    }
	 
	 void deleteHeap(String outfilename1, String outfilename2){
	        
	        //opening the output files
	      
	        
	        
	        //continue while there is elements
	        while(!isHeapEmpty()) {
	            
	            //delete the root
	            deleteRoot(outfilename2);
	            heap[1]= heap[heap[0]];
	            heap[heap[0]] = -1;
	            heap[0]--;
	            bubbleDown();
	            printHeap(outfilename1);
	        }
	       
	        
	        
	    }
	    
	    void deleteRoot(String filename){
	       
	        //uses -1 as a sign for deletion
	        
	        if(isHeapFull()) return;
	        //sends root to output file
	        try {
	              FileWriter writer = new FileWriter(filename, true);
	              BufferedWriter bufferedWriter = new BufferedWriter(writer);
	              
	            	  
	              bufferedWriter.write( heap[1]+ " ");
	              bufferedWriter.write( System.getProperty("line.separator")); 
	              heap[1]=-1;
	            
	              bufferedWriter.close();
	              writer.close();
	          } catch (Exception e) {
	              e.printStackTrace();
	          }
	        
	        
	    }
	    void bubbleDown(){
	    	
	    	//starting at the root 
	        int currentindex=1;
	        
	        while (currentindex < heap[0])	{
	            int leftchildindex = currentindex * 2;
	            int rightchildindex = (currentindex * 2) + 1;
	            
	          //sees if index out of bounds

	            if ((rightchildindex > heap[0]))return;
	            //intilaizte min and find it
	            int minindex=0;
	            
	            if (heap[leftchildindex] <= heap[rightchildindex]){
	            	minindex=leftchildindex;
	            }
	            else if (heap[rightchildindex] < heap[leftchildindex]){
	            	minindex=rightchildindex;
	            }
	            
	            	//compare min to current and swap if it is less ,else do nothing        
	            if(heap[currentindex] > heap[minindex]){
	            	int temp = heap[currentindex];
	                heap[currentindex] = heap[minindex];
	                heap[minindex] = temp;
	                
	                currentindex = minindex;
	            }
	           
	            else return;
	            
	        }
	            
	    
	    }
	    
	    void printHeap(String filename){
	    	//prints the first 10 items including size
		       
	    	  try {
	              FileWriter writer = new FileWriter(filename,true);
	              BufferedWriter bufferedWriter = new BufferedWriter(writer);
	              for(int i =0;i<10;i++){
	            	  if(heap[i]==-1)continue;
	            	  
	              bufferedWriter.write( heap[i]+ " ");
	              }
	              bufferedWriter.write( System.getProperty("line.separator"));    
		    	  
	              
	              bufferedWriter.close();
	              writer.close();
	              
	          } catch (Exception e) {
	              e.printStackTrace();
	          }
	        
	            
	    	  
	        
	       // System.out.println();
	    }
	 
public static void main(String args[]) throws FileNotFoundException{
	
	HeapSort HA;
	String filename = args[0];
	String filename2 = args[0];
	String outfilename = args[1];
	String outfilename2 = args[2];
	int count=0;
	Scanner s = null;
	
	//used to clear the output files
	try {
        FileWriter writer = new FileWriter(outfilename,false);
        BufferedWriter bufferedWriter = new BufferedWriter(writer);
        FileWriter writer1 = new FileWriter(outfilename2,false);
        BufferedWriter bufferedWriter1 = new BufferedWriter(writer1);
        
        bufferedWriter.write("" ); 
        bufferedWriter1.write("" );  
  	  
        
        bufferedWriter.close();
        writer.close();
        bufferedWriter1.close();
        writer1.close();
        
    } catch (Exception e) {
        e.printStackTrace();
    }
	
	
	//gets number of elements
	try {
			
            s = new Scanner(new BufferedReader(new FileReader(filename)));

            while (s.hasNextInt()) {
            	
            	count++;	      
            	
                s.nextInt();
            	
            }
        } catch (Exception e){
        	System.out.print(e);
        }
	
	
	
	HA= new HeapSort(count);
	
	s.close();
	
	HA.buildHeap(filename2,outfilename);
	HA.deleteHeap(outfilename,outfilename2);
	System.out.println("Program Success");
	}
}
