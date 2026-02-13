#ifndef PROCESOS_H
#define PROCESOS_H

#include <windows.h>
#include <string>
#include <vector>

// Estructura que definio Jair con mis añadidos para el analisis
struct ProcessInfo {
    DWORD pid;
    std::string nombre;
    std::string path;
    long memoriaMB;
    
    // Mis variables para el reporte
    bool esSospechoso = false;
    std::string razon = "";
    int nivelRiesgo = 0; 
};

// Prototipo de la funcion de Jair
ProcessInfo* obtenerListaProcesos(int& total);

#endif