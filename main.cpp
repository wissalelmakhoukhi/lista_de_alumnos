#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Función para leer los nombres desde un archivo CSV
vector<string> leerAlumnosCSV(const string &nombreArchivo) {
    vector<string> alumnos;
    ifstream archivo(nombreArchivo);
    string linea, nombre;

    if (!archivo) {
        cerr << "Error al abrir el archivo CSV.\n";
        return alumnos;
    }

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        vector<string> campos;
        while (getline(ss, nombre, ',')) {  // Separar por comas
            if (!nombre.empty()) {
                campos.push_back(nombre);
            }
        }

        // Suponiendo que el nombre completo está en una sola celda del CSV
        if (!campos.empty()) {
            alumnos.push_back(campos[0]);  // Agregar solo la primera columna (nombre)
        }
    }

    archivo.close();
    return alumnos;
}

// Función para generar la hoja de asistencia
void generarHojaAsistencia(const vector<string> &alumnos, const string &nombreArchivoSalida) {
    ofstream archivoSalida(nombreArchivoSalida);

    if (!archivoSalida) {
        cerr << "Error al abrir el archivo de salida.\n";
        return;
    }

    // Encabezado
    archivoSalida << "============================================\n";
    archivoSalida << "            HOJA DE ASISTENCIA             \n";
    archivoSalida << "============================================\n";
    archivoSalida << "Asignatura: PFIS\n";
    archivoSalida << "Fecha: [Ingrese la fecha aquí]\n";
    archivoSalida << "Semana de docencia: [Ingrese la semana aquí]\n";
    archivoSalida << "Tema: [Ingrese el tema aquí]\n";
    archivoSalida << "============================================\n\n";
    archivoSalida << "Nombre,Apellido\n\n";

    // Imprimir alumnos en grupos de 8 (2 columnas)
    int contador = 0;
    for (const auto &alumno : alumnos) {
        archivoSalida << alumno;
        if (++contador % 2 == 0) {
            archivoSalida << "\t\t";  // Tabulación para segunda columna
        } else {
            archivoSalida << "\n";  // Nueva línea después de 2 nombres
        }

        if (contador % 8 == 0) {
            archivoSalida << "\n";  // Espaciado entre grupos de 8
        }
    }

    archivoSalida.close();
    cout << "Hoja de asistencia generada en " << nombreArchivoSalida << "\n";
}

int main() {
    string archivoEntrada = "alumnos.csv";  // Archivo CSV con nombres
    string archivoSalida = "asistencia.txt";  // Archivo de salida

    vector<string> alumnos = leerAlumnosCSV(archivoEntrada);

    if (alumnos.empty()) {
        cerr << "Error: No se encontraron alumnos en " << archivoEntrada << "\n";
        return 1;
    }

    sort(alumnos.begin(), alumnos.end());  // Ordenar alfabéticamente

    generarHojaAsistencia(alumnos, archivoSalida);

    return 0;
}
