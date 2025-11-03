#include <iostream> 
#include <vector> 
#include <algorithm> 
using namespace std; 
 
struct Item { 
    string name; 
    double weight; 
    double value; 
    bool divisible; 
}; 
 
bool cmp(Item a, Item b) { 
    double r1 = a.value / a.weight; 
    double r2 = b.value / b.weight; 
    return r1 > r2; 
} 
 
 
double fractionalKnapsack(vector<Item> &items, double W) { 
    sort(items.begin(), items.end(), cmp); 
    double totalValue = 0.0; 
     
    cout << "Items selected:\n"; 
    for (auto &item : items) { 
        if (W <= 0) break; 
        if (item.weight <= W) { 
            cout << item.name << " (full) - Weight: " << item.weight << ", Value: " << item.value << "\n"; 
            totalValue += item.value; 
            W -= item.weight; 
        } else if (item.divisible) { 
            double fraction = W / item.weight; 
            cout << item.name << " (fraction " << fraction << ") - Weight: " << W << ", Value: " << item.value * fraction << "\n"; 
            totalValue += item.value * fraction; 
            W = 0; 
        } 
    } 
    return totalValue; 
} 
 
int main() { 
    int n; 
    double W; 
    cin >> n; 
    vector<Item> items(n); 
      for (int i = 0; i < n; i++) { 
        cin >> items[i].name >> items[i].weight >> items[i].value >> items[i].divisible; 
    } 
    cin >> W; 
    double maxUtility = fractionalKnapsack(items, W); 
    cout << "\nMaximum total utility value transported: " << maxUtility; 
 
    return 0; 
} 