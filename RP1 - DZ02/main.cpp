#include <iostream>
#include <iomanip>  // za setw
#include "graph.h"

using namespace std;

void printGraph(graph G)
{
    set<char>::iterator si;
    cout << "Vrhovi:";
    for (si = G.vertices.begin(); si != G.vertices.end(); ++si)
        cout << " " << *si;
    cout << endl;

    map<set<char>, int>::iterator mi;
    cout << "Bridovi:" << endl;
    for (mi = G.weights.begin(); mi != G.weights.end(); ++mi)
    {
        si = mi->first.begin();
        cout << "{" << *si++ << ", " << *si << "}, " << mi->second << endl;
    }
}

void printMatrix(vector<vector<int>> M)
{
    vector<vector<int>>::iterator vvi;
    vector<int>::iterator vi;
    for (vvi = M.begin(); vvi != M.end(); ++vvi)
    {
        for (vi = vvi->begin(); vi != vvi->end(); ++vi)
            cout << setw(5) << *vi << " ";
        cout << endl;
    }
}

void printPartition(set<set<char>> P)
{
    bool first = true, first2;
    set<set<char>>::iterator ssi;
    set<char>::iterator si;
    cout << "{";
    for (ssi = P.begin(); ssi != P.end(); ++ssi)
    {
        if (!first)
            cout << ", ";
        first = false;
        cout << "{";
        first2 = true;
        for (si = ssi->begin(); si != ssi->end(); ++si)
        {
            if (!first2)
                cout << ", ";
            first2 = false;
            cout << *si;
        }
        cout << "}";
    }
    cout << "}" << endl;
}

int main()
{
    graph G;
    G.insertEdge('a', 'c', 4);
    G.insertEdge('a', 'd', 2);
    G.insertEdge('b', 'd', 2);
    G.insertEdge('b', 'e', 4);
    G.insertEdge('c', 'f', 2);
    G.insertEdge('c', 'd', 1);
    G.insertEdge('d', 'f', 2);
    G.insertEdge('e', 'f', 2);

    G.insertVertex('x');
    G.insertEdge('x', 'y', 1);
    G.insertEdge('x', 'a', 1);
    G.eraseVertex('x');
    G.eraseEdge('x', 'y');
    G.eraseVertex('y');

    printGraph(G);
    cout << endl;

    vector<vector<int>> L = G.laplacianMatrix();
    printMatrix(L);
    cout << endl;

    set<set<char>> P = G.distancePartition('a');
    printPartition(P);

    return 0;
}