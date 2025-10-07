#include <iostream>
#include <memory>
#include "carte.h"
#include "champion.h"
#include "effet.h"
#include "joueur.h"
#include "zone_de_carte.h"
#include "table_partie.h"

int main() {
    std::cout << "=== Hero Realms - Test du Système ===" << std::endl << std::endl;
    
    // Créer une table de partie
    auto table = std::make_shared<TablePartie>(1, 50);
    
    // Créer des joueurs
    auto joueur1 = std::make_shared<Joueur>(1, 50);
    auto joueur2 = std::make_shared<Joueur>(2, 50);
    
    // Ajouter les joueurs à la table
    table->ajouterJoueur(joueur1);
    table->ajouterJoueur(joueur2);
    
    // Créer quelques effets
    auto effet_or = std::make_shared<Effet>(1, "or", 2);
    auto effet_combat = std::make_shared<Effet>(2, "dmg", 3);
    auto effet_soin = std::make_shared<Effet>(3, "soin", 2, "faction", "Imperial");
    
    // Créer des cartes
    auto carte_action = std::make_shared<Carte>(1, "Pièce d'or", 0, "action", "Neutre", "Donne de l'or");
    carte_action->ajouterEffet(effet_or);
    
    auto carte_objet = std::make_shared<Carte>(2, "Épée", 3, "objet", "Guerrier", "Une arme tranchante");
    carte_objet->ajouterEffet(effet_combat);
    
    // Créer un champion
    auto champion = std::make_shared<Champion>(3, "Garde Imperial", 4, "Imperial", "Un défenseur loyal", 5, true);
    champion->ajouterEffet(effet_soin);
    
    std::cout << "=== Test des cartes ===" << std::endl;
    carte_action->afficher();
    carte_objet->afficher();
    champion->afficher();
    
    // Test des zones
    std::cout << "=== Test des zones ===" << std::endl;
    auto zone_main = joueur1->getZone("main");
    zone_main->ajouterCarte(carte_action);
    zone_main->ajouterCarte(carte_objet);
    zone_main->afficher();
    
    auto zone_champions = joueur1->getZone("champions");
    zone_champions->ajouterCarte(champion);
    champion->activer();
    zone_champions->afficher();
    
    // Test des joueurs
    std::cout << "=== Test des joueurs ===" << std::endl;
    joueur1->ajouterOr(5);
    joueur1->ajouterCombat(3);
    joueur1->afficher();
    
    joueur2->recevoirDegats(10);
    joueur2->soigner(3);
    joueur2->afficher();
    
    // Test du champion
    std::cout << "=== Test du champion ===" << std::endl;
    champion->recevoirDegats(2);
    champion->recevoirDegats(4); // Devrait le vaincre
    
    // Afficher l'état de la table
    std::cout << "=== État final de la table ===" << std::endl;
    table->afficher();
    
    std::cout << "Test terminé avec succès !" << std::endl;
    return 0;
}