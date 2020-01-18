/* Aggregate.java
   CSC 225 - Summer 2018

   Some starter code for programming assignment 1, showing
   the command line argument parsing and the basics of opening
   and reading lines from the CSV file.

   B. Bird - 04/30/2018
*/

import java.util.Arrays;
import java.io.*;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Heap Sort. From Wikipedia, https://zh.wikipedia.org/wiki/%E5%A0%86%E6%8E%92%E5%BA%8F#Java
  
 class HeapSort {
    private String[] arr;
    
    public HeapSort(String[] arr){
        this.arr = arr;
    }
    
    public void sort(){
   
        int len = arr.length - 1;
        int beginIndex = (len - 1) >> 1; 
        for(int i = beginIndex; i >= 0; i--){
            maxHeapify(i, len);
        }
        
        for(int i = len; i > 0; i--){
            swap(0, i);
            maxHeapify(0, i - 1);
        }
    }
    
    private void swap(int i,int j){
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
 
    private void maxHeapify(int index,int len){
        int li = (index << 1) + 1; 
        int ri = li + 1;           
        int cMax = li;             
        
        if(li > len) return;       
        if(ri <= len && arr[ri] > arr[li]) 
            cMax = ri;
        if(arr[cMax] > arr[index]){
            swap(cMax, index);      
            maxHeapify(cMax, len); 
        }
    }

    
}
public class Aggregate{

	
	public static void showUsage(){
		System.err.printf("Usage: java Aggregate <function> <aggregation column> <csv file> <group column 1> <group column 2> ...\n");
		System.err.printf("Where <function> is one of \"count\", \"count_distinct\", \"sum\", \"avg\"\n");	
	}
	

	public static void main(String[] args){
		int i=0;
		int j=0;
		
		//At least four arguments are needed
		if (args.length < 4){
			showUsage();
			return;
		}
		String agg_function = args[0];
		String agg_column = args[1];
		String csv_filename = args[2];
		String[] group_columns = new String[args.length - 3];
		for(int i = 3; i < args.length; i++)
			group_columns[i-3] = args[i];
		
		if (!agg_function.equals("count") && !agg_function.equals("count_distinct") && !agg_function.equals("sum") && !agg_function.equals("avg")){
			showUsage();
			return;
		}
		///////////////////command distinguish above
		
		//Open file
		BufferedReader br = null;																	////////////	BufferedReader
																									////////////
		try{																						////////////
			br = new BufferedReader(new FileReader(csv_filename));									////////////	FileReader
		}catch( IOException e ){																	////////////	IOException
			System.err.printf("Error: Unable to open file %s\n",csv_filename);						////////////
			return;																					////////////	readLine
		}																							////////////	split
		
		//////////First Read header
		String header_line;
		try{			//report error??
			header_line = br.readLine(); //The readLine method returns either the next line of the file or null (if the end of the file has been reached)
		} catch (IOException e){
			System.err.printf("Error reading file\n", csv_filename);
			return;
		}
		
		if (header_line == null){
			System.err.printf("Error: CSV file %s has no header row\n", csv_filename);
			return;
		}
		
		//Split the header_line string into an array of string values using a comma
		//as the separator.
		String[] column_names = header_line.split(",");////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		
		//As a diagnostic, print out all of the argument data and the column names from the CSV file
		//(for testing only: delete this from your final version)
		
/*		System.out.println("Aggregation function: "+agg_function);
		System.out.println("Aggregation column: "+agg_column);
		
		
		for (String s: group_columns)
			System.out.println("Grouping column: "+s);
		System.out.println();
		
		for (String s: column_names)
			System.out.println("CSV column name: "+s);
			
		
*/	//--		//... Your code here .../////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*while(header_line!=null){
			try{			//report error??
			header_line = br.readLine(); //The readLine method returns either the next line of the file or null (if the end of the file has been reached)
		} catch (IOException e){
			System.err.printf("Error reading file\n", csv_filename);
			return;
		}
			System.out.println(header_line);
		}*/
		
		
		
		////////////////////////////////////////////////////////////////////////////////////////////////
		/*String[] group_columns = new String[args.length - 3];
		
		//
		try{			//report error??
			header_line = br.readLine(); //The readLine method returns either the next line of the file or null (if the end of the file has been reached)
		} catch (IOException e){
			System.err.printf("Error reading file\n", csv_filename);
			return;
		}
		
		//
		String[] column_names = header_line.split(",");*/
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int x_axis=column_names.length;// First read ;first header
		
		int y_axis=1;
		while (header_line!=null){
			
			try{			
				header_line = br.readLine(); 
			} catch (IOException e){
				System.err.printf("Error reading file\n", csv_filename);
				return;
			}
			if(!header_line.isEmpty())/////************
				y_axis++;
			column_names = header_line.split(",");//??
			if(column_names.length!=x_axis){
				System.err.printf("Error: CSV file %s has no header row\n", csv_filename);
				return;
			}
		}
		
		br.close();
	/////
		
		String[][] data=new String[x_axis][y_axis];;
		//open again	x
		try{																						
			br = new BufferedReader(new FileReader(csv_filename));									
		}catch( IOException e ){																	
			System.err.printf("Error: Unable to open file %s\n",csv_filename);						
			return;																					
		}	
		
		//read header
		String rows;
		try{			
			rows = br.readLine(); 
		} catch (IOException e){
			System.err.printf("Error reading file\n", csv_filename);
			return;
		}
		//read data
		int j=0;
		int index=0;
		while(rows!=null){//store file in data[][]
		
			try{
				rows=br.readLine();
			}catch(IOException e){
				System.err.printf("Error reading file\n",csv_filname);
				return;
			}
			String[] data_row  = rows.split(",");
			
			 i=0;
			while(i<x_axis){
				data[i][index]=data_row[i];
				i++;
			}
			index++;
		}
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		public static void sortingdata(String agg_column,String[] group_columns){
			int[] gc_index= new int[group_columns.length+1];
			
			for(i=0;i<x_axis;i++){
				if(agg_column==data[i][0])
					gc_index[gc_index.length-1]=i;
			}
			for(i=0;i<(group_columns.length-1);i++){
				for(j=0;j<x_axis;j++){
					if(group_columns[i]==data[j][0]){
						gc_index[i]=j;
					}
					
				}
			}
			////////int gc_index[0]==agg_column;   int gc_index[1,2,3...]==group_columns;   data[gc_index[1]][0]
			string[][] count_data= new string[gc_index.length][y_axis];//copy argument data to count_data
			for(j=0;j<gc_index.lenght;j++){
				for(i=0;i<y_axis;i++)
					count_data[j][i]=data[gc_index[j]][i];
			}
			String[] data_sort=new String[y_axis-1];
			for(j=1;j<y_axis-1;j++){
				for(i=0;i<group_columns.length-1;i++)
					data_sort[j-1]=data_sort[j-1]+count_data[i][j]+ ",";
			}
				
			//////
			HeapSort hello2=new HeapSort();
			hello2(data_sort).sort();  
			 
			 String[][] twoDSD= new String[gc_index.length][data_sort.length]; 
			 for(i=0;i<y_axis-1;i++){
				
				 String[] column_names = data_sort[i].split(",");
				 for(j=0;j<gc_index.length;j++)
					twoDSD[i][j]=column_names[j];
			 }
			 
			 
			}

		public  void count(String[] data_sort,String[][] twoDSD){
			
			////count_data[0][i] is agg_column
			//output
			for(j=1;j<gc_index.length;j++){//print head
				System.out.print(count_data[j][0]+",")；
			}
			System.out.println(count_data[0][0]);
			
			
			;//print data
			
			j=0;
			for(i=0;i<y_axis-1;i++){
				if(data_sort[j]!=data_sort[i]){
					for(int k=0;k<gc_index.length;k++)
						System.out.print(twoDSD[k][i-1]+",");
					System.out.println(i-j);
					j=i;
				}
			}
			if (j=0){
				
				for(int k=0;k<gc_index.length;k++)
						System.out.print(twoDSD[k][i-1]+",");
				System.out.println(i-j);
			}////all data are same above
			
			
		}
		////////////////////////////////////////////////////////
		public  void sum(String[] data_sort,String[][] twoDSD){
			double d,sumD;
			for(j=1;j<gc_index.length;j++){//print head
				System.out.print(count_data[j][0]+",")；
			}
			System.out.println(count_data[0][0]);
			//print data
			j=0;
			for(i=0;i<y_axis-1;i++){
				if(data_sort[j]!=data_sort[i]){
					for(int k=0;k<gc_index.length;k++)
						System.out.print(twoDSD[k][i-1]+",");
					for(int k=0;k<(i-j);k++){
						 d=Double.parseDouble(twoDSD[gc_index.length-1][k]);
						 sumD+=d;
						System.out.println(sumD);
					}
						
					j=i;
				}
			}
			if (j=0){
				
				System.out.print(data_sort[i-1]);
				for(int k=0;k<i;k++){
						 d=Double.parseDouble(twoDSD[gc_index.length-1][k]);
						 sumD+=d;
						System.out.println(sumD);
					}
				
			}////all data are same above
			
		}
		////////////////////////////////////////////////////////////////////////////////////
		public  void avg(String[] data_sort,String[][] twoDSD){
			double d, sumD,avgD;
			for(j=1;j<gc_index.length;j++){//print head
				System.out.print(count_data[j][0]+",")
			}
			System.out.println(count_data[0][0]);
			//print data
			j=0;
			for(i=0;i<y_axis-1;i++){
				if(data_sort[j]!=data_sort[i]){
					for(int k=0;k<gc_index.length;k++)
						System.out.print(twoDSD[k][i-1]+",");
					for(int k=0;k<(i-j);k++){
						 d=Double.parseDouble(twoDSD[gc_index.length-1][k]);
						 sumD += d;
						 avgD=sumD/(i-j);
						System.out.println(avgD);
					}
						
					j=i;
				}
			}
			if (j=0){
				
				System.out.print(data_sort[i-1]);
				for(int k=0;k<i;k++){
						 d=Double.parseDouble(twoDSD[gc_index.length-1][k]);
						 sumD+=d;
						 avgD=sumD/(i-j);
						System.out.println(avgD);
					}
				
			}////all data are same above
		}
		//////////////////////////////////////////////////////////////////////////////////
		public  void count_distinct(String[] data_sort,String[][] twoDSD){
			////count_data[0][i] is agg_column
			//output
			for(j=1;j<gc_index.length;j++){//print head
				System.out.print(count_data[j][0]+",");
			}
			System.out.println(count_data[0][0]);
			
			
			;//print data
			int c_dCount=0;
			j=0;
			for(i=0;i<y_axis-1;i++){
				if(data_sort[j]!=data_sort[i]){
					for(int k=0;(k+1)<(i-j);k+=2){
						if(twoDSD[gc_index.length-1][k]==twoDSD[gc_index.length-1][k+1])
							c_dCount++;
					}
					for(int k=0;k<gc_index.length;k++)
						System.out.print(twoDSD[k][i-1]+",");
					System.out.println(i-j-c_dCount);
					j=i;
				}
			}
			if (j=0){
				for(int k=0;(k+1)<(i-j);k+=2){
						if(twoDSD[gc_index.length-1][k]==twoDSD[gc_index.length-1][k+1])
							c_dCount++;
					}
				for(int k=0;k<gc_index.length;k++)
						System.out.print(twoDSD[k][i-1]+",");
				System.out.println(i-j-c_dCount);
			}////all data are same above
			
		}
		////////////////////////////////////////////////////////////////////////////////////
		Aggregate hello1= new Aggregate();
		hello1.sortingdata(agg_column,group_columns);
		Aggregate hello = new Aggregate();
		switch(agg_function){
			case "count":{
				
				hello.count(data_sort,twoDSD);
			}
			break;
			case "count_distinct": hello.count_distinct(data_sort,twoDSD);
			break;
			case "sum": hello.sum(data_sort,twoDSD);
			break;
			case "avg":hello.avg(data_sort,twoDSD);
		}


	}
}