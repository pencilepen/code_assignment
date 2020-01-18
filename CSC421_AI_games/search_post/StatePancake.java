import java.util.Arrays;

public class StatePancake{

	int[] pancakeArray;
	public StatePancake(int[] pancakeArray){
		this.pancakeArray = pancakeArray;
	}
	
	//It has to be a copy of values not reference because we will 
    //create many states and don't want to overwrite the same array.
	public StatePancake(StatePancake state){
		pancakeArray = new int[6];
		for(int i=0; i<6; i++)
			this.pancakeArray[i] = state.pancakeArray[i];
	}
	
	public boolean equals(Object o){

		 return Arrays.equals(pancakeArray, ((StatePancake) o).pancakeArray);
	}
	
	public int hashcode(){
		 return pancakeArray.hashCode();
	}
	public String toString(){
		return Arrays.toString(pancakeArray);
	}

}