// 3. Implemente una lista enlazada que utilice nodos que simplemente contengan un
// valor y una dirección de memoria de un nodo. Adicionalmente, agregue las siguientes
// funciones para manejar la lista:

// Presentar ejemplos que verifiquen el funcionamiento requerido en las funciones i-vi y,
// muy importante para el ejercicio, sólo utilizar smart pointers. 
#include <iostream>
#include <memory>

using namespace std;

struct node {
    int data;
    shared_ptr<node> next;
};

// i. create_node(): devuelve un nodo.
shared_ptr<node> create_node(int data) {
    auto new_node = make_shared<node>();
    new_node->data = data;
    new_node->next = nullptr;
    return new_node;
}

// ii. push_front(): inserta un nodo al frente de la lista.
void push_front(shared_ptr<node>& head, int data) {
    auto new_node = create_node(data);
    new_node->next = head; // Si no hay head apunta a Null
    head = new_node;
}

// iii. push_back(): inserta un nodo al final de la lista.
void push_back(shared_ptr<node>& head, int data) {
    auto new_node = create_node(data);
    if (!head) {
        head = new_node;
        return;
    }
    auto curr = head;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = new_node;
}

// iv. insert(): inserta un nodo en la posición dada. Si la posición es mayor, lo agrega al final.
void insert(shared_ptr<node>& head, int pos, int data) {
    if (pos <= 0) {
        push_front(head, data);
        return;
    }

    int i = 0;
    auto curr = head;
    while (curr && i < pos - 1) {
        curr = curr->next;
        i++;
    }

    if (!curr) {
        cout << "La posición dada es mayor al largo de la lista, agregando al final" << endl;
        push_back(head, data);
        return;
    }

    auto new_node = create_node(data);
    new_node->next = curr->next;
    curr->next = new_node;
}

// v. erase(): borra un nodo en la posición dada. Si la posición es mayor, borra el último nodo.
void erase(shared_ptr<node>& head, int pos) {
    if (!head) return;

    if (pos <= 0) {
        head = head->next;
        return;
    }

    auto curr = head;
    shared_ptr<node> prev = nullptr;
    int i = 0;

    while (curr->next && i < pos) {
        prev = curr;
        curr = curr->next;
        i++;
    }

    if (!curr->next) {
        if (prev) {
            prev->next = nullptr;
        } else {
            head = nullptr;
        }
        return;
    }

    prev->next = curr->next;
}

// vi. print_list(): imprime la lista.
void print_list(const shared_ptr<node>& head) {
    auto curr = head;
    while (curr) {
        cout << curr->data;
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
