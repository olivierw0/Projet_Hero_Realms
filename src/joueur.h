#ifndef JOUEUR_H
#define JOUEUR_H

#include <vector>
#include <memory>
#include "carte.h"
#include "champion.h"
#include "zone_de_carte.h"

// Codes couleurs ANSI
#define RESET_COLOR   "\033[0m"
#define BOLD_TEXT     "\033[1m"
#define DIM_TEXT      "\033[2m"

class Joueur {
private:
    int id;
    int pv;
    int or_value;
    int combat;
    std::vector<ZoneDeCarte> zones;
    TablePartie* table; // Référence à la table de jeu

    bool godMode;

    void resetCombat();
    void resetOr();
    void resetChampions();

    void ajouterZone(const ZoneDeCarte& zone);
    void creerZone(int id, TypeZone type, Joueur* proprietaire = nullptr, TablePartie* table = nullptr);

public:
    // Constructeur & Destructeur
    Joueur(int id, int pv);
    ~Joueur();

    // Méthodes pour accéder aux attributs
    int getId() const;
    int getPv() const;
    int getOr() const;
    int getCombat() const;
    bool isGodMode() const;
    const std::vector<ZoneDeCarte>& getZones() const;
    TablePartie* getTable() const;
    int getNombreCartesEnMain() const;
    ZoneDeCarte* getZoneByType(TypeZone type);
    const ZoneDeCarte* getZoneByType(TypeZone type) const;
    ZoneDeCarte* getZoneById(int zoneId);

    void setPv(int newPv);
    void setTable(TablePartie* t);
    void activerGodMode();
    void desactiverGodMode();

    void initZonesJoueur(); // Initialisation au début de la partie
    void initDeck(); // Initialisation au début de la partie
    
    void afficherMain() const; // Afficher la main du joueur (indices, nom, description)
    bool jouerCarte(int indice); // Jouer une carte par son indice 
    void jouerToutesLesCartes(); // Jouer toutes les cartes en main
    
    void afficherChampions() const; // Afficher la zone des champions du joueur (indices, nom, description)
    bool tapChampion(int indice);

    bool spendOr(int amount); // False si pas assez d'or.
    void takeDamage(int amount);
    void heal(int amount);
    void addOr(int amount);
    void addCombat(int amount);

    // Gestion du deck
    void melangerDeck(); // Mélanger le deck du joueur
    void piocher(int nbCartes = 1); // Piocher des cartes du deck vers la main
    void degatsFinTour(int totalCombat); // Infliger les dégâts aux champions avec Garde en priorité
    void resetJoueur();
};

#endif // JOUEUR_H