#ifndef ZONE_DE_CARTE_H
#define ZONE_DE_CARTE_H

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

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
    ECARTEES
};

class ZoneDeCarte {
private:
    int id;
    TypeZone type; // deck, main, defausse, champions, deck_marche, marche
    Joueur* proprietaire; // nullptr si zone commune
    TablePartie* table; // nullptr si zone joueur
    std::vector<std::pair<Carte, int>> cartes; // carte + ordre

public:

    // Constructeur
    ZoneDeCarte(int id, TypeZone type, Joueur* proprietaire = nullptr, TablePartie* table = nullptr);
    ~ZoneDeCarte();

    // Méthodes pour accéder aux attributs
    int getId() const;
    TypeZone getType() const;
    Joueur* getProprietaire() const;
    TablePartie* getTable() const;
    const std::vector<std::pair<Carte, int>>& getCartes() const;

    // Ajouter une carte à la zone avec un ordre spécifique
    void ajouterCarte(const Carte& carte, int ordre);

    // Retirer une carte de la zone par son ID
    bool retirerCarte(int carteId);

    // Déplacer une carte vers une autre zone
    bool deplacerCarte(int carteId, ZoneDeCarte& destination, int nouvelOrdre);

    // Déplacer toutes les cartes vers une autre zone
    void deplacerToutesLesCartes(ZoneDeCarte& destination);

    // Vérifier si la zone est vide
    bool estVide() const;

    // Obtenir le nombre de cartes
    size_t taille() const;

    // Trouver une carte par ID (sans la retirer)
    const Carte* trouverCarte(int carteId) const;

};

#endif // ZONE_DE_CARTE_H