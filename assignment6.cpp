#include <bits/stdc++.h> 
using namespace std; 
 
struct Item { 
    string name; 
    int weight; 
    int utility; 
    bool perishable; 
};  
pair<int, vector<int>> knapsackDP(vector<Item> &items, int W) { 
    int n = items.size(); 
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0)); 
 
    for (int i = 1; i <= n; i++) { 
        for (int w = 0; w <= W; w++) { 
            if (items[i - 1].weight <= w) { 
                dp[i][w] = max( 
                    dp[i - 1][w], 
                    dp[i - 1][w - items[i - 1].weight] + items[i - 1].utility 
                ); 
            } else { 
                dp[i][w] = dp[i - 1][w]; 
            } 
        } 
    } 
 
    int maxUtility = dp[n][W]; 
    vector<int> selected; 
 
    int w = W; 
    for (int i = n; i > 0; i--) { 
        if (dp[i][w] != dp[i - 1][w]) { 
            selected.push_back(i - 1); 
            w -= items[i - 1].weight; 
        } 
    } 
 
    reverse(selected.begin(), selected.end()); 
    return {maxUtility, selected}; 
}  

pair<int, vector<int>> greedyApproach(vector<Item> &items, int W) { 
    vector<pair<double, int>> ratio; 
    for (int i = 0; i < items.size(); i++) { 
        ratio.push_back({(double)items[i].utility / items[i].weight, i}); 
    } 
 
    sort(ratio.rbegin(), ratio.rend()); 
 
    int totalWeight = 0, totalUtility = 0; 
    vector<int> selected; 
 
    for (auto &p : ratio) { 
        int i = p.second; 
        if (totalWeight + items[i].weight <= W) { 
            selected.push_back(i); 
            totalWeight += items[i].weight; 
            totalUtility += items[i].utility; 
        } 
    } 
 
    return {totalUtility, selected}; 
}  
void applyPerishablePriority(vector<Item> &items, double multiplier = 1.5) { 
    for (auto &item : items) { 
        if (item.perishable) { 
            item.utility = (int)(item.utility * multiplier); 
        } 
    } 
} 
 
int main() { 
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 
 
    int n, W; 
    cout << "Enter number of items: "; 
    cin >> n; 
8  
    cout << "Enter truck capacity (kg): "; 
    cin >> W; 
 
    vector<Item> items(n); 
    cout << "\nEnter item details (name weight utility perishable[1/0]):\n"; 
    for (int i = 0; i < n; i++) { 
        cin >> items[i].name >> items[i].weight >> items[i].utility >> items[i].perishable; 
    } 
 
    applyPerishablePriority(items); 
 
    auto [maxUtility, selectedDP] = knapsackDP(items, W); 
    auto [approxUtility, selectedGreedy] = greedyApproach(items, W); 
 
    cout << "\n=== Optimal Solution (Dynamic Programming) ===\n"; 
    cout << "Maximum Utility: " << maxUtility << "\nItems Included:\n"; 
    for (int idx : selectedDP) { 
        cout << " - " << items[idx].name << " (Weight: " << items[idx].weight 
             << ", Utility: " << items[idx].utility << ")\n"; 
    } 
 
    cout << "\n=== Greedy Approximation ===\n"; 
    cout << "Approximate Utility: " << approxUtility << "\nItems Included:\n"; 
    for (int idx : selectedGreedy) { 
        cout << " - " << items[idx].name << " (Weight: " << items[idx].weight 
             << ", Utility: " << items[idx].utility << ")\n"; 
    } 
 
    cout << "\nNote: Greedy is faster but may not give the exact optimal result.\n"; 
    return 0; 
} 