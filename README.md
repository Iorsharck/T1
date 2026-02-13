# Descripción del proyecto
En este proyecto se analiza los procesos de Windows usando un programa de cpp que mediante el uso de memoria y la carpeta de ejecución evalua si es sospechoso o no, para posteriormente hacer el reporte. Este proyecto esta dividido en modulos los cuales hacen solo una función, como la creación del reporte, la enumeración de procesos y obtención de datos, y el analisis.
# Integrantes del equipo
- Jair Gonzalo Cortés Romero (https://github.com/Iorsharck)
- Estefani Jazmín Meléndez Magallanes (estefani.melendezmgln@uanl.edu.mx)
# Instrucciones de compilación y ejecución
## Compilación
Para compilar se escribe en PowerShell:`g++ main.cpp -o AnalisisProcesos.exe -lpsapi`
## Ejecución
Se ejecuta AnalisisProcesos.exe con modo administrador para tener los permisos necesarios para ver la dirección de los procesos, o si no se pone PowerShell con administrador y se corre `start AnalisisProcesos.exe`, donde después se ingresa en que modo de seguridad se quiere ejecutar y el nombre del reporte output.
# Enfoque tecnico elegido para obtener procesos
Para obtener los procesos se usa "tlhelp32.h", que es una libreria de Microsoft donde toma una snapshot, como una screenshot de los procesos, y los enumeramos para tener un contador y asi rellenar el struct de los procesos, porque despues loopeamos de nuevo una nueva snapshot pero ya para rellenar con el array del struct creado con los procesos, para ello tuvimos que investigar el struct que usa Microsoft para su funcion que es PROCESSENTRY32, nomas vemos como meter sus valores al struct y seria todo. Ademas, se usa otra libreria para sacar la memoria y eso es mediante otra libreria, solo que esta se tiene que enlazar en la compilación del codigo. *Por cierto, hay algunos procesos que no puede analizar el programa por falta de permisos internos*
# Criterio definido para procesos sospechosos
Para la detección de amenazas, el software evalúa cada proceso bajo los siguientes estándares técnicos:
- Validación de Ubicación (Path Integrity): Se identifican procesos ejecutándose desde directorios temporales o de descarga (\Temp y \Downloads). Esto es un indicador de riesgo, ya que el malware suele utilizar estas rutas para evadir restricciones de administrador.
- Monitoreo de Consumo (Memory Threshold): Se establece un umbral de 500 MB para detectar procesos con uso excesivo de recursos, lo que permite identificar posibles fugas de memoria o actividades de minería no autorizadas.
- Evaluación de Transparencia: Si el sistema devuelve un error de "Acceso Denegado" al consultar detalles, el proceso se etiqueta como "Protegido". Esto ayuda a distinguir entre servicios críticos del sistema y software que utiliza técnicas de ocultamiento.
- Memoria Dinámica: Se implementó el uso de punteros y asignación dinámica para garantizar que el programa utilice únicamente el espacio necesario según la carga de procesos actuales.
- Manejo de Excepciones: El módulo de registro integra bloques try-catch para asegurar la integridad del reporte, evitando cierres inesperados ante errores de permisos o de escritura en disco.
