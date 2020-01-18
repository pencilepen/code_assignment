/* Ladder.java
   CSC 225 - Summer 2018
   
   Starter code for Programming Assignment 3

   B. Bird - 06/30/2018
*/


import java.io.*;
import java.util.LinkedList;

public class Ladder{

	
	public static void showUsage(){
		System.err.printf("Usage: java Ladder <word list file> <start word> <end word>\n");
	}
	

	public static void main(String[] args){
		
		//At least four arguments are needed
		if (args.length < 3){
			showUsage();
			return;
		}
		String wordListFile = args[0];
		String startWord = args[1].trim();
		String endWord = args[2].trim();
		
		
		//Read the contents of the word list file into a LinkedList (requires O(nk) time for
		//a list of n words whose maximum length is k).
		//(Feel free to use a different data structure)
		BufferedReader br = null;
		LinkedList<String> words = new LinkedList<String>();
		
		try{
			br = new BufferedReader(new FileReader(wordListFile));
		}catch( IOException e ){
			System.err.printf("Error: Unable to open file %s\n",wordListFile);
			return;
		}
		
		try{
			for (String nextLine = br.readLine(); nextLine != null; nextLine = br.readLine()){
				nextLine = nextLine.trim();
				if (nextLine.equals(""))
					continue; //Ignore blank lines
				//Verify that the line contains only lowercase letters
				for(int ci = 0; ci < nextLine.length(); ci++){
					//The test for lowercase values below is not really a good idea, but
					//unfortunately the provided Character.isLowerCase() method is not
					//strict enough about what is considered a lowercase letter.
					if ( nextLine.charAt(ci) < 'a' || nextLine.charAt(ci) > 'z' ){
						System.err.printf("Error: Word \"%s\" is invalid.\n", nextLine);
						return;
					}
				}
				words.add(nextLine);
			}
		} catch (IOException e){
			System.err.printf("Error reading file\n");
			return;
		}

		/* Find a word ladder between the two specified words. Ensure that the output format matches the assignment exactly. */
			
		
		/* Your code here */

		int length_startword = startWord.length();
		int length_endword = endWord.length();
		if(length_endword!=length_startword){//if there are different length of words 
			return;}
		//System.out.println(length_startword+" "+ length_endword);
		
		//Linkedlist prime_words contains all same length words
		LinkedList<String> prime_words = new LinkedList<String>();
		for(int i = 0 ; i < words.size() ; i++){
			//System.out.println(words.get(i)+" "+words.get(i).length());
			if(words.get(i).length()!=length_startword){
				continue;}
			prime_words.add(words.get(i));
		}
		//done prime_words Linkedlist
		
		int index_startword = prime_words.indexOf(startWord);
		int index_endword = prime_words.indexOf(endWord);
		if (index_startword==-1 || index_endword==-1){
			System.out.println("No word ladder found.");
			return;
		}
		//graph matrix
		//initiation zero
		int matrix[][] = new int[prime_words.size()][prime_words.size()];
		for (int[] x: matrix){
			for (int y: x){
			y=0;}
		}
	
		//find neighbors
		for (int i=0; i<prime_words.size() ;i++){
			for(int j=0; j<prime_words.size();j++){
				int counter = 0;
				for(int k=0; k<length_startword; k++){//compare each characters
					if(prime_words.get(i).charAt(k)!=prime_words.get(j).charAt(k)){
						counter++;
					}
				}//end comparing each characters
				if(counter ==1){
					matrix[i][j]=1;
				}
			}
		}
		////////////////////
		
		//BFS
		LinkedList<String> queue = new LinkedList<String>();
		String[] parent = new String[prime_words.size()];
		for(String x: parent){
			x = null;
		}
		
		queue.add(startWord);
		//System.out.println(queue);
		parent[prime_words.indexOf(startWord)]=startWord;
		String v;
		while(queue.size()!=0){
			
			v = queue.remove(0);
			//System.out.println("__queue remove -||"+v);
			
			for(int i=0; i<prime_words.size(); i++){
				if(matrix[prime_words.indexOf(v)][i]==1){
					if(parent[i] == null){
						parent[i]=v;
						queue.add(prime_words.get(i));
						//System.out.println("__queue add -||"+prime_words.get(i));
					}
				}
			}
		}
		//System.out.println("__queue_-"+queue);
		/*for(int i=0; i<prime_words.size();i++){
System.out.println(prime_words.get(i)+" 's parent: "+parent[i]);}*/
		/////////////////////////////////////////////////////////////////////////////
		LinkedList<String> word_ladder = new LinkedList<String>();
		word_ladder.add(endWord);
		v = endWord;
		while(v!=startWord){
			word_ladder.add(parent[prime_words.indexOf(v)]);
			v = parent[prime_words.indexOf(v)];
			//System.out.println("v:_---: "+v);
			if(v==null){
				break;
			}
		}
		if(word_ladder.get(word_ladder.size()-1)!=startWord){
			System.out.println("No  word ladder found.");
			return;
		}
		//System.out.println("word_ladder: "+word_ladder);
		//System.out.println("word_ladder size: "+word_ladder.size());
		
		for(int i=(word_ladder.size()-1); i>=0; i--){
			System.out.println(word_ladder.get(i));
		}
		
return;
	}

}