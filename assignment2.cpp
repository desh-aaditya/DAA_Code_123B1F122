#include <iostream> 
#include <vector> 
#include <string> 
using namespace std; 
 
// Structure to store movie details 
struct Movie { 
    string title; 
    double imdb_rating; 
    int release_year; 
    int watch_time_popularity; 
}; 
 
// Swap two movies 
void swap(Movie &a, Movie &b) { 
    Movie temp = a; 
    a = b; 
    b = temp; 
} 
 
// Partition function for Quicksort 
int partition(vector<Movie> &movies, int low, int high, string sort_param) { 
    Movie pivot = movies[high];  // choose last element as pivot 
    int i = low - 1; 
 
    for (int j = low; j < high; j++) { 
        bool condition = false; 
        // Decide comparison based on selected sort parameter 
        if (sort_param == "IMDB_Rating") { 
            condition = movies[j].imdb_rating > pivot.imdb_rating; // descending order 
        }  
 
 
else if (sort_param == "Release_Year") { 
             condition = movies[j].release_year > pivot.release_year; // descending 
 
        } else if (sort_param == "Watch_Time_Popularity") { 
            condition = movies[j].watch_time_popularity > pivot.watch_time_popularity; // descending 
        } 
        if (condition) { 
            i++; 
            swap(movies[i], movies[j]); 
        } 
    } 
    swap(movies[i + 1], movies[high]); 
    return i + 1; 
} 
// Quicksort function 
void quickSort(vector<Movie> &movies, int low, int high, string sort_param) { 
    if (low < high) { 
        int pi = partition(movies, low, high, sort_param); 
        quickSort(movies, low, pi - 1, sort_param); 
        quickSort(movies, pi + 1, high, sort_param); 
    } 
} 
int main() { 
    int n; 
    cout << "Enter number of movies: "; 
    cin >> n; 
    vector<Movie> movies(n); 
    cout << "Enter movie details (Title IMDB_Rating Release_Year Watch_Time_Popularity):\n";
    for (int i = 0; i < n; i++) { 
        cin >> movies[i].title >> movies[i].imdb_rating >> movies[i].release_year >> 
movies[i].watch_time_popularity; 
    } 
    string sort_param; 
    cout << "Enter sort parameter (IMDB_Rating / Release_Year / Watch_Time_Popularity): "; 
    cin >> sort_param; 
    quickSort(movies, 0, n - 1, sort_param); 
    cout << "\nSorted Movies (" << sort_param << " descending):\n"; 
    for (auto &m : movies) { 
        cout << m.title << " " << m.imdb_rating << " " << m.release_year << " " << 
m.watch_time_popularity << endl; 
    } 
    return 0; 
}