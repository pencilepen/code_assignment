/*
 * Name: Andy Xu
 * ID: V00804737
 * Date: 2nd Apr 2018
 * Filename: Heap.java
 * Details: \CSC115\ Assignment <5>
 */

import java.util.List;
import java.util.ArrayList;
import java.util.NoSuchElementException;



public class Heap<E extends Comparable<E>> {

/*
 *Data Field
 */
	private ArrayList<E> heap;
	private int size;
	private static final int CAPACITY = 100;

	/**
	 * Creates an empty heap.
	 */
	public Heap() {
		heap = new ArrayList<E>(CAPACITY);
		for (int i=0; i<CAPACITY; i++) {
			heap.add(null);
		}
	}

/*
 *Check the heap is empty or not.
 */
	public boolean isEmpty(){
		for(int i=0; i<CAPACITY; i++){
			if(heap.get(i) != null){
				return false;
			}
		}
		return true;
	}

/*
 *Return size of heap, counted for some elements that are not null.
 */
	public int size(){
		this.size = 0;
		for(int i=0; i<CAPACITY; i++){
			if(heap.get(i) != null){
				this.size += 1;
			}
			else{
				this.size +=0;
			}
		}
		return this.size;
	}

/*
 *Let users insert an element.
 */
	public void insert(E element){

		for(int i = 0; i < CAPACITY; i++){
			if(heap.get(i) == null){
				heap.set(i, element);
				break;
			}
		}
	}

/*
 *Let users get an element from heap,and also delete that element from heap.
 */
	public E getRootItem()throws NoSuchElementException{
		if(heap.get(0) == null){
			throw new NoSuchElementException("Heap is empty");
		}
		E returnitem = heap.get(0);
		heap.remove(0);
		heap.add(null);
		return returnitem;

	}

/*
 *Display an element by given index.
 */
	public E displayRootItem(int index){
		E returnitem = heap.get(index);
		return returnitem;
	}
/*
 *Replace an element at given index.
 */
	public void prioritySet(int index, E patient){
		heap.set(index, patient);
	}


/*
 *Internal test.
 */
	public static void main(String[] args){
		Heap<String> list = new Heap<String>();
		list.insert("1");
		list.insert("2");
		list.insert("3");
		list.insert(null);
		if(list.isEmpty() == true){
			System.out.println("Heap is empty");
		}
		else{
			System.out.println("Heap is not empty");
		}
		System.out.println("The size is: "+list.size());
		System.out.println(list.displayRootItem(0));
		System.out.println(list.displayRootItem(1));
		System.out.println(list.displayRootItem(2));
		System.out.println(list.getRootItem());
		System.out.println(list.getRootItem());
		System.out.println(list.getRootItem());
		if(list.isEmpty() == true){
			System.out.println("Heap is empty, should be empty");
		}
		else{
			System.out.println("Heap is not empty");
		}

		list.prioritySet(1,"2");
		System.out.println(list.displayRootItem(1));
		System.out.println("The size now is: "+list.size());


	}
}
