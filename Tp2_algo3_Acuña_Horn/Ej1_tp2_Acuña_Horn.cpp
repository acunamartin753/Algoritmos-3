#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n,m;
int timer;
long long casosGanadores;
vector<vector<int>> adj;
vector<bool> visited;
vector<int> tin, low;
vector<int> comp;
vector<pair<int,int>> puentes;

void dfs(int v, int p = -1) {
    visited[v] = true;
    comp.push_back(v);
    tin[v] = low[v] = timer++;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
                puentes.push_back({v,to});
        }
    }
}

void find_bridges() {
    timer = 0;
    visited.assign(n+1, false);
    tin.assign(n+1, -1);
    low.assign(n+1, -1);
    for (int i = 1; i < n+1; ++i) {
        if (!visited[i])
            dfs(i);
    }
}

void find_comps() {
    fill(visited.begin(), visited.end(), 0);
    for (int v = 1; v < n+1; ++v) {
        if (!visited[v]) {
            comp.clear();
            dfs(v);
            ll S =comp.size();
            casosGanadores += S*(S-1)/2;
        }
    }
}

void borrar(vector<vector<int>>& adj, vector<pair<int,int>>& puentes) {
    for (auto p: puentes) {
        for (auto it = adj[p.first].begin(); it != adj[p.first].end(); it++) {
            if (*it == p.second) {
                it = adj[p.first].erase(it);
                it--;
            }
        }
        for (auto it = adj[p.second].begin(); it != adj[p.second].end(); it++) {
            if (*it == p.first) {
                it = adj[p.second].erase(it);
                it--;
            }
        }
    }
}

int main() {
    cin >> n >> m;
    adj.resize(n+1,{});
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    visited.resize(n+1);
    find_bridges();
    borrar(adj,puentes);

    casosGanadores = 0;
    find_comps();   // Cuenta la suma de casos ganadores

    ll N=n;
    double probaGanar = float(casosGanadores)/((N*(N-1))/2);
    cout << fixed << setprecision(5) <<  1.0-probaGanar;

    return 0;
}