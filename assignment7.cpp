#include <bits/stdc++.h> 
using namespace std; 
class Graph { 
    int V; 
    vector<vector<int>> adj; 
public: 
    Graph(int V) { this->V = V; adj.resize(V); } 
    void addEdge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); } 
    void greedyColoring() { 
        vector<int> result(V, -1); 
        result[0] = 0; 
        vector<bool> available(V, false); 
        for (int u = 1; u < V; u++) { 
            for (int i : adj[u]) if (result[i] != -1) available[result[i]] = true; 
            int cr; 
            for (cr = 0; cr < V; cr++) if (!available[cr]) break; 
            result[u] = cr; 
            for (int i : adj[u]) if (result[i] != -1) available[result[i]] = false; 
        } 
        cout << "\nGreedy Coloring Result:\n"; 
        for (int u = 0; u < V; u++) cout << "Course " << u << " -> Slot " << result[u] << "\n"; 
        cout << "Total Slots: " << (*max_element(result.begin(), result.end()) + 1) << "\n"; 
    } 
    void DSATURColoring() { 
        vector<int> result(V, -1), degree(V), sat(V, 0); 
        for (int i = 0; i < V; i++) degree[i] = adj[i].size(); 
        int colored = 0; 
        while (colored < V) { 
            int maxSat = -1, vertex = -1; 
            for (int i = 0; i < V; i++) 
                if (result[i] == -1 && (sat[i] > maxSat || (sat[i] == maxSat && degree[i] > 
degree[vertex]))) { 
                    maxSat = sat[i]; vertex = i; 
                } 
            vector<bool> used(V, false); 
            for (int i : adj[vertex]) if (result[i] != -1) used[result[i]] = true; 
            int color; 
            for (color = 0; color < V; color++) if (!used[color]) break; 
            result[vertex] = color; 
            for (int i : adj[vertex]) if (result[i] == -1) { 
                set<int> colors; 
                for (int j : adj[i]) if (result[j] != -1) colors.insert(result[j]); 
                sat[i] = colors.size(); 
            } 
            colored++; 
        } 
        cout << "\nDSATUR Coloring Result:\n"; 
        for (int u = 0; u < V; u++) cout << "Course " << u << " -> Slot " << result[u] << "\n"; 
        cout << "Total Slots: " << (*max_element(result.begin(), result.end()) + 1) << "\n"; 
    } 
    void WelshPowellColoring() { 
        vector<pair<int, int>> degree(V); 
        for (int i = 0; i < V; i++) degree[i] = { (int)adj[i].size(), i }; 
        sort(degree.rbegin(), degree.rend()); 
        vector<int> result(V, -1); 
        int color = 0; 
        for (int i = 0; i < V; i++) { 
            int v = degree[i].second; 
            if (result[v] == -1) { 
                result[v] = color; 
                for (int j = i + 1; j < V; j++) { 
                    int u = degree[j].second; 
                    if (result[u] == -1) { 
                        bool conflict = false; 
                        for (int k : adj[u]) if (result[k] == color) { conflict = true; break; } 
                        if (!conflict) result[u] = color; 
                    } 
                } 
                color++; 
            } 
        } 
        cout << "\nWelsh-Powell Coloring Result:\n"; 
        for (int u = 0; u < V; u++) cout << "Course " << u << " -> Slot " << result[u] << "\n"; 
        cout << "Total Slots: " << color << "\n"; 
    } 
}; 
 
int main() { 
    int V = 5; 
    Graph g(V); 
    g.addEdge(0, 1); 
    g.addEdge(0, 2); 
    g.addEdge(1, 2); 
    g.addEdge(1, 3); 
    g.addEdge(2, 4); 
    g.greedyColoring(); 
    g.DSATURColoring(); 
    g.WelshPowellColoring(); 
    return 0; 
}