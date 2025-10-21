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

// Fonction utilitaire pour convertir TypeZone en string
std::string typeZoneToString(TypeZone type);

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
    
    // Constructeur de copie
    ZoneDeCarte(const ZoneDeCarte& other);
    
    // Constructeur de déplacement
    ZoneDeCarte(ZoneDeCarte&& other) noexcept;
    
    // Opérateur d'assignation de copie
    ZoneDeCarte& operator=(const ZoneDeCarte& other);
    
    // Opérateur d'assignation de déplacement
    ZoneDeCarte& operator=(ZoneDeCarte&& other) noexcept;
    
    // Destructeur
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
    
    // Mélanger les cartes de la zone et réassigner les indices
    void melangerCartes();
    
    // Trier les cartes par ordre (utile après mélange)
    void trierParOrdre();

};

#endif // ZONE_DE_CARTE_H