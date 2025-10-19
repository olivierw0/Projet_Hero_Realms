#ifndef EFFET_H
#define EFFET_H

#include <string>
#include <vector>
using namespace std;

class Effet {

enum class TypeEffet {
    OR,
    DMG,
    PIOCHE,
    SOIN,
    ADV_DEFAUSSE,
    PREPARE_CHAMPION,
    STUN
};

enum class ConditionEffet {
    AUCUNE,
    DEFAUSSE,
    ROUGE,          // Allié rouge requis
    JAUNE,          // Allié jaune requis  
    VERT,           // Allié vert requis
    BLEU,           // Allié bleu requis
    SACRIFICE,
    NB_CHAMPIONS
};

private:
    int id;
    TypeEffet type;
    vector<int> valeur;
    ConditionEffet condition; 

public:
    // Constructeur par défaut
    Effet() : id(0), type(TypeEffet::OR), valeur({0}), condition(ConditionEffet::AUCUNE) {}
    
    // Constructeur avec paramètres
    Effet(int id, TypeEffet type, vector<int> valeur, ConditionEffet condition = ConditionEffet::AUCUNE)
        : id(id), type(type), valeur(valeur), condition(condition) {}

    // Surcharge du constructeur pour un seul entier comme valeur
    Effet(int id, TypeEffet type, int val, ConditionEffet condition = ConditionEffet::AUCUNE)
    : id(id), type(type), valeur({val}), condition(condition) {}

};

#endif // EFFET_H