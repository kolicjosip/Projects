#include<iostream>
#include"graph.h"

using namespace std;

graph::graph(){
    vertices = {};
    weights = {};
}

graph::graph(std::set<std::tuple<char, char, int>> edge_weights){
    set<tuple<char, char, int>>::iterator it;
    
    for(it = edge_weights.begin(); it != edge_weights.end(); it++){

        char v1 = get<0>(*it);
        char v2 = get<1>(*it);
        int tezina = get<2>(*it);

        vertices.insert(v1);
        vertices.insert(v2);

        set<char> brid = {v1, v2};
        weights[brid] = tezina;
    }
}

bool graph::insertVertex(char a){
    // vratit ce <iterator, bool>
    auto uspjelo = vertices.insert(a);

    return uspjelo.second; // true ili false
}

bool graph::insertEdge(char a, char b, int w){
    vertices.insert(a); vertices.insert(b); // dodajemo u slucaju da vec nisu dodani

    set<char> brid = {a, b};

    // ako brid postoji, ne trebamo ga dodati ponovo
    if(weights.find(brid) != weights.end()) return false;
    // inace
    weights[brid] = w;
    return true;
}

bool graph::eraseVertex(char a){
    if(vertices.find(a) == vertices.end()){
        return false; // nije jedan od vrhova
    }

    map<set<char>,int>::iterator it;

    it = weights.begin();
    while(it != weights.end()){
        if(it->first.count(a)) it = weights.erase(it);
        else it++;
    }

    vertices.erase(a); // micemo a iz vertices
    return true;
}

bool graph::eraseEdge(char a, char b){
    set<char> brid;
    brid.insert(a); brid.insert(b);

    map<set<char>, int>::iterator it = weights.find(brid);

    if(it == weights.end()) return false;

    weights.erase(it);
    return true;
}

std::vector<std::vector<int>> graph::laplacianMatrix(){
    vector<char> sortiraneVertices(vertices.begin(), vertices.end());
    int n;
    
    n = sortiraneVertices.size();
    vector<vector<int>> novi(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++){
        char vi = sortiraneVertices[i];
        int suma = 0;

        for(int j = 0; j < n; j++){
            if(i == j) continue;

            char vj = sortiraneVertices[j];
            set<char> brid = {vi, vj};

            if(weights.find(brid) != weights.end()){
                int w = weights[brid];
                novi[i][j] = -w;
                suma += w;
            }
        }
        novi[i][i] = suma;
    }
    return novi;
}

std::set<std::set<char>> graph::distancePartition(char a){
    map<char, int> udalj;
    const int max = 1e9;

    set<char>::iterator it;

    for(it = vertices.begin(); it != vertices.end(); it++){
        udalj[*it] = max;
    }

    udalj[a] = 0;

    set<pair<int, char>> pq;
    pq.insert({0,a});

    while(!pq.empty()){
        pair<int, char> tr = *pq.begin();
        pq.erase(pq.begin());

        int trUdalj = tr.first;
        char u = tr.second;

        set<char>::iterator it;
        for(it = vertices.begin(); it!= vertices.end(); it++){
            char v = *it;
            if(u == v) continue;

            set<char> brid = {u, v};
            if(weights.find(brid) != weights.end()){
                int w = weights[brid];
                if(udalj[u] + w < udalj[v]){
                    pq.erase({udalj[v], v});
                    udalj[v] = udalj[u] + w;
                    pq.insert({udalj[v], v});
                }
            }
        }
    }

    map<int, set<char>> grupiranje;
    for(map<char,int>::iterator it = udalj.begin(); it != udalj.end(); it++){
        grupiranje[it->second].insert(it->first);
    }

    set<set<char>> rez;

    for(map<int, set<char>>::iterator it = grupiranje.begin(); it != grupiranje.end(); it++){
        rez.insert(it->second);   
    }
    return rez;
}






