import java.util.HashSet;
import java.util.Set;

public class ProblemPancake extends Problem {
	
	boolean goal_test(Object state){
		StatePancake pancake_state = (StatePancake) state;
		
		if(pancake_state.pancakeArray[0]==0&&pancake_state.pancakeArray[1]==1
		&&pancake_state.pancakeArray[2]==2&&pancake_state.pancakeArray[3]==3
		&&pancake_state.pancakeArray[4]==4&&pancake_state.pancakeArray[5]==5){
			return true;}
		else
			return false;
	}
	
	Set<Object> getSuccessors(Object state){
		Set<Object> set = new HashSet<Object>();
		StatePancake pancake_state = (StatePancake) state;
		StatePancake ps = new StatePancake(pancake_state); //successor state
		
		//flip function's parameters
		int i=0,j=0;
		//flip 6 pancakes
		flip(i,j,6,pancake_state,ps,set);

		//flip 5 pancakes
		flip(i,j,5,pancake_state,ps,set);

		//flip 4 pancakes
		flip(i,j,4,pancake_state,ps,set);

		//flip 3 pancakes
		flip(i,j,3,pancake_state,ps,set);
		
		//flip 2 pancakes
		flip(i,j,2,pancake_state,ps,set);

		return set;
	}
	
	private void flip(int i, int j, int num_of_pan,StatePancake pancake_state, StatePancake ps, Set<Object> set){
		ps = new StatePancake(pancake_state);
		i=num_of_pan-1;
		for(j=0;j<num_of_pan;j++){
			ps.pancakeArray[j] = pancake_state.pancakeArray[i];
			i--;
		}
		set.add(ps);
	}

	double step_cost(Object formState, Object toState){return 1;};
	
	public double h(Object state) {return 0;}
	
	public static void main(String[] args) throws Exception{
		ProblemPancake problem = new ProblemPancake();
		int[] PancakeArray = {1,0,3,5,2,4};
		
		problem.initialState = new StatePancake(PancakeArray);
	
		Search search = new Search(problem);
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