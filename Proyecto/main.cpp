#include <iostream>
#include "MagicalCreature.h"
#include "Dragon.h"
#include "Hada.h"
#include "Quimera.h"

//prueba para dejar funcionando las criaturas, falta json, y darle las habilidades especiales

using namespace std;

int main() {
    cout << "== Prueba de Magical Creatures ==" << endl << endl;

    // Crear un Dragon
    Dragon drogon("Drogon", 150, 80, 20);
    cout << "-- Dragon creado --" << endl;
    drogon.mostrar();
    drogon.actuar();
    drogon.recibirAtaque(30);
    drogon.mostrar();
    cout << endl;

    // Crear un Hada
    Hada tinkerbell("Tinkerbell", 100, 50, 15);
    cout << "-- Hada creada --" << endl;
    tinkerbell.mostrar();
    tinkerbell.actuar();
    tinkerbell.recibirAtaque(25);
    tinkerbell.mostrar();
    cout << endl;

    // Crear una Quimera
    Quimera chimera("Chimera", 200, 90, 10, 5, 30);
    cout << "-- Quimera creada --" << endl;
    chimera.mostrar();
    chimera.actuar();
    chimera.recibirAtaque(50);
    chimera.mostrar();
    cout << endl;

    // Serialización de ejemplo (imprimir en JSON)
    cout << "-- Serialización en JSON --" << endl;
    cout << drogon.serializar().dump(4) << endl << endl;
    cout << tinkerbell.serializar().dump(4) << endl << endl;
    cout << chimera.serializar().dump(4) << endl << endl;

    return 0;
}
