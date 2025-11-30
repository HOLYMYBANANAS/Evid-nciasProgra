/*
 * main.cpp
 *
 *  Created on: 23/10/2025
 *      Author: FGPG
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include "movie.h"
#include "avl.h"
#include "sorting.h"


using namespace std;

void cargarPeliculas(AVL<Movie>& arbol, const string& nombreArchivo);
void guardarPeliculas(AVL<Movie>& arbol, const string& nombreArchivo);
void mostrarMenu();

int main() {
    AVL<Movie> arbol;
    string archivo = "peliculas.csv";

    cargarPeliculas(arbol, archivo);

    int opcion;
    do {
        mostrarMenu();
        cout << "Selecciona una opción: ";
        cin >> opcion;
        cin.ignore(); // Limpieza inicial básica

        // =====================================================
        // 1. MOSTRAR RANKING
        // =====================================================
        if (opcion == 1) {
            cout << "\n=== Ranking de Películas ===\n";
            cout << arbol.inorder();
        }

        // =====================================================
        // 2. AGREGAR PELÍCULA
        // =====================================================
        else if (opcion == 2) {
            cout << "\n=== Agregar película ===\n";
            cout << "Presiona ENTER para continuar o escribe M para regresar al menú: ";

            string cancelar;
            getline(cin, cancelar);

            if (cancelar == "M" || cancelar == "m") {
                cout << "Operación cancelada. Regresando al menú...\n";
                continue;
            }

            string nombre;
            int calif;

            cout << "Nombre de la película: ";
            getline(cin, nombre);

            cout << "Calificación (0-100): ";
            cin >> calif;
            cin.ignore();

            // Validar rango de calificación (0-100)

            if (calif < 0) {
                cout << "La calificación debe estar entre 0 y 100.\n";
                continue;
            }
            if (calif > 100) {
                cout << "La calificación debe estar entre 0 y 100.\n";
                continue;
            }

            // Evitar letras en la calificación 

            if (cin.fail()) {
                cout << "La calificación debe ser un número.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            // Verificar si la película ya existe
            if (arbol.findByTitle(nombre)) {
                cout << "La película ya existe en el ranking.\n";
                continue;
            }
            
            Movie nueva(nombre, calif);
            arbol.insert(nueva);

            cout << "Película agregada exitosamente.\n";
        }

        // =====================================================
        // 3. ELIMINAR PELÍCULA
        // =====================================================
        else if (opcion == 3) {
            cout << "\n=== Eliminar película ===\n";
            cout << "Presiona ENTER para continuar o escribe M para regresar al menú: ";

            string cancelar;
            getline(cin, cancelar);

            if (cancelar == "M" || cancelar == "m") {
                cout << "Operación cancelada. Regresando al menú...\n";
                continue;
            }

            string nombre;
            cout << "Nombre de la película a eliminar: ";
            getline(cin, nombre);

            string listado = arbol.inorder();
            stringstream ss(listado);
            string linea;
            bool encontrado = false;
            int ratingReal = 0;

            auto limpiar = [](string &s) {
                while (!s.empty() && isspace((unsigned char)s.back()))
                    s.pop_back();
            };

            while (getline(ss, linea)) {
                limpiar(linea);

                if (linea.empty()) continue;

                size_t posPar = linea.rfind('(');
                size_t posParC = linea.rfind(')');
                if (posPar == string::npos || posParC == string::npos) continue;

                string tituloLinea = linea.substr(0, posPar);
                limpiar(tituloLinea);

                if (tituloLinea == nombre) {
                    string ratingStr = linea.substr(posPar + 1, posParC - posPar - 1);
                    try {
                        ratingReal = stoi(ratingStr);
                        encontrado = true;
                        break;
                    } catch (...) {}
                }
            }

            if (encontrado) {
                arbol.remove(Movie(nombre, ratingReal));
                cout << "Película eliminada.\n";
            } else {
                cout << "No se encontró la película '" << nombre << "'.\n";
            }
        }

        // =====================================================
        // 4. BUSCAR PELÍCULA
        // =====================================================
        else if (opcion == 4) {
            cout << "\n=== Buscar película ===\n";
            cout << "Presiona ENTER para continuar o escribe M para regresar al menú: ";

            string cancelar;
            getline(cin, cancelar);

            if (cancelar == "M" || cancelar == "m") {
                cout << "Operación cancelada. Regresando al menú...\n";
                continue;
            }

            string nombre;
            cout << "Nombre de la película a buscar: ";
            getline(cin, nombre);

            if (arbol.findByTitle(nombre)) {
                cout << "La película '" << nombre << "' está en el ranking.\n";
            } else {
                cout << "No se encontró la película.\n";
            }
        }

        // =====================================================
        // 5. GUARDAR ARCHIVO
        // =====================================================
        else if (opcion == 5) {
            guardarPeliculas(arbol, archivo);
            cout << "Datos guardados exitosamente.\n";
        }

        // =====================================================
        // 6. ACTUALIZAR RANKING DE UNA PELÍCULA
        // =====================================================
        else if (opcion == 6) {
            cout << "\n=== Actualizar ranking de una película ===\n";
            cout << "Presiona ENTER para continuar o escribe M para regresar al menú: ";

            string cancelar;
            getline(cin, cancelar);

            if (cancelar == "M" || cancelar == "m") {
                cout << "Operación cancelada. Regresando al menú...\n";
                continue;
            }

            string nombre;
            cout << "Nombre de la película a actualizar: ";
            getline(cin, nombre);

            // Paso 1: obtener el listado inorder (título + rating)
            string listado = arbol.inorder();
            stringstream ss(listado);
            string linea;
            bool encontrado = false;
            int ratingViejo = 0;

            auto limpiar = [](string &s) {
                while (!s.empty() && isspace((unsigned char)s.back()))
                    s.pop_back();
            };

            // Paso 2: buscar la película para obtener su rating real actual
            while (getline(ss, linea)) {
                limpiar(linea);
                if (linea.empty()) continue;

                size_t posPar = linea.rfind('(');
                size_t posParC = linea.rfind(')');
                if (posPar == string::npos || posParC == string::npos) continue;

                string tituloLinea = linea.substr(0, posPar);
                limpiar(tituloLinea);

                if (tituloLinea == nombre) {
                    string ratingStr = linea.substr(posPar + 1, posParC - posPar - 1);
                    try {
                        ratingViejo = stoi(ratingStr);
                        encontrado = true;
                        break;
                    } catch (...) {}
                }
            }

            if (!encontrado) {
                cout << "No se encontró la película '" << nombre << "'.\n";
                continue;
            }

            cout << "Calificación actual: " << ratingViejo << "\n";

            // Paso 3: Leer el nuevo rating
            int nuevoRating;
            cout << "Nuevo rating (0-100): ";
            cin >> nuevoRating;
            cin.ignore();

            // Paso 3.1: Validar rango de calificación (0-100)

            if (nuevoRating < 0) {
                cout << "La calificación debe estar entre 0 y 100.\n";
                continue;
            }

            if (nuevoRating > 100) {
                cout << "La calificación debe estar entre 0 y 100.\n";
                continue;
            }
            // Paso 3.2: Evitar letras en la calificación 

            if (cin.fail()) {
                cout << "La calificación debe ser un número.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            

            // Paso 4: eliminar la versión vieja
            arbol.remove(Movie(nombre, ratingViejo));

            // Paso 5: insertar la versión nueva
            arbol.insert(Movie(nombre, nuevoRating));

            cout << "La calificación de '" << nombre << "' ha sido actualizada.\n";
        }


            

        // =====================================================
        // 7. MOSTRAR RANKING ALFABETICO (QUICKSORT)
        // =====================================================

            else if (opcion == 7) {
                vector<Movie> lista = arbol.toVectorInOrder();  // Copia desde el AVL
                quickSortMovies(lista);                         // Ordena alfabéticamente

                cout << "\n=== Ranking (orden alfabético por nombre) ===\n";
                for (const Movie& m : lista) {
                    cout << m.getTitle() << " (" << m.getRating() << ")\n";
                }

                cout << "\nPresiona ENTER para volver al menú...";
                cin.ignore();
                cin.get();
            }


        // =====================================================
        // 8. SALIR
        // =====================================================
        else if (opcion != 8) {
            cout << "Opción inválida.\n";
        }

    } while (opcion != 8);

    cout << "Saliendo del programa...\n";
    return 0;
}

void cargarPeliculas(AVL<Movie>& arbol, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se encontró el archivo. Se creará uno nuevo al guardar.\n";
        return;
    }

    auto trim = [](string &s) {
        // trim left
        size_t start = 0;
        while (start < s.size() && isspace((unsigned char)s[start])) start++;
        // trim right
        size_t end = s.size();
        while (end > start && isspace((unsigned char)s[end - 1])) end--;
        s = s.substr(start, end - start);
    };

    string linea;
    bool primeraLinea = true;
    while (getline(archivo, linea)) {
        // eliminar BOM si existe
        if (linea.size() >= 3 &&
            (unsigned char)linea[0] == 0xEF &&
            (unsigned char)linea[1] == 0xBB &&
            (unsigned char)linea[2] == 0xBF) {
            linea = linea.substr(3);
        }

        trim(linea);
        if (linea.empty()) continue;

        // Esperamos formato: Titulo,Rating
        size_t comma = linea.find(',');
        if (comma == string::npos) {
            // línea mal formateada -> ignorar
            continue;
        }

        string nombre = linea.substr(0, comma);
        string califStr = linea.substr(comma + 1);
        trim(nombre);
        trim(califStr);

        // Detectar y omitir header en la primera línea (ej. "Peliculas,Rating")
        string lowerNombre = nombre;
        for (auto &c : lowerNombre) c = tolower((unsigned char)c);
        string lowerCal = califStr;
        for (auto &c : lowerCal) c = tolower((unsigned char)c);

        bool califEsNumero = false;
        if (!califStr.empty()) {
            // permitir signo + - y dígitos
            califEsNumero = true;
            size_t i = 0;
            if (califStr[0] == '+' || califStr[0] == '-') i = 1;
            for (; i < califStr.size(); ++i) {
                if (!isdigit((unsigned char)califStr[i])) { califEsNumero = false; break; }
            }
        }

        if (primeraLinea) {
            primeraLinea = false;
            // Si la primera línea no contiene un número válido como rating o su título parece 'peliculas' -> saltar
            if (!califEsNumero || lowerNombre.find("pelicul") != string::npos || lowerCal.find("rating") != string::npos) {
                continue;
            }
        }

        if (!califEsNumero) {
            // registro inválido -> ignorar
            continue;
        }

        try {
            int calif = stoi(califStr);
            // validar rango 0-100 (opcionalmente puedes ajustar)
            if (calif < 0) calif = 0;
            if (calif > 100) calif = 100;
            arbol.insert(Movie(nombre, calif));
        } catch (...) {
            // si stoi falla por alguna razón -> ignorar línea
            continue;
        }
    }

    archivo.close();
}


void guardarPeliculas(AVL<Movie>& arbol, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar.\n";
        return;
    }

    vector<Movie> lista = arbol.toVectorInOrder();
    for (const Movie& m : lista) {
        archivo << m.getTitle() << "," << m.getRating() << "\n";
    }
    archivo.close();
}

void mostrarMenu() {
    cout << "\n===== MENÚ DE OPCIONES =====\n";
    cout << "1. Mostrar ranking de películas\n";
    cout << "2. Agregar nueva película\n";
    cout << "3. Eliminar película\n";
    cout << "4. Buscar película\n";
    cout << "5. Guardar cambios\n";
    cout << "6. Actualizar ranking de una película\n";  
    cout << "7. Mostrar ranking ordenado con Quicksort\n"; 
    cout << "8. Salir\n";
}

