# Proyecto: Ranking de Películas

Este proyecto es una aplicación de consola que permite gestionar un ranking dinámico de películas. El sistema incluye funcionalidades para agregar, buscar, eliminar, ordenar y guardar información en un archivo CSV, utilizando estructuras de datos eficientes (AVL) y algoritmos de ordenamiento (QuickSort).

---

## Descripción del avance 1

En el primer avance se desarrolló una versión inicial del sistema utilizando un `vector<Movie>` como estructura principal.  
Este avance incluyó:

- Registro básico de películas con título y rating.
- Ordenamiento con **Bubble Sort** para mostrar el ranking.
- División del programa en módulos iniciales.
- Lógica simple de menú interactivo.

---

## Descripción del avance 2

En el segundo avance se realizó un rediseño completo de la estructura del proyecto:

- Sustitución del vector por un **Árbol AVL**, permitiendo inserciones, eliminaciones y búsquedas en **O(log n)**.
- Implementación de recorridos para mantener el ranking automáticamente ordenado por calificación.
- Lectura y escritura del archivo `peliculas.csv`.
- Mejora general de la modularidad.
- Menú de opciones ampliado y optimizado.

---

## Cambios sobre el primer avance

**Cambio 1: Sustitución de Bubble Sort por AVL**  
*Razón:* Bubble Sort era ineficiente para escalar y el vector exigía ordenar de nuevo tras cada operación. El AVL mantiene el ranking ordenado de manera automática.

**Cambio 2: Lectura/escritura desde CSV**  
*Razón:* Para cumplir con los requisitos del curso y conservar persistencia entre ejecuciones.

**Cambio 3: Eliminación del vector como estructura principal**  
*Razón:* Su operación para insertar/eliminar era costosa comparada con el árbol AVL.

---

## Descripción del avance 3

En este avance se integraron técnicas adicionales para mejorar la funcionalidad y la eficiencia del sistema:

- Se añadió **QuickSort** para ordenar alfabéticamente bajo demanda.
- Se corrigió y fortaleció la búsqueda de películas.
- Se completaron las funciones de alta, baja, actualización y guardado.
- Se solucionó un problema crítico al cargar el CSV: ahora se ignora la cabecera.
- Se refinó la interfaz del menú y los mensajes del sistema.

---

## Cambios sobre el segundo avance

**Cambio 1: Implementación de QuickSort**  
*Razón:* El AVL ordena por calificación, no por título. QuickSort permite obtener un orden alfabético eficiente cuando el usuario lo solicita.

**Cambio 2: Manejo robusto del CSV**  
*Razón:* La lectura de la cabecera generaba errores y registros inválidos; se añadió validación de líneas.

**Cambio 3: Correcciones en búsqueda y actualización**  
*Razón:* Se requería una interacción más clara y exacta para localizar y modificar elementos dentro del AVL.

---

## Entrega final

La entrega final contiene:

- Un sistema completo capaz de gestionar un ranking de películas dinámico.
- Estructura basada en AVL para mantener el ranking ordenado por calificación.
- QuickSort para ordenamiento alfabético opcional.
- Mecanismos de carga y guardado en `peliculas.csv`.
- Menú funcional y claro para interactuar con todas las operaciones.
- Código modular dividido en `main.cpp`, `movie.h`, `avl.h` y `sorting.h`.

---

## Cambios sobre el tercer avance

**Cambio 1: Ajustes finales en mensajes y validaciones**  
*Razón:* Mejorar la experiencia de usuario y evitar datos inválidos.

**Cambio 2: Mantenimiento de consistencia entre AVL y CSV**  
*Razón:* Asegurar que los datos persistidos correspondan exactamente a la estructura interna.

**Cambio 3: Limpieza general del código y mejor documentación**  
*Razón:* Cumplir con estándares del curso y entregar un código profesional.

---

## Instrucciones para compilar el proyecto
Ejecuta el siguiente comando en la terminal:

`g++ main.cpp movie.h sorting.h avl.h -std=c++11 -o final` 

## Instrucciones para ejecutar el proyecto
Ejecuta el siguiente comando en la terminal:

`./final` 

## Descripción de las entradas del avance de proyecto

===== MENÚ DE OPCIONES =====  
1. Mostrar ranking (por calificación – AVL)  
2. Agregar película  
3. Eliminar película  
4. Buscar película  
5. Actualizar ranking de una película  
6. Ordenar alfabéticamente (QuickSort)  
7. Guardar cambios en CSV  
8. Salir  
Selecciona una opción: (entre 1 y 8)

