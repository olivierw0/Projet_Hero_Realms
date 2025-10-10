#include "carte.h"
#include "zone_de_carte.h"
#include <iostream>
#include <vector>
#include <algorithm>

// Constructeur
ZoneDeCarte::ZoneDeCarte(int id, TypeZone type, Joueur* proprietaire = nullptr, TablePartie* table = nullptr)
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
