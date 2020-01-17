import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.Set;

public class GameNim extends Game {
    int max_remove= 3;
    int WinningScore = 10;
    int LosingScore = -10;
    int NeutralScore = 0;

    public GameNim() {
        currentState = new StateNim();
        StateNim state = (StateNim) currentState;
        System.out.println("Total: "+state.toString());
    }

    public boolean isWinState(State state){//////////?????????? wrong

        StateNim tstate = (StateNim) state;
        if (tstate.left == 1)
            return true;
        else
            return false;
    }

    public boolean isStuckState(State state){
        if(isWinState(state))
            return false;

        StateNim tstate = (StateNim) state;
        if(tstate.left>=1)
            return false;
        
        return true;
    }

    public Set<State> getSuccessors(State state){
        if(isWinState(state) || isStuckState(state))
            return null;

        Set<State> successors = new HashSet<State>();
        StateNim tstate = (StateNim) state;

        StateNim successor_state;
        
        for(int i=1; i<max_remove+1; i++){
            successor_state = new StateNim(tstate);
            successor_state.left -=i;
            successor_state.player = (state.player==0 ? 1 : 0); 
            successors.add(successor_state);
        }

        return successors;
    }

    public double eval(State state){
        if(isWinState(state)){
            int previous_player = (state.player == 0?1:0);
            if(previous_player == 0)
                return WinningScore;
            else    
                return LosingScore;
        }
        return NeutralScore;
    }

    public static void main(String[] args) throws Exception{
        GameNim game = new GameNim();
        Search search = new Search(game);
        int depth = 8;

        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        while(true){
            StateNim nextState = null;

            switch(game.currentState.player){
                case 1://human
                    System.out.print("Enter your *valid* move>");
                    int person_move = Integer.parseInt( in.readLine() );
                    nextState = new StateNim((StateNim)game.currentState);
                    nextState.player=1;
                    nextState.left -= person_move;
                    System.out.println("Human's left: " + nextState);
                    break;

                case 0://computer
                    nextState = (StateNim)search.bestSuccessorState(depth);
                    nextState.player = 0;
                    System.out.println("Computer's left: " + nextState);
                    break;                    
            }

            game.currentState = nextState;
            game.currentState.player = (game.currentState.player == 0 ? 1 : 0);

            // if(game.isStuckState(game.currentState)){

            //     if(game.isWinState(game.currentState)){
            //         if(game.currentState.player == 1)
            //             System.out.println("Computer wins!");
            //         else 
            //             System.out.println("You win!");
            //         break;
            //     }
            // }
            if ( game.isWinState(game.currentState) ) {
            
            	if (game.currentState.player == 1) //i.e. last move was by the computer
            		System.out.println("Computer wins!");
            	else
            		System.out.println("You win!");
            	
            	break;
            }
            
            if ( game.isStuckState(game.currentState) ) { 
            	System.out.println("Cat's game!");
            	break;
            }

            
           
        }

        



        
    }

}