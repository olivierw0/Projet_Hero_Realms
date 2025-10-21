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
            if(valeur > 1){
                std::cout << "Joueur " << joueurActif.getId() << " pioche " << valeur << " cartes" << std::endl;
                break;
            }
            else{
                std::cout << "Joueur " << joueurActif.getId() << " pioche " << valeur << " carte" << std::endl;
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