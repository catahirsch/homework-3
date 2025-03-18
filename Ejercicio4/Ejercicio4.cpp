/* EJERCICIO 4 */

/* La función compara dos cadenas de texto, carácter a carácter de forma recursiva. Como la función es declarada como constexpr,
si sus argumentos también son constexpr, la evaluación se realice en tiempo de compilación. Pero también permite reutilizar la misma,
tomando argumentos de tipo const char * para también evaluar en tiempo de ejecución y poder comparar los tiempos. */

#include <iostream>
#include <string>
#include <chrono>
using namespace std;

constexpr bool compare_text(const char* text1, const char* text2, size_t index = 0){
    return((text1[index] == '\0' && text2[index] == '\0') || // Si ambos textos llegaron al final (están vacios) devuelvo true
    text1[index] == text2[index] && compare_text(text1, text2, index +1)); // Comparo carácter a carácter
}

int main(){
    // Dos textos de más de 64 caracteres
    const char* text1 = "Atenas es un gato negro con ojos verdes que le encanta sentarse encima de mi computadora mientras intento programar.";
    const char* text2 = "Atenas es un gato negro con ojos verdes que le encanta sentarse encima de mi computadora mientras intento programar.";
    
    auto startTime = chrono::high_resolution_clock::now(); // Inicializo el tiempo
    bool son_iguales = compare_text(text1, text2); // Corro la función
    auto endTime = chrono::high_resolution_clock::now(); // Detengo el tiempo

    auto elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime); // Calculo el tiempo 
    cout << "Los textos " << (son_iguales ? "si" : "no") << " son iguales" << endl; // Devuelvo el mensaje necesario
    std::cout << "A compare_texts le tomó: "<< elapsedTime.count() << " nanosegundos (en tiempo de ejecución)" << endl;

    // Evalúo en tiempo de compilacion
    constexpr char text1_const[] = "Atenas es un gato negro con ojos verdes que le encanta sentarse encima de mi computadora mientras intento programar.";
    constexpr char text2_const[] = "Atenas es un gato negro con ojos verdes que le encanta sentarse encima de mi computadora mientras intento programar.";
    
    auto startTime2 = chrono::high_resolution_clock::now(); // Inicializo otro tiempo
    constexpr bool const_son_iguales = compare_text(text1_const, text2_const); // Corro la función (evalúo en compilación)
    auto endTime2 = chrono::high_resolution_clock::now(); // Detengo el tiempo

    auto elapsedTime2 = chrono::duration_cast<chrono::nanoseconds>(endTime2 - startTime2); // Calculo el tiempo para comparar
    cout << "Los textos " << (const_son_iguales ? "sí" : "no") << " son iguales (evaluado en compilación)." << endl;
    std::cout << "A compare_texts le tomó: "<< elapsedTime2.count() << " nanosegundos (en tiempo de compilación)" << endl;
}

// Elección string vs char*
// Como en los siguientes puntos del ejercicio era necesario utilizar la función constexpr para calcular el tiempo de compilación
// al ser evaluado en compilación, decidí usar char*, de esta manera no fue necesario utilizar una versión especifica de compilador.
// Porque, dependiendo de la versión de compilador usado, la función contexpr puede recibir (o no) un string como argumento.

// CONCLUSIÓN
// El tiempo calculado cuando es evaluado en compilación es significativamente más chico ya que,
// al ser evaluado antes de que el programa se ejecute, su tiempo de ejecución es casi mínimo (casi nulo).
// Y, técnicamente, el tiempo cuando evaluado en compilación debería ser 0, porque no sucede durante la ejecución.