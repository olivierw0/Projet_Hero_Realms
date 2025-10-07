#include "champion.h"
#include <iostream>
#include <algorithm>

Champion::Champion(int id, const std::string& nom, int cout, const std::string& faction,
                   const std::string& description, int pv, bool garde)
    : Carte(id, nom, cout, "champion", faction, description), pv(pv), active(false), garde(garde) {
}

void Champion::recevoirDegats(int degats) {
    pv = std::max(0, pv - degats);
    std::cout << getNom() << " reçoit " << degats << " dégâts. PV restants: " << pv << std::endl;
    
    if (pv <= 0) {
        desactiver();
        std::cout << getNom() << " est vaincu !" << std::endl;
    }
}

void Champion::activer() {
    active = true;
    std::cout << getNom() << " est maintenant actif !" << std::endl;
}

void Champion::desactiver() {
    active = false;
    std::cout << getNom() << " est maintenant inactif." << std::endl;
}

void Champion::afficher() const {
    Carte::afficher();
    std::cout << "PV: " << pv << std::endl;
    std::cout << "Actif: " << (active ? "Oui" : "Non") << std::endl;
    std::cout << "Garde: " << (garde ? "Oui" : "Non") << std::endl;
}