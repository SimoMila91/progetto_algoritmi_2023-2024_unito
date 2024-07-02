package ex3_4.src.ex4;

public class Edge<V, L> implements AbstractEdge<V, L> {

  private V startNode;
  private V endNode;
  private L label;

  public Edge(V startNode, V endNode, L label) {
    this.endNode = endNode;
    this.startNode = startNode;
    this.label = label;
  }

  @Override
  public V getStart() {
    return this.startNode;
  }

  @Override
  public V getEnd() {
    return this.endNode;
  }

  @Override
  public L getLabel() {
    return this.label;
  }

}
