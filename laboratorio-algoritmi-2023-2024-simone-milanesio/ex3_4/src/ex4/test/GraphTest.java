package ex3_4.src.ex4.test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.Collection;

import org.junit.Before;
import org.junit.Test;

import ex3_4.src.ex4.*;

public class GraphTest {

  private Graph<String, Integer> myGraph;

  private void generateGraph() {
    String nodes[] = { "a", "b", "c", "d", "e", "f" };

    for (String each : nodes) {
      myGraph.addNode(each);
    }

    for (int i = 0; i < nodes.length - 1; i++) {
      myGraph.addEdge(nodes[i], nodes[i + 1], i + 1);
    }

  }

  @Before
  public void defaultGraph() {
    this.myGraph = new Graph<>(true, true);

  }

  @Test
  public void testIsDirected() {
    assertTrue(myGraph.isDirected());
  }

  @Test
  public void testIsLabelled() {
    assertTrue(myGraph.isLabelled());
  }

  @Test
  public void addNode() {
    assertTrue(myGraph.addNode("a"));
  }

  @Test
  public void containsEdge() {
    generateGraph();
    assertTrue(myGraph.containsEdge("a", "b"));
  }

  @Test
  public void testRemoveNode() {
    generateGraph();
    assertTrue(myGraph.removeNode("a"));
    assertFalse(myGraph.containsNode("a"));
  }

  @Test
  public void testRemoveEdge() {
    generateGraph();
    assertTrue(myGraph.removeEdge("a", "b"));
    assertFalse(myGraph.containsEdge("a", "b"));
  }

  @Test
  public void testGetNeighbours() {
    generateGraph();
    Collection<String> neighboursOfA = myGraph.getNeighbours("a");
    assertTrue(neighboursOfA.contains("b"));
  }

  @Test
  public void testGetLabel() {
    generateGraph();
    assertEquals(Integer.valueOf(1), myGraph.getLabel("a", "b"));
  }

  @Test
  public void testNumNodes() {
    generateGraph();
    assertEquals(6, myGraph.numNodes());
  }

  @Test
  public void testNumEdges() {
    generateGraph();
    assertEquals(5, myGraph.numEdges());
  }

}
