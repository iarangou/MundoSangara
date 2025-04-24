```mermaid
classDiagram
  class Nodo {
    - int id
    - bool pulso_vital
    - string Estado
    - vector <MagicalCreature>
    + Nodo(id: int)
    + getid() int
    + getpulso_vital() int
    + getestado() string
    + void Mostrarcriaturas()
    + setpulso_vital(pulso : bool)
    + setestado(est: string)
    + agregarcriatura(ctia: MagicalCreature)
    + eliminarcriatura(ctia: MagicalCreature)
    + vaciarse()
  }

classDiagram
    class MagicalCreature {
        - string name
        - int vitalidad
        - int poder
        + MagicalCreature(name: string, vitalidad: int, poder: int)
        + getName() string
        + getVitalidad() int
        + getPoder() int
        + reducirVitalidad(fuerza: int)
        + recibirAtaque(dano: int)*
        + mostrar()*
    }

    class Dragon {
        - int fireResistance
        + Dragon(name: string, vitalidad: int, poder: int, fireResistance: int)
        + recibirAtaque(dano: int)
        + mostrar() 
    }

    class Hada {
        - int healingPower
        + Hada(name: string, vitalidad: int, poder: int, healingPower: int)
        + recibirAtaque(dano: int)
        + mostrar()
    }

    MagicalCreature <|-- Dragon
    MagicalCreature <|-- Hada
```