Además:

- En **Agregar película** se solicita:  
  `Título:` y `Rating (0 a 100):`
- En **Eliminar película** se solicita:  
  `Título a eliminar:`
- En **Buscar película**:  
  `Título a buscar:`
- En **Actualizar ranking**:  
  `Título:` y `Nuevo rating:`
- En **Ordenar alfabéticamente** no se solicita entrada adicional (solo se ejecuta QuickSort).
- En **Guardar cambios** se escribe el AVL completo a `peliculas.csv`.

## Descripción de las salidas del avance de proyecto

- **Ranking (AVL – in-order):**  
  Se imprime como:  
  `Título (Rating)`  
  ordenado por calificación y en caso de empate, por título.

- **Ranking alfabético (QuickSort):**  
  Muestra películas ordenadas por título ascendente.

- **Mensajes de confirmación** al:
  - agregar película  
  - eliminar película  
  - actualizar ranking  
  - guardar cambios  
  - errores informativos (no encontrada, rating inválido, CSV invalido, etc.)

- **Archivo `peliculas.csv`** actualizado **solo** cuando el usuario usa la opción *Guardar cambios*.

- **Advertencias por datos inválidos o no encontrados.**

# Desarrollo de competencias

## SICT0301: Evalúa los componentes

### Análisis de complejidad de ordenamiento

**QuickSort:**
- Mejor/promedio: **O(n log n)**
- Peor: **O(n²)**  
Aplicado únicamente cuando el usuario solicita orden alfabético.

### Análisis de complejidad de estructuras

**AVL:**
- Inserción: **O(log n)**
- Eliminación: **O(log n)**
- Búsqueda: **O(log n)**
- Recorrido in-order: **O(n)**  

Esta estructura fue seleccionada por su eficiencia frente a un vector tradicional.

### Complejidad general del programa

La complejidad final se basa principalmente en:

- Operaciones en AVL: **O(log n)**
- Recorridos: **O(n)**
- Ordenamiento opcional: **O(n log n)**
- Lectura y escritura en CSV: **O(n)**  

Se demuestra un diseño eficiente y escalable.

---

## SICT0302: Toma decisiones

### Selección del algoritmo de ordenamiento
QuickSort fue elegido debido a su excelente rendimiento promedio en colecciones grandes y su eficiencia al ordenar datos que pueden llegar en cualquier orden. Además, su implementación es relativamente sencilla y permite ordenar rápidamente la lista de películas por título sin requerir estructuras adicionales. Aunque en el peor caso puede degradarse, su desempeño general y su compatibilidad con comparaciones entre cadenas lo hacen apropiado para este proyecto.

### Selección de estructura de datos
El árbol AVL se seleccionó porque garantiza operaciones de inserción, eliminación y búsqueda en tiempo logarítmico, lo que resulta ideal para un ranking dinámico de películas. A diferencia de una lista simple, el AVL mantiene el balance automáticamente, evitando degradaciones en el rendimiento a medida que crece el número de elementos. Esto asegura consultas rápidas y un acceso eficiente al ordenamiento por calificación, cualidades esenciales para la funcionalidad del sistema.

---

## SICT0303: Implementa acciones científicas

### Consulta de información
El sistema realiza búsquedas y recorridos dentro del árbol AVL de manera eficiente, aprovechando su estructura balanceada para garantizar tiempos de respuesta rápidos. Esto permite que el usuario obtenga resultados inmediatos al consultar el ranking, buscar títulos específicos o verificar la existencia de una película. La implementación asegura que cada operación siga un proceso lógico y sistemático, alineado con prácticas científicas de organización y análisis de datos

### Lectura de archivo
Durante la carga inicial, el programa procesa el archivo peliculas.csv validando cada línea antes de incorporarla a la estructura de datos. Se omite correctamente la cabecera y se manejan posibles inconsistencias en el formato, evitando interrupciones o inserciones erróneas. Este proceso refleja una metodología rigurosa de recopilación y depuración de información, asegurando que solo datos válidos ingresen al AVL.

### Escritura de archivo
El sistema exporta la información almacenada en el AVL nuevamente hacia peliculas.csv, manteniendo un formato coherente y ordenado. La escritura se realiza de forma controlada para conservar la integridad del archivo, garantizando que los cambios hechos por el usuario se reflejen con precisión. Esto demuestra la aplicación de procedimientos sistemáticos para documentar, preservar y actualizar datos de manera confiable.