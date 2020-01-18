import java.util.HashSet;
import java.util.Set;

public class PW extends Problem{
	//static final int wolf_array_size = 8;
	static final int boatL = 0;
	static final int cabbageL = 1;
	static final int goatL =2;
	static final int wolfL =3;
	static final int boatR =4;
	static final int cabbageR =5;
	static final int goatR = 6;
	static final int wolfR = 7;
	
	boolean goal_test(Object state){
		StateWolf wolf_state = (StateWolf) state;
		
		if( wolf_state.wolfArray[boatL]==0 && wolf_state.wolfArray[cabbageL]==0 &&
			wolf_state.wolfArray[goatL]==0 && wolf_state.wolfArray[wolfL]==0 &&
			wolf_state.wolfArray[boatR]==1 && wolf_state.wolfArray[cabbageR]==1 &&
			wolf_state.wolfArray[goatR]==1 && wolf_state.wolfArray[wolfR]==1 ){
			return true;}
		else 
			return false;
	}
	Set<Object> getSuccessors(Object state){

		Set<Object> set = new HashSet<Object>();
    	StateWolf wolf_state = (StateWolf) state;
		StateWolf s_state;
		
		//cabbage from left to right
		s_state = new StateWolf(wolf_state);
		if(s_state.wolfArray[boatL]==1){
			s_state.wolfArray[boatL] -= 1;
			s_state.wolfArray[boatR]+=1;
			s_state.wolfArray[cabbageL]-=1;
			s_state.wolfArray[cabbageR]+=1;
			if(isValid(s_state)){ set.add(s_state); }
		}
		
		//cabbage from right to left
		s_state = new StateWolf(wolf_state);
		if(s_state.wolfArray[boatR]==1){
			s_state.wolfArray[boatL]+=1;
			s_state.wolfArray[boatR]-=1;
			s_state.wolfArray[cabbageL]+=1;
			s_state.wolfArray[cabbageR]-=1;
			if(isValid(s_state)){ set.add(s_state); }
		}
		
		//goat from left to right
		s_state = new StateWolf(wolf_state);
		if(s_state.wolfArray[boatL]==1){
			s_state.wolfArray[boatL] -= 1;
			s_state.wolfArray[boatR]+=1;
			s_state.wolfArray[goatL]-=1;
			s_state.wolfArray[goatR]+=1;
			if(isValid(s_state)){ set.add(s_state); }
		}
		
		//goat from right to left
		s_state = new StateWolf(wolf_state);
		if(s_state.wolfArray[boatR]==1){
			s_state.wolfArray[boatL]+=1;
			s_state.wolfArray[boatR]-=1;
			s_state.wolfArray[goatL]+=1;
			s_state.wolfArray[goatR]-=1;
			if(isValid(s_state)){ set.add(s_state); }
		}
		
		//wolf from left to right
		s_state = new StateWolf(wolf_state);
		if(s_state.wolfArray[boatL]==1){
			s_state.wolfArray[boatL] -= 1;
			s_state.wolfArray[boatR]+=1;
			s_state.wolfArray[wolfL]-=1;
			s_state.wolfArray[wolfR]+=1;
			if(isValid(s_state)){ set.add(s_state); }
		}
		
		//wolf from right to left
		s_state = new StateWolf(wolf_state);
		if(s_state.wolfArray[boatR]==1){
			s_state.wolfArray[boatL]+=1;
			s_state.wolfArray[boatR]-=1;
			s_state.wolfArray[wolfL]+=1;
			s_state.wolfArray[wolfR]-=1;
			if(isValid(s_state)){ set.add(s_state); }
		}
		
		//boat from left to right
		s_state = new StateWolf(wolf_state);
		if(s_state.wolfArray[boatL]==1){
			s_state.wolfArray[boatL] -= 1;
			s_state.wolfArray[boatR]+=1;
			if(isValid(s_state)){ set.add(s_state); }
		}
		//boat from left to right
		s_state = new StateWolf(wolf_state);
		if(s_state.wolfArray[boatR]==1){
			s_state.wolfArray[boatL]+=1;
			s_state.wolfArray[boatR]-=1;
			if(isValid(s_state)){ set.add(s_state); }
		}
		return set;

	}
	private boolean isValid(StateWolf state){
		for(int i=0; i<8; i++){
			if(state.wolfArray[i]<0 || state.wolfArray[i]>1)
				return false;
		}
		if(state.wolfArray[boatL] == state.wolfArray[boatR] || 
			state.wolfArray[cabbageL] == state.wolfArray[cabbageR] ||
			state.wolfArray[goatL] == state.wolfArray[goatR] ||
			state.wolfArray[wolfL] == state.wolfArray[wolfR] )
				return false;
	
		if(state.wolfArray[boatL]==1){
			if(state.wolfArray[cabbageR] == 1 && state.wolfArray[goatR] ==1){
				return false;
			}
			if(state.wolfArray[wolfR] == 1 && state.wolfArray[goatR] ==1)
				return false;
		}
		if(state.wolfArray[boatR]==1){
			if(state.wolfArray[cabbageL] == 1 && state.wolfArray[goatL] ==1){
				return false;
			}
			if(state.wolfArray[wolfL] == 1 && state.wolfArray[goatL] ==1)
				return false;
		}
		   
		return true;
		
	}
	double step_cost(Object fromState, Object toState){return 1;}
	
	public double h(Object state) {return 0;}
	
	public static void main(String[] args) throws Exception {
		PW problem = new PW();
		int[] wolfArray = {1,1,1,1,0,0,0,0};
		problem.initialState = new StateWolf(wolfArray);

		Search search  = new Search(problem);
		
		System.out.println("TreeSearch------------------------");
		System.out.println("BreadthFirstTreeSearch:\t\t" + search.BreadthFirstTreeSearch());
		System.out.println("UniformCostTreeSearch:\t\t" + search.UniformCostTreeSearch());
		System.out.println("DepthFirstTreeSearch:\t\t" + search.DepthFirstTreeSearch());
		System.out.println("GreedyBestFirstTreeSearch:\t" + search.GreedyBestFirstTreeSearch());
		System.out.println("AstarTreeSearch:\t\t" + search.AstarTreeSearch());
		
		System.out.println("\n\nGraphSearch----------------------");
		System.out.println("BreadthFirstGraphSearch:\t" + search.BreadthFirstGraphSearch());
		System.out.println("UniformCostGraphSearch:\t\t" + search.UniformCostGraphSearch());
		System.out.println("DepthFirstGraphSearch:\t\t" + search.DepthFirstGraphSearch());
		System.out.println("GreedyBestGraphSearch:\t\t" + search.GreedyBestFirstGraphSearch());
		System.out.println("AstarGraphSearch:\t\t" + search.AstarGraphSearch());
		
		System.out.println("\n\nIterativeDeepening----------------------");
		System.out.println("IterativeDeepeningTreeSearch:\t" + search.IterativeDeepeningTreeSearch());
		System.out.println("IterativeDeepeningGraphSearch:\t" + search.IterativeDeepeningGraphSearch());
	}
  
	
}