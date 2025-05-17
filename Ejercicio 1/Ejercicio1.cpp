#include <iostream>
#include <fstream>
#include <memory>

class IMediciones{ // Interfaz para las mediciones
    public:
        virtual void serializar(std::ofstream& out) const = 0;
        virtual void deserializar(std::ifstream& in) = 0;
        virtual ~IMediciones() {};
};

class MedicionBase{ // Clase abstracta
    protected:
        std::unique_ptr<float> tiempoMedicion; // Puntero inteligente para manejar el tiempo de medición
    
    public:
        MedicionBase(float tiempoMedicion) : tiempoMedicion((std::make_unique<float>(tiempoMedicion))) {}

        MedicionBase(const MedicionBase& otro) : tiempoMedicion((std::make_unique<float>(*otro.tiempoMedicion))) {} // Constructor de copia

        MedicionBase& operator=(const MedicionBase& otro) { // Operador de asignación
            if (this != &otro) {
                tiempoMedicion = std::make_unique<float>(*otro.tiempoMedicion);
            }
            return *this;
        }
        
        float getTiempo() const {
            return *tiempoMedicion;
        }

        virtual void imprimir() const = 0;

        virtual ~MedicionBase() {};
};

class Presion: public MedicionBase, public IMediciones{ // Clase derivada
    public:
        float presionEstatica; //p
        float presionDinamica; //q

        Presion(float p, float q, float t) : MedicionBase(t), presionEstatica(p), presionDinamica(q) {}

        Presion(const Presion& otro) : MedicionBase(*otro.tiempoMedicion), presionEstatica(otro.presionEstatica), presionDinamica(otro.presionDinamica) {} // Constructor de copia porque un unique puntero no se puede copiar directamente

        Presion& operator=(const Presion& otro) { // Operador de asignación para reasignar porque unique puntero no se puede asignar por copia directamente
            if (this != &otro) {
                MedicionBase::operator=(otro);
                presionEstatica = otro.presionEstatica;
                presionDinamica = otro.presionDinamica;
            }
            return *this;
        }

        void imprimir() const override { // Método para imprimir los datos de presión
            std::cout << "Presion Estatica: " << presionEstatica << ", Presion Dinamica: " << presionDinamica << ", Tiempo: " << getTiempo() << std::endl;
        }

        void serializar(std::ofstream& out) const override { // Método para serializar los datos de presión
            out.write(reinterpret_cast<const char*>(&presionEstatica), sizeof(presionEstatica));
            out.write(reinterpret_cast<const char*>(&presionDinamica), sizeof(presionDinamica));
            float tiempo = getTiempo(); // Obtener el tiempo de medición
            out.write(reinterpret_cast<const char*>(&tiempo), sizeof(tiempo)); // Escribir el tiempo de medición
        }

        void deserializar(std::ifstream& in) override { // Método para deserializar los datos de presión
            in.read(reinterpret_cast<char*>(&presionEstatica), sizeof(presionEstatica));
            in.read(reinterpret_cast<char*>(&presionDinamica), sizeof(presionDinamica));
            float tiempo; // Leer el tiempo de medición
            in.read(reinterpret_cast<char*>(&tiempo), sizeof(tiempo));
            tiempoMedicion = std::make_unique<float>(tiempo); // Asignar el tiempo de medición
        }

        ~Presion() {
            std::cout << "\nDestruyendo la presion" << std::endl;
        }
};

class Posicion: public MedicionBase, public IMediciones{ // Clase derivada
    public:
        float latitud;
        float longitud;
        float altitud;

        Posicion(float lat, float lon, float alt, float t) : MedicionBase(t), latitud(lat), longitud(lon), altitud(alt) {}

        Posicion(const Posicion& otro) : MedicionBase(*otro.tiempoMedicion), latitud(otro.latitud), longitud(otro.longitud), altitud(otro.altitud) {} // Constructor de copia porque un unique puntero no se puede copiar directamente

        Posicion& operator=(const Posicion& otro) { // Operador de asignación porque un unique puntero no se puede asignar por copia directamente
            if (this != &otro) {
                MedicionBase::operator=(otro);
                latitud = otro.latitud;
                longitud = otro.longitud;
                altitud = otro.altitud;
            }
            return *this;
        }

        void imprimir() const override {
            std::cout << "Latitud: " << latitud << ", Longitud: " << longitud << ", Altitud: " << altitud << ", Tiempo: " << getTiempo() << std::endl;
        }

        void serializar(std::ofstream& out) const override {
            out.write(reinterpret_cast<const char*>(&latitud), sizeof(latitud));
            out.write(reinterpret_cast<const char*>(&longitud), sizeof(longitud));
            out.write(reinterpret_cast<const char*>(&altitud), sizeof(altitud));
            float tiempo = getTiempo();
            out.write(reinterpret_cast<const char*>(&tiempo), sizeof(tiempo));
        }

        void deserializar(std::ifstream& in) override {
            in.read(reinterpret_cast<char*>(&latitud), sizeof(latitud));
            in.read(reinterpret_cast<char*>(&longitud), sizeof(longitud));
            in.read(reinterpret_cast<char*>(&altitud), sizeof(altitud));
            float tiempo;
            in.read(reinterpret_cast<char*>(&tiempo), sizeof(tiempo));
            tiempoMedicion = std::make_unique<float>(tiempo);
        }

        ~Posicion() {
            std::cout << "\nDestruyendo la posicion" << std::endl;
        }
};

class SaveFlightData{ // Clase que guarda los datos de vuelo y utiliza las clases anteriores
    public:
        Posicion posicion;
        Presion presion;

        SaveFlightData(const Posicion& p, const Presion& q) : posicion(p), presion(q) {}

        void serializar(std::ofstream& out) { // Método para serializar los datos de vuelo
            posicion.serializar(out);
            presion.serializar(out);
        }

        void deserializar(std::ifstream& in) { // Método para deserializar los datos de vuelo
            posicion.deserializar(in);
            presion.deserializar(in);
        }

        void imprimir(){ // Método para imprimir los datos de vuelo (sin override ya que no hereda de MedicionBase)
            std::cout << "Datos de Vuelo: " << std::endl;
            posicion.imprimir();
            presion.imprimir();
        }

        ~SaveFlightData() {} // Destructor
};

int main(){
    Posicion posicion(-34.6f, -58.4f, 950.0f, 5.3f);
    Presion presion(101.3f, 5.8f, 6.1f);
    
    SaveFlightData datosVuelo(posicion, presion);
    std::cout << "Datos originales: \n" << std::endl; // Imprimir los datos originales
    datosVuelo.imprimir();

    std::ofstream archivoEscribir("vuelo.dat", std::ios::binary); // Crear archivo binario
    datosVuelo.serializar(archivoEscribir); // Serializar los datos
    archivoEscribir.close();

    std::ifstream archivoLeer("vuelo.dat", std::ios::binary); // Leer archivo binario
    SaveFlightData datosRecuperados(Posicion(0,0,0,0), Presion(0,0,0)); // Crear objeto vacío para recuperar los datos
    datosRecuperados.deserializar(archivoLeer); // Deserializar los datos
    archivoLeer.close();

    std::cout << "\n##################\n\nDatos recuperados: \n" << std::endl;
    datosRecuperados.imprimir(); // Imprimir los datos recuperados

    std::cout << "\n##################\n\nDestruyendo los objetos..." << std::endl;

    return 0;

}