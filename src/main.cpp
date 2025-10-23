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
        #ifndef DEBUG 
            partie.afficherEtatPartie();
        #endif

        Joueur& joueurActuel = partie.getJoueurActuel();
        Joueur& adversaire = partie.getAdversaire();
        
        // Afficher la main du joueur
        joueurActuel.afficherMain();
        
        // Menu des commandes
        std::cout << "\n=== Tour du Joueur " << joueurActuel.getId() << " ===" << std::endl;
        std::cout << "Choisissez une action:" << std::endl;
        std::cout << "[1] Jouer une carte" << std::endl;
        std::cout << "[2] Jouer toutes les cartes de la main" << std::endl;
        std::cout << "[3] Acheter une carte du marché" << std::endl;
        std::cout << "[4] Activer un Champion" << std::endl;
        std::cout << "[5] Sacrifier une carte" << std::endl;
        std::cout << "[6] Regarder sa défausse" << std::endl;
        std::cout << "[7] Regarder la défausse ennemie" << std::endl;
        std::cout << "[777] Passer en mode Dieu" << std::endl; // à cacher ou protéger dans la version finale
        std::cout << "[0] Finir le tour" << std::endl;
        std::cout << "[-1] Quitter le jeu" << std::endl;
        std::cout << "Votre choix: ";
        
        int choix;
        std::cin >> choix;
        
        switch (choix) {
            case -1: // quitter le jeu
                std::cout << "Fin du jeu." << std::endl;
                finDePartie = true;
                break;
            case 0: // fin de tour
                std::cout << "Fin du tour du joueur " << joueurActuel.getId() << std::endl;
                partie.endTurn();
                break;
            case 1: // choisir de jouer une carte
                std::cout << "Entrez l'indice de la carte à jouer: ";
                std::cin >> choix;
                if (joueurActuel.jouerCarte(choix, adversaire)) {
                    std::cout << "Carte jouée avec succès!" << std::endl;
                }
                break;
            case 2: // jouer toutes les cartes de la main
                break;
            case 3: // acheter une carte du marché 
                break;
            case 4: // Activer un Champion
                break;
            case 5: // sacrifier une carte (-- Sacrifice_TO_MARCHE aussi)
                break;
            case 6: // regarder sa défausse
                break;
            case 7: // regarder la défausse ennemie
                break;
            case 777: // passer en god mode
                // joueurActuel.activerGodMode(); //TODO: implémenter
                break;
            default:
                std::cout << "Choix invalide! Essayez à nouveau." << std::endl;
                break;
        }        
        
        // Vérifier la condition de fin de partie (joueur mort)
        if (adversaire.getPv() <= 0) {
            std::cout << "\n🎉 Joueur " << joueurActuel.getId() << " gagne! 🎉" << std::endl;
            finDePartie = true;
        }
        
    } while (!finDePartie);

    return 0;
}