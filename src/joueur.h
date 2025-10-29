#ifndef JOUEUR_H
#define JOUEUR_H

#include <vector>
#include <memory>
#include "carte.h"
#include "champion.h"
#include "zone_de_carte.h"

class Joueur {
private:
    int id;
    int pv;
    int or_value;
    int combat;
    std::vector<ZoneDeCarte> zones;
    TablePartie* table; // Référence à la table de jeu
    std::pair<bool,int> nextAcquiredTopDeck = {false, 0}; // Indique si les prochaines cartes acquises doivent être top-deckées et combien (exemple pour 3 cartes acquises ce tour à placer au top du deck : {true, 3})
    std::pair<bool,int> nextAcquiredTopDeckAction = {false, 0}; // Même chose mais pour les actions (exemple pour 2 actions achetées ce tour à placer au top du deck : {true, 2})
    std::pair<bool,int> nextAcquiredHand = {false, 0}; // Indique si les prochaines cartes acquises doivent être placées en main (exemple pour 1 carte acquise ce tour à placer en main : {true, 1})

public:
    // Constructeur
    Joueur(int id, int pv) : id(id), pv(pv), or_value(0), combat(0), table(nullptr) {
        initZonesJoueur();
    }
    ~Joueur();

    // Méthodes pour accéder aux attributs
    int getId() const { return id; }
    int getPv() const { return pv; }
    int getOr() const { return or_value; }
    int getCombat() const { return combat; }
    const std::vector<ZoneDeCarte>& getZones() const { return zones; }
    TablePartie* getTable() const { return table; }
    std::pair<bool,int> getNextAcquiredTopDeck() const { return nextAcquiredTopDeck; }
    std::pair<bool,int> getNextAcquiredTopDeckAction() const { return nextAcquiredTopDeckAction; }
    std::pair<bool,int> getNextAcquiredHand() const { return nextAcquiredHand; }
    void setTable(TablePartie* t) { table = t; }
    void setNextAcquiredTopDeck(bool value, int nbCarte);
    void setNextAcquiredTopDeckAction(bool value, int nbCarte);
    void setNextAcquiredHand(bool value, int nbCarte);
    

    void takeDamage(int amount);
    void heal(int amount);
    void addOr(int amount);
    bool spendOr(int amount); // False si pas assez d'or.
    void addCombat(int amount);

    // A chaque fin de tour : or & combat sont reset
    void resetCombat();
    void resetOr();
    void resetChampions(); // Untap tous les champions non eliminés
    void resetNextAcquiredTopDeck() { nextAcquiredTopDeck = {false, 0}; } 
    void resetNextAcquiredTopDeckAction() { nextAcquiredTopDeckAction = {false, 0}; }
    void resetNextAcquiredHand() { nextAcquiredHand = {false, 0}; }

    // Ajouter une zone au joueur
    void ajouterZone(const ZoneDeCarte& zone) {
        zones.push_back(zone);
    }

    void creerZone(int id, TypeZone type, Joueur* proprietaire = nullptr, TablePartie* table = nullptr);
    ZoneDeCarte* getZoneByType(TypeZone type);
    const ZoneDeCarte* getZoneByType(TypeZone type) const;
    ZoneDeCarte* getZoneById(int zoneId);

    void initZonesJoueur(); // Initialisation au début de la partie
    void initDeck(); // Initialisation au début de la partie
    
    // Gestion des cartes en main
    void afficherMain() const; // Afficher la main du joueur (indices, nom, description) (1-based)
    void afficherChampions() const; // Afficher la zone des champions du joueur (indices, nom, description) (1-based)
    bool jouerCarte(int indice); // Jouer une carte par son indice (1-based)
    int getNombreCartesEnMain() const;
    void jouerToutesLesCartes(); // Jouer toutes les cartes en main

    // Gestion du deck
    void melangerDeck(); // Mélanger le deck du joueur
    void piocher(int nbCartes = 1); // Piocher des cartes du deck vers la main

    void degatsFinTour(int totalCombat); // Infliger les dégâts aux champions avec Garde en priorité
};

#endif // JOUEUR_H