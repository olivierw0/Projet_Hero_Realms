#ifndef TABLE_PARTIE_H
#define TABLE_PARTIE_H

#include <vector>
#include <memory>
#include "zone_de_carte.h"

class Joueur;

class TablePartie {
private:
    int id;
    int nb_gemmes;
    std::vector<std::shared_ptr<Joueur>> joueurs;
    std::vector<std::shared_ptr<ZoneDeCarte>> zones_communes;

public:

};

#endif // TABLE_PARTIE_H