//Nim game
//There are 13 coins.
//Person picks first(1,2, or 3).
//Computer picks second(1,2, or 3).
//The player who pick the last coin loses.

public class StateNim extends State{

    public int board;
    public int left;

    public StateNim(){
        board=13;
        left = 13;
        player =1;
    }
    public StateNim(StateNim state){
        this.board = state.board;
        this.left = state.left;
        player = state.player;
    }
    public String toString(){
        String ret = "";
        ret+= left + "\n";

        return ret;
    }
    
}