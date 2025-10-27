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

    // Indices des zones dans zones_communes
    int idx_marche;
    int idx_deck_marche;
    int idx_gemmes_feu;
    int idx_cartes_ecartees;


    // Méthode auxiliaire pour afficher une zone d'un joueur
    

    // Méthode auxiliaire pour afficher une zone commune
    void afficherZoneCommune(TypeZone type_zone) const;

    // Méthode auxiliaire pour afficher le marché avec indices
    void afficherMarche() const;

    // Méthode auxiliaire pour afficher une carte
    void afficherCarte(const Carte& carte, bool est_champion) const;

private:
    // Fonctions d'aide pour l'affichage formaté
    std::string formaterTypeEffet(TypeEffet type, int valeur) const;
    std::string formaterCondition(ConditionEffet condition) const;
    std::string formaterEffet(const Effet& effet, bool avecCondition = true) const;
    std::string formaterListeEffets(const std::vector<Effet>& effets) const;
    
public:
    void afficherCarteFormatee(const Carte* carte, int indice = -1, bool afficherCout = true) const;
    void afficherChampionFormate(const Champion* champion, int indice = -1) const;
    void afficherZoneJoueur(const Joueur& joueur, TypeZone type_zone, bool est_champion) const;
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

    ZoneDeCarte* getMarche() { return (idx_marche >= 0 && idx_marche < zones_communes.size()) ? &zones_communes[idx_marche] : nullptr; }
    ZoneDeCarte* getDeckMarche() { return (idx_deck_marche >= 0 && idx_deck_marche < zones_communes.size()) ? &zones_communes[idx_deck_marche] : nullptr; }
    ZoneDeCarte* getGemmesFeu() { return (idx_gemmes_feu >= 0 && idx_gemmes_feu < zones_communes.size()) ? &zones_communes[idx_gemmes_feu] : nullptr; }
    ZoneDeCarte* getCartesEcartees() { return (idx_cartes_ecartees >= 0 && idx_cartes_ecartees < zones_communes.size()) ? &zones_communes[idx_cartes_ecartees] : nullptr; }
};

#endif // TABLE_PARTIE_H