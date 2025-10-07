#include "joueur.h"
#include <iostream>
#include <algorithm>

Joueur::Joueur(int id, int pv) : id(id), pv(pv), or_value(0), combat(0) {
    // Initialiser les zones du joueur
    zones.push_back(std::make_shared<ZoneDeCarte>(id * 10 + 1, "deck", id));
    zones.push_back(std::make_shared<ZoneDeCarte>(id * 10 + 2, "main", id));
    zones.push_back(std::make_shared<ZoneDeCarte>(id * 10 + 3, "defausse", id));
    zones.push_back(std::make_shared<ZoneDeCarte>(id * 10 + 4, "champions", id));
}

void Joueur::ajouterOr(int quantite) {
    or_value += quantite;
    std::cout << "Joueur " << id << " gagne " << quantite << " or. Total: " << or_value << std::endl;
}

void Joueur::depenser(int quantite) {
    if (or_value >= quantite) {
        or_value -= quantite;
        std::cout << "Joueur " << id << " dépense " << quantite << " or. Restant: " << or_value << std::endl;
    } else {
        std::cout << "Pas assez d'or ! Disponible: " << or_value << ", requis: " << quantite << std::endl;
    }
}

void Joueur::ajouterCombat(int quantite) {
    combat += quantite;
    std::cout << "Joueur " << id << " gagne " << quantite << " combat. Total: " << combat << std::endl;
}

void Joueur::recevoirDegats(int degats) {
    pv = std::max(0, pv - degats);
    std::cout << "Joueur " << id << " reçoit " << degats << " dégâts. PV restants: " << pv << std::endl;
}

void Joueur::soigner(int soin) {
    pv += soin;
    std::cout << "Joueur " << id << " récupère " << soin << " PV. Total: " << pv << std::endl;
}

void Joueur::ajouterZone(std::shared_ptr<ZoneDeCarte> zone) {
    
}

std::shared_ptr<ZoneDeCarte> Joueur::getZone(const std::string& type) {
    
}

void Joueur::afficher() const {
}