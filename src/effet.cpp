#include "effet.h"
#include "joueur.h"
#include <iostream>

// Constructeur avec paramètres
Effet::Effet(int id, TypeEffet type, int valeur, ConditionEffet condition, int param)
    : id(id), type(type), valeur(valeur), condition(condition), param(param) {
    // Le constructeur initialise simplement les attributs
    // Les effets seront activés lors de l'appel à activerEffet()
}

// Méthode principale pour activer l'effet quand une carte est jouée
void Effet::activerEffet(Joueur& joueurActif, Joueur& adversaire) const {
    // Vérifier si les conditions sont remplies
    if (!verifierConditions(joueurActif, adversaire)) {
        std::cout << "Conditions non remplies pour l'effet " << id << std::endl;
        return;
    }
    
    // Appliquer l'effet selon son type
    switch (type) {
        case TypeEffet::OR:
            joueurActif.addOr(valeur);
            std::cout << "Joueur " << joueurActif.getId() << " gagne " << valeur << " or" << std::endl;
            break;
            
        case TypeEffet::DMG:
            joueurActif.addCombat(valeur);
            std::cout << "Joueur " << joueurActif.getId() << " gagne " << valeur << " points de combat" << std::endl;
            break;
            
        case TypeEffet::SOIN:
            joueurActif.heal(valeur);
            std::cout << "Joueur " << joueurActif.getId() << " récupère " << valeur << " PV" << std::endl;
            break;
            
        case TypeEffet::PIOCHE:
            joueurActif.piocher(valeur);
            std::cout << "Joueur " << joueurActif.getId() << " pioche " << valeur << " carte(s)" << std::endl;
            break;

        case TypeEffet::DRAW_DISCARD:
        {

            // 1. Déterminer le nombre de cartes à piocher et défausser

            // Demander au joueur actif combien de cartes il souhaite piocher et défausser
            int choix_valeur; 
            std::cout << "Choisissez le nombre de cartes à piocher et défausser (0 à " << valeur << ") : ";
            std::cin >> choix_valeur;

            // Valider l'entrée
            while (choix_valeur < 0 || choix_valeur > valeur) {
                std::cout << "Erreur : Veuillez entrer une valeur entre 0 et " << valeur << " : ";
                std::cin >> choix_valeur;
            }
            
            // Si le joueur choisit 0, on ne fait rien
            if (choix_valeur == 0) {
                std::cout << "Joueur " << joueurActif.getId() << " ne pioche aucune carte, aucune carte à défausser " << std::endl;
                break;
            }

            // 2. Piocher les cartes
            
            joueurActif.piocher(choix_valeur);
            std::cout << "Joueur " << joueurActif.getId() << " pioche " << valeur << " carte(s)" << std::endl;
            
            // 3. Défausser les cartes choisies par le joueur

            // Afficher la main actuelle
            joueurActif.afficherMain();
            ZoneDeCarte* main = joueurActif.getZoneByType(TypeZone::MAIN);
            ZoneDeCarte* defausse = joueurActif.getZoneByType(TypeZone::DEFAUSSE);
            for (int i = 0; i < choix_valeur; ++i) {
                int indice_carte;
                std::cout << "Entrez l'indice de la carte à défausser (" << (i + 1) << "/" << choix_valeur << ") : ";
                std::cin >> indice_carte;

                // Valider l'indice
                while (indice_carte < 1 || indice_carte > static_cast<int>(main->taille())) {
                    std::cout << "Indice invalide! Choisissez entre 1 et " << main->taille() << " : ";
                    std::cin >> indice_carte;
                }

                // Récupérer l'ID de la carte à défausser
                const auto& cartes_main = main->getCartes();
                int carteId = cartes_main[indice_carte - 1].first.getId();

                // Déplacer la carte de la main vers la défausse
                main->deplacerCarte(carteId, *defausse, 1);
                std::cout << "Carte défaussée." << std::endl;
            }
            break;
        }

        case TypeEffet::DMG_ou_SOIN:{
            
            int choix;
            std::cout << "Choisissez une option (1 ou 2): " << std::endl
            << "  1 - Gagner 3 points de combat" << std::endl
            << "  2 - Récupérer 3 PV" << std::endl;
            std::cin >> choix;
            
            if (choix == 1) {
                joueurActif.addCombat(valeur);
                std::cout << "Joueur " << joueurActif.getId() << " gagne " << valeur << " points de combat" << std::endl;
            } else if (choix == 2) {
                joueurActif.heal(valeur);
                std::cout << "Joueur " << joueurActif.getId() << " récupère " << valeur << " PV" << std::endl;
            } else {
                std::cout << "Choix invalide. Aucune action effectuée." << std::endl;
            }
            break;
        }


            
        default:
            std::cout << "Effet non implémenté : " << static_cast<int>(type) << std::endl;
            break;
    }
}

// Méthode pour vérifier si les conditions de l'effet sont remplies
bool Effet::verifierConditions(const Joueur& joueurActif, const Joueur& adversaire) const {
    switch (condition) {
        case ConditionEffet::AUCUNE:
            return true; // Aucune condition, toujours activable
            
        case ConditionEffet::SACRIFICE:
            // TODO: Vérifier si un sacrifice a été effectué
            std::cout << "Vérification condition SACRIFICE (non implémentée)" << std::endl;
            return false;
            
        case ConditionEffet::ROUGE_ALLY:
        case ConditionEffet::JAUNE_ALLY:
        case ConditionEffet::VERT_ALLY:
        case ConditionEffet::BLEU_ALLY:
            // TODO: Vérifier la présence d'alliés de la bonne faction
            std::cout << "Vérification condition ALLY (non implémentée)" << std::endl;
            return false;
            
        case ConditionEffet::NB_CHAMPIONS:
        case ConditionEffet::NB_GARDES:
        case ConditionEffet::NB_VERT_CARDS_IN_PLAY:
            // TODO: Compter les cartes appropriées en jeu
            std::cout << "Vérification condition comptage (non implémentée)" << std::endl;
            return false;
            
        default:
            return false;
    }
}