#include <iostream>
#include <memory>
#include "carte.h"
#include "effet.h"
#include "joueur.h"
#include "zone_de_carte.h"
#include "table_partie.h"
#include "utils.h"

int main() {
    // Créer une partie avec 16 gemmes de feu
    TablePartie partie(1, 16);
    
    bool finDePartie = false;
    
    // Initialiser complètement la partie
    partie.initPartie();
    
    do {
        // Afficher l'état de la partie et la main du joueur actuel
        partie.afficherEtatPartie();

        Joueur& joueurActuel = partie.getJoueurActuel();
        Joueur& adversaire = partie.getAdversaire();
        
        // Menu des commandes
        std::cout << "\n=== Tour du Joueur " << joueurActuel.getId() << " ===" << std::endl;
        std::cout << "Choisissez une action:" << std::endl;
        std::cout << "[1] Jouer une carte" << std::endl;
        std::cout << "[2] Jouer toutes les cartes de la main" << std::endl;
        std::cout << "[3] Acheter une carte du marché" << std::endl;
        std::cout << "[4] Activer un Champion" << std::endl;
        std::cout << "[5] Regarder sa défausse" << std::endl;
        std::cout << "[6] Regarder la défausse ennemie" << std::endl;
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
                if (joueurActuel.jouerCarte(choix)) {
                    std::cout << "Carte jouée avec succès!" << std::endl;
                }
                break;
            case 2: // jouer toutes les cartes de la main
                joueurActuel.jouerToutesLesCartes();
                std::cout << "Toutes les cartes de la main ont été jouées!" << std::endl;
                break;
            case 3: // acheter une carte du marché
                std::cout << "Entrez l'indice de la carte à acheter: ";
                std::cin >> choix;
                // Logique d'achat de carte
                if (partie.acheterCarteMarche(choix, joueurActuel)) {
                    std::cout << "Carte achetée avec succès!" << std::endl;
                }
                break;
            case 4: // Activer un Champion
                // std::cout << "Entrez l'indice du champion à activer: ";
                // std::cin >> choix;
                // if (joueurActuel.activerChampion(choix)) {
                //     std::cout << "Champion activé avec succès!" << std::endl;
                // }
                break;
            case 5: // regarder sa défausse
                // joueurActuel.regarderDefausse();
                break;
            case 6: // regarder la défausse ennemie
                // adversaire.regarderDefausse();
                break;
            case 777: // passer en god mode
                if (joueurActuel.isGodMode()) {
                    joueurActuel.desactiverGodMode();
                } else {
                    joueurActuel.activerGodMode();
                    
                    // Menu God Mode
                    bool continuerGodMode = true;
                    while (continuerGodMode) {
                        #ifndef DEBUG
                            clearTerminal();
                        #endif
                        std::cout << "\n=======<< MENU GOD MODE >>=======" << std::endl;
                        std::cout << "[1] Afficher le deck du marché" << std::endl;
                        std::cout << "[2] Mettre tous les joueurs à 1 PV" << std::endl;
                        std::cout << "[3] Pioche une carte spécifique (par ID)" << std::endl;
                        std::cout << "[0] Retour au jeu" << std::endl;
                        std::cout << "Choix: ";
                        
                        int godChoix;
                        std::cin >> godChoix;
                        
                        switch (godChoix) {
                            case 0:
                                continuerGodMode = false;
                                break;
                            case 1:
                                partie.afficherDeckMarche();
                                break;
                            case 2: 
                                joueurActuel.setPv(1);
                                adversaire.setPv(1);
                                std::cout << "❤️ Tous les joueurs mis à 1 PV!" << std::endl;
                                break;
                            case 3:
                                partie.afficherDeckMarche();
                                std::cout << "Entrez l'ID de la carte à acheter: ";
                                int idCarte;
                                std::cin >> idCarte;
                                partie.piocheCarteSpecifique(idCarte, joueurActuel);
                                break;
                            default:
                                std::cout << "Choix invalide!" << std::endl;
                                break;
                        }
                    }
                }
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