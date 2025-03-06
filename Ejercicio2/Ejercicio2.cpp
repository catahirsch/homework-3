// 2. En muchos sistemas, es importante registrar todo lo que sucede mientras están en
// funcionamiento. Para ello, se utiliza un sistema de log que almacena los eventos
// relevantes. Cada evento recibe una etiqueta que indica su nivel de importancia o
// gravedad. Las etiquetas más comunes son: DEBUG, INFO, WARNING, ERROR y
// CRITICAL.

// a. En este ejercicio, se pide crear un sistema log que permite agregar entradas a un
// archivo mediante el llamado a una función logMessage definida en pseudo código de
// la siguiente manera:

// void logMessage(String mensaje, Integer/Otro NivelSeveridad)
// Donde NivelSeveridad corresponderá con unas de las leyendas previamente
// mencionadas. El formato esperado en una línea del archivo de log es el siguiente
// [ERROR] <Mensaje>
// [INFO] <Mensaje>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void logMessage(const string& mensaje, const string& NivelSeveridad){
    ofstream logfile("LogfileA.txt", ios::app);
    if (logfile.is_open()){
        logfile << "[" << NivelSeveridad << "] " << mensaje << endl;
        logfile.close();
    }
}

// Verifique su funcionamiento con al menos una entrada de cada tipo.

// b. En un proyecto usualmente se solicitan cambios para mejorar o agregar funcionalidad.
// Para el caso del código del ejercicio 2.a, se requiere tener la habilidad de agregar
// mensajes personalizados para registrar otro tipo de eventos. Los requisitos son los
// siguientes:
// i. Todos los nuevos mensajes deben ser invocados con logMessage.
// ii. Se requiere la posibilidad de registrar errores, indicando el mensaje de error, el
// archivo y la línea de código donde sucedió este error, es decir:
// logMessage(String Mensage_de_Error, String Archivo, Int Línea_de_Código)
// iii. Se requiere la posibilidad de registrar un mensaje de “Acceso de Usuario” a la
// aplicación. Este mensaje debe tener una leyenda nueva: [SECURITY]. La misma
// debe ser ingresada de la siguiente manera:
// logMessage(String Mensaje_De_Acceso, String Nombre_de_Usuario)
// Los mensajes de acceso pueden ser: Access Granted, Access Denied, etc.
// iv. Se requiere un código que pruebe que el sistema verifica la funcionalidad
// requerida y que además demuestre que puede capturar un error en runtime,
// crear una entrada en el log y después detener la ejecución del programa y salir
// del mismo con un código de error (return 1)

void logMessageB(const string& mensaje, const string& parametro2, int linea_de_codigo = 0, const string& parametro3 = ""){
    ofstream logfile("LogfileB.txt", ios::app);
    if (logfile.is_open()){
        if (linea_de_codigo != 0){
            logfile << "[ERROR] " << mensaje << " en archivo "<< parametro2 <<" en linea " << linea_de_codigo << endl;
        }else if (not parametro3.empty()){
            logfile << "[SECURITY] User " << parametro3 << " " << mensaje << endl;
        }else{
            logfile << "[" << parametro2 << "] " << mensaje << endl;
        }
        logfile.close();
    }
}

int main(){
    logMessage("Debugging", "DEBUG");
    logMessage("Información", "INFO");
    logMessage("Aviso", "WARNING");
    logMessage("Hubo un error", "ERROR");
    logMessage("Fallo crítico", "CRITICAL");

    logMessageB("Debugging", "DEBUG");
    logMessageB("Información", "INFO");
    logMessageB("Aviso", "WARNING");
    logMessageB("Hubo un error", "ERROR");
    logMessageB("Fallo crítico", "CRITICAL");

    logMessageB("Access granted","",0,"Cata");

    logMessageB("Error 2", "hola.cpp", 15);
}