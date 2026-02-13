# Descripción del proyecto
En este proyeccto se analisa los procesos de Windows usando un programa de cpp que mediante el uso de memoria y la carpeta de ejecución evalua si es sospechoso o no, para posteriormente hacer el reporte.
# Integrantes de equipo
- Jair Gonzalo Cortés Romero  
- Estefani Jazmín Meléndez Magallanes
# Instrucciones de compilación y ejecución
## Compilación
Para compilar se escribe en PowerShell:``g++ main.cpp -o AnalisisProcesos.exe -lpsapi``
## Ejecución
Se ejecuta AnalisisProcesos.exe con modo admnistrador para tener los permisos necesarios para ver la dirección de los procesos, o si no se pone PowerShell con administrador y se corre ``start AnalisisProcesos.exe``, donde despúes se ingresa en que modo de seguridad se quiere ejecutar y el nombre del reporte output.
# Enfoque tecnico para elegido para obtener procesos
Para obtener los procesos se usa "tlhelp32.h", que es una libreria de Microsoft donde toma una snapshot, como una screenshot de los procesos, y los enumeramos para tener un contador y asi rellenar el struct de los procesos, porque despues loopeamos de nuevo una nueva snapshot pero ya para rellenar con el array del struct creado con los procesos, para ello tuvimos que investigar el struct que usa Microsoft para su funcion que es PROCESSENTRY32, nomas vemos como meter sus valores al struct y seria todo. Ademas, se usa otra libreria para sacar la memoria y eso es mediante otra libreria, solo que esta se tiene que enlazar en la compilación del codigo. **Por cierto, hay algunos procesos que no puede analizar el programa por falta de permisos internos**
# Criterio definido para procesos sospechosos
