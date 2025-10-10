#ifndef ZONE_DE_CARTE_H
#define ZONE_DE_CARTE_H

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class Carte;
class Joueur;
class TablePartie;

enum class TypeZone {
    DECK,
    MAIN,
    DEFAUSSE,
    CHAMPIONS,
    DECK_MARCHE,
    MARCHE,
};

class ZoneDeCarte {
private:
    int id;
    TypeZone type; // deck, main, defausse, champions, deck_marche, marche
    Joueur* proprietaire; // nullptr si zone commune
    TablePartie* table; // nullptr si zone joueur
    std::vector<std::pair<Carte, int>> cartes; // carte + ordre

public:

    // Constructeur
    ZoneDeCarte(int id, TypeZone type, Joueur* proprietaire = nullptr, TablePartie* table = nullptr)
        : id(id), type(type), proprietaire(proprietaire), table(table) {}

    // Méthodes pour accéder aux attributs
    int getId() const { return id; }
    TypeZone getType() const { return type; }
    Joueur* getProprietaire() const { return proprietaire; }
    TablePartie* getTable() const { return table; }
    const std::vector<std::pair<Carte, int>>& getCartes() const { return cartes; }

    // Ajouter une carte à la zone avec un ordre spécifique
    void ajouterCarte(const Carte& carte, int ordre) {
        cartes.emplace_back(carte, ordre);
    }

    // Retirer une carte de la zone par son ID
    bool retirerCarte(int carteId) {
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
    bool deplacerCarte(int carteId, ZoneDeCarte& destination, int nouvelOrdre = -1) {
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
    void deplacerToutesLesCartes(ZoneDeCarte& destination) {
        for (const auto& paire : cartes) {
            destination.ajouterCarte(paire.first, paire.second);
        }
        cartes.clear();
    }

    // Vérifier si la zone est vide
    bool estVide() const {
        return cartes.empty();
    }

    // Obtenir le nombre de cartes
    size_t taille() const {
        return cartes.size();
    }

    // Trouver une carte par ID (sans la retirer)
    const Carte* trouverCarte(int carteId) const {
        for (const auto& paire : cartes) {
            if (paire.first.getId() == carteId) {
                return &paire.first;
            }
        }
        return nullptr;
    }

};

#endif // ZONE_DE_CARTE_H