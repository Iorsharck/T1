#include "Procesos.h"

void ejecutarAnalisis(ProcessInfo* lista, int total, int modo) {
    for (int i = 0; i < total; i++) {
        // Analisis por ubicacion sospechosa
        if (lista[i].path.find("Temp") != std::string::npos || 
            lista[i].path.find("Downloads") != std::string::npos) {
            lista[i].esSospechoso = true;
            lista[i].razon = "Ubicacion insegura";
            lista[i].nivelRiesgo = 3;
        }

        // Analisis por consumo (unicamentee en modo estricto)
        if (modo == 2 && lista[i].memoriaMB > 500) {
            if (!lista[i].esSospechoso) {
                lista[i].esSospechoso = true;
                lista[i].razon = "Consumo excesivo de RAM";
                lista[i].nivelRiesgo = 2;
            }
        }
    }
}