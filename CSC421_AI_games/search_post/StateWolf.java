import java.util.Arrays;

public class StateWolf{

	int wolfArray[];
	static final int wolf_array_size=8;
	public StateWolf(int[] wolfArray){
		this.wolfArray = wolfArray;
	}
	
	//It has to be a copy of values not reference because we will 
    //create many states and don't want to overwrite the same array.
	public StateWolf(StateWolf state){
		wolfArray = new int[wolf_array_size];
		for(int i=0; i<wolf_array_size; i++)
			this.wolfArray[i] = state.wolfArray[i];
	}
	
	public boolean equals(Object o){

		 return Arrays.equals(wolfArray, ((StateWolf) o).wolfArray);
	}
	
	public int hashcode(){
		 return wolfArray.hashCode();
	}
	public String toString(){
		return Arrays.toString(wolfArray);
	}
	
}