/* NiceSimulator.java
   CSC 225 - Summer 2018

   An empty shell of the operations needed by the NiceSimulator
   data structure.

   B. Bird - 06/18/2018
*/


import java.io.*;
import java.util.List;
import java.util.ArrayList;

public class NiceSimulator{

	public static final int SIMULATE_IDLE = -2;
	public static final int SIMULATE_NONE_FINISHED = -1;
	
	private ArrayList<E> nice_time_remain;
	private ArrayList<E> nice_priority;
	/* Constructor(maxTasks)
	   Instantiate the data structure with the provided maximum 
	   number of tasks. No more than maxTasks different tasks will
	   be simultaneously added to the simulator, and additionally
	   you may assume that all task IDs will be in the range
	     0, 1, ..., maxTasks - 1
	*/
	public NiceSimulator(int maxTasks){
		nice_time_remain = new ArrayList<E>(maxTasks);
		nice_priority = new ArrayList<E>(maxTasks);
		
		for(int i=0;i<maxTasks;i++){
			nice_priority.add(null);
			nice_time_remain.add(null);
		}
	}
	
	/* taskValid(taskID)
	   Given a task ID, return true if the ID is currently
	   in use by a valid task (i.e. a task with at least 1
	   unit of time remaining) and false otherwise.
	   
	   Note that you should include logic to check whether 
	   the ID is outside the valid range 0, 1, ..., maxTasks - 1
	   of task indices.
	
	*/
	public boolean taskValid(int taskID){// false - stop program
		if(nice_time_remain.get(taskID)>0)
			return true;
		else
			return false;
	}
	
	/* getPriority(taskID)
	   Return the current priority value for the provided
	   task ID. You may assume that the task ID provided
	   is valid.
	
	*/
	public int getPriority(int taskID){
		
		return nice_priority.get(taskID);
		//return -1;
	}
	
	/* getRemaining(taskID)
	   Given a task ID, return the number of timesteps
	   remaining before the task completes. You may assume
	   that the task ID provided is valid.
	
	*/
	public int getRemaining(int taskID){
		return nice_time_remain.get(taskID);
		//return -1;
	}
	
	
	/* add(taskID, time_required)
	   Add a task with the provided task ID and time requirement
	   to the system. You may assume that the provided task ID is in
	   the correct range and is not a currently-active task.
	   The new task will be assigned nice level 0.
	*/
	public void add(int taskID, int time_required){
		nice_time_remain.set(taskID, time_required);
		nice_priority.set(taskID, 0);
	}
	
	
	/* kill(taskID)
	   Delete the task with the provided task ID from the system.
	   You may assume that the provided task ID is in the correct
	   range and is a currently-active task.
	*/
	public void kill(int taskID){
		nice_time_remain.remove(taskID);
		nice_time_remain.add(taskID, null);
		nice_priority.remove(taskID);
	}
	
	
	/* renice(taskID, new_priority)
	   Change the priority of the the provided task ID to the new priority
       value provided. The change must take effect at the next simulate() step.
	   You may assume that the provided task ID is in the correct
	   range and is a currently-active task.
	
	*/
	public void renice(int taskID, int new_priority){
		nice_priority.set(taskID, new_priority);
	}

	
	/* simulate()
	   Run one step of the simulation:
		 - If no tasks are left in the system, the CPU is idle, so return
		   the value SIMULATE_IDLE.
		 - Identify the next task to run based on the criteria given in the
		   specification (tasks with the lowest priority value are ranked first,
		   and if multiple tasks have the lowest priority value, choose the 
		   task with the lowest task ID).
		 - Subtract one from the chosen task's time requirement (since it is
		   being run for one step). If the task now requires 0 units of time,
		   it has finished, so remove it from the system and return its task ID.
		 - If the task did not finish, return SIMULATE_NONE_FINISHED.
	*/
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	public int simulate(){//////PROBLEMS
		int min = -1;
		int time_remaining;//min is index of array, which has minimum priority.
		//array.size()
		for(int i =0; i<(nice_priority.size()-1); i++){
			if(nice_priority.get(i) != null){
				if(nice_priority.get(i)<= nice_priority.get(i+1))
					min=i;
				else
					min = i+1;
			}	
			
		}
		if(min!= -1){
			time_remaining=nice_time_remain.get(min)-1;
			if(time_remaining == 0){
				kill(min);//problem
				return min;
			}
			else if(time_remaining > 0)
				return SIMULATE_NONE_FINISHED;
		
		}
		else
			return SIMULATE_IDLE;
	}


}
