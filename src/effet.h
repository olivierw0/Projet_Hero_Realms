#ifndef EFFET_H
#define EFFET_H

#include <string>

class Effet {

enum class TypeEffet {
    OR,
    DMG,
    PIOHE,
    SOIN,
    ADV_DEFAUSSE,
    PREPARE_CHAMPION
};

enum class ConditionEffet {
    AUCUNE,
    DEFAUSSE,
    FACTION,
    SACRIFICE
};

private:
    int id;
    TypeEffet type;
    int valeur;
    ConditionEffet condition; 

public:
    // Constructeur par défaut
    Effet() : id(0), type(TypeEffet::OR), valeur(0), condition(ConditionEffet::AUCUNE) {}
    
    // Constructeur avec paramètres
    Effet(int id, TypeEffet type, int valeur, ConditionEffet condition = ConditionEffet::AUCUNE)
        : id(id), type(type), valeur(valeur), condition(condition) {}

};

#endif // EFFET_H