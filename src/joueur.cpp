#include <vector>
#include <memory>
#include <iostream>
#include "carte.h"
#include "champion.h"
#include "zone_de_carte.h"
#include "joueur.h"
#include "carte_db.h"

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

void Joueur::creerZone(int id, TypeZone type, Joueur* proprietaire, TablePartie* table){
    zones.emplace_back(id, type, proprietaire ? proprietaire : this, table);
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
    // Réserver la capacité pour éviter les redimensionnements
    zones.reserve(4);
    
    // Initialisation des zones de cartes du joueur (construction directe dans le vector)
    creerZone(1, TypeZone::MAIN);
    creerZone(2, TypeZone::DECK);
    creerZone(3, TypeZone::DEFAUSSE);
    creerZone(4, TypeZone::CHAMPIONS);
}

void Joueur::initDeck(){
    ZoneDeCarte* deck = getZoneByType(TypeZone::DECK);
    std::cout << "Initialisation du deck du Joueur : " << id << std::endl;
    std::cout << "deck taille : " << (deck ? deck->taille() : 0) << std::endl;
    if (deck) {
        std::vector<Carte*> deckInitial = creerDeckDeBase();
        for (const auto& carte : deckInitial) {
            // Passer le pointeur directement (en supprimant const car nos zones gèrent des cartes modifiables)
            deck->ajouterCarte(const_cast<Carte*>(carte), static_cast<int>(deck->taille()));
        }
    }
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
        if (cartes[i].first != nullptr) {
            std::cout << "[" << (i + 1) << "] " << cartes[i].first->getNom() 
                      << " (" << cartes[i].first->getDescription() << ")" << std::endl;
        }
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
    Carte* carteAJouer = cartes[indice - 1].first;
    
    if (carteAJouer == nullptr) {
        std::cout << "Erreur: Carte invalide!" << std::endl;
        return false;
    }
    
    // Jouer la carte (activer ses effets)
    carteAJouer->jouerCarte(*this, adversaire);
    
    // Déplacer la carte de la main vers la défausse
    if (carteAJouer->getType() == TypeCarte::CHAMPION) {
        // Si c'est un champion, le déplacer vers la zone des champions
        main->deplacerCarte(carteAJouer->getId(), *champions, 1);
    } else {
        // Sinon, le déplacer vers la défausse
        main->deplacerCarte(carteAJouer->getId(), *defausse, 1);
    }
    
    return true;
}

// Obtenir le nombre de cartes en main
int Joueur::getNombreCartesEnMain() const {
    ZoneDeCarte* main = const_cast<Joueur*>(this)->getZoneByType(TypeZone::MAIN);
    if (!main) return 0;
    return static_cast<int>(main->getCartes().size());
}

// Jouer toutes les cartes en main
void Joueur::jouerToutesLesCartes(Joueur& adversaire) {
    for (int i = 0; i < getNombreCartesEnMain(); ++i) {
        jouerCarte(1, adversaire);
    }
}
// Mélanger le deck du joueur
void Joueur::melangerDeck() {
    ZoneDeCarte* deck = getZoneByType(TypeZone::DECK);
    if (deck && !deck->estVide()) {
        deck->melangerCartes();
        std::cout << "Joueur " << id << " a mélangé son deck." << std::endl;
    }
}

// Piocher des cartes du deck vers la main
void Joueur::piocher(int nbCartes) {
    ZoneDeCarte* deck = getZoneByType(TypeZone::DECK);
    ZoneDeCarte* main = getZoneByType(TypeZone::MAIN);
    ZoneDeCarte* defausse = getZoneByType(TypeZone::DEFAUSSE);
    
    if (!deck || !main) {
        std::cout << "Erreur: zones introuvables pour la pioche." << std::endl;
        return;
    }
    
    for (int i = 0; i < nbCartes; ++i) {
        // Si le deck est vide, mélanger la défausse dans le deck
        if (deck->estVide() && defausse && !defausse->estVide()) {
            std::cout << "Deck vide! Mélange de la défausse dans le deck..." << std::endl;
            defausse->deplacerToutesLesCartes(*deck);
            deck->melangerCartes();
        }
        
        // Piocher une carte si le deck n'est pas vide
        if (!deck->estVide()) {
            const auto& cartes = deck->getCartes();
            if (!cartes.empty() && cartes[0].first != nullptr) {
                int carteId = cartes[0].first->getId(); // Prendre la première carte
                deck->deplacerCarte(carteId, *main, static_cast<int>(main->taille()));
                std::cout << "Joueur " << id << " pioche une carte." << std::endl;
            }
        } else {
            std::cout << "Impossible de piocher: deck et défausse vides!" << std::endl;
            break;
        }
    }
}
