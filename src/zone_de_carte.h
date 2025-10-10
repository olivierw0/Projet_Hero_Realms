#ifndef ZONE_DE_CARTE_H
#define ZONE_DE_CARTE_H

#include <string>
#include <vector>
#include <memory>

class Carte;
class Joueur;
class TablePartie;

enum class TypeZone {
    DECK,
    MAIN,
    DEFAUSSE,
    CHAMPIONS,
    DECK_MARCHE,
    MARCHE,
};

class ZoneDeCarte {
private:
    int id;
    TypeZone type; // deck, main, defausse, champions, deck_marche, marche
    int owner_id; // si à qui appartient la zone (joueur), -1 si commune
    
    std::vector<std::pair<Carte, int>> cartes; // carte + ordre

public:

};

#endif // ZONE_DE_CARTE_H