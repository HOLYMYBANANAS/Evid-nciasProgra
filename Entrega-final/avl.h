#ifndef AVL_H_
#define AVL_H_

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


// ============================================================
// AVL Tree Implementation
// ------------------------------------------------------------
// Todas las operaciones de búsqueda, inserción y eliminación
// mantienen O(log n) gracias al balanceo automático del AVL.
// Los recorridos completos son O(n).
// ============================================================


template <class T>
class AVL {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;
        int height;
        Node(const T& v) : value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    // ============================================================
    // nodeHeight
    // ------------------------------------------------------------
    // O(1): acceso directo a datos del nodo.
    // ============================================================
    int nodeHeight(Node* n) const { return (n == nullptr) ? 0 : n->height; }

    // ============================================================
    // updateHeight
    // ------------------------------------------------------------
    // O(1): solo compara dos valores y asigna.
    // ============================================================
    void updateHeight(Node* n) {
        if (n) n->height = 1 + max(nodeHeight(n->left), nodeHeight(n->right));
    }

    // ============================================================
    // getBalance
    // ------------------------------------------------------------
    // O(1): resta de alturas.
    // ============================================================
    int getBalance(Node* n) const {
        return (n == nullptr) ? 0 : nodeHeight(n->left) - nodeHeight(n->right);
    }

    // ============================================================
    // rotateRight
    // ------------------------------------------------------------
    // O(1): rotación simple, tiempo constante.
    // ============================================================
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);
        return x;
    }

    // ============================================================
    // rotateLeft
    // ------------------------------------------------------------
    // O(1): rotación simple, operaciones constantes.
    // ============================================================
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);
        return y;
    }

    // ============================================================
    // balance
    // ------------------------------------------------------------
    // O(1): check de balance + posibles rotaciones (O(1)).
    // ============================================================
    Node* balance(Node* n) {
        if (!n) return n;
        updateHeight(n);
        int bf = getBalance(n);

        // Left heavy
        if (bf > 1) {
            if (getBalance(n->left) < 0)
                n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        // Right heavy
        if (bf < -1) {
            if (getBalance(n->right) > 0)
                n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        return n;
    }

    // ============================================================
    // insertNode
    // ------------------------------------------------------------
    // O(log n) promedio y garantizado por el AVL.
    // Recorrido descendente + balanceo O(1).
    // ============================================================
    Node* insertNode(Node* node, const T& value) {
        if (node == nullptr) return new Node(value);

        if (value < node->value)
            node->left = insertNode(node->left, value);
        else if (value > node->value)
            node->right = insertNode(node->right, value);
        else
            return node; // no duplicates exactos

        return balance(node);
    }

    // ============================================================
    // findMin
    // ------------------------------------------------------------
    // O(log n): baja hasta el extremo izquierdo.
    // ============================================================
    Node* findMin(Node* node) {
        Node* cur = node;
        while (cur && cur->left) cur = cur->left;
        return cur;
    }

    // ============================================================
    // removeNode
    // ------------------------------------------------------------
    // O(log n): búsqueda + rebalanceo.
    // ============================================================
    Node* removeNode(Node* node, const T& value) {
        if (!node) return nullptr;

        if (value < node->value)
            node->left = removeNode(node->left, value);
        else if (value > node->value)
            node->right = removeNode(node->right, value);
        else {
            // found node to remove
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) {
                    delete node;
                    node = nullptr;
                } else {
                    Node* toDelete = node;
                    node = temp;
                    delete toDelete;
                }
            } else {
                // two children: successor
                Node* temp = findMin(node->right);
                node->value = temp->value;
                node->right = removeNode(node->right, temp->value);
            }
        }
        if (!node) return node;
        return balance(node);
    }

    // ============================================================
    // searchNode
    // ------------------------------------------------------------
    // O(log n): búsqueda binaria en árbol balanceado.
    // ============================================================
    Node* searchNode(Node* node, const T& value) const {
        if (!node) return nullptr;
        if (value == node->value) return node;
        if (value < node->value) return searchNode(node->left, value);
        return searchNode(node->right, value);
    }

    // ============================================================
    // searchByTitle
    // O(n): el árbol está ordenado por 'value', no por título.
    // Para encontrar un título se debe recorrer potencialmente
    // todo el árbol, ya que no es clave de ordenamiento.
    // ============================================================
    bool searchByTitle(Node* node, const string& title) const {
        if (!node) return false;
        if (node->value.getTitle() == title) return true;
        return searchByTitle(node->left, title) || searchByTitle(node->right, title);
    }

    // ============================================================
    // inorderDesc
    // ------------------------------------------------------------
    // O(n): visita todos los nodos una vez.
    // ============================================================
    void inorderDesc(Node* node, stringstream& ss) const {
        if (!node) return;
        inorderDesc(node->right, ss);
        ss << node->value.toString() << "\n";
        inorderDesc(node->left, ss);
    }

    // ============================================================
    // toVectorHelper
    // ------------------------------------------------------------
    // O(n): recorrido completo.
    // ============================================================
    void toVectorHelper(Node* node, vector<T>& out) const {
        if (!node) return;
        toVectorHelper(node->right, out);
        out.push_back(node->value);
        toVectorHelper(node->left, out);
    }

    // ============================================================
    // clearNode
    // ------------------------------------------------------------
    // O(n): libera todos los nodos del árbol.
    // ============================================================
    void clearNode(Node* node) {
        if (!node) return;
        clearNode(node->left);
        clearNode(node->right);
        delete node;
    }

    // ============================================================
    // toVectorInOrderHelper
    // ------------------------------------------------------------
    // O(n): recorrido completo.
    // ============================================================
    void toVectorInOrderHelper(Node* node, vector<T>& out) const {
        if (!node) return;
        toVectorInOrderHelper(node->left, out);
        out.push_back(node->value);
        toVectorInOrderHelper(node->right, out);
    }

