#include "MagicalCreature.h"
#include <iostream>

MagicalCreature::MagicalCreature(string name, int vitalidad, int poder)
    : name(name), vitalidad(vitalidad), poder(poder) {}

string MagicalCreature::getName() const {
    return name;
}

int MagicalCreature::getVitalidad() const {
    return vitalidad;
}

int MagicalCreature::getPoder() const {
    return poder;
}

void MagicalCreature::reducirVitalidad(int fuerza) {
    vitalidad -= fuerza;
    if (vitalidad < 0) vitalidad = 0;
}

void MagicalCreature::recibirAtaque(int dano) {
    reducirVitalidad(dano);
}

void MagicalCreature::actuar() {
    cout << name << " actúa misteriosamente..." << endl;
}

void MagicalCreature::reproducirse() {
    cout << name << " intenta reproducirse..." << endl;
}

void MagicalCreature::morir() {
    cout << name << " ha muerto." << endl;
}

void MagicalCreature::mutar() {
    cout << name << " sufre una mutación." << endl;
}

void MagicalCreature::mostrar() const {
    cout << "Nombre: " << name << ", Vitalidad: " << vitalidad << ", Poder: " << poder << endl;
}

json MagicalCreature::serializar() const {
    return json{
            {"name", name},
            {"vitalidad", vitalidad},
            {"poder", poder}
    };
}

