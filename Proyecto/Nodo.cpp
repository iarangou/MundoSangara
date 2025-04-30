
#include "Nodo.h"

void Nodo::mostrarCriaturas() {
    for (auto* criatura : criaturas) {
        criatura->mostrar();
    }
}

json Nodo::serializar() const {
    json j;
    j["id"] = id;
    j["pulso_vital"] = pulso_vital;
    j["estado"] = estado;
    j["criaturas"] = json::array();
    for (auto* criatura : criaturas) {
        j["criaturas"].push_back(criatura->serializar());
    }
    return j;
}

Nodo::Nodo(int id): id(id), pulso_vital(true), estado("Activo") {}

int Nodo::getId() const {
    return id;
}

bool Nodo::getPulsoVital() const {
    return pulso_vital;
}

string Nodo::getEstado() const {
    return estado;
}

vector<MagicalCreature *> * Nodo::getCriaturas() {
    return &criaturas;
}

void Nodo::setCriaturas(const vector<MagicalCreature *> &nuevas) {
    criaturas = nuevas;
}

void Nodo::setPulsoVital(bool pulso) {
    pulso_vital = pulso;
}

void Nodo::setEstado(const string &est) {
    estado = est;
}

void Nodo::agregarCriatura(MagicalCreature *creature) {
    criaturas.push_back(creature);
}

void Nodo::eliminarCriatura(MagicalCreature *creature) {
    criaturas.erase(remove(criaturas.begin(), criaturas.end(), creature), criaturas.end());
}

void Nodo::vaciarse() {
    criaturas.clear();
}
