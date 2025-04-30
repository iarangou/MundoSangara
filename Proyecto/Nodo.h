

#ifndef NODO_H
#define NODO_H



#include <iostream>
#include <vector>
#include <string>
#include "json.hpp"  // Para usar json
using json = nlohmann::json;
using namespace std;

#include "MagicalCreature.h"



class Nodo {
private:
    int id;
    bool pulso_vital;
    string estado;
    vector<MagicalCreature*> criaturas;

public:
    // Constructor
    Nodo(int id);

    // Getters
    int getId() const;

    bool getPulsoVital() const;

    string getEstado() const;


    vector<MagicalCreature*>* getCriaturas();

    void setCriaturas(const vector<MagicalCreature*>& nuevas);

    // Setters
    void setPulsoVital(bool pulso);

    void setEstado(const string& est);

    // Métodos funcionales
    void agregarCriatura(MagicalCreature* creature);

    void eliminarCriatura(MagicalCreature* creature);

    void vaciarse();

    void mostrarCriaturas();

    // Serialización a JSON nodo
    json serializar() const;
};




#endif //NODO_H

