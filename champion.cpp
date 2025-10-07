#include "champion.h"
#include <iostream>
#include <algorithm>

Champion::Champion(int id, const std::string& nom, int cout, FactionCarte faction,
                   const std::string& description, int pv, bool garde)
    : Carte(id, nom, cout, TypeCarte::CHAMPION, faction, description), pv(pv), active(false), garde(garde) {
}

void Champion::recevoirDegats(int degats) {

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
}

void Champion::detruire() {
    std::cout << getNom() << " a été détruit !" << std::endl;
}
    // Logique de destruction (retirer des zones, libérer ressources, etc.)