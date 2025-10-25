#include "table_partie.h"
#include "joueur.h"
#include "carte.h"
#include "champion.h"
#include "effet.h"
#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <cstdlib>

// Fonction utilitaire pour clear le terminal
void TablePartie::clearTerminal() {
    #ifdef _WIN32
        system("cls");          // Windows
    #else
        system("clear");        // Linux/Mac/Unix
    #endif
}

// Constructeur / Destructeur

TablePartie::TablePartie(int id, int nb_gemmes) : id(id), nb_gemmes(nb_gemmes), joueur_actuel_index(0) {
    std::cout << "Construction de la table de partie" << std::endl;
}   

TablePartie::~TablePartie() {
    // Destruction des joueurs et des zones communes si nécessaire
    joueurs.clear();
    zones_communes.clear();
    std::cout << "Destruction de la table de partie" << std::endl;
}

// Méthode auxiliaire pour afficher une zone d'un joueur
void TablePartie::afficherZoneJoueur(const Joueur& joueur, TypeZone type_zone, bool est_champion) const {
    for (const auto& zone : joueur.getZones()) {
        if (zone.getType() == type_zone) {
            for (const auto& paire_carte : zone.getCartes()) {
                afficherCarte(paire_carte.first, est_champion);
            }
            if (zone.getCartes().empty()) {
                std::cout << "..." << std::endl;
            }
            return;
        }
    }
}

// Méthode auxiliaire pour afficher une zone commune
void TablePartie::afficherZoneCommune(TypeZone type_zone) const {
    for (const auto& zone : zones_communes) {
        if (zone.getType() == type_zone) {
            for (const auto& paire_carte : zone.getCartes()) {
                std::cout << "(" << paire_carte.first.getCout() << ") ";
                afficherCarte(paire_carte.first, false);
            }
            if (zone.getCartes().empty()) {
                std::cout << "..." << std::endl;
            }
            return;
        }
    }
}

// Méthode auxiliaire pour afficher une carte
void TablePartie::afficherCarte(const Carte& carte, bool est_champion) const {
    
    if (est_champion && carte.getType() == TypeCarte::CHAMPION) {
        // Essayer de caster vers Champion pour accéder à l'état d'activation
        try {
            const Champion& champion = dynamic_cast<const Champion&>(carte);
            std::cout << (champion.isActive() ? "(actif) " : "(désactivé) ");
        } catch (const std::bad_cast&) {
            std::cout << "(activé) "; // Fallback si le cast échoue
        }
    }

    std::cout << carte.getNom() << " / ";
    
    // Afficher faction
    switch (carte.getFaction()) {
        case FactionCarte::ROUGE: std::cout << "ROUGE"; break;
        case FactionCarte::BLEU: std::cout << "BLEU"; break;
        case FactionCarte::VERT: std::cout << "VERT"; break;
        case FactionCarte::JAUNE: std::cout << "JAUNE"; break;
        case FactionCarte::NEUTRE: std::cout << "NEUTRE"; break;
    }
    
    std::cout << " / ";
    
    // Afficher type
    switch (carte.getType()) {
        case TypeCarte::ACTION: std::cout << "ACTION"; break;
        case TypeCarte::OBJET: std::cout << "OBJET"; break;
        case TypeCarte::CHAMPION: std::cout << "CHAMPION"; break;
    }
    
    if (est_champion) {
        // Afficher PV pour les champions
        std::cout << " / PV:" << carte.getPV();
    }
    
    std::cout << " / CONDITION : EFFET";
    
    // TODO: Afficher les vrais effets de la carte
    // for (const auto& effet : carte.getEffets()) { ... }
    
    std::cout << std::endl;
}

// Ajouter un joueur à la partie
void TablePartie::ajouterJoueur(const Joueur& joueur) { joueurs.push_back(joueur); }

// Ajouter une zone commune à la partie

void TablePartie::creerZoneCommune(int id, TypeZone type) {
    zones_communes.emplace_back(id, type, nullptr, this);
}

// Méthodes pour accéder aux attributs
int TablePartie::getId() const { return id; }
int TablePartie::getNbGemmes() const { return nb_gemmes; }
std::vector<Joueur>& TablePartie::getJoueurs() { return joueurs; }
const std::vector<ZoneDeCarte>& TablePartie::getZonesCommunes() const { return zones_communes; }
Joueur& TablePartie::getJoueurActuel() { return joueurs[joueur_actuel_index]; }
Joueur& TablePartie::getAdversaire() { return joueurs[1 - joueur_actuel_index]; }
int TablePartie::getJoueurActuelIndex() const { return joueur_actuel_index; }


