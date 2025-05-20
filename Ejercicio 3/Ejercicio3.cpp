#include <cstddef>
#include <iostream>
#include <vector>
#include <concepts>
#include <string>
#include <fstream>

// Defino los vectores a utilizar
using vec_doubles = std::vector<double>;
using palabras = std::vector<std::string>;
using listas = std::vector<std::pair<int, int>>;

// Defino los concepts para los tipos de datos de los vectores
template<typename T>
concept isDouble = std::is_floating_point_v<T>;

template<typename T>
concept isString = std::is_same_v<T, std::string>;

template<typename T>
concept isPair = std::is_same_v<T, std::pair<int, int>>;

class Clase1{
    protected:
        palabras palabras_;
        listas listas_;
        vec_doubles vec_doubles_;

    public:
        Clase1(){};

        template<typename T> // Plantilla para agregar valores a los vectores
        void agregarValor(const T& valor){
            if constexpr (isDouble<T>){ // Si el tipo es double
                vec_doubles_.push_back(valor); // Agrego el valor al vector de doubles
            }
            else if constexpr(isString<T>){ // Si el tipo es string
                palabras_.push_back(valor); // Agrego el valor al vector de palabras
            }
            else if constexpr(isPair<T>){ // Si el tipo es un par de ints
                listas_.push_back(valor); // Agrego el valor al vector de listas (directo porque ya es un par de ints)
            }
        }  

        ::palabras getPalabras() const { // Método para obtener el vector de palabras
            return palabras_;
        }

        ::listas getListas() const { // Método para obtener el vector de listas
            return listas_;
        }

        ::vec_doubles getVecDoubles() const { // Método para obtener el vector de doubles
            return vec_doubles_;
        }

        ~Clase1(){}
};

class Clase2 : public Clase1{ // Clase derivada de Clase1
    public:
        Clase2(){};

        void printVecDouble(std::ostream& os){ // Método para imprimir el vector de doubles generalizado para cout o ofstream
            os << "{ "<< "\"vec_doubles\": [";
            for(size_t i = 0; i < vec_doubles_.size(); ++i){
                os << vec_doubles_[i];
                if (i != vec_doubles_.size() - 1) {
                    os << ", ";
                }
            }
            os << "]," << std::endl;
        }

        void printPalabras(std::ostream& os){ // Método para imprimir el vector de palabras generalizado para cout o ofstream
            os << "  \"palabras\": [";
            for (size_t i = 0; i < palabras_.size(); ++i) {
                os << "\"" << palabras_[i] << "\"";
                if (i != palabras_.size() - 1) {
                    os << ", ";
                }
            }
            os << "]," << std::endl;
        }

        void printListas(std::ostream& os){ // Método para imprimir el vector de listas generalizado para cout o ofstream
            os << "  \"listas\": [\n";
            for (size_t i = 0; i < listas_.size(); ++i) {
                os << "\t[" << listas_[i].first << ", " << listas_[i].second << "]";
                if (i != listas_.size() - 1) {
                    os << ", \n";
                }
            }
            os << "\n\t]\n}" << std::endl;
        }

        void construirJson(){
            this->printVecDouble(std::cout); // Imprimo el vector de doubles en la consola
            this->printPalabras(std::cout); // Imprimo el vector de palabras en la consola
            this->printListas(std::cout); // Imprimo el vector de listas en la consola

            std::ofstream archivo("salida.json"); // Abro el archivo de salida
            if (archivo.is_open()) { // Verifico si el archivo se abrió correctamente
                this->printVecDouble(archivo); // Imprimo el vector de doubles en el archivo
                this->printPalabras(archivo); // Imprimo el vector de palabras en el archivo
                this->printListas(archivo); // Imprimo el vector de listas en el archivo
                archivo.close(); // Cierro el archivo
            } else {
                std::cerr << "Error al abrir el archivo de salida." << std::endl;
            }
        }
};

int main(){
    double d1 = 1.3;
    double d2 = 2.1;
    double d3 = 3.2;

    std::string s1 = "Hola";
    std::string s2 = "Mundo";

    std::pair<int, int> p1 = {1, 2};
    std::pair<int, int> p2 = {3, 4};

    Clase2 c2; // Instancio la clase derivada

    c2.agregarValor(d1); // Agrego valores a los vectores
    c2.agregarValor(d2);
    c2.agregarValor(d3);
    
    c2.agregarValor(s1);
    c2.agregarValor(s2);

    c2.agregarValor(p1);
    c2.agregarValor(p2);

    c2.construirJson(); // Construyo el JSON y lo imprimo en la consola y en el archivo de salida
}