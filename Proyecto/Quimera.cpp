#include "Quimera.h"
#include <iostream>

using namespace std;

Quimera::Quimera(const string& name, int vitalidad, int poder, int fireResistance, int healingPower, int cabezasExtras)
    : MagicalCreature(name, vitalidad, poder), Dragon(name, vitalidad, poder, fireResistance), Hada(name, vitalidad, poder, healingPower),
      cabezasExtras(cabezasExtras) {}

void Quimera::recibirAtaque(int dano) {
    int danoReducido = dano - fireResistance + healingPower;
    if (danoReducido < 0) danoReducido = 0;
    reducirVitalidad(danoReducido);
}

void Quimera::actuar() {
    cout << name << " ataca brutalmente con sus múltiples cabezas y luego se cura parcialmente!" << endl;
}

void Quimera::reproducirse() {
    cout << name << " se reproduce formando una quimera aún más feroz!" << endl;
}

void Quimera::morir() {
    cout << name << " ruge antes de caer derrotada." << endl;
}

void Quimera::mutar() {
    fireResistance += 5;
    healingPower += 5;
    cabezasExtras++;
    cout << name << " muta: ¡Ahora tiene más cabezas, más resistencia y mayor curación!" << endl;
}

void Quimera::mostrar() const {
    cout << "[Quimera] " << name << " - Vitalidad: " << vitalidad << " - Poder: " << poder
         << " - Resistencia al fuego: " << fireResistance
         << " - Poder de curación: " << healingPower
         << " - Cabezas extras: " << cabezasExtras << endl;
}

json Quimera::serializar() const {
    return {
            {"tipo", "Quimera"},
            {"nombre", name},
            {"vitalidad", vitalidad},
            {"poder", poder},
            {"fireResistance", fireResistance},
            {"healingPower", healingPower},
            {"cabezasExtras", cabezasExtras}
    };
}