public:

    // ============================================================
    // Constructor
    // ------------------------------------------------------------
    // O(1)
    // ============================================================
    AVL() : root(nullptr) {}

    // ============================================================
    // Destructor
    // ------------------------------------------------------------
    // O(n): libera toda la memoria del árbol.
    // ============================================================
    ~AVL() { clearNode(root); root = nullptr; }

    // ============================================================
    // insert
    // ------------------------------------------------------------
    // O(log n)
    // ============================================================
    void insert(const T& value) { root = insertNode(root, value); }

    // ============================================================
    // remove
    // ------------------------------------------------------------
    // O(log n)
    // ============================================================
    void remove(const T& value) { root = removeNode(root, value); }

    // ============================================================
    // contains
    // ------------------------------------------------------------
    // O(log n)
    // ============================================================
    bool contains(const T& value) const {
        return searchNode(root, value) != nullptr;
    }

    // ============================================================
    // findByTitle
    // ------------------------------------------------------------
    // O(n): no está ordenado por título.
    // ============================================================
    bool findByTitle(const string& title) const {
        return searchByTitle(root, title);
    }

    // ============================================================
    // get
    // ------------------------------------------------------------
    // O(log n)
    // ============================================================
    T* get(const T& value) const {
        Node* n = searchNode(root, value);
        return n ? &(n->value) : nullptr;
    }

    // ============================================================
    // inorder
    // ------------------------------------------------------------
    // O(n)
    // ============================================================
    string inorder() const {
        stringstream ss;
        inorderDesc(root, ss);
        return ss.str();
    }

    // ============================================================
    // toVector
    // ------------------------------------------------------------
    // O(n)
    // ============================================================
    vector<T> toVector() const {
        vector<T> out;
        toVectorHelper(root, out);
        return out;
    }

    // ============================================================
    // exportInorder
    // ------------------------------------------------------------
    // O(n)
    // ============================================================
    void exportInorder(vector<T>& out) const {
        toVectorHelper(root, out);
    }

    // ============================================================
    // clear
    // ------------------------------------------------------------
    // O(n)
    // ============================================================
    void clear() {
        clearNode(root);
        root = nullptr;
    }

    // ============================================================
    // empty
    // ------------------------------------------------------------
    // O(1)
    // ============================================================
    bool empty() const { return root == nullptr; }

    // ============================================================
    // toVectorInOrder
    // ------------------------------------------------------------
    // O(n)
    // ============================================================
    vector<T> toVectorInOrder() const {
        vector<T> out;
        toVectorInOrderHelper(root, out);
        return out;
    }

};

// ============================================================
//             COMPLEJIDAD TOTAL DE OPERACIONES (AVL)
// ============================================================
//
// Inserción:
// Promedio: O(log n)
// Mejor caso: O(log n)
// Peor caso: O(log n)
//
// Búsqueda:
// Promedio: O(log n)
// Mejor caso: O(log n)
// Peor caso: O(log n)
//
// Eliminación:
// Promedio: O(log n)
// Mejor caso: O(log n)
// Peor caso: O(log n)
//
// Rotaciones (simple y doble):
// Todas: O(1)
//
// Recorridos (inorder / preorder / postorder):
// Promedio: O(n)
// Mejor caso: O(n)
// Peor caso: O(n)
//
// Altura del árbol:
// Siempre O(log n) debido al balanceo automático del AVL.
//
// Nota:
// La tabla mantiene su desempeño logarítmico en todos los casos gracias
// a la propiedad de balanceo del AVL, que evita casos degenerados.
// ============================================================

#endif /* AVL_H_ */
