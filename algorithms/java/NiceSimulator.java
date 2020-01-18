/* NiceSimulator.java
   CSC 225 - Summer 2018

   An empty shell of the operations needed by the NiceSimulator
   data structure.

   B. Bird - 06/18/2018
*/


import java.io.*;
//import java.util.List;
//import java.util.ArrayList;

public class NiceSimulator{

	public static final int SIMULATE_IDLE = -2;
	public static final int SIMULATE_NONE_FINISHED = -1;
	
	public int[] nice_priority;//store priority value
	public int[] nice_time_remain;//store time requirement
	public int[] nice_task_id;//store task ID, elements are -1 which doesn't store id
	public int index = -1;
	
	/* Constructor(maxTasks)
	   Instantiate the data structure with the provided maximum 
	   number of tasks. No more than maxTasks different tasks will
	   be simultaneously added to the simulator, and additionally
	   you may assume that all task IDs will be in the range
	     0, 1, ..., maxTasks - 1
	*/
	public NiceSimulator(int maxTasks){
		
		nice_priority = new int[maxTasks];
		nice_time_remain = new int[maxTasks];
		nice_task_id = new int[maxTasks];
		for(int i=0;i<maxTasks;i++){
			nice_priority[i]=0;
			nice_time_remain[i]=0;
			nice_task_id[i]= -1;
			
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
		//if(nice_time_remain.get(taskID)>0)
		if(nice_time_remain[taskID]>0)
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
		return nice_priority[taskID];
		//return nice_priority.get(taskID);
		//return -1;
	}
	
	/* getRemaining(taskID)
	   Given a task ID, return the number of timesteps
	   remaining before the task completes. You may assume
	   that the task ID provided is valid.
	
	*/
	public int getRemaining(int taskID){
		return nice_time_remain[taskID];
		//return nice_time_remain.get(taskID);
		//return -1;
	}
	
	
	/* add(taskID, time_required)
	   Add a task with the provided task ID and time requirement
	   to the system. You may assume that the provided task ID is in
	   the correct range and is not a currently-active task.
	   The new task will be assigned nice level 0.
	*/
	public void add(int taskID, int time_required){
		index++;// = "number of tasks" - 1
		nice_time_remain[taskID]= time_required;
		nice_priority[taskID]=0;
		nice_task_id[index]=taskID;
		heapsort(0,index);
		
	}
	
	
	/* kill(taskID)
	   Delete the task with the provided task ID from the system.
	   You may assume that the provided task ID is in the correct
	   range and is a currently-active task.
	*/
	public void kill(int taskID){
		//find taskID in nice_task_id
		int order = find_id(0, index, taskID);// order is an index of taskID in nice_task_id
		nice_task_id[order]=nice_task_id[index];
		nice_task_id[index] = -1;
		index--;
		
		heapsort(0,index);
		
	}
	
	
	/* renice(taskID, new_priority)
	   Change the priority of the the provided task ID to the new priority
       value provided. The change must take effect at the next simulate() step.
	   You may assume that the provided task ID is in the correct
	   range and is a currently-active task.
	
	*/
	public void renice(int taskID, int new_priority){
		nice_priority[taskID]=new_priority;
		heapsort(0,index);
		//////////////////////////
		//System.out.printf("Renice after Heap sort.\n");
		//nice_priority.set(taskID, new_priority);
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
	public int simulate(){
		if(nice_task_id[0] == -1){
			return SIMULATE_IDLE;
		}
		else{
			nice_time_remain[nice_task_id[0]]-=1;
			if (nice_time_remain[nice_task_id[0]] == 0){
				int task_idnp = nice_task_id[0];
				kill(task_idnp);
				//runing time of finding task_idnp from nice_task_id array is 1,
				//because index is 0,
				return task_idnp;
			}
			else if (nice_task_id[0] == -1)
				return SIMULATE_IDLE;
			else 
				return SIMULATE_NONE_FINISHED;
			
		}
		
	}
	public void heapsort(int root, int bottom){
		int parent;
		if (bottom > root){
			parent = bottom/2;
			//System.out.printf("parent: %d\n",parent);
			if (nice_priority[nice_task_id[parent]] > nice_priority[nice_task_id[bottom]]){
				int temp = nice_task_id[bottom];
				nice_task_id[bottom] = nice_task_id[parent];
				nice_task_id[parent] = temp;
				heapsort(parent, bottom);
			}
			else if (nice_priority[nice_task_id[parent]] == nice_priority[nice_task_id[bottom]]){
				if(nice_task_id[parent] > nice_task_id[bottom]){
					int temp = nice_task_id[bottom];
					nice_task_id[bottom] = nice_task_id[parent];
					nice_task_id[parent] = temp;
					heapsort(parent, bottom);
				}
			}
			heapsort(root, parent);
			//System.out.print("Heap sort done\n");
		}		
	}
	public int find_id(int first, int last, int taskID){
		int order = (first + last)/2;
		if (nice_priority[taskID] < nice_priority[nice_task_id[order]]){
			return find_id(first, order, taskID);
		}
		else if (nice_priority[taskID] > nice_priority[nice_task_id[order]])
			return find_id(order, last, taskID);
		else{// may priority of all tasks are same.
			if(taskID < nice_task_id[order])
				return find_id(first, (last-2), taskID);
			else if(taskID > nice_task_id[order])
				return find_id((first+2), last, taskID);
			else
				return order;
		}
		
	}
	
}