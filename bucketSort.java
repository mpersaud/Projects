
import java.util.Scanner;
import java.io.*;

public class bucketSort {
	int minData=0;
    int maxData=0;
    int offSet=0;
    int bucketSize;
    int []bucketAry;
    
    //constructor
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
    
    
    void printBucketAry(String filename){
    	
    	
    	 try {
             FileWriter writer = new FileWriter(filename,true);
             for (int i =0;i<=18;i++){
                 if(i>=10){
                     writer.write(i+"  ");
                     continue;
                 }
                 writer.write(i+"   ");
                 
             }
             writer.write( System.getProperty("line.separator")); 
             for (int i =0;i<=18;i++){
                 writer.write(bucketAry[i]+"   ");
             }
             writer.close();
             
         } catch (Exception e) {
             e.printStackTrace();
         }
        
    }
    void printSortedData(String filename){
    	try {
            FileWriter writer = new FileWriter(filename,false);
            
            for (int i=0;i<bucketSize;i++){
                int index=i;
                
                while(bucketAry[index]!=0){
                	
                	int t= i + offSet;
                    writer.write(t+ "");
                    writer.write( System.getProperty("line.separator"));
                    bucketAry[index]--;
                }
            }
            writer.close();
            
        } catch (Exception e) {
            e.printStackTrace();
        }
 
    }
    
    int getIndex(int data){
        
        return data-offSet;
    }
    
    static void findMinMax(int[] min, int[] max, int input){
    
        if (input < min[0] )min[0]=input;
        else if (input > max[0] ) max[0] = input;
        else return;
            
    }

    public static  void main (String args[]){
    	
    	String filename = args[0];
    	String outfilename = args[1];
    	String outfilename2 = args[2];
    	int[] min= new int[1];
    	int[] max= new int[1];
    	min[0]=0;
    	max[0]=0;
    	int input =0;
    	Scanner s = null;
    	
	try {
			
            s = new Scanner(new FileReader(filename));
            input= s.nextInt();
            min[0] =input;
            max[0]=input;
            while (s.hasNextInt()) {
            	
            	findMinMax(min,max,input);
            	input= s.nextInt();
            	
            }
        } catch (Exception e){
        	System.out.print(e);
        }
	
	
	int size= max[0]-min[0]+1;
    bucketSort BS = new bucketSort(size,min[0],max[0],min[0]);
	s.close();
	Scanner s1 = null;
	FileWriter writer;
	
	try {
		
        s1 = new Scanner(new FileReader(filename));
        writer = new FileWriter(outfilename2,false);
        while (s1.hasNextInt()) {
        	
        	input= s1.nextInt();
        	int index = BS.getIndex(input);
            BS.bucketAry[index]++;
            
            writer.write(input +" " +index);
            writer.write( System.getProperty("line.separator"));

        }
        writer.close(); 
    } catch (Exception e){
    	System.out.println(e);
    }
	
	 BS.printBucketAry(outfilename2);
	 BS.printSortedData(outfilename);
	
	System.out.println("Program Success");
    }
}
