/* EJERCICIO 1 */

/* Para este ejercicio, originalmente considere inicializar una matriz con tamaño 100 x 100, ya que C++ no acepta matrices de tamaño
variable. Pero decidí intentar resolver este problema dado a que el usuario podría ingresar un valor mayor a 100. Para resolver esto
decidí utilizar una matriz de punteros, y así crear un arreglo de punteros por fila y por columnas, el cuál depende del valor
ingresado por el usuario. Al resolverlo de esta manera es necesario eliminar la memoria utilizada luego de imprimir la matriz */

#include <iostream>
using namespace std;

void matriz_cuadrada(int** matriz, int n){
    int num = 1; int i; int j;
    for(i=0; i<n; ++i){ // Recorro por fila
        for(j=0; j<n; ++j){ // Recorro por columna
            matriz[i][j] = num++; // Asigno el valor correspondiente
        }
    }
}

void imprimir_matriz(int** matriz, int n){
    int i; int j; int total = n * n;
    for (int k = total; k >= 1; --k) { // Recorre la matriz de mayor a menor (desde n^2)
        i = (k - 1) / n; // Encuentro la fila
        j = (k - 1) % n; // Encuentro la columna
        cout << "M" <<n<< "[" << i << "][" << j << "] = " << matriz[i][j] << endl; // Imprimo el valor de la matriz con su índice
    }
}

int main(){
    int n; // Inicializo las variables

    try{
        cout << "Ingrese un valor entero n (>1): ";
        cin >> n;
        if (n>1){
            int **matriz =  new int*[n]; // Para que el tamaño de la matriz sea dinámico, crea un arreglo de punteros (n filas)
            for(int i=0; i<n; ++i){  // Recorre la matriz
                matriz[i] = new int[n]; // Por cada fila crea un arreglo de punteros (n columnas)
            }

            matriz_cuadrada(matriz, n);
            imprimir_matriz(matriz, n);

            // Libero memoria
            for(int i=0; i<n; ++i){ 
                delete[] matriz[i];
            }
            delete[] matriz;

        }else{
            throw(n);
        }
    }
    catch(int n){
        cout << "El valor debe ser >1\n"; // N debe ser valor entero, positivo y mayor a uno
    }

    return 0;
}

// Nota: recuerde que se deben imprimir los índices de la matriz

