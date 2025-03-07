// 3. Implemente una lista enlazada que utilice nodos que simplemente contengan un
// valor y una dirección de memoria de un nodo. Adicionalmente, agregue las siguientes
// funciones para manejar la lista:

// Presentar ejemplos que verifiquen el funcionamiento requerido en las funciones i-vi y,
// muy importante para el ejercicio, sólo utilizar smart pointers. 
#include <iostream>
#include <memory>
using namespace std;

struct node{
    int data;
    shared_ptr<node> next;

    node(int data) : data(data), next(nullptr) {}
};

shared_ptr<node> head = nullptr;

// i. create_node(): devuelve un nodo.
shared_ptr<node> create_node(int data){
    auto new_node = make_shared<node>(data);
    return new_node;
}

// ii. push_front(): inserta un nodo al frente de la lista.
void push_front(int data){
    auto new_node = create_node(data);
    new_node -> next = head;
    head = new_node;
}

// iii. push_back(): inserta un nodo al final de la lista.
void push_back(int data){
    auto new_node = create_node(data);
    if (!head){
        head = new_node;
        return;
    }
    auto curr = head;
    while(curr -> next){
        curr = curr -> next;
    }
    curr -> next = new_node;
}

// iv. insert(): inserta un nodo en la posición que se le pase a la función. Si se le pasa
// una posición mayor al largo de la lista, se debe indicar lo ocurrido y se debe de
// agregar el nodo al final de la lista.
void insert(int pos, int data){
    if (pos <= 0){
        push_front(data);
        return;
    }
    int i = 0;
    auto curr = head;
    while (curr && i < pos - 1){
        curr = curr -> next;
        i++;
    }

    if (curr == NULL){
            cout << "La posición dada es mayor al largo de la lista, agregando al final" << endl;
            push_back(data);
            return;
        }

    auto new_node = create_node(data);
    new_node -> next = curr -> next;
    curr -> next = new_node;
}

// v. erase(): borra un nodo en la posición que se le pase a la función. Similar a la
// función insert(), si la posición es mayor que el largo de la lista, se debe de borrar
// el último nodo.
void erase(int pos){
    if(!head){
        return;
    }
    if (pos <= 0){
        head = head -> next;
        return;
    }
    int i = 0;
    auto curr = head;
    while (curr -> next && i < pos - 1){
        curr = curr -> next;
        i++;
    }

    if (!curr -> next){
            cout << "La posición dada es mayor al largo de la lista, borrando al final" << endl;
            curr = head;
            while (curr -> next -> next){
                curr = curr -> next;
            }
            curr -> next = nullptr;
            return;
        }

    curr -> next = curr -> next -> next;
}

// vi. print_list(): imprime la lista completa, separando el valor en cada nodo con “->”.

void print_list(){
    if(!head){
        return;
    }
    auto curr = head;
    while (curr){
        cout << curr -> data;
        if (curr -> next){
            cout << " -> ";
        }
        curr = curr -> next;
    }
    cout << endl;
}

int main() {
    cout << "Creando lista..." << endl;

    push_front(30);      // Lista: 30
    push_front(20);      // Lista: 20 -> 30
    push_front(10);      // Lista: 10 -> 20 -> 30
    print_list();

    cout << "\nAgregando al final:" << endl;
    push_back(40);       // Lista: 10 -> 20 -> 30 -> 40
    push_back(50);       // Lista: 10 -> 20 -> 30 -> 40 -> 50
    print_list();

    cout << "\nInsertando en posición 2 (entre 20 y 30):" << endl;
    insert(2, 25);       // Lista: 10 -> 20 -> 25 -> 30 -> 40 -> 50
    print_list();

    cout << "\nInsertando en posición 0 (inicio):" << endl;
    insert(0, 5);        // Lista: 5 -> 10 -> 20 -> 25 -> 30 -> 40 -> 50
    print_list();

    cout << "\nInsertando en posición 100 (muy grande, se agrega al final):" << endl;
    insert(100, 60);     // Lista: 5 -> 10 -> 20 -> 25 -> 30 -> 40 -> 50 -> 60
    print_list();

    cout << "\nBorrando posición 3 (debería borrar el 25):" << endl;
    erase(3);            // Lista: 5 -> 10 -> 20 -> 30 -> 40 -> 50 -> 60
    print_list();

    cout << "\nBorrando primera posición:" << endl;
    erase(0);            // Lista: 10 -> 20 -> 30 -> 40 -> 50 -> 60
    print_list();

    cout << "\nBorrando posición 100 (muy grande, borra el último):" << endl;
    erase(100);          // Lista: 10 -> 20 -> 30 -> 40 -> 50
    print_list();

    cout << "\nLista final:" << endl;
    print_list();

    return 0;
}
