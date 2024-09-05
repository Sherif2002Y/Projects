#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a disjoint set for union-find operations
struct DisjointSet {
    vector<int> parent, rank;

    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int v) {
        if (parent[v] != v)
            parent[v] = find(parent[v]);
        return parent[v];
    }

    void unionSets(int v1, int v2) {
        int root1 = find(v1);
        int root2 = find(v2);
        if (root1 != root2) {
            if (rank[root1] < rank[root2])
                parent[root1] = root2;
            else if (rank[root1] > rank[root2])
                parent[root2] = root1;
            else {
                parent[root2] = root1;
                rank[root1]++;
            }
        }
    }
};

// Comparator function to sort edges by weight in non-decreasing order
bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

// Function to find the MST using Kruskal's algorithm
vector<Edge> findMST(vector<Edge>& edges, int numVertices) {
    // Sort the edges in non-decreasing order of their weights
    sort(edges.begin(), edges.end(), compareEdges);

    // Create a disjoint set to keep track of connected components
    DisjointSet ds(numVertices);

    vector<Edge> mst; // Stores the edges in the MST

    for (const auto& edge : edges) {
        int src = edge.src;
        int dest = edge.dest;

        // Check if including the current edge forms a cycle
        if (ds.find(src) != ds.find(dest)) {
            // Add the edge to the MST
            mst.push_back(edge);
            ds.unionSets(src, dest);
        }
    }

    return mst;
}

// Function to print the edges of the MST
void printMST(const vector<Edge>& mst) {
    cout << "MST Edges: [";
    for (int i = 0; i < mst.size(); ++i) {
        cout << "(" << static_cast<char>('A' + mst[i].src) << ", " << static_cast<char>('A' + mst[i].dest) << ")";
        if (i != mst.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    int numVertices, numEdges;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    vector<Edge> edges(numEdges);

    cout << "Enter the source, destination, and weight of each edge:" << endl;
    for (int i = 0; i < numEdges; ++i) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    vector<Edge> mst = findMST(edges, numVertices);
    printMST(mst);

    return 0;
}