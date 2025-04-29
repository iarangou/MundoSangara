#ifndef MAGICALCREATURE_H
#define MAGICALCREATURE_H

#include <string>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class MagicalCreature {
protected:
    string name;
    int vitalidad;
    int poder;

public:
    MagicalCreature(string name, int vitalidad, int poder);

    string getName() const;
    int getVitalidad() const;
    int getPoder() const;

    void reducirVitalidad(int fuerza);

    virtual void recibirAtaque(int dano);
    virtual void actuar();
    virtual void reproducirse();
    virtual void morir();
    virtual void mutar();
    virtual void mostrar() const;
    virtual json serializar() const;

    virtual ~MagicalCreature() = default;
};

#endif
