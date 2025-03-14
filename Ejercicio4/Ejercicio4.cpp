// 4. Recursión y ejecución en tiempo de compilación:
// a. Se requiere el código de una función recursiva que compare dos variables que
// contengan texto e indique mediante una variable bool si son iguales (true si son
// iguales, false si no lo son). Explique su elección entre los tipos string y char* (lea
// el siguiente item de este ejercicio antes de elegir el tipo de variable) y demuestre
// la funcionalidad de su código con un texto de, al menos, 64 caracteres.

// b. El componente high_resolution_clock de <chrono> permite calcular el tiempo
// de ejecución de un proceso al hacer:
// #include <chrono>
// …
// auto startTime = std::chrono::high_resolution_clock::now();
// miProcesoAMedir();
// auto endTime = std::chrono::high_resolution_clock::now();
// auto elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(
// endTime - startTime);
// std::cout << “A miProcesoAMedir le tomó: “ << elapsedTime.count() << “
// nanosegundos” << std::endl;
// Utilice esté código y las modificaciones necesarias que crea conveniente para
// verificar cuanto tiempo toma la ejecución del código del ejercicio 4.1.

// c. Modifique el código del ejercicio 4.1 para que la comparación de los textos se
// realice en tiempo de compilación y obtenga el tiempo de ejecución. Compare
// este tiempo con el obtenido en el ejercicio 4.2 y justifique brevemente la
// diferencia (puede escribir su conclusión como un comentario al final del código
// de este item)


#include <iostream>
#include <string>
#include <chrono>
using namespace std;

constexpr bool compare_text(const char* text1, const char* text2, size_t index = 0){
    return((text1[index] == '\0' && text2[index] == '\0') || 
    text1[index] == text2[index] && compare_text(text1, text2, index +1));
}

int main(){
    const char* text1 = "Atenas es un gato negro con ojos verdes que le encanta sentarse encima de mi computadora mientras intento programar.";
    const char* text2 = "Atenas es un gato negro con ojos verdes que le encanta sentarse encima de mi computadora mientras intento programar.";
    
    auto startTime = chrono::high_resolution_clock::now();
    bool son_iguales = compare_text(text1, text2);
    auto endTime = chrono::high_resolution_clock::now();

    auto elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);
    cout << "Los textos " << (son_iguales ? "si" : "no") << " son iguales" << endl;
    std::cout << "A compare_texts le tomó: "<< elapsedTime.count() << " nanosegundos (sin realizar en tiempo de compilacion)" << endl;

    // En tiempo de compilacion

    constexpr char text1_const[] = "Atenas es un gato negro con ojos verdes que le encanta sentarse encima de mi computadora mientras intento programar.";
    constexpr char text2_const[] = "Atenas es un gato negro con ojos verdes que le encanta sentarse encima de mi computadora mientras intento programar.";
    
    auto startTime2 = chrono::high_resolution_clock::now();
    constexpr bool const_son_iguales = compare_text(text1_const, text2_const);
    auto endTime2 = chrono::high_resolution_clock::now();

    auto elapsedTime2 = chrono::duration_cast<chrono::nanoseconds>(endTime2 - startTime2);
    cout << "Los textos " << (const_son_iguales ? "sí" : "no") << " son iguales (evaluado en compilación)." << endl;
    std::cout << "A compare_texts le tomó: "<< elapsedTime2.count() << " nanosegundos (en tiempo de compilación)" << endl;
}

// Elección string vs char*
// Como en los siguientes puntos del ejercicio era necesario utilizar la función constexpr para calcular el tiempo de compilación
// al ser evaluado en compilación, decidí usar char*, de esta manera no fue necesario utilizar una versión especifica de compilador.
// Porque, dependiendo de la versión de compilador usado, la función contexpr puede recibir (o no) un string como argumento.


// CONCLUSION
// El tiempo calculado cuando es evaluado en compilación es significativamente más chico ya que,
// al ser evaluado antes de que el programa se ejecute, su tiempo de ejecución es casi mínimo (casi nulo).
// Y, técnicamente, el tiempo cuando evaluado en compilación debería ser 0, porque no sucede durante la ejecución.