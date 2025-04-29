

#ifndef NODO_H
#define NODO_H



#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // std::remove
#include "json.hpp"  // Para usar json
using json = nlohmann::json;
using namespace std;

#include "MagicalCreature.h"
#include "Dragon.h"
#include "Hada.h"
#include "Quimera.h"


class Nodo {
private:
    int id;
    bool pulso_vital;
    string estado;
    vector<MagicalCreature*> criaturas;

public:
    // Constructor
    Nodo(int id) : id(id), pulso_vital(true), estado("Activo") {}

    // Getters
    int getId() const {
        return id;
    }

    bool getPulsoVital() const {
        return pulso_vital;
    }

    string getEstado() const {
        return estado;
    }


    vector<MagicalCreature*>* getCriaturas() {
        return &criaturas;
    }

    void setCriaturas(const vector<MagicalCreature*>& nuevas) {
        criaturas = nuevas;
    }

    // Setters
    void setPulsoVital(bool pulso) {
        pulso_vital = pulso;
    }

    void setEstado(const string& est) {
        estado = est;
    }

    // Métodos funcionales
    void agregarCriatura(MagicalCreature* creature) {
        criaturas.push_back(creature);
    }

    void eliminarCriatura(MagicalCreature* creature) {
        criaturas.erase(remove(criaturas.begin(), criaturas.end(), creature), criaturas.end());
    }

    void vaciarse() {
        criaturas.clear();
    }

    void mostrarCriaturas() {
        for (auto* criatura : criaturas) {
            criatura->mostrar();
        }
    }

    // Serialización a JSON
    json serializar() const {
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
};




#endif //NODO_H
