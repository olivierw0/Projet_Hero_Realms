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
    std::vector<Joueur> joueurs;
    std::vector<ZoneDeCarte> zones_communes;

public:

    // Constructeur
    TablePartie(int id, int nb_gemmes) : id(id), nb_gemmes(nb_gemmes) {}

    // Ajouter un joueur à la partie
    void ajouterJoueur(const Joueur& joueur) {
        joueurs.push_back(joueur);
    }

    // Ajouter une zone commune à la partie
    void ajouterZoneCommune(const ZoneDeCarte& zone) {
        zones_communes.push_back(zone);
    }

    // Méthodes pour accéder aux attributs
    int getId() const { return id; }
    int getNbGemmes() const { return nb_gemmes; }
    const std::vector<Joueur>& getJoueurs() const { return joueurs; }
    const std::vector<ZoneDeCarte>& getZonesCommunes() const { return zones_communes; }


};

#endif // TABLE_PARTIE_H