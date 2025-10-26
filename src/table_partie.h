#ifndef TABLE_PARTIE_H
#define TABLE_PARTIE_H

#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>
#include "zone_de_carte.h"
#include "joueur.h"
#include "carte.h"
#include "effet.h"

class Joueur;

class TablePartie {
private:
    int id;
    int nb_gemmes;
    std::vector<Joueur> joueurs;
    std::vector<ZoneDeCarte> zones_communes;
    int joueur_actuel_index; // Index du joueur qui joue actuellement

    ZoneDeCarte* marche;
    ZoneDeCarte* deck_marche;
    ZoneDeCarte* gemmes_feu;
    ZoneDeCarte* cartes_ecartees;


    // Méthode auxiliaire pour afficher une zone d'un joueur
    void afficherZoneJoueur(const Joueur& joueur, TypeZone type_zone, bool est_champion) const;

    // Méthode auxiliaire pour afficher une zone commune
    void afficherZoneCommune(TypeZone type_zone) const;

    // Méthode auxiliaire pour afficher une carte
    void afficherCarte(const Carte& carte, bool est_champion) const;

public:

    // Constructeur / Destructeur
    TablePartie(int id, int nb_gemmes);
    ~TablePartie();

    // Ajouter un joueur à la partie
    void ajouterJoueur(const Joueur& joueur);

    // Ajouter une zone commune à la partie
    void creerZoneCommune(int id, TypeZone type);

    // Méthodes pour accéder aux attributs
    int getId() const;
    int getNbGemmes() const;
    std::vector<Joueur>& getJoueurs();
    const std::vector<ZoneDeCarte>& getZonesCommunes() const;

    void afficherEtatPartie() const;

    // Méthode pour changer de joueur (fin de tour)
    void endTurn();

    // Getter pour le joueur actuel
    Joueur& getJoueurActuel();
    
    // Getter pour l'adversaire du joueur actuel
    Joueur& getAdversaire();

    // Getter pour l'index du joueur actuel
    int getJoueurActuelIndex() const;
    
    // Fonction utilitaire pour clear le terminal
    static void clearTerminal();

    // Initialiser les zones de chaque joueur
    void initZones();
    
    // Initialiser complètement la partie (zones, decks, mains initiales)
    void initPartie();


    void initMarche();                          // Initialiser le marché avec les cartes
    void remplirMarche();                       // Remplir le marché à 5 cartes
    bool acheterCarteMarche(int indice, Joueur& acheteur); // Acheter une carte du marché
    void afficherMarche() const;                // Afficher les cartes disponibles

    ZoneDeCarte* getMarche() { return marche; }
    ZoneDeCarte* getDeckMarche() { return deck_marche; }
    ZoneDeCarte* getGemmesFeu() { return gemmes_feu; }
    ZoneDeCarte* getCartesEcartees() { return cartes_ecartees; }
};

#endif // TABLE_PARTIE_H