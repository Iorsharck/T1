#include "Procesos.h"
#include <tlhelp32.h>
#include <psapi.h>
#include <iostream>

using namespace std;

ProcessInfo* obtenerListaProcesos(int& total) {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) return nullptr;

    pe32.dwSize = sizeof(PROCESSENTRY32);
    int count = 0;

    if (Process32First(hProcessSnap, &pe32)) {
        do { count++; } while (Process32Next(hProcessSnap, &pe32));
    }
    CloseHandle(hProcessSnap);

    total = count;
    ProcessInfo* processes = new ProcessInfo[count];

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        delete[] processes;
        return nullptr;
    }

    int index = 0;
    if (Process32First(hProcessSnap, &pe32)) {
        do {
            processes[index].pid = pe32.th32ProcessID;
            processes[index].nombre = pe32.szExeFile;

            // Memoria
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe32.th32ProcessID);
            if (hProcess) {
                PROCESS_MEMORY_COUNTERS pmc;
                if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
                    processes[index].memoriaMB = pmc.WorkingSetSize / (1024 * 1024);
                }
                CloseHandle(hProcess);
            }

            // Ruta del ejecutable
            HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pe32.th32ProcessID);
            if (hModuleSnap != INVALID_HANDLE_VALUE) {
                MODULEENTRY32 me32;
                me32.dwSize = sizeof(MODULEENTRY32);
                if (Module32First(hModuleSnap, &me32)) processes[index].path = me32.szExePath;
                CloseHandle(hModuleSnap);
            } else {
                processes[index].path = "Protegido/Sistema";
            }
            index++;
        } while (Process32Next(hProcessSnap, &pe32) && index < count);
    }
    CloseHandle(hProcessSnap);
    return processes;
}