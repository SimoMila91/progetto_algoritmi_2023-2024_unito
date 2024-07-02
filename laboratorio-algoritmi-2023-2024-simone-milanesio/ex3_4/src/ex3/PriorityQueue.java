package ex3_4.src.ex3;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;

public class PriorityQueue<E> implements AbstractQueue<E> {

  /**
   * @apiNote with hashmap we can
   */

  private ArrayList<E> heap;
  private HashMap<E, Integer> map;
  private Comparator<E> compare;

  public PriorityQueue(Comparator<E> compare) {
    this.compare = compare;
    this.heap = new ArrayList<>();
    this.map = new HashMap<>();
  }

  public int getSize() {
    return this.heap.size();
  }

  /**
   * 
   * @param index: current index to get the parent
   * @return parent index as int
   */

  private int getParent(int index) {
    if (index > 2 && !this.empty()) {
      return (index - 1) / 2;
    } else {
      return 0;
    }

  }

  /**
   * 
   * @param index: current index to get children
   * @return right/left child as int
   */

  private int getLeft(int index) {
    return 2 * index + 1 <= this.heap.size() ? (2 * index) + 1 : index;
  }

  private int getRight(int index) {
    return (2 * index) + 2 <= this.heap.size() ? (2 * index) + 2 : index;
  }

  /**
   * 
   * @param index
   * 
   * @apiNote: Update heap after remove
   */

  private void heapify(int index) {

    int minIndex = getSmallestIndex(index);

    if (minIndex != index) {

      swap(index, minIndex);
      heapify(minIndex);

    }
  }

  /**
   * 
   * @param largest
   * @param smallest
   * 
   * @apiNote: swap two element and replace keys's positions in the hashmap
   */
  private void swap(int largest, int smallest) {
    E min = this.heap.get(smallest);
    E max = this.heap.get(largest);

    this.map.replace(min, largest);
    this.map.replace(max, smallest);

    this.heap.set(smallest, max);
    this.heap.set(largest, min);
  }

  /**
   * 
   * @param index
   * @return minIndex{ H[index], H[left(index)], H[right(index)] } as int
   */

  private int getSmallestIndex(int index) {

    E smallest = this.heap.get(index);

    int left = this.getLeft(index);
    int right = this.getRight(index);

    if (right < this.heap.size() && this.compare.compare(smallest, this.heap.get(right)) > 0) {
      smallest = this.heap.get(right);
    }

    if (left < this.heap.size() && this.compare.compare(smallest, this.heap.get(left)) > 0) {
      smallest = this.heap.get(left);
    }

    return this.map.get(smallest);
  }

  /**
   * 
   * @param index
   * @param e
   * 
   * @apiNote: Update heap after insert
   */

  private void updateHeap(int index, E e) {

    while (index > 0) {

      int parentIndex = this.getParent(index);

      if (this.compare.compare(this.heap.get(parentIndex), e) > 0) {

        swap(index, parentIndex);
        index = parentIndex;

      } else
        break;

    }
  }

  @Override
  public boolean empty() {
    return this.heap.isEmpty();
  }

  @Override
  public boolean push(E e) {

    boolean res = this.contains(e) ? false : this.heap.add(e);

    if (res) {

      int index = this.heap.size() - 1;
      // System.err.println(index);
      map.put(e, index);

      updateHeap(index, e);
    }

    return res;
  }

  @Override
  public boolean contains(E e) {
    return this.map.containsKey(e);
  }

  /**
   * @return null if heap is empty, the element on the top otherwise.
   */

  @Override
  public E top() {
    if (!empty()) {
      return this.heap.get(0);
    }
    return null;
  }

  @Override
  public void pop() {
    if (!this.empty()) {
      this.remove(this.heap.get(0));
    }
  }

  /**
   * 
   * @param e: the element to be removed
   * @return boolean
   * @apiNote: return true if the element exists and it has been removed, false
   *           otherwise.
   */

  @Override
  public boolean remove(E e) {

    boolean res = this.contains(e);

    if (res) {

      int removedIndex = this.map.get(e);
      int lastIndex = this.heap.size() - 1;

      if (lastIndex > 0) {

        this.heap.set(removedIndex, this.heap.get(lastIndex));
        this.map.remove(e);
        this.map.replace(this.heap.get(lastIndex), removedIndex);
        this.heap.remove(lastIndex);

        if (removedIndex != lastIndex) {

          E movedElement = this.heap.get(removedIndex);

          this.heapify(removedIndex);
          if (this.map.get(movedElement) == removedIndex) {
            this.updateHeap(removedIndex, movedElement);
          }
        }

      } else {

        this.heap.clear();
        this.map.clear();
      }
    }

    return res;

  }

}
