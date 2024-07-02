/**
 * 
 * @author Simone Milanesio  
 *
 */

package ex3_4.src.ex4;

import java.util.Collection;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

public class Graph<V, L> implements AbstractGraph<V, L> {

  private boolean isDirected;
  private boolean isLabelled;
  private Map<V, List<Edge<V, L>>> indexMap;

  public Graph(boolean isDirected, boolean isLabelled) {

    this.isDirected = isDirected;
    this.isLabelled = isLabelled;
    this.indexMap = new HashMap<>();

  }

  @Override
  public boolean isDirected() {
    return this.isDirected;
  }

  @Override
  public boolean isLabelled() {
    return this.isLabelled;
  }

  @Override
  public boolean addNode(V a) {
    boolean res = false;

    if (!this.containsNode(a)) {
      this.indexMap.put(a, new LinkedList<>());
      res = true;
    }

    return res;
  }

  @Override
  public boolean addEdge(V a, V b, L l) {

    if (!this.containsEdge(a, b) && this.containsNode(a) && this.containsNode(b)) {

      this.indexMap.get(a).add(new Edge<V, L>(a, b, this.isLabelled ? l : null));

      if (!this.isDirected) {

        this.indexMap.get(b).add(new Edge<V, L>(b, a, this.isLabelled ? l : null));

      }

      return true;
    }

    return false;
  }

  @Override
  public boolean containsNode(V a) {
    return indexMap.containsKey(a);
  }

  @Override
  public boolean containsEdge(V a, V b) {

    if (this.containsNode(a)) {

      for (Edge<V, L> e : this.indexMap.get(a)) {
        if (e.getEnd().equals(b)) {
          return true;
        }
      }
    }

    return false;
  }

  @Override
  public boolean removeNode(V a) {

    boolean res = false;

    if (this.containsNode(a)) {
      res = true;
      this.indexMap.remove(a);
      for (V key : indexMap.keySet()) {
        this.indexMap.get(key).removeIf(e -> e.getEnd().equals(a));
      }
    }

    return res;
  }

  @Override
  public boolean removeEdge(V a, V b) {

    boolean res = false;

    if (this.containsEdge(a, b)) {
      res = true;
      this.indexMap.get(a).removeIf(e -> e.getEnd().equals(b));

      if (!this.isDirected) {
        this.indexMap.get(b).removeIf(e -> e.getEnd().equals(a));
      }
    }

    return res;
  }

  @Override
  public int numNodes() {
    return this.indexMap.size();
  }

  @Override
  public int numEdges() {

    int counter = 0;

    for (List<Edge<V, L>> e : this.indexMap.values()) {
      counter += e.size();

    }
    return this.isDirected ? counter : counter / 2;
  }

  @Override
  public Collection<V> getNodes() {
    return this.indexMap.keySet();
  }

  @Override
  public Collection<? extends AbstractEdge<V, L>> getEdges() {

    List<Edge<V, L>> list = new LinkedList<>();

    for (List<Edge<V, L>> e : this.indexMap.values()) {
      list.addAll(e);
    }

    return list;
  }

  @Override
  public Collection<V> getNeighbours(V a) {

    List<V> neighbours = new LinkedList<>();

    if (this.containsNode(a)) {
      for (Edge<V, L> e : this.indexMap.get(a)) {
        neighbours.add(e.getEnd());
      }
    }

    return neighbours;
  }

  @Override
  public L getLabel(V a, V b) {
    if (this.isLabelled()) {
      for (Edge<V, L> e : this.indexMap.get(a)) {
        if (e.getEnd().equals(b))
          return e.getLabel();
      }
    }
    return null;
  }

}
