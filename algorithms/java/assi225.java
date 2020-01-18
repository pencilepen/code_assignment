/* Ladder.java
   CSC 225 - Summer 2018
   
   Starter code for Programming Assignment 3

   B. Bird - 06/30/2018
*/


import java.io.*;
import java.util.LinkedList;

public class assi225{

	
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
		LinkedList<String> bfs = new LinkedList<String>();
		String[] parent = new String[words.size()];
		int[] tree_level = new int[words.size()];
		for(int y: tree_level){
			y=-1;
		}
		bfs.add(startWord);
		String x = startWord;
		int counter = 0;
		int level=0;
		
		parent[words.indexOf(startWord)]=startWord;
		tree_level[words.indexOf(startWord)]=0;
		while(bfs.size()!=0){
			bfs.remove(0);
			for(int i=0;i<words.size();i++){
				if(words.get(i).length()!=x.length()){
					continue;
				}
				for(int k=0; k<x.length(); k++){//compare each characters
					if(words.get(i).charAt(k)!=x.charAt(k)){
						counter++;
					}
				}
				if (counter==1){

					parent[words.indexOf(words.get(i))]=x;
					//x=words.get(i);
					counter=0;
					tree_level[words.indexOf(words.get(i))]=level;
					bfs.add(words.get(i));
					level++;
				}
			}
			try{
			x=bfs.get(0);
			}
			catch(IndexOutOfBoundsException e){
			break;
			}
			if (x==endWord){
				break;
			}
			
		}
		
		LinkedList<String> word_ladder=new LinkedList<String>();
		word_ladder.add(endWord);
		String v;
		v = endWord;
		while(v!=startWord){
			word_ladder.add(parent[words.indexOf(v)]);
			v = parent[words.indexOf(v)];
			System.out.println("v:_---: "+v);
			if(v==null){
				break;
			}
		}
		word_ladder.add(startWord);
		if(word_ladder.get(word_ladder.size()-1)!=startWord){
			System.out.println("No  word ladder found.");
			return;
		}
		for(int i=(word_ladder.size()-1); i>=0; i--){
			System.out.println(word_ladder.get(i));
		}
return;
	}

}