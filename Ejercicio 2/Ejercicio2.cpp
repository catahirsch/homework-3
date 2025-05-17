#include <iostream>
#include <cmath>

class Punto { // Clase para representar un punto en el plano
    private:
        int x, y;

    public:
        Punto(int x, int y) : x(x), y(y) {}
        // Setters y getters para las coordenadas
        void set_X(int x) { this->x = x;}

        void set_Y(int y) { this->y = y;}

        int get_X() const { return x;}

        int get_Y() const { return y;}

        void mostrar() const { // Método para mostrar las coordenadas del punto
            std::cout << "Punto(" << x << ", " << y << ")" << std::endl; 
        }

        ~Punto() {
            std::cout << "Destruyendo el punto" << std::endl;
        }
};

class Circulo{
    private:
        Punto posicion; // Posición del centro del círculo
        int radio;

    public:
        Circulo(int x, int y, int radio) : posicion(x, y), radio(radio) {}

        void set_Posicion(int x, int y) { // Setters para la posición y el radio
            posicion.set_X(x);
            posicion.set_Y(y);
        }

        void set_Radio(int radio) { this->radio = radio;}

        Punto get_Posicion() const { return posicion;}

        int get_Radio() const { return radio;}

        void mostrar() const { // Método para mostrar la información del círculo
            std::cout << "Circulo: \nPosición: ";
            posicion.mostrar();
            std::cout << "Radio: " << radio << std::endl; 
        }

        ~Circulo() {
            std::cout << "Destruyendo el círculo" << std::endl;
        }
};

class Elipse{
    private:
        Punto centro;
        int a, b;

    public:
        Elipse(int x, int y, int a, int b) : centro(x, y), a(a), b(b) {}

        void set_Centro(int x, int y) {
            centro.set_X(x);
            centro.set_Y(y);
        }

        void set_SemiEjeMayor(int a) { this->a = a;}

        void set_SemiEjeMenor(int b) { this->b = b;}

        Punto get_Centro() const { return centro;}

        int get_SemiEjeMayor() const { return a;}

        int get_SemiEjeMenor() const { return b;}

        void mostrar() const {
            std::cout << "Elipse: \nCentro: ";
            centro.mostrar();
            std::cout << "Semi-eje Mayor: " << a << ", Semi-eje Menor: " << b << std::endl;
        }

        ~Elipse() {
            std::cout << "Destruyendo la elipse" << std::endl;
        }
};

class Rectangulo{
    private:
        Punto VerIzqInf;
        int ancho;
        int largo;

    public:
        Rectangulo(int x, int y, int ancho, int largo) : VerIzqInf(x, y), ancho(ancho), largo(largo) {}

        void set_VerIzqInf(int x, int y) {
            VerIzqInf.set_X(x);
            VerIzqInf.set_Y(y);
        }

        void set_Ancho(int ancho) { this->ancho = ancho;}

        void set_Largo(int largo) { this->largo = largo;}

        Punto get_VerIzqInf() const { return VerIzqInf;}

        int get_Ancho() const { return ancho;}

        int get_Largo() const { return largo;}

        void mostrar() const {
            std::cout << "Rectangulo: \nVértice Izquierdo Inferior: ";
            VerIzqInf.mostrar();
            std::cout << "Ancho: " << ancho << ", Largo: " << largo << std::endl;
        }

        ~Rectangulo() {
            std::cout << "Destruyendo el rectángulo" << std::endl;
        }
};

template <typename T>
class ProcesadorFigura {
    public:
        static double calcularArea(const T& figura);
};

template<>
double ProcesadorFigura<Punto>::calcularArea(const Punto& punto) {
    return 0; // El área de un punto es 0
}

template<>
double ProcesadorFigura<Circulo>::calcularArea(const Circulo& circulo) {
    return M_PI * pow(circulo.get_Radio(), 2);
}

template<>
double ProcesadorFigura<Elipse>::calcularArea(const Elipse& elipse) {
    return M_PI * elipse.get_SemiEjeMayor() * elipse.get_SemiEjeMenor();
}

template<>
double ProcesadorFigura<Rectangulo>::calcularArea(const Rectangulo& rectangulo) {
    return rectangulo.get_Ancho() * rectangulo.get_Largo();
}


int main(){
    // Crear un punto
    std::cout<<"Creando un punto: \n";

    int x; int y;
    std::cout<<"Ingrese la coordenada x: ";
    std::cin>>x;

    std::cout<<"Ingrese la coordenada y: ";
    std::cin>>y;
    
    std::cout<<"Creando el punto: \n";
    Punto p(x, y);
    p.mostrar();

    // Calcular el área del punto
    double areaPunto = ProcesadorFigura<Punto>::calcularArea(p);
    std::cout << "Área del punto: " << areaPunto << "\n" << std::endl;

    // #########################################
    // Crear un círculo
    std::cout << "Creando un círculo: \n";

    int x_circulo; int y_circulo; int radio;
    std::cout << "Ingrese la coordenada x: ";
    std::cin >> x_circulo;

    std::cout << "Ingrese la coordenada y: ";
    std::cin >> y_circulo;

    std::cout << "Ingrese el radio: ";
    std::cin >> radio;

    std::cout << "Creando el círculo: \n";
    Circulo c(x_circulo, y_circulo, radio);
    c.mostrar();

    // Calcular el área del círculo
    double areaCirculo = ProcesadorFigura<Circulo>::calcularArea(c);
    std::cout << "Área del círculo: " << areaCirculo << "\n" << std::endl;

    // #########################################
    // Crear una elipse
    std::cout << "Creando una elipse: \n";

    int x_elipse; int y_elipse; int a; int b;
    std::cout << "Ingrese la coordenada x del centro: ";
    std::cin >> x_elipse;

    std::cout << "Ingrese la coordenada y del centro: ";
    std::cin >> y_elipse;

    std::cout << "Ingrese el semi-eje mayor: ";
    std::cin >> a;

    std::cout << "Ingrese el semi-eje menor: ";
    std::cin >> b;

    std::cout << "Creando la elipse: \n";
    Elipse e(x_elipse, y_elipse, a, b);
    e.mostrar();

    // Calcular el área de la elipse
    double areaElipse = ProcesadorFigura<Elipse>::calcularArea(e);
    std::cout << "Área de la elipse: " << areaElipse << "\n" << std::endl;

    // #########################################
    // Crear un rectángulo
    std::cout << "Creando un rectángulo: \n";

    int x_rectangulo; int y_rectangulo; int ancho; int largo;
    std::cout << "Ingrese la coordenada x del vértice izquierdo inferior: ";
    std::cin >> x_rectangulo;

    std::cout << "Ingrese la coordenada y del vértice izquierdo inferior: ";
    std::cin >> y_rectangulo;

    std::cout << "Ingrese el ancho: ";
    std::cin >> ancho;

    std::cout << "Ingrese el largo: ";
    std::cin >> largo;

    std::cout << "Creando el rectángulo: \n";
    Rectangulo rectangulo(x_rectangulo, y_rectangulo, ancho, largo);
    rectangulo.mostrar();

    // Calcular el área del rectángulo
    double areaRectangulo = ProcesadorFigura<Rectangulo>::calcularArea(rectangulo);
    std::cout << "Área del rectángulo: " << areaRectangulo << "\n" << std::endl;

    return 0;
}