#ifndef SORTING_H_
#define SORTING_H_

#include <vector>
#include "movie.h"
using namespace std;

// ----------------------------------------------------
// Comparador alfabético
// Comparación de strings → O(k), donde k = tamaño del título
// Para análisis algorítmico se considera O(1) porque k es pequeño y fijo.
// ----------------------------------------------------
bool movieLess(const Movie& a, const Movie& b) {
    return a.getTitle() < b.getTitle(); // O(n)
} // Complejidad total: O(n)


// ----------------------------------------------------
// PARTITION de QuickSort
// ----------------------------------------------------
int partitionMovies(vector<Movie>& arr, int low, int high) {

    // pivot = arr[high] : O(1)
    Movie pivot = arr[high];

    int i = low - 1; // O(1)

    // Bucle j = low → high-1 (recorre n elementos)
    // Cada comparación usa movieLess → O(n)
    // Cada swap → O(1)
    for (int j = low; j < high; j++) {     // Se ejecuta O(n) veces
        if (movieLess(arr[j], pivot)) {    // O(n)
            i++;                           // O(1)
            swap(arr[i], arr[j]);          // O(1)
        }
    }

    swap(arr[i + 1], arr[high]); // O(1)
    return i + 1; // O(1)
}

// COMPLEJIDAD de partitionMovies:
// → Recorrido lineal: O(n)
// → Comparaciones y swaps constantes
// → TOTAL: **O(n)**


// ----------------------------------------------------
// QuickSort recursivo
// ----------------------------------------------------
void quickSortMoviesHelper(vector<Movie>& arr, int low, int high) {
    if (low < high) { // O(1)

        // partition: O(n)
        int pi = partitionMovies(arr, low, high);

        // Recursión en dos subarreglos
        // Mejor y promedio: O(n log n)
        // Peor caso: O(n²)
        quickSortMoviesHelper(arr, low, pi - 1);
        quickSortMoviesHelper(arr, pi + 1, high);
    }
}


// ----------------------------------------------------
// QuickSort público
// ----------------------------------------------------
void quickSortMovies(vector<Movie>& arr) {
    if (arr.size() < 2) return;   // O(1)
    quickSortMoviesHelper(arr, 0, arr.size() - 1);
}

// COMPLEJIDAD FINAL:
// Promedio:  O(n log n)
// Mejor caso: O(n log n)
// Peor caso: O(n²)

#endif
