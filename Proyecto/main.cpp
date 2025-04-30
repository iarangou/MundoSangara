#include <iostream>                     // Entrada/salida
#include "MagicalCreature.h"           // Clase base de criaturas
#include "Dragon.h"                    // Clase derivada: Dragón
#include "Hada.h"                      // Clase derivada: Hada
#include "Quimera.h"                   // Clase derivada: Quimera
#include "Nodo.h"                      // Clase Nodo (espacio del mundo)
#include <random>                      // Para generar números aleatorios
#include <vector>                      // Para usar vectores
#include<fstream>

using namespace std;
using json = nlohmann::json;

// === Generador de números aleatorios ===
std::random_device rd;                 // Fuente de entropía del sistema
std::mt19937 gen(rd());                // Motor Mersenne Twister con semilla aleatoria

// Función para obtener un entero aleatorio entre a y b (inclusive)
int aleatorioEntre(int a, int b) {
    std::uniform_int_distribution<> distribucion(a, b);
    return distribucion(gen);
}

// === Función para crear una criatura aleatoria ===
MagicalCreature* generarCriatura(const string& nombreBase) {
    int tipo = aleatorioEntre(0, 2);               // 0: Dragón, 1: Hada, 2: Quimera
    int vitalidad = aleatorioEntre(10, 1000);      // Vitalidad aleatoria
    int poder = aleatorioEntre(30, 400);           // Poder aleatorio

    if (tipo == 0)
        return new Dragon(nombreBase + "_D", vitalidad, poder, aleatorioEntre(100, 400));
    else if (tipo == 1)
        return new Hada(nombreBase + "_H", vitalidad, poder, aleatorioEntre(100, 400));
    else
        return new Quimera(nombreBase + "_Q", vitalidad, poder, aleatorioEntre(100, 400), aleatorioEntre(100, 400), aleatorioEntre(100, 400));
}

// === Menú del Observador ===
void menu() {
    cout << "\n=== ¿Qué quieres hacer, Observador? ===\n";
    cout << "1. Siguiente ciclo\n";
    cout << "2. Aislar nodo\n";
    cout << "3. Mostrar mundo\n";
    cout << "4. Guardar mundo\n";
    cout << "5. Salir\n";
    cout << "Opción: ";
}

