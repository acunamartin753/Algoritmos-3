#include <bits/stdc++.h>
#include <cmath>
#include <tuple>
#include <iostream>
#include <vector>

using namespace std;

using ll = double;
ll sumaU;
ll sumaV;

int n,r,w,U,V,casos,k;
vector<tuple<ll,int,int>> E;
vector<tuple<ll,int,int>> arbol;

ll costo(pair<int,int> a, pair<int,int> b){
    ll distancia = sqrt(ll(pow(a.first-b.first,2)+pow(a.second-b.second,2)));
    ll res;
    if(distancia<=r){
        res = distancia * U;
    }else{
        res = distancia * V;
    }
    return res;
}

struct DSU{

    DSU(int n){
        padre = rank = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
    }

    vector<int> padre;
    vector<int> rank;
};

//  Redefinimos la estructura DSU con las funciones find y unite sin optimizar
//  Para testear las distintas versiones fuimos alternando entre las distintas implementaciones de estas funciones

/*
struct DSU_no_optimizado{

    DSU_no_optimizado(int n){
        padre = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        padre[v] = padre[u];
    }

    vector<int> padre;
};
*/

void kruskal(){
    sort(E.begin(),E.end());
    ll res = 0;
    int aristas = 0;
    DSU dsu(n);
    for(auto [c,u,v] : E){
        //si (u,v) es arista segura
        if(dsu.find(u) != dsu.find(v)){
            // agregar
            dsu.unite(u,v);
            arbol.push_back({c,u,v});

            if(c<=r*U){
                sumaU+=c;
            }else{
                sumaV+=c;
            }

            aristas++;

            if(n-aristas==w){
                cout << "Caso #" << k << ": " << fixed << setprecision(3) << sumaU << " " << sumaV << endl;
                k++;
            }

            res += c;
        }
    }
}

int main() {
    cin>>casos;
    k=1;
    while(casos>0){
        cin>>n>>r>>w>>U>>V;
        vector<pair<int,int>> posiciones(n,{0,0});
        E.clear();
        arbol.clear();
        for(int i=0;i<n;i++){
            cin >> posiciones[i].first;
            cin >> posiciones[i].second;
        }

        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                ll c;
                c = costo(posiciones[i],posiciones[j]);
                E.push_back({c,i,j});
            }
        }

        sumaV=0;
        sumaU=0;
        kruskal();
        casos--;
    }

    return 0;
}
