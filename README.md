# MundoSangara

## Descripción del proyecto

**MundoSangara** es una simulación interactiva desarrollada en C++ que representa un ecosistema mágico compuesto por criaturas como **Dragones**, **Hadas** y **Quimeras**, distribuidas en nodos interconectados. Cada criatura posee comportamientos únicos, y durante cada ciclo puede tomar decisiones como actuar, mutar, reproducirse, migrar o morir, afectando su entorno y a las demás criaturas.

El propósito del sistema es brindar una herramienta didáctica para comprender conceptos de **programación orientada a objetos**, como herencia, polimorfismo, uso de punteros, manejo de memoria dinámica, y simulación basada en agentes. Está dirigido principalmente a estudiantes de ingeniería o ciencia de la computación que se estén iniciando en el desarrollo de sistemas complejos y orientados a objetos.


##  Manual del usuario

###  Principales funcionalidades

- Ejecutar ciclos de simulación donde cada criatura actúa de forma autónoma.
- Comportamientos diferenciados por especie: las Hadas curan, los Dragones atacan con fuego y las Quimeras combinan múltiples habilidades.
- Reproducción y migración de criaturas entre nodos activos.
- Aislamiento de nodos para evitar la participación de criaturas en el ciclo.
- Guardado del estado del mundo en un archivo JSON.
- Carga automática del mundo si existe un archivo previo.

### 🕹 Instrucciones de uso

1. Ejecuta el programa desde la consola o terminal.
2. Al iniciar, el sistema buscará un archivo de guardado (`mundo_sangara.json`). Si no lo encuentra, se genera un mundo nuevo con nodos y criaturas aleatorias.
3. Aparecerá un menú interactivo con las siguientes opciones:

```text
=== ¿Qué quieres hacer, Observador? ===
1. Siguiente ciclo         ← Ejecuta una iteración del mundo
2. Aislar nodo             ← Desactiva un nodo específico
3. Mostrar mundo           ← Muestra el estado actual de todos los nodos
4. Guardar mundo           ← Guarda el estado en un archivo JSON
5. Salir                   ← Finaliza la simulación
```

4. Ingresa el número de la opción deseada y sigue las instrucciones en pantalla.
5. Al finalizar, el estado del mundo puede guardarse para continuar la simulación más adelante.

### Requisitos mínimos
- **Sistema operativo**: Windows, Linux o macOS.
- **Compilador**: compatible con C++.
- **Consola**: soporte para codificación UTF-8 (en Windows ejecutar chcp 65001 para evitar problemas con acentos).
- **Opcional**: entorno de desarrollo como CLion

## 📂 Estructura del código fuente

El proyecto está organizado en una estructura clara que separa los componentes principales del sistema:

### Organización general del código

El archivo central del sistema es `main.cpp`, que representa al **Observador**, encargado de controlar los ciclos del mundo y la interacción con el usuario. Su estructura está dividida en varias secciones clave:

- **Carga del mundo**: al iniciar, `main.cpp` intenta leer el archivo `mundo_sangara.json` para reconstruir el estado anterior. Si no existe o está vacío, genera un mundo nuevo con nodos y criaturas aleatorias.
- **Menú interactivo**: el usuario puede avanzar ciclos, aislar nodos, mostrar el estado del mundo, guardar el progreso o salir.
- **Simulación de ciclos**: en cada ciclo, todas las criaturas activas toman decisiones como actuar, mutar, reproducirse, recibir ataques, morir o migrar.

Este archivo coordina el uso de las clases `Nodo`, `MagicalCreature` y sus derivados, funcionando como punto de entrada del sistema.

### Carpetas y archivos principales

MundoSangara/Proyecto  
├── main.cpp                  ← Archivo principal del simulador  
├── Nodo.h / Nodo.cpp         ← Representación de nodos (entorno)  
├── MagicalCreature.h/cpp     ← Clase base abstracta  
├── Dragon.h/cpp              ← Comportamiento de los Dragones  
├── Hada.h/cpp                ← Comportamiento de las Hadas  
├── Quimera.h/cpp             ← Comportamiento híbrido de Quimeras  
├── json.hpp                  ← Librería para manejar archivos JSON  
├── mundo_sangara.json        ← Archivo de guardado del mundo  



### Módulos o clases clave

- `MagicalCreature`: clase abstracta que define las operaciones generales que toda criatura debe tener (`actuar`, `mutar`, `morir`, `reproducirse`, `serializar`).
- `Dragon`: lanza ataques de fuego que afectan a las hadas.
- `Hada`: puede curar a sus aliadas dentro del mismo nodo.
- `Quimera`: híbrido con capacidad de ataque masivo y curación.
- `Nodo`: almacena las criaturas de un sector del mundo y puede ser activado o aislado.
- `main`: orquesta los ciclos del simulador y maneja entrada/salida del usuario.


##  Créditos y roles del equipo

### Participantes

- **Isabella Arango**
- **Santiago Carvajal**

### Responsabilidades y tareas realizadas

- **Santiago Carvajal** fue responsable del diseño e implementación de todas las clases derivadas de criaturas mágicas (`Dragon`, `Hada`, `Quimera`), tomando como punto de partida una tarea anterior y realizando las modificaciones necesarias para adaptarlas a la lógica de la simulación.

- **Isabella Arango** se encargó del desarrollo de la clase `Nodo` y del archivo `main.cpp`, donde reside la lógica central del simulador (el Observador), incluyendo la gestión del ciclo de vida, el menú de usuario, y la integración de comportamientos. Además, fue responsable del manejo del repositorio en GitHub y de la organización general del proyecto.


