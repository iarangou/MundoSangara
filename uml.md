```mermaid
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
        + actuar()*  
        + reproducirse()*  
        + moverse()*  
        + morir()*  
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

    class Quimera {
        - int ferocidad
        + Quimera(name: string, vitalidad: int, poder: int, fireResistance: int, healingPower: int, ferocidad: int)
        + recibirAtaque(dano: int)
        + mostrar()
    }

    class Nodo {
        - int id
        - bool pulso_vital
        - string Estado
        - vector<MagicalCreature>
        + Nodo(id: int)
        + getid() int
        + getpulso_vital() bool
        + getestado() string
        + void Mostrarcriaturas()
        + setpulso_vital(pulso: bool)
        + setestado(est: string)
        + agregarcriatura(ctia: MagicalCreature)
        + eliminarcriatura(ctia: MagicalCreature)
        + vaciarse()
        + saveToJSON(path: string)
        + loadFromJSON(path: string)
    }

    class Mundo {
        - vector<vector<Nodo>> grid
        + Mundo(rows: int, cols: int)
        + iniciarSimulacion()
        + actualizarCiclo()
        + saveToJSON(path: string)
        + loadFromJSON(path: string)
    }

    %% Asociación simple entre criaturas
    MagicalCreature "1" ..> "0..*" MagicalCreature : interactuarCon

    %% Nota sobre RNG
    note right of MagicalCreature
      Se utiliza <random> para movimientos,
      mutaciones y decisiones.
    end note

    %% Herencias
    MagicalCreature <|-- Dragon
    MagicalCreature <|-- Hada
    Dragon <|-- Quimera
    Hada <|-- Quimera

    %% Composición Mundo → Nodo
    Mundo o-- Nodo : contiene
```
