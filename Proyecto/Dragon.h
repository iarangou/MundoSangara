#pragma once
#include "MagicalCreature.h"

class Dragon : virtual public MagicalCreature {
protected: // Cambié de private a protected
    int fireResistance;

public:
    Dragon(const std::string& name, int vitalidad, int poder, int fireResistance);

    virtual void recibirAtaque(int dano) override;
    virtual void actuar() override;
    virtual void reproducirse() override;
    virtual void morir() override;
    virtual void mutar() override;
    virtual void mostrar() const override;
    virtual json serializar() const override;
};
