// Justice Smith 2/2021
// Unfinished graph analyzer

function foo(items) {
  var i;
  for (i = 0; i < items.length; i++) {

  }
}

Q: Given a graph write a function to determine if the graph is a tree?

            a
        |        |
       b          c

          Tree


            a
        |        |
       b          c
         |      |
            d

          Not tree

public class Node {
    /& Adjacency List &/
    public List<Node> connectedNodes;
    public int value;
}

public class Graph {
    // List of Graph Nodes Vertices in the Graph
    public List<Node> graphNodes;
}

Public class NodeQueue {
      public void add(Node node); // Add to queue
      public Node poll() // Remove Node From queue
}


// Behavior
// Add starting node
// For items.length - 1
// If queue length != 0
// Check for existence of node value
// if exists, return false
// Else, add to queue
// Grab next value from array.

Boolean determineType(int items[]);

int main() {

    Boolean determineType(items[], length);
    return 0;
}

Boolean determineType(int items[], int length) {
    char foundValues[length];
    int size = 0;
    // This layer goes through each element of input data
    for(int i = 0; i < length; i++) {
        // This layer checks each of the existing elements in the stored array
        for(int j = 0; j < size; j++) {
            // Leaves when we reach the end of the input array
            // This means that we didn't find the same value
            if(size < length) {
                // Char compares ASCII values
                if(items[i] == foundValues[j]) {
                    return False;
                }
                else {
                    foundValues[size] = items[i];
                    size++;
                }
            }
            return True;
        }
    }
}


