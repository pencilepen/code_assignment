public class StateCannibals 
{    
    int canArray[];
    
    public StateCannibals(int[] canArray) { this.canArray = canArray; }
    
    //It has to be a copy of values not reference because we will 
    //create many states and don't want to overwrite the same array.
    public StateCannibals(StateCannibals state) {
    	canArray = new int[6];
        for(int i=0; i<6; i++) 
            this.canArray[i] = state.canArray[i];
    }
    
    public boolean equals(Object o) {
        return java.util.Arrays.equals( canArray, ((StateCannibals) o).canArray );
    }
    
    public int hashCode() {
        return java.util.Arrays.hashCode( canArray );
    }    
    
    public String toString() {
    	return java.util.Arrays.toString( canArray );
    }
    
}