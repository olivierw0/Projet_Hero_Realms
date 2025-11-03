#include <iostream>
#include <memory>
#include <limits>
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
        std::cout << "[0] Finir le tour" << std::endl;
        std::cout << "[-1] Quitter le jeu" << std::endl;
        if (!joueurActuel.isGodMode()) {
            std::cout << "[777] Passer en mode Dieu" << std::endl; // à cacher ou protéger dans la version finale
        } else if (joueurActuel.isGodMode()) {
            std::cout << "\n=======<< MENU GOD MODE >>=======" << std::endl;
            std::cout << "[10] Afficher le deck du marché" << std::endl;
            std::cout << "[20] Mettre tous les joueurs à 1 PV" << std::endl;
            std::cout << "[30] Pioche une carte spécifique (par ID)" << std::endl;
            std::cout << "[777] Quitter le mode Dieu" << std::endl;
            std::cout << "=======<<               >>=======\n" << std::endl;
        }
        std::cout << "Votre choix: " << std::endl;
        
        std::string string;
        std::cin >> string;
        int choix = -2;
        try
        {
            choix = std::stoi(string);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            choix = -2;
        }
        
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
                std::cin >> string;
                try {
                    choix = std::stoi(string);
                    std::cout << choix << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Choix invalide! Essayez à nouveau." << std::endl;
                    choix = -2;
                }
                if (joueurActuel.jouerCarte(choix)) {
                    std::cout << "Carte jouée avec succès!" << std::endl;
                }
                break;
            case 2: // jouer toutes les cartes de la main
                joueurActuel.jouerToutesLesCartes();
                std::cout << "\nToutes les cartes de la main ont été jouées!" << std::endl;
                break;
            case 3: // acheter une carte du marché
                std::cout << "Entrez l'indice de la carte à acheter: ";
                std::cin >> string;
                try {
                    choix = std::stoi(string);
                } catch (const std::exception& e) {
                    std::cerr << "Choix invalide! Essayez à nouveau." << std::endl;
                    choix = -2;
                }
                // Logique d'achat de carte
                if (partie.acheterCarteMarche(choix, joueurActuel)) {
                    std::cout << "Carte achetée avec succès!" << std::endl;
                }
                break;
            case 4: // Activer un Champion
                std::cout << "Entrez l'indice du champion à activer: ";
                std::cin >> string;
                try {
                    choix = std::stoi(string);
                } catch (const std::exception& e) {
                    std::cerr << "Choix invalide! Essayez à nouveau." << std::endl;
                    choix = -2;
                }
                if (joueurActuel.tapChampion(choix, adversaire)) {
                    std::cout << "Champion activé avec succès!" << std::endl;
                }
                break;
            case 5: // regarder sa défausse
                joueurActuel.regarderDefausse();
                break;
            case 6: // regarder la défausse ennemie
                adversaire.regarderDefausse();
                break;
            case 10:
                if (joueurActuel.isGodMode()) {
                    partie.afficherDeckMarche();
                }else {
                    std::cerr << "Choix invalide! Essayez à nouveau." << std::endl;
                }
                break;
            case 20: 
                if (joueurActuel.isGodMode()) {
                    joueurActuel.setPv(1);
                    adversaire.setPv(1);
                    std::cout << "❤️ Tous les joueurs mis à 1 PV!" << std::endl;
                }else {
                    std::cerr << "Choix invalide! Essayez à nouveau." << std::endl;
                }
                break;
            case 30:
                if (joueurActuel.isGodMode()) {
                    partie.afficherDeckMarche();
                    int idCarte = -1;
                    while (idCarte != 0){
                        std::cout << "Entrez l'ID de la carte à acheter (0 pour quitter) : ";
                        std::cin >> string;
                        try {
                            idCarte = std::stoi(string);
                        } catch (const std::exception& e) {
                            std::cerr << "Choix invalide! Essayez à nouveau." << std::endl;
                            idCarte = -1;
                        }
                        partie.piocheCarteSpecifique(idCarte, joueurActuel);
                    }
                }else {
                    std::cerr << "Choix invalide! Essayez à nouveau." << std::endl;
                }
                break;
            case 777: // passer en god mode
                if (!joueurActuel.isGodMode()) {
                    std::cout << "Veuillez entrer le mot de passe : ";
                    std::string password;
                    std::cin >> password;
                    if (password == "godmode123") {
                        std::cout << "Accès au mode Dieu accordé!" << std::endl;
                        joueurActuel.activerGodMode();
                    } else {
                        std::cout << "Mot de passe incorrect!" << std::endl;
                        break;
                    }
                }else{
                    joueurActuel.desactiverGodMode();
                }

                break;
            default:
                std::cerr << "Choix invalide! Essayez à nouveau." << std::endl;
                break;
            }
    
        // Vérifier la condition de fin de partie (joueur mort)
        if (adversaire.getPv() <= 0) {
            std::cout << "\n🎉 Joueur " << joueurActuel.getId() << " gagne! 🎉" << std::endl;
            finDePartie = true;
        }
        std::cout << "\nEntrée pour continuer..." << std::endl;
        std::cin.ignore();
        std::cin.get();
        
    } while (!finDePartie);

    return 0;
}