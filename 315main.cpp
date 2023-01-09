// INCLUDE & USING STATEMENTS *************************************************

// libraries
#include <iostream>
#include <functional>
#include <cstdlib> 
#include <ctime>
#include <iomanip>

// header files
#include "graph.h"
#include "hash_problem.h"

using namespace std;

// available functions
int gcd(int lhs, int rhs); // 2.16
int find_root(int (*f)(int), int high, int low); // 2.18
int minus5(int x); // 2.18


// FUNCTION DECLARATIONS*******************************************************
int main()
{
    int myGraphSize;
    vector<Edge> graph2;

    cout << "Enter graph size: ";
    cin >> myGraphSize;
    cout << endl;

    Graph myGraph(myGraphSize);
    myGraph.initGraph();
    graph2 = myGraph.makeEdgeVect();
    graph2 = myGraph.kruskalAlgorithm(graph2, myGraphSize);
    printEdges(graph2);
}