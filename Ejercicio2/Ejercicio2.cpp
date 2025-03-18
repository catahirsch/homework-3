/* EJERCICIO 2 */

/* Para este ejercicio, decidí utilizar function overloading para poder pasarle a la misma función, diferentes argumentos, y que cumpla
lo necesario para cada punto pedido. Para los niveles de severidad definidos anteriormente, utilice un enum que luego convierto a string.
Para los errores en archivo, la función recibe el nombre del archivo y el número de línea a registrar. Y, para los mensajes de seguridad,
la función recibe dos strings. De esta manera, diferencio los mensajes de seguridad (dos strings) y los mensajes ya definidos (enum)*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum NivelesSeveridad{
    DEBUG, INFO, WARNING, ERROR, CRITICAL // Inicializo un enum con los posibles niveles de severidad para después utilizar function overloading
};

const string file_name = "log_file.txt"; // Declaro el nombre del archivo a utilizar

string NivelesToString(NivelesSeveridad nivelseveridad) { // Convierto a string para el mensaje
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
    ofstream logfile(file_name, ios::app); // Abro el archivo para editar si existe o crear y editar si no existe
    if (logfile.is_open()){
        logfile << "[" << nivelseveridad << "] " << mensaje << endl;
        logfile.close();
    }else{
        cout << "No se pudo abrir el archivo de log" << endl;
    }
}

void logMessage(const string& mensaje, NivelesSeveridad nivelseveridad){
    writeMessage(mensaje, NivelesToString(nivelseveridad));
}

void logMessage(const string& mensaje, const string& archivo, int linea_de_codigo){
    string mensaje_completo = mensaje + " en archivo "+ archivo +" en linea " + to_string(linea_de_codigo);
    writeMessage(mensaje_completo, "ERROR"); // Si es un error escribo el mensaje y paso un nivel de severidad
}

void logMessage(const string& Mensaje_De_Acceso, const string& Nombre_de_Usuario){
    string mensaje_completo = "Usuario " + Nombre_de_Usuario + ": " + Mensaje_De_Acceso;
    writeMessage(mensaje_completo, "SECURITY"); // Si es security armo el mensaje y paso otro nivel de severidad
}

int main(){
    // Prueba con una entrada de cada tipo
    logMessage("Debugging", DEBUG);
    logMessage("Información", INFO);
    logMessage("Aviso", WARNING);
    logMessage("Hubo un error", ERROR);
    logMessage("Fallo crítico", CRITICAL);

    logMessage("Access granted","Cata");
 
    logMessage("Error 2", "hola.cpp", 15);

    // Funcionamiento por pedido al usuario
    int opcion;
    string mensaje;
    while (true){
        cout << "Seleccione el número de la opción necesaria:\n 1. DEBUG\n 2. INFO\n 3. WARNING\n 4. ERROR\n 5. CRITICAL\n 6. SECURITY\n 7. ERROR EN ARCHIVO\n 8. PERSONALIZADO\n 0. EXIT\n";
        cin >> opcion;
        cin.ignore(); // Ignora el carácter de salto de linea

        if (opcion == 0)break; // Exit

        cout << "Ingrese el mensaje: ";
        getline(cin, mensaje); // Permite la entrada del usuario de varias líneas

        if(opcion >= 1 && opcion < 6){ // Si es parte de los niveles de severidad
            logMessage(mensaje, static_cast<NivelesSeveridad>(opcion-1));
        }else if(opcion == 6){ // Si es seguridad
            string nombre;
            cout << "Ingrese el nombre de usuario: ";
            getline(cin, nombre);
            logMessage(mensaje, nombre);
        }else if(opcion == 7){ // Si es un error
            string archivo; int linea;
            cout << "Ingrese el nombre del archivo: ";
            getline(cin, archivo);

            cout << "Ingrese el número de línea del error: ";
            cin >> linea;
            cin.ignore();

            logMessage(mensaje, archivo, linea);
        }else if(opcion == 8){ // Si es personalizado
            string evento;
            cout << "Ingrese el evento: ";
            getline(cin, evento);
            writeMessage(mensaje, evento);
        }else{ // Si la opción elegida no es valida
            cout << "Eliga una opción de la lista" << endl;
        }
    }

}