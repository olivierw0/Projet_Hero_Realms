#ifndef CARTE_H
#define CARTE_H

#include <string>
#include <vector>
#include <memory>

class Effet;

// Énumérations pour les types et factions de cartes
enum class TypeCarte {
    ACTION,
    OBJET,
    CHAMPION
};

enum class FactionCarte {
    ROUGE,      // Faction de Nécros
    BLEU,       // Faction de la Guilde
    VERT,       // Faction Sauvage
    JAUNE,      // Faction Impériale
    NEUTRE      // Cartes de Base
};

class Carte {
private:
    int id;        // ID unique de cette carte
    std::string nom;
    int cout;
    TypeCarte type;
    FactionCarte faction;
    std::string description;
    std::vector<Effet> effets;

public:

};

#endif // CARTE_H