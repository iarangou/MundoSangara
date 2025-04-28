#include "Hada.h"
#include <iostream>

using namespace std;

Hada::Hada(const string& name, int vitalidad, int poder, int healingPower)
    : MagicalCreature(name, vitalidad, poder), healingPower(healingPower) {}

void Hada::recibirAtaque(int dano) {
    reducirVitalidad(dano);
}

void Hada::actuar() {
    cout << name << " cura a sus aliados!" << endl;
}

void Hada::reproducirse() {
    cout << name << " esparce polvos mágicos para reproducirse." << endl;
}

void Hada::morir() {
    cout << name << " se desvanece en una luz brillante." << endl;
}

void Hada::mutar() {
    healingPower += 5;
    cout << name << " muta y su poder de curación aumenta." << endl;
}

void Hada::mostrar() const {
    cout << "[Hada] " << name << " - Vitalidad: " << vitalidad << " - Poder: " << poder
         << " - Poder de curación: " << healingPower << endl;
}

json Hada::serializar() const {
    return {
            {"tipo", "Hada"},
            {"nombre", name},
            {"vitalidad", vitalidad},
            {"poder", poder},
            {"healingPower", healingPower}
    };
}
