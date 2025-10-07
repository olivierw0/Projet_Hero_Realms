#include "table_partie.h"
#include "joueur.h"
#include <iostream>

TablePartie::TablePartie(int id, int nb_gemmes) : id(id), nb_gemmes(nb_gemmes) {
    // Initialiser les zones communes
    zones_communes.push_back(std::make_shared<ZoneDeCarte>(1, "deck_marche", -1, id));
    zones_communes.push_back(std::make_shared<ZoneDeCarte>(2, "marche", -1, id));
    zones_communes.push_back(std::make_shared<ZoneDeCarte>(3, "sacrifice", -1, id));
}

void TablePartie::ajouterJoueur(std::shared_ptr<Joueur> joueur) {
    joueurs.push_back(joueur);
    std::cout << "Joueur " << joueur->getId() << " rejoint la partie." << std::endl;
}

void TablePartie::ajouterZoneCommune(std::shared_ptr<ZoneDeCarte> zone) {
    zones_communes.push_back(zone);
}

std::shared_ptr<ZoneDeCarte> TablePartie::getZoneCommune(const std::string& type) {
    for (auto& zone : zones_communes) {
        if (zone->getType() == type) {
            return zone;
        }
    }
    return nullptr;
}

void TablePartie::initialiserPartie() {
    std::cout << "Initialisation de la partie avec " << joueurs.size() << " joueurs." << std::endl;
    
    // Logique d'initialisation de base
    for (auto& joueur : joueurs) {
        std::cout << "Préparation du joueur " << joueur->getId() << std::endl;
        // Ici, on pourrait ajouter des cartes de départ, mélanger les decks, etc.
    }
    
    std::cout << "Partie initialisée !" << std::endl;
}

void TablePartie::afficher() const {
    std::cout << "=== Table de Partie " << id << " ===" << std::endl;
    std::cout << "Nombre de gemmes: " << nb_gemmes << std::endl;
    std::cout << "Nombre de joueurs: " << joueurs.size() << std::endl;
    
    std::cout << "Zones communes:" << std::endl;
    for (const auto& zone : zones_communes) {
        std::cout << "  " << zone->getType() << ": " << zone->getNombreCartes() << " cartes" << std::endl;
    }
    
    std::cout << "Joueurs:" << std::endl;
    for (const auto& joueur : joueurs) {
        std::cout << "  Joueur " << joueur->getId() << " - PV: " << joueur->getPv() << std::endl;
    }
    std::cout << std::endl;
}