#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<vector<int>> adj, adj_rev;
vector<bool> used;
vector<int> order, component;

void dfs1(int v) {
    used[v] = true;

    for (auto u : adj[v])
        if (!used[u])
            dfs1(u);

    order.push_back(v);
}

void dfs2(int v) {
    used[v] = true;
    component.push_back(v);

    for (auto u : adj_rev[v])
        if (!used[u])
            dfs2(u);
}

int main() {
    int n,m;
    cin >> n >> m;
    adj.resize(n+1,{});
    adj_rev.resize(n+1,{});
    
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj_rev[b].push_back(a);
    }

    used.resize(n+1);
    used.assign(n+1, false);

    for (int i = 1; i < n+1; i++)
        if (!used[i])
            dfs1(i);

    used.assign(n+1, false);
    reverse(order.begin(), order.end());

    for (auto v : order)
        if (!used[v]) {
            dfs2 (v);
            vector<int> C2 = component;
            component.clear();
        }

    vector<int> roots(n+1, 0);
    vector<int> root_nodes;
    vector<vector<int>> adj_scc(n+1);
    used.assign(n+1, false);

    for (auto v : order) {
        if (!used[v]) {
            dfs2(v);

            int root = component.front();
            for (auto u: component) roots[u] = root;
            root_nodes.push_back(root);
            component.clear();
        }
    }

    for (int v = 1; v < n+1; v++) {
        for (auto u: adj[v]) {
            int root_v = roots[v],
                    root_u = roots[u];
            if (root_u != root_v)
                adj_scc[root_v].push_back(root_u);
        }
    }

    used.assign(n+1, false);
    vector<int> res;
    for(auto v : root_nodes){
        if(!used[v]){
            used[v]=true;
            res.push_back(v);
        }
        for(auto u : adj_scc[v]){
            used[u]=true;
        }
    }

    reverse(res.begin(), res.end());

    cout << res.size() << endl;
    for(int i=0;i<res.size();i++){
        cout << res[i] << " ";
    }

    return 0;
}