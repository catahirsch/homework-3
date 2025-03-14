// 1. a. Crear una función que dado un valor entero “n”, positivo y mayor a uno, devuelva
// una matriz cuadrada con valores como en los siguientes ejemplos para n=2 y n=3:

// b. Proveer un código que imprima el contenido de la matriz, utilizando un único ciclo
// for, desde el mayor valor al menor, es decir, para el ejemplo de Para 𝑀2:


#include <iostream>
using namespace std;

void matriz_cuadrada(int matriz[100][100], int n){
    int num = 1; int i; int j;
    for(i=0; i<n; ++i){
        for(j=0; j<n; ++j){
            matriz[i][j] = num++;
        }
    }
}

void imprimir_matriz(int matriz[100][100], int n){
    int i; int j; int total = n * n;
    for (int k = total; k >= 1; --k) {
        i = (k - 1) / n;
        j = (k - 1) % n;
        cout << "M" <<n<< "[" << i << "][" << j << "] = " << matriz[i][j] << endl;
    }
}

int main(){
    int n; int matriz[100][100];int valor = 1;

    try{
        cout << "Ingrese un valor entero n (>1): ";
        cin >> n;
        if (n>1){
            matriz_cuadrada(matriz, n);
            imprimir_matriz(matriz, n);
        } else{
            throw(n);
        }
    }
    catch(int n){
        cout << "El valor debe ser >1\n";
    }
    
    return 0;
}

// Nota: recuerde que se deben imprimir los índices de la matriz

