#ifndef ZONE_DE_CARTE_H
#define ZONE_DE_CARTE_H

#include <string>
#include <vector>
#include <memory>

class Carte;
class Joueur;
class TablePartie;

class ZoneDeCarte {
private:
    int id;
    std::string type; // deck, main, defausse, champions, deck_marche, marche, sacrifice
    int owner_joueur_id; // si la zone appartient à un joueur
    int owner_table_id; // si la zone appartient à la table
    std::vector<std::pair<std::shared_ptr<Carte>, int>> cartes; // carte + ordre

public:
    ZoneDeCarte(int id, const std::string& type, int owner_joueur_id = -1, int owner_table_id = -1);
    
    // Getters
    int getId() const { return id; }
    const std::string& getType() const { return type; }
    int getOwnerJoueurId() const { return owner_joueur_id; }
    int getOwnerTableId() const { return owner_table_id; }
    const std::vector<std::pair<std::shared_ptr<Carte>, int>>& getCartes() const { return cartes; }
    size_t getNombreCartes() const { return cartes.size(); }
    
    // Setters
    void setOwnerJoueur(int joueur_id) { this->owner_joueur_id = joueur_id; }
    void setOwnerTable(int table_id) { this->owner_table_id = table_id; }
    
    // Méthodes
    void ajouterCarte(std::shared_ptr<Carte> carte, int ordre = -1);
    std::shared_ptr<Carte> retirerCarte(int index);
    std::shared_ptr<Carte> retirerCarteParId(int carte_id);
    void melangerCartes();
    std::shared_ptr<Carte> piocher(); // retire la première carte
    void afficher() const;
    
    ~ZoneDeCarte() = default;
};

#endif // ZONE_DE_CARTE_H