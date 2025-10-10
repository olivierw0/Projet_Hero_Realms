// Exemple simple d'utilisation des zones de cartes
#include "carte.h"
#include "effet.h"
#include "zone_de_carte.h"
#include <iostream>

int main() {
    // Créer quelques cartes d'exemple
    std::vector<Effet> effets_vides;
    Carte garde(1, "Garde Impérial", 3, TypeCarte::CHAMPION, FactionCarte::JAUNE, "Champion 4 PV", effets_vides);
    Carte or_carte(2, "Or", 0, TypeCarte::ACTION, FactionCarte::NEUTRE, "Gagnez 1 or", effets_vides);
    Carte dague(3, "Dague", 0, TypeCarte::OBJET, FactionCarte::NEUTRE, "1 dégât", effets_vides);

    // Créer les zones d'un joueur
    ZoneDeCarte main(1, TypeZone::MAIN);
    ZoneDeCarte champions(2, TypeZone::CHAMPIONS);
    ZoneDeCarte defausse(3, TypeZone::DEFAUSSE);
    ZoneDeCarte deck(4, TypeZone::DECK);

    // === CAS 1: Jouer un champion de la main vers la zone champions ===
    std::cout << "=== Cas 1: Jouer un champion ===" << std::endl;
    
    // Le champion est d'abord en main
    main.ajouterCarte(garde, 1);
    std::cout << "Champion en main: " << main.taille() << " cartes" << std::endl;
    std::cout << "Zone champions: " << champions.taille() << " cartes" << std::endl;

    // Déplacer le champion de la main vers la zone champions
    if (main.deplacerCarte(1, champions)) {
        std::cout << "Champion déplacé avec succès !" << std::endl;
        std::cout << "Main: " << main.taille() << " cartes" << std::endl;
        std::cout << "Zone champions: " << champions.taille() << " cartes" << std::endl;
    }

    // === CAS 2: Champion éliminé vers défausse ===
    std::cout << "\n=== Cas 2: Champion éliminé ===" << std::endl;
    
    std::cout << "Champions avant élimination: " << champions.taille() << std::endl;
    std::cout << "Défausse avant: " << defausse.taille() << std::endl;

    // Déplacer le champion de la zone champions vers la défausse
    if (champions.deplacerCarte(1, defausse)) {
        std::cout << "Champion éliminé et envoyé en défausse !" << std::endl;
        std::cout << "Champions après: " << champions.taille() << std::endl;
        std::cout << "Défausse après: " << defausse.taille() << std::endl;
    }

    // === CAS 3: Mélanger défausse dans deck quand deck vide ===
    std::cout << "\n=== Cas 3: Deck vide, mélanger défausse ===" << std::endl;
    
    // Ajouter quelques cartes en défausse
    defausse.ajouterCarte(or_carte, 1);
    defausse.ajouterCarte(dague, 2);
    
    std::cout << "Deck: " << deck.taille() << " cartes" << std::endl;
    std::cout << "Défausse: " << defausse.taille() << " cartes" << std::endl;

    // Si le deck est vide, déplacer toute la défausse
    if (deck.estVide() && !defausse.estVide()) {
        std::cout << "Deck vide ! Mélange de la défausse..." << std::endl;
        defausse.deplacerToutesLesCartes(deck);
        std::cout << "Deck après mélange: " << deck.taille() << " cartes" << std::endl;
        std::cout << "Défausse après mélange: " << defausse.taille() << " cartes" << std::endl;
    }

    return 0;
}

// Fonction utilitaire pour jouer une carte action/objet
bool jouerCarte(int carteId, ZoneDeCarte& main, ZoneDeCarte& defausse) {
    const Carte* carte = main.trouverCarte(carteId);
    if (carte && (carte->getType() == TypeCarte::ACTION || carte->getType() == TypeCarte::OBJET)) {
        std::cout << "Joue la carte: " << carte->getNom() << std::endl;
        // Appliquer les effets de la carte ici...
        
        // Déplacer vers défausse
        return main.deplacerCarte(carteId, defausse);
    }
    return false;
}

// Fonction utilitaire pour jouer un champion
bool jouerChampion(int carteId, ZoneDeCarte& main, ZoneDeCarte& champions) {
    const Carte* carte = main.trouverCarte(carteId);
    if (carte && carte->getType() == TypeCarte::CHAMPION) {
        std::cout << "Joue le champion: " << carte->getNom() << std::endl;
        
        // Déplacer vers zone champions
        return main.deplacerCarte(carteId, champions);
    }
    return false;
}