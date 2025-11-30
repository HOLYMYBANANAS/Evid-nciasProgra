#ifndef MOVIE_H_
#define MOVIE_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Movie {
private:
    string title;     // O(1)
    int rating;       // O(1)

public:
    Movie() : title(""), rating(0) {}                     // O(1)
    Movie(const string& t, int r) : title(t), rating(r) {} // O(1)

    // --- Getters / Setters ---
    // Todos O(1)
    string getTitle() const { return title; }  // O(1)
    int getRating() const { return rating; }   // O(1)

    void setTitle(const string& t) { title = t; } // O(1)
    void setRating(int r) { rating = r; }         // O(1)

    // ------------------------------------------------------------
    // Comparadores
    // Comparan enteros y strings
    // Comparar strings cuesta O(n)
    // ------------------------------------------------------------

    bool operator<(const Movie& other) const {
        // rating : O(1)
        // title  : O(n)
        if (rating != other.rating) return rating < other.rating;
        return title < other.title;
    } // Complejidad: O(n)

    bool operator>(const Movie& other) const {
        if (rating != other.rating) return rating > other.rating;
        return title > other.title;
    } // Complejidad: O(n)

    bool operator==(const Movie& other) const {
        // title == other.title -> O(n)
        // rating == other.rating -> O(1)
        return title == other.title && rating == other.rating;
    } // O(n)

    Movie& operator=(const Movie& other) {
        // asignación de string: O(n)
        if (this != &other) {
            title = other.title; // O(n)
            rating = other.rating; // O(1)
        }
        return *this;
    } // O(n)

    // Conversión a string
    string toString() const {
        // construir string = O(n)
        stringstream ss;
        ss << title << " (" << rating << ")";
        return ss.str();
    } // O(n)
};

// operador << imprime -> O(n)
inline ostream& operator<<(ostream& os, const Movie& m) {
    os << m.getTitle() << " (" << m.getRating() << ")";
    return os;
} // O(n)

#endif /* MOVIE_H_ */
