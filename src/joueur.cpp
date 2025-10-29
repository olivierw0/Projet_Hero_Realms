#include <vector>
#include <memory>
#include <iostream>
#include "carte.h"
#include "champion.h"
#include "zone_de_carte.h"
#include "table_partie.h"
#include "joueur.h"
#include "effet.h"
#include "carte_db.h"

void Joueur::takeDamage(int amount){
    pv -= amount;
    if(pv<0){ 
        pv = 0; 
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

const ZoneDeCarte* Joueur::getZoneByType(TypeZone type) const {
    for(const ZoneDeCarte& zone : zones){
        if(zone.getType() == type){
            return &zone;
        }
    }
    return nullptr;
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
        for (auto carte : deckInitial) {
            deck->ajouterCarte(carte, static_cast<int>(deck->taille()));
        }
    }
}

// Codes couleurs ANSI
#define RESET_COLOR   "\033[0m"
#define BOLD_TEXT     "\033[1m"
#define DIM_TEXT      "\033[2m"

void Joueur::afficherMain() const {
    const ZoneDeCarte* main = getZoneByType(TypeZone::MAIN);
    if (!main) {
        std::cout << "Main introuvable!" << std::endl;
        return;
    }
    
    const auto& cartes = main->getCartes();
    if (cartes.empty()) {
        std::cout << DIM_TEXT << "  (main vide)" << RESET_COLOR << std::endl;
        return;
    }
    
    int indice = 1;
    for (const auto& paire_carte : cartes) {
        if (paire_carte.first != nullptr) {
            std::cout << BOLD_TEXT << "[" << indice << "] " << RESET_COLOR 
                      << paire_carte.first->getNom() << std::endl;
            indice++;
        }
    }
}

//afficher champions pour les choix d'effet
void Joueur::afficherChampions() const {
    const ZoneDeCarte* champions = getZoneByType(TypeZone::CHAMPIONS);
    if (!champions) {
        std::cout << "Zone champions introuvable!" << std::endl;
        return;
    }
    
    const auto& cartes = champions->getCartes();
    if (cartes.empty()) {
        std::cout << DIM_TEXT << "  (aucun champion)" << RESET_COLOR << std::endl;
        return;
    }
    
    int indice = 1;
    for (const auto& paire_carte : cartes) {
        if (paire_carte.first != nullptr) {
            const Champion* champion = dynamic_cast<const Champion*>(paire_carte.first);
            std::cout << BOLD_TEXT << "[" << indice << "] " << RESET_COLOR 
                      << paire_carte.first->getNom();
            if (champion) {
                std::cout << " [" << champion->getPV() << " PV]";
                if (champion->hasGarde()) {
                    std::cout << " 🛡️";
                }
            }
            std::cout << std::endl;
            indice++;
        }
    }
}

// Obtenir le nombre de cartes en main
int Joueur::getNombreCartesEnMain() const {
    ZoneDeCarte* main = const_cast<Joueur*>(this)->getZoneByType(TypeZone::MAIN);
    if (!main) return 0;
    return static_cast<int>(main->getCartes().size());
}

// Jouer toutes les cartes en main
void Joueur::jouerToutesLesCartes() {
    int nbCartes = getNombreCartesEnMain();
    for (int i = 0; i < nbCartes; ++i) {
        jouerCarte(1);
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

// Jouer une carte par son indice (1-based)
bool Joueur::jouerCarte(int indice) {
    ZoneDeCarte* main = getZoneByType(TypeZone::MAIN);
    if (!main) {
        std::cout << "Main introuvable!" << std::endl;
        return false;
    }

    const auto& cartes = main->getCartes();
    if (indice < 1 || indice > static_cast<int>(cartes.size())) {
        std::cout << "Indice invalide!" << std::endl;
        return false;
    }

    Carte* carte = cartes[indice - 1].first;
    if (!carte) {
        std::cout << "Carte invalide!" << std::endl;
        return false;
    }

    std::cout << "Joue la carte: " << carte->getNom() << std::endl;

    // Déterminer si c'est un champion
    Champion* champion = dynamic_cast<Champion*>(carte);
    bool estChampion = (champion != nullptr);

    // Si c'est un CHAMPION : le poser en jeu SANS activer ses effets
    if (estChampion) {
        ZoneDeCarte* champions = getZoneByType(TypeZone::CHAMPIONS);
        if (!champions) {
            std::cout << "Zone champions introuvable!" << std::endl;
            return false;
        }
        
        main->deplacerCarte(carte->getId(), *champions, champions->taille());
        std::cout << "→ Champion posé en jeu (pas d'effet à l'entrée)" << std::endl;
        champion->setActive(true);
    } 
    // Si c'est une ACTION ou un OBJET
    else {
        // Vérifier si la carte a un effet de sacrifice
        bool aEffetSacrifice = false;
        for (const auto& effet : carte->getEffets()) {
            if (effet.getCondition() == ConditionEffet::SACRIFICE ||
                effet.getCondition() == ConditionEffet::SACRIFICE_TO_MARCHE) {
                aEffetSacrifice = true;
                break;
            }
        }

        bool sacrifier = false;
        
        // Si la carte a un effet de sacrifice, demander au joueur
        if (aEffetSacrifice) {
            std::cout << carte->getNom() << " a un effet de SACRIFICE." << std::endl;
            std::cout << "Voulez-vous SACRIFIER cette carte ? (o/n): ";
            char reponse;
            std::cin >> reponse;
            sacrifier = (reponse == 'o' || reponse == 'O');
        }

        // Activer les effets appropriés
        std::cout << "→ Activation des effets..." << std::endl;
        
        for (const auto& effet : carte->getEffets()) {
            // Si on a choisi de sacrifier, n'activer QUE les effets de sacrifice
            if (sacrifier) {
                if (effet.getCondition() == ConditionEffet::SACRIFICE ||
                    effet.getCondition() == ConditionEffet::SACRIFICE_TO_MARCHE) {
                    effet.activerEffet(*this, table->getAdversaire(), carte);
                }
            }
            // Sinon, activer les effets normaux (sauf sacrifice)
            else {
                if (effet.getCondition() != ConditionEffet::SACRIFICE &&
                    effet.getCondition() != ConditionEffet::SACRIFICE_TO_MARCHE) {
                    // Vérifier autres conditions (allié, etc.)
                    if (table && effet.verifierConditions(*this, table->getAdversaire())) {
                        effet.activerEffet(*this, table->getAdversaire(), carte);
                    }
                }
            }
        }

        // Déplacer la carte vers la destination appropriée
        if (sacrifier) {
            // Vérifier si c'est une Fire Gem (SACRIFICE_TO_MARCHE)
            bool estFireGem = false;
            for (const auto& effet : carte->getEffets()) {
                if (effet.getCondition() == ConditionEffet::SACRIFICE_TO_MARCHE) {
                    estFireGem = true;
                    break;
                }
            }

            if (estFireGem) {
                // Retourner dans la pile de gemmes de feu
                ZoneDeCarte* gemmesFeu = table->getGemmesFeu();
                if (gemmesFeu) {
                    main->deplacerCarte(carte->getId(), *gemmesFeu, gemmesFeu->taille());
                    std::cout << "→ Fire Gem retourne dans la pile" << std::endl;
                }
            } else {
                // Écarter la carte du jeu
                ZoneDeCarte* ecartees = table->getCartesEcartees();
                if (ecartees) {
                    main->deplacerCarte(carte->getId(), *ecartees, ecartees->taille());
                    std::cout << "→ Carte ÉCARTÉE du jeu définitivement" << std::endl;
                }
            }
        } else {
            // Défausser normalement
            ZoneDeCarte* defausse = getZoneByType(TypeZone::DEFAUSSE);
            if (defausse) {
                main->deplacerCarte(carte->getId(), *defausse, defausse->taille());
                std::cout << "→ Carte défaussée" << std::endl;
            }
        }
    }

    return true;
}

void Joueur::resetChampions(){
    ZoneDeCarte* champions = getZoneByType(TypeZone::CHAMPIONS);
    ZoneDeCarte* defausse = getZoneByType(TypeZone::DEFAUSSE);
    if (!champions) {
        std::cout << "Zone champions introuvable!" << std::endl;
        return;
    }
    const auto& cartes = champions->getCartes();
    
    for (const auto& paire_carte : cartes) {
        Champion* champion = dynamic_cast<Champion*>(paire_carte.first);
        if (champion && champion->getPv() > 0) {
            std::cout << "Réactivation du champion " << champion->getNom() << std::endl;
            champion->setActive(true);
        }
        if (champion && champion->getPv() <= 0) {
            std::cout << "Champion " << champion->getNom() << " est mort, va à la défausse" << std::endl;
            deplacerCarte(champion->getId(), *defausse, defausse->taille());
        }
    }
}

void degatsFinTour(int totalCombat){
    ZoneDeCarte* champions = getZoneByType(TypeZone::CHAMPIONS);
    if (!champions) {
        std::cout << "Zone champions introuvable!" << std::endl;
        return;
    }
    // CAS 1 : Aucun champion en jeu
    auto& cartes = champions->getCartes();
    if (cartes.empty()) {
        std::cout << "Aucun champion en jeu." << std::endl;
        std::cout << "Tous les dégâts sont infligés au joueur." << std::endl;
        takeDamage(totalCombat);
        return;
    }
    
    // CAS 2 : Il y a des champions en jeu
    // Infliger les dégâts aux champions avec Garde en priorité
    // Filtrer les champions avec Garde
    std::vector<Champion*> gardes;
    for (const auto& paire_carte : cartes) {
        Champion* champion = dynamic_cast<Champion*>(paire_carte.first);
        if (champion && champion->hasGarde() && champion->getPv() > 0) {
            gardes.push_back(champion);
        }
    }

    if (!gardes.empty()) {
        std::cout << "\n Il y a " << gardes.size() << " champion(s) avec GARDE!" << std::endl;
        std::cout << "Les dégâts doivent être infligés aux gardes en priorité." << std::endl;
        
        while (totalCombat > 0 && !gardes.empty()) {
            // Afficher les gardes disponibles
            std::cout << "\nGardes disponibles:" << std::endl;
            for (size_t i = 0; i < gardes.size(); ++i) {
                if (gardes[i]->getPv() > 0) {
                    std::cout << "[" << (i + 1) << "] " << gardes[i]->getNom() 
                              << " (" << gardes[i]->getPv() << " PV) 🛡️" << std::endl;
                }
            }
            
            int choix;
            std::cout << "Infligez " << totalCombat << " dégât(s) au garde n°: ";
            std::cin >> choix;
            
            if (choix < 1 || choix > static_cast<int>(gardes.size())) {
                std::cout << "Choix invalide!" << std::endl;
                continue;
            }
            
            Champion* garde = gardes[choix - 1];
            int pvAvant = garde->getPv();
            int degatsInfliges = std::min(totalCombat, pvAvant);
            
            garde->takeDamage(totalCombat);
            totalCombat -= degatsInfliges;
            
            std::cout << "→ " << degatsInfliges << " dégât(s) infligé(s) à " << garde->getNom();
            
            if (garde->getPv() <= 0) {
                std::cout << " (DÉTRUIT! )" << std::endl;
                // Retirer le garde de la liste
                gardes.erase(gardes.begin() + (choix - 1));
            } else {
                std::cout << " (reste " << garde->getPv() << " PV)" << std::endl;
            }
            
            if (totalCombat > 0) {
                std::cout << "\nIl reste " << totalCombat << " dégât(s) à placer..." << std::endl;
            }
        }
        // Si tous les gardes sont morts et qu'il reste des dégâts
        if (totalCombat > 0 && gardes.empty()) {
            std::cout << "\nTous les gardes sont détruits!" << std::endl;
            std::cout << "Il reste " << totalCombat << " dégât(s) à placer." << std::endl;
            // Continuer vers le cas sans garde
        } else {
            return; // Tous les dégâts ont été placés
        }
    }
    while (totalCombat > 0){
        std::vector<Champion*> championsEnVie;
        for (const auto& paire_carte : cartes) {
            Champion* champion = dynamic_cast<Champion*>(paire_carte.first);
            if (champion && champion->getPv() > 0) {
                championsEnVie.push_back(champion);
            }
        }
        if (championsEnVie.empty()) {
            std::cout << "Aucun champion en vie. Tous les dégâts restants (" << totalCombat << ") sont infligés au joueur." << std::endl;
            takeDamage(totalCombat);
            break;
        }

        std::cout << "\nChampions disponibles:" << std::endl;
        for (size_t i = 0; i < championsEnVie.size(); ++i) {
            std::cout << "[" << (i + 1) << "] " << championsEnVie[i]->getNom() 
                      << " (" << championsEnVie[i]->getPv() << " PV)" << std::endl;
        }

        int choix;
        std::cout << "Infligez " << totalCombat << " dégât(s) au champion n°: ";
        std::cin >> choix;
        if (choix == 0){ 
            std::cout << "Tous les dégâts restants (" << totalCombat << ") sont infligés au joueur." << std::endl;
            takeDamage(totalCombat);
            break;
        }else if (choix >= 1 && choix < static_cast<int>(championsEnVie.size())) {
            Champion* cible = championsEnVie[choix - 1];
            int pvChamp = cible->getPv();
            if (totalCombat > pvChamp) {
                cible->setPV(0);
            }
            // Les champions n'ont pas de méthode takeDamage, donc on utilise setPV directement
            // De toutes manières ils se soignent à chaque début de tour
            totalCombat -= pvChamp;
            std::cout << "→ " << pvChamp << " dégât(s) infligé(s) à " << cible->getNom();
            if (cible->getPv() <= 0) {
                std::cout << " (DÉTRUIT!)" << std::endl;
            }
        }else{
            std::cout << "Choix invalide!" << std::endl;
        }
    }
}