void TablePartie::afficherEtatPartie() const {
    // Clear le terminal avant d'afficher
    clearTerminal();
    
    if (joueurs.empty()) {
        std::cout << "Aucun joueur dans la partie." << std::endl;
        return;
    }

    const Joueur& joueur_actuel = joueurs[joueur_actuel_index];
    const Joueur& ennemi = joueurs[(joueur_actuel_index + 1) % joueurs.size()];

    // === JOUEUR ACTUEL ===
    std::cout << "\nJoueur " << joueur_actuel.getId() << std::endl;
    std::cout << "========" << std::endl;
    std::cout << "PV  = " << joueur_actuel.getPv() << std::endl;
    std::cout << "OR  = " << joueur_actuel.getOr() << std::endl;
    std::cout << "DMG = " << joueur_actuel.getCombat() << std::endl;

    // === PV ENNEMI ===
    std::cout << "\nPV Ennemi" << std::endl;
    std::cout << "=========" << std::endl;
    std::cout << "PV = " << ennemi.getPv() << std::endl;

    // === CHAMPIONS ===
    std::cout << "\nChampions" << std::endl;
    std::cout << "=========" << std::endl;
    afficherZoneJoueur(joueur_actuel, TypeZone::CHAMPIONS, true);

    // === CARTES MARCHÉ ===
    std::cout << "\nCartes marche" << std::endl;
    std::cout << "=============" << std::endl;
    afficherZoneCommune(TypeZone::MARCHE);

    // Afficher les gemmes de feu
    std::cout << "(" << 2 << ") Gemmes de feu / " << nb_gemmes << " / EFFETS" << std::endl;

    // === CHAMPIONS ENNEMIS ===
    std::cout << "\nChampions ennemis" << std::endl;
    std::cout << "=================" << std::endl;
    afficherZoneJoueur(ennemi, TypeZone::CHAMPIONS, true);

    // === DÉFAUSSE ===
    std::cout << "\nDefausse" << std::endl;
    std::cout << "========" << std::endl;
    afficherZoneJoueur(joueur_actuel, TypeZone::DEFAUSSE, false);

    // === DÉFAUSSE ENNEMIE ===
    std::cout << "\nDefausse ennemie" << std::endl;
    std::cout << "================" << std::endl;
    afficherZoneJoueur(ennemi, TypeZone::DEFAUSSE, false);

    // === CARTES ÉCARTÉES ===
    std::cout << "\nCartes ecartees" << std::endl;
    std::cout << "===============" << std::endl;
    std::cout << "..." << std::endl;
}

// Méthode pour changer de joueur (fin de tour)
void TablePartie::endTurn() {
    joueur_actuel_index = (joueur_actuel_index + 1) % joueurs.size();
    std::cout << "\n=== FIN DE TOUR ===\n" << std::endl;
    afficherEtatPartie(); 
}

void TablePartie::initZones() {
    // Initialiser les zones des joueurs
    for (Joueur& joueur : joueurs) {
        joueur.initZonesJoueur();
    }
    
    // Réserver la capacité pour les zones communes
    zones_communes.reserve(3);
    
    // Initialiser les zones communes (construction directe dans le vector)
    creerZoneCommune(1, TypeZone::MARCHE);
    creerZoneCommune(2, TypeZone::DECK_MARCHE);
    creerZoneCommune(3, TypeZone::ECARTEES);
}

void TablePartie::initPartie() {
    std::cout << "\n=== Initialisation de la partie ===" << std::endl;
    
    // 1. Initialiser toutes les zones
    initZones();
    
    // 2. Initialiser les decks et distribuer les cartes initiales
    std::cout << "Initialisation des decks et distribution des cartes..." << std::endl;
    for (auto& joueur : joueurs) {
        std::cout << "\nJoueur " << joueur.getId() << ":" << std::endl;
        joueur.initDeck(); // Ajouter les cartes de base au deck
        joueur.melangerDeck(); // Mélanger le deck
        joueur.piocher(5); // Chaque joueur pioche 5 cartes au début
        std::cout << "Deck: " << joueur.getZoneByType(TypeZone::DECK)->taille() << " cartes" << std::endl;
        std::cout << "Main: " << joueur.getNombreCartesEnMain() << " cartes" << std::endl;
    }
    
    std::cout << "\n=== Partie prête à commencer ===" << std::endl;
}
