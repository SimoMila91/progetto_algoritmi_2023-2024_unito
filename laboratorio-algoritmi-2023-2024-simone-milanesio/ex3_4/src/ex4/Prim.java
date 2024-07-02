package ex3_4.src.ex4;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Comparator;
import java.util.HashSet;

import ex3_4.src.ex3.PriorityQueue;

import java.util.List;

public class Prim {

  /**
   * 
   * @param path: percorso file preso in input
   * @return lista di array di stinghe [0]: place1, [1]: place2, [2]: label
   */

  public static List<String[]> readFromFile(String path) {

    List<String[]> lines = new ArrayList<>();

    System.out.println(path);

    try (BufferedReader reader = new BufferedReader(new FileReader(path))) {

      String line;

      while ((line = reader.readLine()) != null) {

        String[] values = line.split(",");

        lines.add(values);

      }

    } catch (IOException ex) {

      ex.printStackTrace();
    }

    return lines;
  }

  public static void populateGraph(List<String[]> csv, Graph<String, Double> graph) {

    for (String[] row : csv) {

      String place1 = row[0];
      String place2 = row[1];
      Double distance = Double.parseDouble(row[2]);

      graph.addNode(place1);
      graph.addNode(place2);
      graph.addEdge(place1, place2, distance);

    }

  }

  static class DoubleComparatore<V, L> implements Comparator<Edge<V, L>> {

    @Override
    public int compare(Edge<V, L> first, Edge<V, L> second) {

      return Double.compare((Double) first.getLabel(), (Double) second.getLabel());
    }

  }

  /**
   * 
   * @apiNote: Calcolo della foresta minima ricoprente.
   * @param <V>
   * @param <L>
   * @param graph
   * @return collection con la foresta minima
   */

  public static <V, L extends Number> Collection<? extends AbstractEdge<V, L>> minimumSpanningForest(
      Graph<V, L> graph) {

    var priorityQueue = new PriorityQueue<Edge<V, L>>(new DoubleComparatore<>());

    // Insieme per tenere traccia dei nodi visitati
    var visitedNodes = new HashSet<>(graph.numNodes());

    // Lista per mantenere gli archi mst
    var msf = new ArrayList<AbstractEdge<V, L>>();

    for (var node : graph.getNodes()) {

      // Se il nodo è già stato visitato passo a quello successivo altrimenti lo segno
      // come visitato
      if (!visitedNodes.add(node))
        continue;

      // Continuo fino a quando tutti i vertici non sono stati visitati.
      while (visitedNodes.size() < graph.numNodes()) {

        // Itero i vertici vicini al nodo corrente
        for (var neighbour : graph.getNeighbours(node)) {
          // Se il vicino non è ancora stato visitato aggiungo l'arco tra il nodo corrente
          // e il vicino alla coda di priorità.
          if (!visitedNodes.contains(neighbour)) {
            var edge = new Edge<>(node, neighbour, graph.getLabel(node, neighbour));
            priorityQueue.push(edge);
          }
        }

        // Estraggo l'arco minimo e rimuovo archi con un endpoint già visitati e passo
        // all'arco successivo
        var minEdge = priorityQueue.top();
        while (minEdge != null && visitedNodes.contains(minEdge.getEnd())) {
          priorityQueue.pop();
          minEdge = priorityQueue.top();
        }

        // Se l'arco minimo è NULL termino il ciclo e passo al nodo successivo
        if (minEdge == null)
          break;

        // Aggiungo l'arco minimo e passo al nodo successivo
        msf.add(minEdge);
        visitedNodes.add(minEdge.getEnd());
        node = minEdge.getEnd();
      }

      // Se tutti i vertici sono stati visitati esco dal ciclo principale. MST
      // completo.
      if (visitedNodes.size() == graph.numNodes())
        break;
    }

    return msf;
  }

  public static void main(String[] args) {

    // leggo i dati CSV del grafo dal percorso in args[1]
    // data/fileName.*

    List<String[]> csv = readFromFile(args[0]);

    Graph<String, Double> graph = new Graph<>(false, true);

    populateGraph(csv, graph);

    // calcolo la minima foresta ricoprente con minimumSpanningForest

    Collection<? extends AbstractEdge<String, Double>> mstEdges = minimumSpanningForest(graph);

    Double weight = 0.0;

    for (AbstractEdge<String, Double> edge : mstEdges) {

      Double label = edge.getLabel();
      weight += label;

      System.out.println(edge.getStart() + "," + edge.getEnd() + "," + label);

    }

    System.err.println("Numero di nodi nella foresta: " + graph.numNodes());
    System.err.println("Numero di archi nella foresta: " + mstEdges.size());
    System.err.println("Peso della foresta: " + new DecimalFormat("#.###").format((weight / 1000)) + "km");

  }
}
