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

// =====================================================
// CODES COULEURS ANSI
// =====================================================
#define RESET_COLOR   "\033[0m"
#define BOLD_TEXT     "\033[1m"
#define DIM_TEXT      "\033[2m"
#define ITALIC_TEXT   "\033[3m"

// Couleurs de factions (renommées pour éviter conflit avec FactionCarte::JAUNE, etc.)
#define COLOR_JAUNE   "\033[93m"
#define COLOR_BLEU    "\033[94m"
#define COLOR_ROUGE   "\033[31m"
#define COLOR_VERT    "\033[92m"
#define COLOR_GRIS    "\033[90m"

// Couleurs d'effets
#define COLOR_OR         "\033[33m"
#define COLOR_DMG        "\033[91m"
#define COLOR_HEALTH     "\033[32m"
#define COLOR_CARD       "\033[36m"
#define COLOR_SACRIFICE  "\033[35m"

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

    void initMarche();
    void initZones();

    void ajouterJoueur(const Joueur& joueur);
    void creerZoneCommune(int id, TypeZone type); 

    void afficherZoneJoueur(const Joueur& joueur, TypeZone type_zone) const;
    void afficherMarche() const;
    void afficherChampionFormate(const Champion* champion, int indice = -1) const;
    
    void remplirMarche();

    // Fonctions d'aide pour l'affichage formaté
    std::string formaterTypeEffet(TypeEffet type, int valeur) const;
    std::string formaterCondition(ConditionEffet condition) const;
    std::string formaterEffet(const Effet& effet, bool avecCondition = true) const;
    std::string formaterListeEffets(const std::vector<Effet>& effets) const;
    const char* getCouleurFaction(FactionCarte faction) const;
    std::string factionToString(FactionCarte faction) const;
    std::string typeCarteToString(TypeCarte type) const;

public:
    // Constructeur / Destructeur
    TablePartie(int id, int nb_gemmes);
    ~TablePartie();

    // Getters & Setters
    int getId() const;
    int getNbGemmes() const;
    std::vector<Joueur>& getJoueurs();
    Joueur& getJoueurActuel();
    Joueur& getAdversaire();
    int getJoueurActuelIndex() const;

    const std::vector<ZoneDeCarte>& getZonesCommunes() const;
    ZoneDeCarte* getMarche();
    ZoneDeCarte* getDeckMarche();
    ZoneDeCarte* getGemmesFeu();
    ZoneDeCarte* getCartesEcartees();

    // Méthodes publiques
    void initPartie();
    void afficherEtatPartie() const;
    bool acheterCarteMarche(int indice, Joueur& acheteur);
    void endTurn();
    
    void afficherDeckMarche() const;
    bool piocheCarteSpecifique(int idCarte, Joueur& joueur);
    void afficherCarteFormatee(const Carte* carte, int indice = -1, bool afficherCout = true) const;

};

#endif // TABLE_PARTIE_H