#include <iostream>
#include "MagicalCreature.h"
#include "Dragon.h"
#include "Hada.h"
#include "Quimera.h"
#include "Nodo.h"
#include <random>
#include <vector>

using namespace std;

// Random global
std::random_device rd;
std::mt19937 gen(rd());

int aleatorioEntre(int a, int b) {
    std::uniform_int_distribution<> distribucion(a, b);
    return distribucion(gen);
}

MagicalCreature* generarCriatura(const string& nombreBase) {
    int tipo = aleatorioEntre(0, 2);
    int vitalidad = aleatorioEntre(10, 1000);
    int poder = aleatorioEntre(30, 400);

    if (tipo == 0)
        return new Dragon(nombreBase + "_D", vitalidad, poder, aleatorioEntre(100, 400));
    else if (tipo == 1)
        return new Hada(nombreBase + "_H", vitalidad, poder, aleatorioEntre(100, 400));
    else
        return new Quimera(nombreBase + "_Q", vitalidad, poder, aleatorioEntre(100, 400), aleatorioEntre(100, 400), aleatorioEntre(100, 400));
}

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
    cout << "== Prueba de Mundo Sangara ==" << endl;

    // Inicializar el mundo
    vector<Nodo*> mundo;
    for (int i = 0; i < 1; i++) {
        mundo.push_back(new Nodo(i));
        int ale = aleatorioEntre(1, 3);
        for (int j = 0; j < ale; j++) {
            mundo[i]->agregarCriatura(generarCriatura("cria"));
        }
    }

    int opc;
    do {
        menu();
        cin >> opc;

        switch (opc) {
            case 1: {
                cout << "== Siguiente ciclo ==" << endl;
                for (int i = 0; i < mundo.size(); i++) {
                    if (mundo[i]->getPulsoVital()) {
                        cout << "\nNodo " << mundo[i]->getId() << " activo:" << endl;

                        vector<MagicalCreature*>* criaturas = mundo[i]->getCriaturas();

                        for (auto it = criaturas->begin(); it != criaturas->end(); ) {
                            MagicalCreature* criatura = *it;
                            int accion = aleatorioEntre(0, 4); // 0: actuar, 1: mutar, 2: reproducirse, 3: recibir ataque, 4: morir

                            switch (accion) {
                                case 0:  // actuar con efecto
                                    // HADA: cura a aliados
                                    if (Hada* hada = dynamic_cast<Hada*>(criatura)) {
                                        cout << hada->getName() << " cura a sus aliados del nodo." << endl;
                                        for (MagicalCreature* otra : *criaturas) {
                                            if (otra != hada  && dynamic_cast<Hada*>(otra)) {
                                                otra->reducirVitalidad(-aleatorioEntre(10, 30)); // -dano = curar
                                                cout << " -> " << otra->getName() << " fue curado." << endl;
                                            }
                                        }
                                    }

                                    // DRAGON: daña a hadas
                                    else if (Dragon* dragon = dynamic_cast<Dragon*>(criatura)) {
                                        cout << dragon->getName() << " lanza una llamarada!" << endl;
                                        for (MagicalCreature* otra : *criaturas) {
                                            if (otra != dragon && dynamic_cast<Hada*>(otra)) {
                                                otra->recibirAtaque(aleatorioEntre(20, 60));
                                                cout << " -> " << otra->getName() << " (hada) fue quemada." << endl;
                                            }
                                        }
                                    }

                                    // QUIMERA: daña a todos y se cura
                                    else if (Quimera* quimera = dynamic_cast<Quimera*>(criatura)) {
                                        cout << quimera->getName() << " ataca brutalmente a todos y luego se cura." << endl;
                                        for (MagicalCreature* otra : *criaturas) {
                                            if (otra != quimera) {
                                                otra->recibirAtaque(aleatorioEntre(30, 80));
                                                cout << " -> " << otra->getName() << " fue golpeada." << endl;
                                            }
                                        }
                                        quimera->reducirVitalidad(-aleatorioEntre(20, 40)); // se cura
                                        cout << " -> " << quimera->getName() << " recuperó vitalidad." << endl;
                                    }

                                    //else {
                                      //  criatura->actuar(); // fallback genérico
                                    //}

                                    ++it;
                                    break;
                                case 1:
                                    criatura->mutar();
                                    ++it;
                                    break;
                                case 2: {
                                    // reproducirse
                                    cout << criatura->getName() << " intenta reproducirse..." << endl;
                                    criatura->reproducirse(); // mensaje propio

                                    // Ahora creamos un nuevo ser basado en el tipo
                                    MagicalCreature* nuevo = nullptr;

                                    if (Hada* hada = dynamic_cast<Hada*>(criatura)) {
                                        nuevo = new Hada(
                                            hada->getName() + "_hijo",
                                            aleatorioEntre(hada->getVitalidad() / 2, hada->getVitalidad()),
                                            aleatorioEntre(hada->getPoder() / 2, hada->getPoder()),
                                            aleatorioEntre(10, 50)
                                        );
                                    }
                                    else if (Dragon* dragon = dynamic_cast<Dragon*>(criatura)) {
                                        nuevo = new Dragon(
                                            dragon->getName() + "_hijo",
                                            aleatorioEntre(dragon->getVitalidad() / 2, dragon->getVitalidad()),
                                            aleatorioEntre(dragon->getPoder() / 2, dragon->getPoder()),
                                            aleatorioEntre(10, 50)
                                        );
                                    }
                                    else if (Quimera* quimera = dynamic_cast<Quimera*>(criatura)) {
                                        nuevo = new Quimera(
                                            quimera->getName() + "_hijo",
                                            aleatorioEntre(quimera->getVitalidad() / 2, quimera->getVitalidad()),
                                            aleatorioEntre(quimera->getPoder() / 2, quimera->getPoder()),
                                            aleatorioEntre(10, 50),
                                            aleatorioEntre(10, 50),
                                            aleatorioEntre(1, 3)
                                        );
                                    }

                                    if (nuevo != nullptr) {
                                        criaturas->push_back(nuevo); // agregamos el nuevo hijo al mismo nodo
                                        cout << " -> Se ha creado un nuevo ser: " << nuevo->getName() << endl;
                                    }

                                    ++it;
                                    break;
                                }
                                case 3:
                                    criatura->recibirAtaque(aleatorioEntre(10, 100));
                                    ++it;
                                    break;
                                case 4:
                                    criatura->morir();
                                    delete criatura;
                                    it = criaturas->erase(it);
                                    break;
                            }
                        }
                    } else {
                        cout << "Nodo " << mundo[i]->getId() << " sin pulso vital." << endl;
                    }
                }
                break;
            }

            case 2:
                cout << "== Aislar nodo ==" << endl;
                // Ejemplo: puedes pedir ID y desactivar el nodo
                break;

            case 3:
                cout << "== Mostrar mundo ==" << endl;
                for (Nodo* n : mundo) {
                    cout << "Nodo " << n->getId() << " - Estado: " << n->getEstado() << " - Pulso: " << (n->getPulsoVital() ? "Sí" : "No") << endl;
                    n->mostrarCriaturas();
                }
                break;

            case 4:
                cout << "== Guardar mundo ==" << endl;
                // Aquí puedes serializar a JSON si lo deseas
                break;

            case 5:
                cout << "== Saliendo del mundo Sangara... ==" << endl;
                break;

            default:
                cout << "Opción no válida." << endl;
        }

    } while (opc != 5);

    // Liberar memoria
    for (Nodo* n : mundo) {
        vector<MagicalCreature*>* criaturas = n->getCriaturas();
        for (MagicalCreature* c : *criaturas) {
            delete c;
        }
        delete n;
    }

    return 0;
}
