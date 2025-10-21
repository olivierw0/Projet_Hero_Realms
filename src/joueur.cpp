#include <vector>
#include <memory>
#include <iostream>
#include "carte.h"
#include "champion.h"
#include "zone_de_carte.h"
#include "joueur.h"

void Joueur::takeDamage(int amount){
    pv -= amount;
    if(pv<0){ 
        pv = 0; 
        isDead = true;    
    }
}

void Joueur::heal(int amount){
    pv += amount;
}

void Joueur::addOr(int amount){
    or_value += amount;
}

bool Joueur::spendOr(int amount){
    int new_or_value = or_value - amount;

    if (new_or_value < 0){ return false; } // Pas assez d'or

    or_value = new_or_value;
    return true;
}

void Joueur::addCombat(int amount){
    combat += amount;
}

void Joueur::resetCombat(){
    combat = 0;
}

void Joueur::resetOr(){
    or_value = 0;
}

void Joueur::ajouterZone(ZoneDeCarte&& zone){
    zones.push_back(zone);
}

ZoneDeCarte* Joueur::getZoneByType(TypeZone type){
    for(ZoneDeCarte& zone : zones){
        if(zone.getType() == type){
            return &zone;
        }
    }
    return nullptr;
}

ZoneDeCarte* Joueur::getZoneById(int zoneId){
    for(ZoneDeCarte& zone : zones){
        if(zone.getId() == zoneId){
            return &zone;
        }
    }
    return nullptr;
}

void Joueur::initZonesJoueur(){
    // Initialisation des zones de cartes du joueur
    ajouterZone(ZoneDeCarte(1, TypeZone::MAIN, this, nullptr));
    ajouterZone(ZoneDeCarte(2, TypeZone::DECK, this, nullptr));
    ajouterZone(ZoneDeCarte(3, TypeZone::DEFAUSSE, this, nullptr));
    ajouterZone(ZoneDeCarte(4, TypeZone::CHAMPIONS, this, nullptr));
}

// Afficher la main du joueur avec des indices
void Joueur::afficherMain() const {
    ZoneDeCarte* main = const_cast<Joueur*>(this)->getZoneByType(TypeZone::MAIN);
    if (!main) {
        std::cout << "Erreur: Main non trouvée!" << std::endl;
        return;
    }
    
    std::cout << "\n=== Main du Joueur " << id << " ===" << std::endl;
    const auto& cartes = main->getCartes();
    
    if (cartes.empty()) {
        std::cout << "Aucune carte en main." << std::endl;
        return;
    }
    
    for (size_t i = 0; i < cartes.size(); ++i) {
        std::cout << "[" << (i + 1) << "] " << cartes[i].first.getNom() 
                  << " (" << cartes[i].first.getDescription() << ")" << std::endl;
    }
}

// Jouer une carte par son indice (1-based)
bool Joueur::jouerCarte(int indice, Joueur& adversaire) {
    ZoneDeCarte* main = getZoneByType(TypeZone::MAIN);
    ZoneDeCarte* defausse = getZoneByType(TypeZone::DEFAUSSE);
    ZoneDeCarte* champions = getZoneByType(TypeZone::CHAMPIONS);

    if (!main || !defausse || !champions) {
        std::cout << "Erreur: Zones non trouvées!" << std::endl;
        return false;
    }
    
    const auto& cartes = main->getCartes();
    
    // Vérifier que l'indice est valide (conversion 1-based vers 0-based)
    if (indice < 1 || indice > static_cast<int>(cartes.size())) {
        std::cout << "Indice invalide! Choisissez entre 1 et " << cartes.size() << std::endl;
        return false;
    }
    
    // Récupérer la carte à jouer
    Carte carteAJouer = cartes[indice - 1].first;
    
    // Jouer la carte (activer ses effets)
    carteAJouer.jouerCarte(*this, adversaire);
    
    // Déplacer la carte de la main vers la défausse
    if (carteAJouer.getType() == TypeCarte::CHAMPION) {
        // Si c'est un champion, le déplacer vers la zone des champions
        main->deplacerCarte(carteAJouer.getId(), *champions);
    } else {
        // Sinon, le déplacer vers la défausse
        main->deplacerCarte(carteAJouer.getId(), *defausse);
    }
    
    return true;
}

// Obtenir le nombre de cartes en main
int Joueur::getNombreCartesEnMain() const {
    ZoneDeCarte* main = const_cast<Joueur*>(this)->getZoneByType(TypeZone::MAIN);
    if (!main) return 0;
    return static_cast<int>(main->getCartes().size());
}
