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

enum NivelesSeveridad{
    DEBUG, INFO, WARNING, ERROR, CRITICAL
};

const string file_name = "log_file.txt";

string NivelesToString(NivelesSeveridad nivelseveridad) {
    switch (nivelseveridad) {
        case DEBUG: return "DEBUG";
        case INFO: return "INFO";
        case WARNING: return "WARNING";
        case ERROR: return "ERROR";
        case CRITICAL: return "CRITICAL";
        default: return "UNKNOWN";
    }
}


void writeMessage(const string& mensaje, const string& nivelseveridad){
    ofstream logfile(file_name, ios::app);
    if (logfile.is_open()){
        logfile << "[" << nivelseveridad << "] " << mensaje << endl;
        logfile.close();
    }else{
        cout << "No se pudo abrir el archivo de log" << endl;
    }
}

void logMessage(string mensaje, NivelesSeveridad nivelseveridad){
    return writeMessage(mensaje, NivelesToString(nivelseveridad));
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

void logMessage(string mensaje, string archivo, int linea_de_codigo){
    string mensaje_completo = mensaje + " en archivo "+ archivo +" en linea " + to_string(linea_de_codigo);
    return writeMessage(mensaje_completo, "ERROR");
}

void logMessage(string Mensaje_De_Acceso, string Nombre_de_Usuario){
    string mensaje_completo = "Usuario " + Nombre_de_Usuario + ": " + Mensaje_De_Acceso;
    return writeMessage(mensaje_completo, "SECURITY");
}

int main(){
    logMessage("Debugging", DEBUG);
    logMessage("Información", INFO);
    logMessage("Aviso", WARNING);
    logMessage("Hubo un error", ERROR);
    logMessage("Fallo crítico", CRITICAL);

    logMessage("Access granted","Cata");
 
    logMessage("Error 2", "hola.cpp", 15);

    int opcion;
    string mensaje;
    while (true){
        cout << "Seleccione el número de la opción necesaria:\n 1. DEBUG\n 2. INFO\n 3. WARNING\n 4. ERROR\n 5. CRITICAL\n 6. SECURITY\n 7. ERROR EN ARCHIVO\n 8. PERSONALIZADO\n 0. EXIT\n";
        cin >> opcion;
        cin.ignore();

        if (opcion == 0)break;

        cout << "Ingrese el mensaje: ";
        getline(cin, mensaje);

        if(opcion >= 1 && opcion < 6){
            logMessage(mensaje, static_cast<NivelesSeveridad>(opcion-1));
        }else if(opcion == 6){
            string nombre;
            cout << "Ingrese el nombre de usuario: ";
            getline(cin, nombre);
            logMessage(mensaje, nombre);
        }else if(opcion == 7){
            string archivo; int linea;
            cout << "Ingrese el nombre del archivo: ";
            getline(cin, archivo);

            cout << "Ingrese el número de línea del error: ";
            cin >> linea;
            cin.ignore();

            logMessage(mensaje, archivo, linea);
        }else if(opcion == 8){
            string evento;
            cout << "Ingrese el evento: ";
            getline(cin, evento);
            writeMessage(mensaje, evento);
        }else{
            cout << "Eliga una opción de la lista" << endl;
        }
    }

}