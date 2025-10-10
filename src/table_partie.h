#ifndef TABLE_PARTIE_H
#define TABLE_PARTIE_H

#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>
#include "zone_de_carte.h"

class Joueur;

class TablePartie {
private:
    int id;
    int nb_gemmes;
    std::vector<Joueur> joueurs;
    std::vector<ZoneDeCarte> zones_communes;
    int joueur_actuel_index; // Index du joueur qui joue actuellement

public:

    // Constructeur
    TablePartie(int id, int nb_gemmes) : id(id), nb_gemmes(nb_gemmes), joueur_actuel_index(0) {}

    // Ajouter un joueur à la partie
    void ajouterJoueur(const Joueur& joueur) {
        joueurs.push_back(joueur);
    }

    // Ajouter une zone commune à la partie
    void ajouterZoneCommune(const ZoneDeCarte& zone) {
        zones_communes.push_back(zone);
    }

    // Méthodes pour accéder aux attributs
    int getId() const { return id; }
    int getNbGemmes() const { return nb_gemmes; }
    const std::vector<Joueur>& getJoueurs() const { return joueurs; }
    const std::vector<ZoneDeCarte>& getZonesCommunes() const { return zones_communes; }

    void afficherEtatPartie() const {
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

        // === CARTES EN MAIN ===
        std::cout << "\nCartes en main" << std::endl;
        std::cout << "==============" << std::endl;
        afficherZoneJoueur(joueur_actuel, TypeZone::MAIN, false);

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

private:
    // Méthode auxiliaire pour afficher une zone d'un joueur
    void afficherZoneJoueur(const Joueur& joueur, TypeZone type_zone, bool est_champion) const {
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
        std::cout << "..." << std::endl;
    }

    // Méthode auxiliaire pour afficher une zone commune
    void afficherZoneCommune(TypeZone type_zone) const {
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
        std::cout << "..." << std::endl;
    }

    // Méthode auxiliaire pour afficher une carte
    void afficherCarte(const Carte& carte, bool est_champion) const {
        if (est_champion) {
            std::cout << "(activé) "; // À modifier selon l'état du champion
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

public:
    // Méthode pour changer de joueur (fin de tour)
    void endTurn() {
        joueur_actuel_index = (joueur_actuel_index + 1) % joueurs.size();
        std::cout << "\n=== FIN DE TOUR ===\n" << std::endl;
        afficherEtatPartie(); 
    }

    // Getter pour le joueur actuel
    const Joueur& getJoueurActuel() const {
        return joueurs[joueur_actuel_index];
    }

    // Getter pour l'index du joueur actuel
    int getJoueurActuelIndex() const {
        return joueur_actuel_index;
    }
};

#endif // TABLE_PARTIE_H