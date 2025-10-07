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
    TablePartie(int id, int nb_gemmes = 50);
    
    // Getters
    int getId() const { return id; }
    int getNbGemmes() const { return nb_gemmes; }
    const std::vector<std::shared_ptr<Joueur>>& getJoueurs() const { return joueurs; }
    const std::vector<std::shared_ptr<ZoneDeCarte>>& getZonesCommunes() const { return zones_communes; }
    
    // Setters
    void setNbGemmes(int gemmes) { this->nb_gemmes = gemmes; }
    
    // Méthodes
    void ajouterJoueur(std::shared_ptr<Joueur> joueur);
    void ajouterZoneCommune(std::shared_ptr<ZoneDeCarte> zone);
    std::shared_ptr<ZoneDeCarte> getZoneCommune(const std::string& type);
    void initialiserPartie();
    void afficher() const;
    
    ~TablePartie() = default;
};

#endif // TABLE_PARTIE_H