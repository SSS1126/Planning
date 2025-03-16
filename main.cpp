#include <iostream>
#include <vector>
#include "D:\C_plus\Dijkstra\dijkstra.h"
using namespace std;
const int M = 100000;

int main() {
    dijkstra method;
    char Node[] = {'A', 'B', 'C', 'D', 'E'}; 
    int graph[5][5] = {
            {0, 4, M, 2, M},
            {4, 0, 4, 1, M},
            {M, 4, 0, 1, 3},
            {2, 1, 1, 0, 7},
            {M, M, 3, 7, 0}
    };
    int firstNode = 0;
    int endNode = 4;
    vector<int> result = method.source(graph, firstNode, endNode);
    for (auto it : result) {
        cout << Node[it] <<endl;
    }
    return 0;
}