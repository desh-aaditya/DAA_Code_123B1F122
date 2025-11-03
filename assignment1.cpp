#include <iostream> 
#include <vector> 
#include <string> 
using namespace std; 
struct Order { 
    long long timestamp; 
    string details; 
}; 
void merge(vector<Order>& arr, int left, int mid, int right) { 
    int start1 = left; 
    int start2 = mid + 1; 
    while (start1 <= mid && start2 <= right) { 
        if (arr[start1].timestamp <= arr[start2].timestamp) { 
            start1++; 
        } else { 
            Order value = arr[start2]; 
            int index = start2; 
            while (index != start1) { 
                arr[index] = arr[index - 1]; 
 
                index--; 
            } 
            arr[start1] = value; 
            start1++; 
            mid++; 
            start2++; 
        } 
    } 
} 
void mergeSort(vector<Order>& arr, int left, int right) { 
    if (left < right) { 
        int mid = left + (right - left) / 2; 
        mergeSort(arr, left, mid); 
        mergeSort(arr, mid + 1, right); 
        merge(arr, left, mid, right); 
    } 
} 
int main() { 
    int n; 
    cout << "Enter number of orders: "; 
 
    cin >> n; 
    vector<Order> orders(n); 
    cout << "Enter timestamp and details for each order:\n"; 
    for (int i = 0; i < n; i++) { 
        cin >> orders[i].timestamp >> orders[i].details; 
    } 
    mergeSort(orders, 0, n - 1); 
    cout << "\nSorted Orders (by timestamp):\n"; 
    for (int i = 0; i < n; i++) { 
        cout << orders[i].timestamp << " " << orders[i].details << endl; 
    } 
    return 0; 
}  