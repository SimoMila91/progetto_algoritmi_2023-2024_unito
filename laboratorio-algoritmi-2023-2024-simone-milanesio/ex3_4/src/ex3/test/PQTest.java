package ex3_4.src.ex3.test;

import static org.junit.Assert.assertTrue;

import java.util.Comparator;

import org.junit.Before;
import org.junit.Test;

import ex3_4.src.ex3.*;

public class PQTest {
  class IntegerComparator implements Comparator<Integer> {
    @Override
    public int compare(Integer first, Integer second) {
      return first.compareTo(second);
    }
  }

  private PriorityQueue<Integer> queue;

  private void populate() {
    for (int i = 0; i <= 10; i++) {
      this.queue.push(i);
    }
  }

  @Before
  public void createHeap() {
    this.queue = new PriorityQueue<>(new IntegerComparator());
  }

  @Test
  public void testIsEmpty() {
    assertTrue(this.queue.empty());
  }

  @Test
  public void testInsert() {
    this.queue.push(0);
    assertTrue(this.queue.getSize() == 1);
  }

  @Test
  public void testSize() {
    this.populate(); /* add 10 elements */
    assertTrue(this.queue.getSize() == 11);
  }

  @Test
  public void testMinHeap() {
    this.populate();
    assertTrue(this.queue.top() == 0);
  }

  @Test
  public void testPop() {
    this.populate();
    this.queue.pop();
    assertTrue(this.queue.getSize() == 10);
    assertTrue(this.queue.top() == 1);
  }

  @Test
  public void testRemove() {
    this.populate();
    assertTrue(this.queue.remove(7));
    assertTrue(this.queue.getSize() == 10);
    assertTrue(this.queue.top() == 0);
  }

  @Test
  public void testContains() {
    this.populate();
    assertTrue(this.queue.contains(3));
    assertTrue(!this.queue.contains(99));
  }

}
