/* EJERCICIO 3 */

/* En mi implementación de una lsita simplemente enlazada, utilizo shared_ptr para aprovechar el manejo de memoria automático.
Evitando tener que borrar la memoria */

#include <iostream>
#include <memory>

using namespace std;

struct node { // Inicializo la estructura de nodo con un valor y puntero a siguiente
    int data;
    shared_ptr<node> next;
};

// i. create_node(): devuelve un nodo.
shared_ptr<node> create_node(int data) {
    auto new_node = make_shared<node>(); // Creo un nuevo nodo
    new_node->data = data; // Inicializo el dato
    new_node->next = nullptr; // Inicializo puntero a NULL
    return new_node;
}

// ii. push_front(): inserta un nodo al frente de la lista.
void push_front(shared_ptr<node>& head, int data) {
    auto new_node = create_node(data); // Creo un nodo nuevo
    new_node->next = head; // Si no hay head apunta a Null
    head = new_node; // Asigno head como el nuevo nodo
}

// iii. push_back(): inserta un nodo al final de la lista.
void push_back(shared_ptr<node>& head, int data) {
    auto new_node = create_node(data); 
    if (!head) { // Si no hay head, el nuevo nodo es el head
        head = new_node;
        return;
    }
    auto curr = head;
    while (curr->next) {
        curr = curr->next; // Recorro la lista hasta llegar a puntero a NULL
    }
    curr->next = new_node; // Asigno último puntero al nuevo nodo
}

// iv. insert(): inserta un nodo en la posición dada. Si la posición es mayor, lo agrega al final.
void insert(shared_ptr<node>& head, int pos, int data) {
    if (pos <= 0) { // Si la posición es menor o igual a 0, inserto nodo al principio de la lista
        push_front(head, data);
        return;
    }

    int i = 0;
    auto curr = head;
    while (curr && i < pos - 1) { // Recorro hasta puntero a null o hasta la posición dada
        curr = curr->next;
        i++;
    }

    if (!curr) { // Si la posición es más grande que el largo, inserto el nodo al final de la lista
        cout << "La posición dada es mayor al largo de la lista, agregando al final" << endl;
        push_back(head, data);
        return;
    }

    auto new_node = create_node(data); // Si la posición no es mayor, creo el nodo
    new_node->next = curr->next; // Asigno el puntero a next del nuevo nodo al puntero next del nodo anterior
    curr->next = new_node; // Asigno el puntero a next del nodo anterior al nuevo nodo
}

// v. erase(): borra un nodo en la posición dada. Si la posición es mayor, borra el último nodo.
void erase(shared_ptr<node>& head, int pos) {
    if (!head) return; // Si la lista esta vacía, termina la función

    if (pos <= 0) { // Si la posición refiere al head, elimino el head
        head = head->next; // Como es un shared ptr, cuando ya no haya referencias apuntando hacia el ptr, se elimina automáticamente 
        return;
    }

    auto curr = head;
    shared_ptr<node> prev = nullptr; // Recorro guardando el nodo anterior
    int i = 0;

    while (curr->next && i < pos) {
        prev = curr;
        curr = curr->next;
        i++;
    }

    if (!curr->next) { // Si la posición es mayor al largo de la lista, borro el último nodo
        if (prev) {
            prev->next = nullptr;
        } else {
            head = nullptr;
        }
        return;
    }

    prev->next = curr->next; // Elimina al nodo deseado, modificando los punteros ("saltea al nodo")
}

// vi. print_list(): imprime la lista.
void print_list(const shared_ptr<node>& head) {
    auto curr = head;
    while (curr) { // Recorre la lista
        cout << curr->data; // Imprime cada valor
        if (curr->next) {
            cout << " -> ";
        }
        curr = curr->next;
    }
    cout << endl;
}

int main() {
    shared_ptr<node> head = nullptr;

    cout << "Creando lista" << endl;
    push_front(head, 30);
    push_front(head, 20);
    push_front(head, 10);
    print_list(head);

    cout << "\nAgregando al final:" << endl;
    push_back(head, 40);
    push_back(head, 50);
    print_list(head);

    cout << "\nInsertando en posición 2 (entre 20 y 30):" << endl;
    insert(head, 2, 25);
    print_list(head);

    cout << "\nInsertando en posición 0 (inicio):" << endl;
    insert(head, 0, 5);
    print_list(head);

    cout << "\nInsertando en posición 100 (muy grande, se agrega al final):" << endl;
    insert(head, 100, 60);
    print_list(head);

    cout << "\nBorrando posición 3 (debería borrar el 25):" << endl;
    erase(head, 3);
    print_list(head);

    cout << "\nBorrando primera posición:" << endl;
    erase(head, 0);
    print_list(head);

    cout << "\nBorrando posición 100 (muy grande, borra el último):" << endl;
    erase(head, 100);
    print_list(head);

    cout << "\nLista final:" << endl;
    print_list(head);

    return 0;
}
