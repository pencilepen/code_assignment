
import java.util.HashSet;
import java.util.Set;

public class ProblemWaterJug extends Problem {

    static final int large = 0;
    static final int medium = 1;
    static final int small = 2;

    boolean goal_test(Object state) {
        StateWaterJug jug_state = (StateWaterJug) state;

        if (jug_state.JugArray[large] == 1 || jug_state.JugArray[medium] == 1 || jug_state.JugArray[small] == 1) {
            return true;
        } else {
            return false;
        }
    }

    Set<Object> getSuccessors(Object state) {

        Set<Object> set = new HashSet<Object>();
        StateWaterJug jug_state = (StateWaterJug) state;

        //Let's create without any constraint, then remove the illegal ones
        StateWaterJug successor_state;

        //fill up large
        successor_state = new StateWaterJug(jug_state);
        successor_state.JugArray[large] = 12;
        if (isValid(successor_state)) {
            set.add(successor_state);
        }

        //fill up medium
        //TODO        
        successor_state = new StateWaterJug(jug_state);
        successor_state.JugArray[medium] = 8;
        if (isValid(successor_state)) {
            set.add(successor_state);
        }

        //fill up small
        //TODO
        successor_state = new StateWaterJug(jug_state);
        successor_state.JugArray[small] = 3;
        if (isValid(successor_state)) {
            set.add(successor_state);
        }

        //empty large
        //TODO        
        successor_state = new StateWaterJug(jug_state);
        successor_state.JugArray[large] = 0;
        if (isValid(successor_state)) {
            set.add(successor_state);
        }

        //empty medium
        //TODO
        successor_state = new StateWaterJug(jug_state);
        successor_state.JugArray[medium] = 0;
        if (isValid(successor_state)) {
            set.add(successor_state);
        }

        //empty small
        //TODO
        successor_state = new StateWaterJug(jug_state);
        successor_state.JugArray[small] = 0;
        if (isValid(successor_state)) {
            set.add(successor_state);
        }

        // large to small 
        //TODO
        successor_state = new StateWaterJug(jug_state);
        if (successor_state.JugArray[small] + successor_state.JugArray[large] >= 3) {
            successor_state.JugArray[large] -= (3 - successor_state.JugArray[small]);
            successor_state.JugArray[small] = 3;
            if (isValid(successor_state)) {
                set.add(successor_state);
            }
        }

        //medium to small
        //TODO
        successor_state = new StateWaterJug(jug_state);
        if (successor_state.JugArray[small] + successor_state.JugArray[medium] >= 3) {
            successor_state.JugArray[medium] -= (3 - successor_state.JugArray[small]);
            successor_state.JugArray[small] = 3;
            if (isValid(successor_state)) {
                set.add(successor_state);
            }
        }

        //all large to small 
        //TODO
        successor_state = new StateWaterJug(jug_state);
        if (successor_state.JugArray[small] + successor_state.JugArray[large] < 3) {
            successor_state.JugArray[small] += successor_state.JugArray[large];
            successor_state.JugArray[large] = 0;

            if (isValid(successor_state)) {
                set.add(successor_state);
            }
        }

        //all medium to small
        //TODO
        successor_state = new StateWaterJug(jug_state);
        if (successor_state.JugArray[small] + successor_state.JugArray[medium] < 3) {
            successor_state.JugArray[small] += successor_state.JugArray[medium];
            successor_state.JugArray[medium] = 0;

            if (isValid(successor_state)) {
                set.add(successor_state);
            }
        }

        //large to medium 
        //TODO
        successor_state = new StateWaterJug(jug_state);
        if (successor_state.JugArray[medium] + successor_state.JugArray[large] >= 8) {
            successor_state.JugArray[large] -= (8 - successor_state.JugArray[medium]);
            successor_state.JugArray[medium] = 8;
            if (isValid(successor_state)) {
                set.add(successor_state);
            }
        }
        //small to medium
        //TODO
        successor_state = new StateWaterJug(jug_state);
        if (successor_state.JugArray[medium] + successor_state.JugArray[small] >= 8) {
            successor_state.JugArray[small] -= (8 - successor_state.JugArray[medium]);
            successor_state.JugArray[medium] = 8;
            if (isValid(successor_state)) {
                set.add(successor_state);
            }
        }
        // all large to medium
        //TODO
        successor_state = new StateWaterJug(jug_state);
        if (successor_state.JugArray[medium] + successor_state.JugArray[large] < 8) {
            successor_state.JugArray[medium] += successor_state.JugArray[large];
            successor_state.JugArray[large] = 0;

            if (isValid(successor_state)) {
                set.add(successor_state);
            }
        }
        // all small to medium 
        // TODO
        successor_state = new StateWaterJug(jug_state);
        if (successor_state.JugArray[medium] + successor_state.JugArray[small] < 8) {
            successor_state.JugArray[medium] += successor_state.JugArray[small];
            successor_state.JugArray[small] = 0;

            if (isValid(successor_state)) {
                set.add(successor_state);
            }
        }

        // small to large
        //TODO
        successor_state = new StateWaterJug(jug_state);
        if (successor_state.JugArray[small] + successor_state.JugArray[large] >= 12) {
            successor_state.JugArray[small] -= (12 - successor_state.JugArray[large]);
            successor_state.JugArray[large] = 12;
            if (isValid(successor_state)) {
                set.add(successor_state);
            }
        }

        //medium to large
        //TODO
        successor_state = new StateWaterJug(jug_state);
        if (successor_state.JugArray[medium] + successor_state.JugArray[large] >= 12) {
            successor_state.JugArray[medium] -= (12 - successor_state.JugArray[large]);
            successor_state.JugArray[large] = 12;
            if (isValid(successor_state)) {
                set.add(successor_state);
            }
        }
        // all small to large
        //TODO
        successor_state = new StateWaterJug(jug_state);
        if (successor_state.JugArray[large] + successor_state.JugArray[small] < 12) {
            successor_state.JugArray[large] += successor_state.JugArray[small];
            successor_state.JugArray[small] = 0;

            if (isValid(successor_state)) {
                set.add(successor_state);
            }
        }
        // all medium to large
        //TODO
        successor_state = new StateWaterJug(jug_state);
        if (successor_state.JugArray[large] + successor_state.JugArray[medium] < 12) {
            successor_state.JugArray[large] += successor_state.JugArray[medium];
            successor_state.JugArray[medium] = 0;

            if (isValid(successor_state)) {
                set.add(successor_state);
            }
        }

        return set;
    }

    private boolean isValid(StateWaterJug state) {
        //Checking to see if any element of the array is negative 
        for (int i = 0; i < 3; i++) {
            if (state.JugArray[i] < 0) {
                return false;
            }
        }

        // check if water is over the jug
        if (state.JugArray[large] > 12 || state.JugArray[medium] > 8 || state.JugArray[small] > 3) {

            return false;
        }
        return true;
    }

    double step_cost(Object fromState, Object toState) {
        StateWaterJug from = (StateWaterJug) fromState;
        StateWaterJug to = (StateWaterJug) toState;
        
        for (int i = 0; i < 3; i++) {
            if(to.JugArray[i]!=from.JugArray[i]){
                
              return Math.abs(to.JugArray[i]- from.JugArray[i]);
                
            }
        }
        return 999;// as positive infinity
    }

    public double h(Object state) {
        return 0;
    }

    public static void main(String[] args) throws Exception {
        ProblemWaterJug problem = new ProblemWaterJug();
        int[] JugArray = {0, 0, 0,};
        problem.initialState = new StateWaterJug(JugArray);

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
