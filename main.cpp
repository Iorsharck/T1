#include <iostream>
#include <string>
#include "Procesos.h"

// Los incluimos asi para que el compilador vea las funciones
#include "Procesos.cpp"
#include "Analisis.cpp"
#include "Registro.cpp"

using namespace std;

int main() {
    int total = 0;
    int modo;
    string archivo;

    cout << "--- MONITOR DE SEGURIDAD V1.0 ---" << endl;
    cout << "1. Escaneo Rapido\n2. Escaneo Profundo\nOpcion: ";
    cin >> modo;
    
    cout << "Nombre del reporte: ";
    cin >> archivo;

    // Obtenemos la lista (gestion de memoria dinamica)
    ProcessInfo* lista = obtenerListaProcesos(total);

    if (lista) {
        ejecutarAnalisis(lista, total, modo);
        generarReporte(archivo, lista, total);

        // Liberamos memoria
        delete[] lista;
        cout << "Memoria liberada. Proceso finalizado." << endl;
    } else {
        cout << "Error critico al obtener procesos." << endl;
    }

    return 0;
}