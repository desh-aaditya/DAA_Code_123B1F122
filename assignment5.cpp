#include <bits/stdc++.h> 
using namespace std; 
using ll = long long; 
const ll INF = 1e15; 
 
struct Edge { 
    int to; 
    ll weight; 
    int id; 
}; 
 
struct Graph { 
    int stagesCount; 
    int V; 
    vector<int> stage; 
    vector<vector<Edge>> adj; 
    struct RawEdge { int u, v; ll w; }; 
    vector<RawEdge> edges; 
 
    Graph(int v = 0, int s = 0) { init(v, s); } 
 
    void init(int v, int s) { 
        V = v; 
        stagesCount = s; 
        stage.assign(V, -1); 
        adj.assign(V, {}); 
        edges.clear(); 
    } 
 
    void setStage(int node, int s) { 
        stage[node] = s; 
    } 
 
    int addEdge(int u, int v, ll w) { 
        if (stage[u] > stage[v]) return -1; 
        int id = edges.size(); 
        edges.push_back({u, v, w}); 
        adj[u].push_back({v, w, id}); 
        return id; 
    } 
 
    void updateEdgeWeight(int id, ll newW) { 
        if (id < 0 || id >= edges.size()) return; 
        edges[id].w = newW; 
        for (auto &e : adj[edges[id].u]) { 
            if (e.id == id) e.weight = newW; 
        } 
    } 
 
    void applyMultiplierToEdge(int id, double m) { 
        if (id < 0 || id >= edges.size()) return; 
        ll newW = (ll)(edges[id].w * m); 
        updateEdgeWeight(id, newW); 
    } 
 
    pair<ll, vector<int>> dijkstra(int src, int dst) { 
        vector<ll> dist(V, INF); 
        vector<int> parent(V, -1); 
        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq; 
        dist[src] = 0; 
        pq.push({0, src}); 
 
        while (!pq.empty()) { 
            auto [d, u] = pq.top(); 
            pq.pop(); 
            if (d != dist[u]) continue; 
            if (u == dst) break; 
            for (auto &e : adj[u]) { 
                int v = e.to; 
                if (stage[u] > stage[v]) continue; 
                ll nd = d + e.weight; 
                if (nd < dist[v]) { 
                    dist[v] = nd; 
                    parent[v] = u; 
                    pq.push({nd, v}); 
                } 
            } 
        } 
 
        if (dist[dst] == INF) return {INF, {}}; 
        vector<int> path; 
        for (int cur = dst; cur != -1; cur = parent[cur]) path.push_back(cur); 
        reverse(path.begin(), path.end()); 
        return {dist[dst], path}; 
    } 
}; 
 
int main() { 
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 
 
    int Nstages, V; 
    cin >> Nstages >> V; 
 
    Graph G(V, Nstages); 
    for (int i = 0; i < V; i++) { 
        int s; cin >> s; 
        G.setStage(i, s); 
    } 
 
    int E; 
    cin >> E; 
    for (int i = 0; i < E; i++) { 
        int u, v; ll w; 
        cin >> u >> v >> w; 
        G.addEdge(u, v, w); 
    } 
 
    int Q; 
    cin >> Q; 
    for (int i = 0; i < Q; i++) { 
        int src, dst; 
        cin >> src >> dst; 
        auto [cost, path] = G.dijkstra(src, dst); 
        if (cost == INF) { 
            cout << "Unreachable from " << src << " to " << dst << "\n"; 
        } else { 
            cout << "Optimal cost: " << cost << " | Path: "; 
            for (int j = 0; j < path.size(); j++) { 
                if (j) cout << "->"; 
                cout << path[j]; 
            } 
            cout << "\n"; 
        } 
    } 
    return 0; 
} 