#ifndef QUIMERA_H
#define QUIMERA_H


#include "Dragon.h"
#include "Hada.h"

class Quimera : public Dragon, public Hada {
private:
    int cabezasExtras;

public:
    Quimera(const std::string& name, int vitalidad, int poder, int fireResistance, int healingPower, int cabezasExtras);

    virtual void recibirAtaque(int dano) override;
    virtual void actuar() override;
    virtual void reproducirse() override;
    virtual void morir() override;
    virtual void mutar() override;
    virtual void mostrar() const override;
    virtual json serializar() const override;
};

#endif