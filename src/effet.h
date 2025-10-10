#ifndef EFFET_H
#define EFFET_H

#include <string>

class Effet {

enum class TypeEffet {
    OR,
    DMG,
    PIOHE,
    SOIN,
    ADV_DEFAUSSE
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

};

#endif // EFFET_H