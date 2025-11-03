#include <iostream> 
#include <vector> 
#include <queue> 
#include<climits>
#include <limits> 
using namespace std; 
 
struct Edge { 
    int to; 
    int weight; 
}; 
 
void dijkstra(int n, int source, vector<vector<Edge>> &adj, vector<int> &dist,vector<int> &parent) { 
    dist.assign(n, INT_MAX); 
    parent.assign(n, -1); 
    dist[source] = 0; 
 
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; 
    pq.push({0, source}); 
 
    while (!pq.empty()) { 
        int u_dist = pq.top().first; 
        int u = pq.top().second; 
        pq.pop(); 
 
        if (u_dist > dist[u]) continue; 
 
        for (auto &edge : adj[u]) { 
            int v = edge.to; 
            int w = edge.weight; 
            if (dist[u] + w < dist[v]) { 
                dist[v] = dist[u] + w; 
                parent[v] = u; 
                pq.push({dist[v], v}); 
            } 
        } 
    } 
} 
 
 
 
void printPath(int destination, vector<int> &parent) { 
    if (destination == -1) return; 
    printPath(parent[destination], parent); 
    cout << destination << " "; 
} 
 
int main() { 
    int n, m; 
    cout << "Enter number of intersections (nodes) and roads (edges): "; 
    cin >> n >> m; 
 
    vector<vector<Edge>> adj(n); 
 
    cout << "Enter roads (u v travel_time):\n"; 
    for (int i = 0; i < m; i++) { 
        int u, v, w; 
        cin >> u >> v >> w; 
        adj[u].push_back({v, w}); 
        adj[v].push_back({u, w}); 
    } 
 
    int source, hospital_count; 
    cout << "Enter ambulance location (source node): "; 
    cin >> source; 
    cout << "Enter number of hospitals: "; 
    cin >> hospital_count; 
 
    vector<int> hospitals(hospital_count); 
    cout << "Enter hospital nodes:\n"; 
    for (int i = 0; i < hospital_count; i++) cin >> hospitals[i]; 
 
    vector<int> dist, parent; 
    dijkstra(n, source, adj, dist, parent); 
 
    cout << "\nShortest paths to hospitals:\n"; 
    for (int h : hospitals) { 
        cout << "Hospital " << h << ": distance = " << dist[h] << ", path = "; 
        printPath(h, parent); 
        cout << "\n"; 
    } 
 
    return 0; 
}