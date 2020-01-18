import java.util.Arrays;

public class StateWaterJug 
{    
    int JugArray[];
    
    public StateWaterJug (int[] JugArray) { this.JugArray = JugArray; }
    
    //It has to be a copy of values not reference because we will 
    //create many states and don't want to overwrite the same array.
    public StateWaterJug(StateWaterJug state){
		JugArray = new int[3];
		for(int i=0; i<3; i++)
			this.JugArray[i] = state.JugArray[i];
	}
	
	public boolean equals(Object o){

		 return Arrays.equals(JugArray, ((StateWaterJug) o).JugArray);
	}
	
	public int hashcode(){
		 return JugArray.hashCode();
	}
	public String toString(){
		return Arrays.toString(JugArray);
	}

}