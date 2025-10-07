#include "zone_de_carte.h"
#include "carte.h"
#include <iostream>
#include <algorithm>
#include <random>

ZoneDeCarte::ZoneDeCarte(int id, const std::string& type, int owner_joueur_id, int owner_table_id)
    : id(id), type(type), owner_joueur_id(owner_joueur_id), owner_table_id(owner_table_id) {
}

void ZoneDeCarte::ajouterCarte(std::shared_ptr<Carte> carte, int ordre) {
    if (ordre == -1) {
        ordre = cartes.size();
    }
    cartes.push_back(std::make_pair(carte, ordre));
}

std::shared_ptr<Carte> ZoneDeCarte::retirerCarte(int index) {
    if (index < 0 || index >= static_cast<int>(cartes.size())) {
        return nullptr;
    }
    
    auto carte = cartes[index].first;
    cartes.erase(cartes.begin() + index);
    return carte;
}

std::shared_ptr<Carte> ZoneDeCarte::retirerCarteParId(int carte_id) {
    for (auto it = cartes.begin(); it != cartes.end(); ++it) {
        if (it->first->getId() == carte_id) {
            auto carte = it->first;
            cartes.erase(it);
            return carte;
        }
    }
    return nullptr;
}

void ZoneDeCarte::melangerCartes() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cartes.begin(), cartes.end(), g);
    
    // Réassigner les ordres après mélange
    for (size_t i = 0; i < cartes.size(); ++i) {
        cartes[i].second = i;
    }
}

std::shared_ptr<Carte> ZoneDeCarte::piocher() {
    if (cartes.empty()) {
        return nullptr;
    }
    
    auto carte = cartes[0].first;
    cartes.erase(cartes.begin());
    return carte;
}

void ZoneDeCarte::afficher() const {
    std::cout << "Zone " << type << " (ID: " << id << ")" << std::endl;
    std::cout << "Propriétaire - Joueur: " << owner_joueur_id << ", Table: " << owner_table_id << std::endl;
    std::cout << "Nombre de cartes: " << cartes.size() << std::endl;
    
    if (!cartes.empty()) {
        std::cout << "Cartes:" << std::endl;
        for (const auto& pair : cartes) {
            std::cout << "  [" << pair.second << "] " << pair.first->getNom() << std::endl;
        }
    }
    std::cout << std::endl;
}