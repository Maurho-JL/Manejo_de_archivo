#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <sys/stat.h>
using namespace std;

struct Registro {
    string nombre;
    string apellido;
    int edad;
};

bool archivoExiste(const string& archivo) {
    struct stat buffer;
    return (stat(archivo.c_str(), &buffer) == 0);
}

void escribirCSV(const string& archivo, const Registro& registro, bool agregarEncabezado) {
    ofstream archivoCSV;

    if (agregarEncabezado && !archivoExiste(archivo)) {
        archivoCSV.open(archivo);
        archivoCSV << "Nombre,Apellido,Edad\n";
    } else {
        archivoCSV.open(archivo, ios::app);
    }

    if (archivoCSV.is_open()) {
        archivoCSV << registro.nombre << "," << registro.apellido << "," << registro.edad << "\n";

        archivoCSV.close();
        cout << "Registro agregado al archivo CSV exitosamente.\n";
    } else {
        cerr << "No se pudo abrir el archivo CSV.\n";
    }
}

void leerCSV(const string& archivo) {
    ifstream archivoCSV(archivo);

    if (archivoCSV.is_open()) {
        string linea;

        getline(archivoCSV, linea); // Leer y descartar la primera línea (encabezado)

        while (getline(archivoCSV, linea)) {
            istringstream ss(linea);
            string nombre, apellido;
            int edad;

            getline(ss, nombre, ',');
            getline(ss, apellido, ',');
            ss >> edad;

            cout << "Nombre: " << nombre << ", Apellido: " << apellido << ", Edad: " << edad << "\n";
        }

        archivoCSV.close();
    } else {
        cerr << "No se pudo abrir el archivo CSV.\n";
    }
}

double calcularPromedioEdades(const vector<Registro>& registros) {
    double sumaEdades = 0;
    for (const Registro& registro : registros) {
        sumaEdades += registro.edad;
    }

    return sumaEdades / registros.size();
}

int contarDatos(const vector<Registro>& registros) {
    return registros.size();
}

bool validarEdad(const string& input, int& edad) {
    stringstream ss(input);
    if (ss >> edad) {
        return true;
    } else {
        cout << "Dato ingresado inválido. Ingrese un número entero válido.\n";
        return false;
    }
}

int main() {
    bool agregarEncabezado = true;
    string archivo = "datos.csv";

    if (archivoExiste(archivo)) {
        agregarEncabezado = false;
    }

    int opcion;
    do {
        cout << "=== MENÚ ===\n";
        cout << "1. Agregar un nuevo registro\n";
        cout << "2. Leer datos del archivo\n";
        cout << "3. Generar promedio de edades\n";
        cout << "4. Contar datos existentes\n";
        cout << "5. Salir\n";
        cout << "Ingrese su opción: ";
        cin >> opcion;
        cin.ignore(); // Ignorar el salto de línea residual después de ingresar la opción

        switch (opcion) {
            case 1: {
                Registro nuevoRegistro;

                cout << "Ingrese el nombre: ";
                getline(cin, nuevoRegistro.nombre);

                cout << "Ingrese el apellido: ";
                getline(cin, nuevoRegistro.apellido);

                string inputEdad;
                bool edadValida = false;
                do {
                    cout << "Ingrese la edad: ";
                    getline(cin, inputEdad);
                    edadValida = validarEdad(inputEdad, nuevoRegistro.edad);
                } while (!edadValida);

                escribirCSV(archivo, nuevoRegistro, agregarEncabezado);
                agregarEncabezado = false;
                break;
            }
            case 2: {
                leerCSV(archivo);
                break;
            }
            case 3: {
                ifstream archivoCSV(archivo);

                if (archivoCSV.is_open()) {
                    vector<Registro> registros;
                    string linea;

                    getline(archivoCSV, linea); // Leer y descartar la primera línea (encabezado)

                    while (getline(archivoCSV, linea)) {
                        istringstream ss(linea);
                        string nombre, apellido;
                        int edad;

                        getline(ss, nombre, ',');
                        getline(ss, apellido, ',');
                        ss >> edad;

                        Registro registro = {nombre, apellido, edad};
                        registros.push_back(registro);
                    }

                    archivoCSV.close();

                    if (!registros.empty()) {
                        double promedio = calcularPromedioEdades(registros);
                        cout << "El promedio de edades es: " << promedio << "\n";
                    } else {
                        cout << "No hay datos para calcular el promedio de edades.\n";
                    }
                } else {
                    cerr << "No se pudo abrir el archivo CSV.\n";
                }

                break;
            }
            case 4: {
                ifstream archivoCSV(archivo);

                if (archivoCSV.is_open()) {
                    vector<Registro> registros;
                    string linea;

                    getline(archivoCSV, linea); // Leer y descartar la primera línea (encabezado)

                    while (getline(archivoCSV, linea)) {
                        istringstream ss(linea);
                        string nombre, apellido;
                        int edad;

                        getline(ss, nombre, ',');
                        getline(ss, apellido, ',');
                        ss >> edad;

                        Registro registro = {nombre, apellido, edad};
                        registros.push_back(registro);
                    }

                    archivoCSV.close();

                    int cantidadDatos = contarDatos(registros);
                    cout << "La cantidad de datos existentes es: " << cantidadDatos << "\n";
                } else {
                    cerr << "No se pudo abrir el archivo CSV.\n";
                }

                break;
            }
            case 5: {
                cout << "Saliendo del programa...\n";
                break;
            }
            default: {
                cout << "Opción inválida. Por favor, ingrese una opción válida.\n";
                break;
            }
        }

        cout << "\n";
    } while (opcion != 5);

    return 0;
}