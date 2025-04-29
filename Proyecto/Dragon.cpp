#include "Dragon.h"
#include <iostream>

using namespace std;

Dragon::Dragon(const string& name, int vitalidad, int poder, int fireResistance)
    : MagicalCreature(name, vitalidad, poder), fireResistance(fireResistance) {}

void Dragon::recibirAtaque(int dano) {
    int danoReducido = dano - fireResistance;
    if (danoReducido < 0) danoReducido = 0;
    reducirVitalidad(danoReducido);
}

void Dragon::actuar() {
    cout << name << " lanza una llamarada!" << endl;
}

void Dragon::reproducirse() {
    cout << name << " busca otro dragon para reproducirse." << endl;
}

void Dragon::morir() {
    cout << name << " cae del cielo y muere." << endl;
}

void Dragon::mutar() {
    fireResistance += 5;
    cout << name << " muta y ahora resiste mejor el fuego." << endl;
}

void Dragon::mostrar() const {
    cout << "[Dragon] " << name << " - Vitalidad: " << vitalidad << " - Poder: " << poder
         << " - Resistencia al fuego: " << fireResistance << endl;
}

json Dragon::serializar() const {
    return {
            {"tipo", "Dragon"},
            {"nombre", name},
            {"vitalidad", vitalidad},
            {"poder", poder},
            {"fireResistance", fireResistance}
    };
}
