#include "carte.h"
#include "zone_de_carte.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

// Fonction utilitaire pour convertir TypeZone en string
std::string typeZoneToString(TypeZone type) {
    switch (type) {
        case TypeZone::DECK: return "DECK";
        case TypeZone::MAIN: return "MAIN";
        case TypeZone::DEFAUSSE: return "DEFAUSSE";
        case TypeZone::CHAMPIONS: return "CHAMPIONS";
        case TypeZone::DECK_MARCHE: return "DECK_MARCHE";
        case TypeZone::MARCHE: return "MARCHE";
        case TypeZone::ECARTEES: return "ECARTEES";
        default: return "UNKNOWN";
    }
}

// ===========================
// Constructeurs & Destructeur
// ===========================
ZoneDeCarte::ZoneDeCarte(int id, TypeZone type, Joueur* proprietaire, TablePartie* table)
    : id(id), type(type), proprietaire(proprietaire), table(table) {
    // Debug : affichage seulement en mode debug
    #ifdef DEBUG
        std::cout << "Construction de la zone " << typeZoneToString(type) << " (ID: " << id << ")" << std::endl;
    #endif
}
// Constructeur de copie
ZoneDeCarte::ZoneDeCarte(const ZoneDeCarte& other)
    : id(other.id), type(other.type), proprietaire(other.proprietaire), 
      table(other.table), cartes(other.cartes) {
    #ifdef DEBUG
        std::cout << "Copie de la zone " << typeZoneToString(type) << " (ID: " << id << ")" << std::endl;
    #endif
}
// Constructeur de déplacement  
ZoneDeCarte::ZoneDeCarte(ZoneDeCarte&& other) noexcept
    : id(other.id), type(other.type), proprietaire(other.proprietaire),
      table(other.table), cartes(std::move(other.cartes)) {
    #ifdef DEBUG
        std::cout << "Déplacement de la zone " << typeZoneToString(type) << " (ID: " << id << ")" << std::endl;
    #endif
}

ZoneDeCarte::~ZoneDeCarte() {
    cartes.clear();
    #ifdef DEBUG
        std::cout << "Destruction de la zone " << typeZoneToString(type) << " (ID: " << id << ")" << std::endl;
    #endif
}

// Opérateur d'assignation de copie
ZoneDeCarte& ZoneDeCarte::operator=(const ZoneDeCarte& other) {
    if (this != &other) {
        id = other.id;
        type = other.type;
        proprietaire = other.proprietaire;
        table = other.table;
        cartes = other.cartes;
    }
    return *this;
}

// Opérateur d'assignation de déplacement
ZoneDeCarte& ZoneDeCarte::operator=(ZoneDeCarte&& other) noexcept {
    if (this != &other) {
        id = other.id;
        type = other.type;
        proprietaire = other.proprietaire;
        table = other.table;
        cartes = std::move(other.cartes);
    }
    return *this;
}



// Méthodes pour accéder aux attributs
int ZoneDeCarte::getId() const { return id; }
TypeZone ZoneDeCarte::getType() const { return type; }
Joueur* ZoneDeCarte::getProprietaire() const { return proprietaire; }
TablePartie* ZoneDeCarte::getTable() const { return table; }
const std::vector<std::pair<Carte*, int>>& ZoneDeCarte::getCartes() const { return cartes; }

// Ajouter une carte à la zone avec un ordre spécifique
void ZoneDeCarte::ajouterCarte(Carte* carte, int ordre) {
    if (ordre < 0 || ordre >= cartes.size()) {
        cartes.emplace_back(carte, cartes.size());
    } else {
        // Décaler les cartes existantes
        for (auto& p : cartes) {
            if (p.second >= ordre) p.second++;
        }
        cartes.emplace_back(carte, ordre);
    }
}


// Retirer une carte de la zone par son ID
bool ZoneDeCarte::retirerCarte(int carteId) {
    auto it = std::remove_if(cartes.begin(), cartes.end(),
                                [carteId](const std::pair<Carte*, int>& p) {
                                    return p.first->getId() == carteId;
                                });
    if (it != cartes.end()) {
        cartes.erase(it, cartes.end());
        return true;
    }
    return false;
}

// Déplacer une carte vers une autre zone
bool ZoneDeCarte::deplacerCarte(int carteId, ZoneDeCarte& destination, int nouvelOrdre = -1) {
    // Trouver la carte dans cette zone
    for (const auto& paire : cartes) {
        if (paire.first->getId() == carteId) {
            Carte* carte = paire.first;
            int ordre = (nouvelOrdre == -1) ? paire.second : nouvelOrdre;
            
            // Retirer de cette zone
            if (retirerCarte(carteId)) {
                // Ajouter à la destination
                destination.ajouterCarte(carte, ordre);
                return true;
            }
        }
    }
    return false;
}
// Déplacer toutes les cartes vers une autre zone
void ZoneDeCarte::deplacerToutesLesCartes(ZoneDeCarte& destination) {
    for (const auto& paire : cartes) {
        destination.ajouterCarte(paire.first, paire.second);
    }
    cartes.clear();
}

// Vérifier si la zone est vide
bool ZoneDeCarte::estVide() const {
    return cartes.empty();
}
// Obtenir le nombre de cartes
size_t ZoneDeCarte::taille() const {
    return cartes.size();
}

// Mélanger les cartes de la zone et réassigner les indices
void ZoneDeCarte::melangerCartes() {
    if (cartes.empty()) return;
    
    // Créer un générateur de nombres aléatoires
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 generator(static_cast<unsigned int>(seed));
    
    // Mélanger le vecteur de cartes
    std::shuffle(cartes.begin(), cartes.end(), generator);
    
    // Réassigner les indices après mélange (0, 1, 2, ...)
    for (size_t i = 0; i < cartes.size(); ++i) {
        cartes[i].second = static_cast<int>(i);
    }
    #ifdef DEBUG
        std::cout << "Zone " << id << " mélangée (" << cartes.size() << " cartes)" << std::endl;
    #endif
}

// Trier les cartes par ordre (utile après mélange)
void ZoneDeCarte::trierParOrdre() {
    std::sort(cartes.begin(), cartes.end(), 
              [](const std::pair<Carte*, int>& a, const std::pair<Carte*, int>& b) {
                  return a.second < b.second;
              });
}
