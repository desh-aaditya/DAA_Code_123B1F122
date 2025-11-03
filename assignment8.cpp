#include <bits/stdc++.h> 
using namespace std; 
 
const int INF = 1e9; 
 
struct Node { 
    vector<int> path; 
    vector<vector<int>> reducedMatrix; 
    int cost; 
    int vertex; 
    int level; 
}; 
 
int N; 
 
int reduceMatrix(vector<vector<int>>& matrix) { 
    int reduction = 0; 
    for (int i = 0; i < N; i++) { 
        int rowMin = INF; 
        for (int j = 0; j < N; j++) 
            if (matrix[i][j] < rowMin) rowMin = matrix[i][j]; 
        if (rowMin != INF && rowMin > 0) { 
            reduction += rowMin; 
            for (int j = 0; j < N; j++) 
                if (matrix[i][j] != INF) matrix[i][j] -= rowMin; 
        } 
    } 
 
    for (int j = 0; j < N; j++) { 
        int colMin = INF; 
        for (int i = 0; i < N; i++) 
            if (matrix[i][j] < colMin) colMin = matrix[i][j]; 
        if (colMin != INF && colMin > 0) { 
            reduction += colMin; 
            for (int i = 0; i < N; i++) 
                if (matrix[i][j] != INF) matrix[i][j] -= colMin; 
        } 
    } 
    return reduction; 
} 
 
Node* newNode(vector<vector<int>> parentMatrix, vector<int> const& path, int level, int i, int 
j) { 
    Node* node = new Node; 
    node->path = path; 
    if (level != 0) 
        node->path.push_back(j); 
    node->reducedMatrix = parentMatrix; 
 
    if (level != 0) 
        for (int k = 0; k < N; k++) { 
            node->reducedMatrix[i][k] = INF; 
            node->reducedMatrix[k][j] = INF; 
        } 
 
    node->reducedMatrix[j][0] = INF; 
    node->level = level; 
    node->vertex = j; 
    return node; 
} 
 
int calculateCost(Node* node) { 
    return node->cost + reduceMatrix(node->reducedMatrix); 
} 
 
struct compare { 
    bool operator()(const Node* lhs, const Node* rhs) const { 
        return lhs->cost > rhs->cost; 
    } 
}; 
 
void solveTSP(vector<vector<int>> costMatrix) { 
    N = costMatrix.size(); 
 
    priority_queue<Node*, vector<Node*>, compare> pq; 
 
    vector<vector<int>> rootMatrix = costMatrix; 
    int rootCost = reduceMatrix(rootMatrix); 
 
    Node* root = new Node; 
    root->path.push_back(0); 
    root->reducedMatrix = rootMatrix; 
    root->cost = rootCost; 
    root->level = 0; 
    root->vertex = 0; 
 
    pq.push(root); 
 
    int minCost = INF; 
    vector<int> bestPath; 
 
    while (!pq.empty()) { 
        Node* minNode = pq.top(); 
        pq.pop(); 
 
        int i = minNode->vertex; 
 
        if (minNode->level == N - 1) { 
            minNode->path.push_back(0); 
            int totalCost = minNode->cost + costMatrix[i][0]; 
            if (totalCost < minCost) { 
                minCost = totalCost; 
                bestPath = minNode->path; 
            } 
            continue; 
        } 
 
        for (int j = 0; j < N; j++) { 
            if (minNode->reducedMatrix[i][j] != INF) { 
                Node* child = newNode(minNode->reducedMatrix, minNode->path, minNode->level 
+ 1, i, j); 
                child->cost = minNode->cost + minNode->reducedMatrix[i][j] + reduceMatrix(child
>reducedMatrix); 
                pq.push(child); 
            } 
        } 
    } 
 
    cout << "\nOptimal Delivery Route:\n"; 
    for (int i = 0; i < bestPath.size(); i++) 
        cout << bestPath[i] << (i == bestPath.size() - 1 ? "" : " -> "); 
    cout << "\nTotal Minimum Cost: " << minCost << endl; 
} 
 
int main() { 
    int n; 
    cout << "Enter number of cities: "; 
    cin >> n; 
 
    vector<vector<int>> costMatrix(n, vector<int>(n)); 
    cout << "Enter cost matrix (use 999 for no direct route):\n"; 
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) { 
            cin >> costMatrix[i][j]; 
            if (costMatrix[i][j] == 999) costMatrix[i][j] = INF; 
        } 
 
    solveTSP(costMatrix); 
    return 0; 
} 