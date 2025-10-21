#include "carte.h"
#include "zone_de_carte.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

// Constructeur
ZoneDeCarte::ZoneDeCarte(int id, TypeZone type, Joueur* proprietaire, TablePartie* table)
    : id(id), type(type), proprietaire(proprietaire), table(table) {
    std::cout << "Construction de la zone de carte" << std::endl;
}
ZoneDeCarte::~ZoneDeCarte() {
    cartes.clear();
    std::cout << "Destruction de la zone de carte" << std::endl;
}

// Méthodes pour accéder aux attributs
int ZoneDeCarte::getId() const { return id; }
TypeZone ZoneDeCarte::getType() const { return type; }
Joueur* ZoneDeCarte::getProprietaire() const { return proprietaire; }
TablePartie* ZoneDeCarte::getTable() const { return table; }
const std::vector<std::pair<Carte, int>>& ZoneDeCarte::getCartes() const { return cartes; }

// Ajouter une carte à la zone avec un ordre spécifique
void ZoneDeCarte::ajouterCarte(const Carte& carte, int ordre) {
    cartes.emplace_back(carte, ordre);
}

// Retirer une carte de la zone par son ID
bool ZoneDeCarte::retirerCarte(int carteId) {
    auto it = std::remove_if(cartes.begin(), cartes.end(),
                                [carteId](const std::pair<Carte, int>& p) {
                                    return p.first.getId() == carteId;
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
        if (paire.first.getId() == carteId) {
            Carte carte = paire.first;
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

// Trouver une carte par ID (sans la retirer)
const Carte* ZoneDeCarte::trouverCarte(int carteId) const {
    for (const auto& paire : cartes) {
        if (paire.first.getId() == carteId) {
            return &paire.first;
        }
    }
    return nullptr;
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
    
    std::cout << "Zone " << id << " mélangée (" << cartes.size() << " cartes)" << std::endl;
}

// Trier les cartes par ordre (utile après mélange)
void ZoneDeCarte::trierParOrdre() {
    std::sort(cartes.begin(), cartes.end(), 
              [](const std::pair<Carte, int>& a, const std::pair<Carte, int>& b) {
                  return a.second < b.second;
              });
}