int main() {
    int numeronodos = 1;
    system("chcp 65001"); // Activa UTF-8 en consola para mostrar tildes correctamente
    cout << "== Prueba de Mundo Sangara ==" << endl;

    // === Inicialización del mundo ( nodos con criaturas aleatorias) ===
    // Declaración del mundo
    vector<Nodo*> mundo;

    // Intentar abrir archivo
    ifstream archivo("mundo_sangara.json");

    if (!archivo) {
        // No existe el archivo o no se pudo abrir -> generar mundo nuevo
        cout << "No se encontró el archivo. Se generará un mundo nuevo." << endl;
        for (int i = 0; i < numeronodos; i++) {
            Nodo* nodo = new Nodo(i);
            int ale = aleatorioEntre(1, 3);
            for (int j = 0; j < ale; j++) {
                nodo->agregarCriatura(generarCriatura("cria"));
            }
            mundo.push_back(nodo);
        }
    } else {
        // Leer archivo JSON y reconstruir el mundo
        json mundo_json;
        archivo >> mundo_json;
        archivo.close();

        for (const auto& nodo_json : mundo_json) {
            Nodo* nodo = new Nodo(nodo_json["id"]);
            nodo->setPulsoVital(nodo_json["pulso_vital"]);
            nodo->setEstado(nodo_json["estado"]);

            for (const auto& criatura_json : nodo_json["criaturas"]) {
                string tipo = criatura_json["tipo"];
                MagicalCreature* criatura = nullptr;

                if (tipo == "Dragon") {
                    criatura = new Dragon(
                        criatura_json["nombre"],
                        criatura_json["vitalidad"],
                        criatura_json["poder"],
                        criatura_json["fireResistance"]
                    );
                } else if (tipo == "Hada") {
                    criatura = new Hada(
                        criatura_json["nombre"],
                        criatura_json["vitalidad"],
                        criatura_json["poder"],
                        criatura_json["healingPower"]
                    );
                } else if (tipo == "Quimera") {
                    criatura = new Quimera(
                        criatura_json["nombre"],
                        criatura_json["vitalidad"],
                        criatura_json["poder"],
                        criatura_json["fireResistance"],
                        criatura_json["healingPower"],
                        criatura_json["cabezasExtras"]
                    );
                }

                if (criatura != nullptr) {
                    nodo->agregarCriatura(criatura);
                }
            }

            mundo.push_back(nodo);
        }

        cout << "Mundo cargado correctamente desde 'mundo_sangara.json'." << endl;
    }


    // === Bucle principal del menú ===
    int opc;
    do {
        menu();
        cin >> opc;

        switch (opc) {

            // === Caso 1: Ejecutar un ciclo del mundo ===
            case 1: {
                cout << "== Siguiente ciclo ==" << endl;
                for (int i = 0; i < mundo.size(); i++) {
                    if (mundo[i]->getPulsoVital()) {
                        cout << "\nNodo " << mundo[i]->getId() << " activo:" << endl;

                        vector<MagicalCreature*>* criaturas = mundo[i]->getCriaturas();

                        // Recorrer criaturas y ejecutar acción aleatoria
                        for (auto it = criaturas->begin(); it != criaturas->end(); ) {
                            MagicalCreature* criatura = *it;
                            int accion = aleatorioEntre(0, 5);  // 6 posibles acciones

                            switch (accion) {
                                case 0:  // === Actuar ===
                                    if (Hada* hada = dynamic_cast<Hada*>(criatura)) {
                                        // Hada cura a otras hadas
                                        cout << hada->getName() << " cura a sus aliados del nodo." << endl;
                                        for (MagicalCreature* otra : *criaturas) {
                                            if (otra != hada && dynamic_cast<Hada*>(otra)) {
                                                otra->reducirVitalidad(-aleatorioEntre(10, 30));
                                                cout << " -> " << otra->getName() << " fue curado." << endl;
                                            }
                                        }
                                    } else if (Dragon* dragon = dynamic_cast<Dragon*>(criatura)) {
                                        // Dragón quema a hadas
                                        cout << dragon->getName() << " lanza una llamarada!" << endl;
                                        for (MagicalCreature* otra : *criaturas) {
                                            if (otra != dragon && dynamic_cast<Hada*>(otra)) {
                                                otra->recibirAtaque(aleatorioEntre(20, 60));
                                                cout << " -> " << otra->getName() << " (hada) fue quemada." << endl;
                                            }
                                        }
                                    } else if (Quimera* quimera = dynamic_cast<Quimera*>(criatura)) {
                                        // Quimera ataca a todos y se cura
                                        cout << quimera->getName() << " ataca brutalmente a todos y luego se cura." << endl;
                                        for (MagicalCreature* otra : *criaturas) {
                                            if (otra != quimera) {
                                                otra->recibirAtaque(aleatorioEntre(30, 80));
                                                cout << " -> " << otra->getName() << " fue golpeada." << endl;
                                            }
                                        }
                                        quimera->reducirVitalidad(-aleatorioEntre(20, 40));
                                        cout << " -> " << quimera->getName() << " recuperó vitalidad." << endl;
                                    }
                                    ++it;
                                    break;

                                case 1:  // === Mutar ===
                                    criatura->mutar();
                                    ++it;
                                    break;

                                case 2: {  // === Reproducirse ===
                                    cout << criatura->getName() << " intenta reproducirse..." << endl;
                                    criatura->reproducirse();

                                    // Crear copia del mismo tipo
                                    MagicalCreature* nuevo = nullptr;

                                    if (Hada* hada = dynamic_cast<Hada*>(criatura)) {
                                        nuevo = new Hada(hada->getName() + "_hijo", aleatorioEntre(hada->getVitalidad()/2, hada->getVitalidad()), aleatorioEntre(hada->getPoder()/2, hada->getPoder()), aleatorioEntre(10, 50));
                                    } else if (Dragon* dragon = dynamic_cast<Dragon*>(criatura)) {
                                        nuevo = new Dragon(dragon->getName() + "_hijo", aleatorioEntre(dragon->getVitalidad()/2, dragon->getVitalidad()), aleatorioEntre(dragon->getPoder()/2, dragon->getPoder()), aleatorioEntre(10, 50));
                                    } else if (Quimera* quimera = dynamic_cast<Quimera*>(criatura)) {
                                        nuevo = new Quimera(quimera->getName() + "_hijo", aleatorioEntre(quimera->getVitalidad()/2, quimera->getVitalidad()), aleatorioEntre(quimera->getPoder()/2, quimera->getPoder()), aleatorioEntre(10, 50), aleatorioEntre(10, 50), aleatorioEntre(1, 3));
                                    }

                                    if (nuevo != nullptr) {
                                        criaturas->push_back(nuevo);
                                        cout << " -> Se ha creado un nuevo ser: " << nuevo->getName() << endl;
                                    }

                                    ++it;
                                    break;
                                }

                                case 3:  // === Recibir ataque ===
                                    criatura->recibirAtaque(aleatorioEntre(10, 100));
                                    ++it;
                                    break;

                                case 4:  // === Morir ===
                                    criatura->morir();
                                    delete criatura;
                                    it = criaturas->erase(it);
                                    break;

                                case 5: {  // === Migrar a otro nodo ===
                                    cout << criatura->getName() << " quiere migrar a otro nodo..." << endl;

                                    // Buscar nodos válidos para moverse
                                    vector<int> nodos_disponibles;
                                    for (int nid = 0; nid < mundo.size(); nid++) {
                                        if (nid != i && mundo[nid]->getPulsoVital()) {
                                            nodos_disponibles.push_back(nid);
                                        }
                                    }

                                    if (!nodos_disponibles.empty()) {
                                        int idx = aleatorioEntre(0, nodos_disponibles.size() - 1);
                                        int destino = nodos_disponibles[idx];

                                        mundo[destino]->agregarCriatura(criatura);  // mover criatura
                                        cout << " -> " << criatura->getName() << " ha migrado al nodo " << destino << endl;
                                        it = criaturas->erase(it);  // eliminar del nodo actual
                                    } else {
                                        cout << " -> No hay nodos disponibles para migrar." << endl;
                                        ++it;
                                    }
                                    break;
                                }
                            }
                        }

                    } else {
                        cout << "Nodo " << mundo[i]->getId() << " sin pulso vital." << endl;
                    }
                }
                break;
            }

            // === Caso 2: Aislar nodo ===
            case 2: {
                cout << "== Aislar nodo ==" << endl;
                cout << "Ingrese el ID del nodo a aislar (0 - " << mundo.size() - 1 << "): ";
                int id_nodo;
                cin >> id_nodo;

                if (id_nodo >= 0 && id_nodo < mundo.size()) {
                    mundo[id_nodo]->setPulsoVital(false);
                    mundo[id_nodo]->setEstado("Aislado");
                    cout << "Nodo " << id_nodo << " ha sido aislado correctamente." << endl;
                } else {
                    cout << "ID de nodo no válido." << endl;
                }
                break;
            }

            // === Caso 3: Mostrar el estado de todos los nodos ===
            case 3:
                cout << "== Mostrar mundo ==" << endl;
                for (Nodo* n : mundo) {
                    cout << "Nodo " << n->getId() << " - Estado: " << n->getEstado() << " - Pulso: " << (n->getPulsoVital() ? "Sí" : "No") << endl;
                    n->mostrarCriaturas();
                }
                break;

            // === Caso 4: Guardar mundo (por implementar) ===
            case 4: {
                cout << "== Guardar mundo ==" << endl;

                json mundo_json = json::array();  // arreglo de nodos

                for (Nodo* n : mundo) {
                    mundo_json.push_back(n->serializar());  // cada nodo serializa su info + criaturas
                }

                ofstream archivo("mundo_sangara.json");
                if (archivo.is_open()) {
                    archivo << mundo_json.dump(4);  // dump con indentación de 4 espacios
                    archivo.close();
                    cout << "Mundo guardado en 'mundo_sangara.json' correctamente." << endl;
                } else {
                    cerr << "Error: No se pudo abrir el archivo para guardar." << endl;
                }

                break;
            }

            // === Caso 5: Salir ===
            case 5:
                cout << "== Saliendo del mundo Sangara... ==" << endl;
                break;

            default:
                cout << "Opción no válida." << endl;
        }

    } while (opc != 5);
    return 0;
}
