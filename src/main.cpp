#include <iostream>
#include <memory>
#include "carte.h"
#include "effet.h"
#include "joueur.h"
#include "zone_de_carte.h"
#include "table_partie.h"

int main() {
    // Créer une partie avec 16 gemmes de feu
    TablePartie partie(1, 16);
    
    // Créer deux joueurs
    Joueur joueur1(1, 50);  // Joueur 1 avec 50 PV
    Joueur joueur2(2, 50);  // Joueur 2 avec 50 PV
    
    // Ajouter les joueurs à la partie
    partie.ajouterJoueur(joueur1);
    partie.ajouterJoueur(joueur2);

    bool finDePartie = false;

    // Initialiser complètement la partie
    partie.initPartie();
    
    do {
        // Afficher l'état de la partie et la main du joueur actuel
        partie.afficherEtatPartie();
        
        Joueur& joueurActuel = partie.getJoueurActuel();
        Joueur& adversaire = partie.getAdversaire();
        
        // Afficher la main du joueur
        joueurActuel.afficherMain();
        
        // Menu des commandes
        std::cout << "\n=== Tour du Joueur " << joueurActuel.getId() << " ===" << std::endl;
        std::cout << "Choisissez une action:" << std::endl;
        std::cout << "1-" << joueurActuel.getNombreCartesEnMain() << ": Jouer une carte" << std::endl;
        std::cout << "0: Finir le tour" << std::endl;
        std::cout << "-1: Quitter le jeu" << std::endl;
        std::cout << "Votre choix: ";
        
        int choix;
        std::cin >> choix;
        
        if (choix == -1) {
            std::cout << "Fin du jeu." << std::endl;
            finDePartie = true;
        }
        else if (choix == 0) {
            std::cout << "Fin du tour du joueur " << joueurActuel.getId() << std::endl;
            partie.endTurn();
        }
        else if (choix >= 1 && choix <= joueurActuel.getNombreCartesEnMain()) {
            // Jouer la carte choisie
            if (joueurActuel.jouerCarte(choix, adversaire)) {
                std::cout << "Carte jouée avec succès!" << std::endl;
            }
            // Ne pas changer de tour automatiquement, laisser le joueur jouer d'autres cartes
        }
        else {
            std::cout << "Choix invalide! Essayez à nouveau." << std::endl;
        }
        
        // Vérifier la condition de fin de partie (joueur mort)
        if (adversaire.getPv() <= 0) {
            std::cout << "\n🎉 Joueur " << joueurActuel.getId() << " gagne! 🎉" << std::endl;
            finDePartie = true;
        }
        
    } while (!finDePartie);

    return 0;
}