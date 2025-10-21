#include "carte.h"
#include "joueur.h"
#include <iostream>

// Méthode pour jouer la carte et activer ses effets
void Carte::jouerCarte(Joueur& joueurActif, Joueur& adversaire) const {
    std::cout << "Joueur " << joueurActif.getId() << " joue la carte '" << nom << "'" << std::endl;
    
    // Activer tous les effets de la carte
    for (const auto& effet : effets) {
        effet.activerEffet(joueurActif, adversaire);
    }
    
    std::cout << "La carte '" << nom << "' a été jouée et va dans la défausse." << std::endl;
    // Note: La carte sera effectivement déplacée vers la défausse par le système de jeu
}