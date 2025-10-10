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

    do {
        // Afficher l'état initial de la partie
        partie.afficherEtatPartie();
        
        std::cout << "\n=== Attendre une commande du joueur " << partie.getJoueurActuel().getId() << " ===" << std::endl;
        std::cin.get();
        // TODO: Gérer les commandes du joueur

        // Changer de joueur
        partie.endTurn();
    } while (!finDePartie);

    return 0;
}