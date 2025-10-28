#include "effet.h"
#include "joueur.h"
#include <iostream>

Champion* getChampionFromCarte(const Carte& carte);

// Constructeur avec paramètres
Effet::Effet(int id, TypeEffet type, int valeur, ConditionEffet condition, int param)
    : id(id), type(type), valeur(valeur), condition(condition), param(param) {
    // Le constructeur initialise simplement les attributs
    // Les effets seront activés lors de l'appel à activerEffet()
}

// Méthode principale pour activer l'effet quand une carte est jouée
void Effet::activerEffet(Joueur& joueurActif, Joueur& adversaire, const Carte* source) const {
    // Vérifier si les conditions sont remplies
    if (!verifierConditions(joueurActif, adversaire)) {
        std::cout << "Conditions non remplies pour l'effet " << id << std::endl;
        return;
    }

    // Si c'est un champion, on vérifie qu'il est actif avant d'appliquer l'effet
    if (source && source->getType() == TypeCarte::CHAMPION) {
        const Champion* champion = static_cast<const Champion*>(source);
        if (!champion->isActive()) {
            std::cout << "Ce champion est epuisé et ne peut pas utiliser ses effets." << std::endl;
            return;
        }
    }
    
    // Appliquer l'effet selon son type
    switch (type) {
        case TypeEffet::EXPEND_CHAMPION:
            if (source && source->getType() == TypeCarte::CHAMPION) {
                Champion* champion = const_cast<Champion*>(static_cast<const Champion*>(source));
                champion->desactiver();
                std::cout << "Champion " << champion->getNom() << " est maintenant expendu." << std::endl;
            }
            break;
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

        case TypeEffet::DMG_ou_SOIN:{
            
            // 1. Demander au joueur quel effet il souhaite appliquer

            int choix;
            std::cout << "Choisissez une option (1 ou 2): " << std::endl
            << "  1 - Gagner 3 points de combat" << std::endl
            << "  2 - Récupérer 3 PV" << std::endl;
            std::cin >> choix;

            // Valider l'entrée
            while (choix != 1 && choix != 2) {
                std::cout << "Choix invalide. Veuillez choisir 1 ou 2: ";
                std::cin >> choix;
            }

            // 2. Appliquer l'effet choisi

            if (choix == 1) {
                joueurActif.addCombat(valeur);
                std::cout << "Joueur " << joueurActif.getId() << " gagne " << valeur << " points de combat" << std::endl;
            } else if (choix == 2) {
                joueurActif.heal(valeur);
                std::cout << "Joueur " << joueurActif.getId() << " récupère " << valeur << " PV" << std::endl;
            }
            break;
        }

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
            
            // Si le joueur choisit 0, on fait rien
            if (choix_valeur == 0) {
                std::cout << "Joueur " << joueurActif.getId() << " ne pioche aucune carte, aucune carte à défausser " << std::endl;
                break;
            }

            // 2. Piocher les cartes
            
            joueurActif.piocher(choix_valeur);
            std::cout << "Joueur " << joueurActif.getId() << " pioche " << choix_valeur << " carte(s)" << std::endl;
            
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
                int carteId = cartes_main[indice_carte - 1].first->getId();

                // Déplacer la carte de la main vers la défausse
                main->deplacerCarte(carteId, *defausse, 1);
                std::cout << "Carte défaussée." << std::endl;
            }
            break;
        }
        
        case TypeEffet::FORCE_DISCARD_OPPONENT:{
            // Forcer l'adversaire à défausser "valeur" cartes
            ZoneDeCarte* mainAdversaire = adversaire.getZoneByType(TypeZone::MAIN);
            ZoneDeCarte* defausseAdversaire = adversaire.getZoneByType(TypeZone::DEFAUSSE);
            if (!mainAdversaire || !defausseAdversaire) {
                std::cout << "Erreur: Zones de l'adversaire non trouvées!" << std::endl;
                break;
            }

            std::cout << "Joueur " << adversaire.getId() << " doit défausser " << valeur << " carte(s)." << std::endl;

            for (int i = 0; i < valeur; ++i) {
                // Afficher la main de l'adversaire
                adversaire.afficherMain();
                int indice_carte;
                std::cout << "Joueur " << adversaire.getId() << ", entrez l'indice de la carte à défausser (" << (i + 1) << "/" << valeur << ") : ";
                std::cin >> indice_carte;

                // Valider l'indice
                while (indice_carte < 1 || indice_carte > static_cast<int>(mainAdversaire->taille())) {
                    std::cout << "Indice invalide! Choisissez entre 1 et " << mainAdversaire->taille() << " : ";
                    std::cin >> indice_carte;
                }

                // Récupérer l'ID de la carte à défausser
                const auto& cartes_main = mainAdversaire->getCartes();
                int carteId = cartes_main[indice_carte - 1].first->getId();

                // Déplacer la carte de la main vers la défausse
                mainAdversaire->deplacerCarte(carteId, *defausseAdversaire, 1);
                std::cout << "Carte défaussée." << std::endl;
            }
            break;
        }


        case TypeEffet::OR_ou_nDMG:{
            
            // 1. Demander au joueur quel effet il souhaite appliquer

            int choix;
            std::cout << "Choisissez une option (1 ou 2): " << std::endl
            << "  1 - Gagner 1 or" << std::endl
            << "  2 - Gagner " << valeur << " points de combat" << std::endl;
            std::cin >> choix;

            // Valider l'entrée
            while (choix != 1 && choix != 2) {
                std::cout << "Choix invalide. Veuillez choisir 1 ou 2: ";
                std::cin >> choix;
            }

            // 2. Appliquer l'effet choisi

            if (choix == 1) {
                joueurActif.addOr(1);
                std::cout << "Joueur " << joueurActif.getId() << " gagne 1 or" << std::endl;
            } else if (choix == 2) {
                joueurActif.addCombat(valeur);
                std::cout << "Joueur " << joueurActif.getId() << " gagne " << valeur << " points de combat" << std::endl;
            }
            
            break;
        }

        case TypeEffet::OR_ou_SOIN_per_CHAMP:{

            // 1. Demander au joueur quel effet il souhaite appliquer

            int choix;
            std::cout << "Choisissez une option (1 ou 2): " << std::endl
            << "  1 - Gagner 1 or" << std::endl
            << "  2 - Gagner 1 PV par champions que vous avez en jeu" << std::endl;
            std::cin >> choix;

            // Valider l'entrée
            while (choix != 1 && choix != 2) {
                std::cout << "Choix invalide. Veuillez choisir 1 ou 2: ";
                std::cin >> choix;
            }

            // 2. Appliquer l'effet choisi

            // Choix 1 : Gagner 1 or
            if (choix == 1) {
                joueurActif.addOr(valeur);
                std::cout << "Joueur " << joueurActif.getId() << " gagne 1 or" << std::endl;
            } 
            
            // Choix 2 : +1 PV par champion en jeu
            else if (choix == 2) {
            
                // Compter le nombre de champions en jeu pour le joueur actif
                ZoneDeCarte* zoneChampions = joueurActif.getZoneByType(TypeZone::CHAMPIONS);
                int nbChampions = zoneChampions ? static_cast<int>(zoneChampions->taille()) : 0;

                if (nbChampions > 0) {
                    joueurActif.heal(valeur*nbChampions);
                    std::cout << "Joueur " << joueurActif.getId() << " récupère " << valeur*nbChampions << " PV ("<< valeur << " par champion en jeu)" << std::endl;
                } else {
                    std::cout << "Aucun champion en jeu pour le joueur " << joueurActif.getId() << ". Aucun PV récupéré." << std::endl;
                }
            }
            
            break;
        }


        // case TypeEffet::PREPARE_CHAMPION:
        //     std::cout << "Choisissez un champion à préparer :" << std::endl;
        //     {
        //         ZoneDeCarte* zoneChampions = joueurActif.getZoneByType(TypeZone::CHAMPIONS);
        //         if (!zoneChampions || zoneChampions->estVide()) {
        //             std::cout << "Aucun champion à préparer." << std::endl;
        //             break;
        //         }

        //         // Afficher les champions disponibles
        //         const auto& cartes = zoneChampions->getCartes();
        //         for (size_t i = 0; i < cartes.size(); ++i) {
        //             const Carte& carte = cartes[i].first;
        //             std::cout << (i + 1) << "- " << carte.getNom() << (static_cast<const Champion&>(carte).isActive() ? " (Actif)" : " (Epuisé)") << std::endl;
        //         }

        //         int choix_champion;
        //         std::cout << "Entrez l'indice du champion à préparer : ";
        //         std::cin >> choix_champion;

        //         // Valider l'indice
        //         while (choix_champion < 1 || choix_champion > static_cast<int>(cartes.size())) {
        //             std::cout << "Indice invalide! Choisissez entre 1 et " << cartes.size() << " : ";
        //             std::cin >> choix_champion;
        //         }

        //         // Préparer le champion choisi
        //         Champion* champion = getChampionFromCarte(cartes[choix_champion - 1].first);
        //         champion->activer();
        //         std::cout << "Champion " << champion->getNom() << " est maintenant préparé." << std::endl;
        //     }
        //     break;

        
        case TypeEffet::SACRIFICE_HAND_DISCARD: {
            // Sacrifier jusqu'à [valeur] carte(s) de la main et/ou de la défausse pour activer l'effet associé
            int reponse;
            for (int i = 0; i < valeur; ++i) {

                std::cout << "Voulez vous sacrifier une carte de votre main ou défausse ? (1 = Oui, 0 = Non) : ";
                std::cin >> reponse;

                while (reponse != 0 && reponse != 1) {
                    std::cout << "Réponse invalide! Entrez 1 pour Oui ou 0 pour Non : ";
                    std::cin >> reponse;
                }

                if (reponse == 0) {
                    std::cout << "Fin du sacrifice de cartes." << std::endl;
                    break;
                }

                std::cout << "Choisissez une carte à sacrifier de votre main ou défausse :" << std::endl;
                
                // Afficher les cartes de la main et de la défausse
                ZoneDeCarte* main = joueurActif.getZoneByType(TypeZone::MAIN);
                ZoneDeCarte* defausse = joueurActif.getZoneByType(TypeZone::DEFAUSSE);
                
                std::vector<std::pair<Carte*, TypeZone>> cartesDisponibles;
                
                if (main) {
                    const auto& cartesMain = main->getCartes();
                    for (const auto& paire : cartesMain) {
                        cartesDisponibles.emplace_back(paire.first, TypeZone::MAIN);
                    }
                }
                
                if (defausse) {
                    const auto& cartesDefausse = defausse->getCartes();
                    for (const auto& paire : cartesDefausse) {
                        cartesDisponibles.emplace_back(paire.first, TypeZone::DEFAUSSE);
                    }
                }
                
                // Afficher les options
                for (size_t j = 0; j < cartesDisponibles.size(); ++j) {
                    std::cout << (j + 1) << "- " << cartesDisponibles[j].first->getNom()
                              << " (de la " << (cartesDisponibles[j].second == TypeZone::MAIN ? "main" : "défausse") << ")" << std::endl;
                }
                
                int choix_carte;
                std::cout << "Entrez l'indice de la carte à sacrifier : ";
                std::cin >> choix_carte;
                
                // Valider l'indice
                while (choix_carte < 1 || choix_carte > static_cast<int>(cartesDisponibles.size())) {
                    std::cout << "Indice invalide! Choisissez entre 1 et " << cartesDisponibles.size() << " : ";
                    std::cin >> choix_carte;
                }
                
                // Sacrifier la carte choisie
                Carte* carteASacrifier = cartesDisponibles[choix_carte - 1].first;
                TypeZone zoneOrigine = cartesDisponibles[choix_carte - 1].second;
                ZoneDeCarte* zoneDestination = joueurActif.getZoneByType(TypeZone::ECARTEES);

                if (zoneOrigine == TypeZone::MAIN && main){
                    main->deplacerCarte(carteASacrifier->getId(), *zoneDestination, 1);
                } else if (zoneOrigine == TypeZone::DEFAUSSE && defausse) {
                    defausse->deplacerCarte(carteASacrifier->getId(), *zoneDestination, 1);
                }
            }
            break;
        }
            
        case TypeEffet::SOIN_per_CHAMP:{
            // Soigner le joueur actif de (valeur * nombre de champions en jeu)
            ZoneDeCarte* zoneChampions = joueurActif.getZoneByType(TypeZone::CHAMPIONS);
            int nbChampions = zoneChampions ? static_cast<int>(zoneChampions->taille()) : 0;

            if (nbChampions > 0) {
                joueurActif.heal(valeur * nbChampions);
                std::cout << "Joueur " << joueurActif.getId() << " récupère " << (valeur * nbChampions) << " PV (" << valeur << " par champion en jeu)" << std::endl;
            } else {
                std::cout << "Aucun champion en jeu pour le joueur " << joueurActif.getId() << ". Aucun PV récupéré." << std::endl;
            }
            break;
        }

        case TypeEffet::STUN: {
            // Étourdir un champion adverse
            std::cout << "Choisissez un champion adverse à étourdir :" << std::endl;

            ZoneDeCarte* zoneChampionsAdversaire = adversaire.getZoneByType(TypeZone::CHAMPIONS);
            if (!zoneChampionsAdversaire || zoneChampionsAdversaire->estVide()) {
                std::cout << "Aucun champion adverse à étourdir." << std::endl;
                break;
            }

            // Afficher les champions adverses disponibles (lecture seule)
            const auto& cartes = zoneChampionsAdversaire->getCartes();
            for (size_t i = 0; i < cartes.size(); ++i) {
                const Carte* carte = cartes[i].first;
                const Champion* champion = dynamic_cast<const Champion*>(carte);
                if (champion) {
                    std::cout << (i + 1) << "- " << champion->getNom()
                            << (champion->isStunned() ? " (Étourdi)" : " (Non étourdi)")
                            << std::endl;
                }
            }

            // Demander au joueur de choisir un champion
            int choix_champion;
            std::cout << "Entrez l'indice du champion à étourdir : ";
            std::cin >> choix_champion;

            // Valider l'indice
            while (choix_champion < 1 || choix_champion > static_cast<int>(cartes.size())) {
                std::cout << "Indice invalide! Choisissez entre 1 et " << cartes.size() << " : ";
                std::cin >> choix_champion;
            }

            // Étourdir le champion choisi (modification de l'état)
            Carte* carteChoisie = cartes[choix_champion - 1].first;
            Champion* champion = dynamic_cast<Champion*>(carteChoisie);
            if (champion) {
                champion->stun();
                std::cout << "Champion " << champion->getNom() << " est maintenant étourdi. Joueur " <<
                adversaire.getId() << " ne pourra pas utiliser ce champion au prochain tour" << std::endl;
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
        case ConditionEffet::SACRIFICE_TO_MARCHE: // pour les gemmes de feu
            // TODO: Vérifier si un sacrifice a été effectué
        case ConditionEffet::SACRIFICE_HAND_DISCARD:
            // TODO: Vérifier si une carte a été défaussée de la main
            std::cout << "Vérification condition SACRIFICE_HAND_DISCARD (non implémentée)" << std::endl;
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

/**
 * @brief Convertit une Carte en Champion si possible
 * 
 * Fonction utilitaire qui permet de convertir une référence de Carte en pointeur
 * vers Champion.
 * 
 * @param carte La carte à convertir
 * @return Champion* Pointeur vers le Champion si la conversion est possible,
 *                   nullptr si la carte n'est pas un Champion
 * 
 * @note Cette fonction doit être utilisée uniquement quand on est sûr que
 *       la carte est un Champion, sinon vérifier le retour
 */
Champion* getChampionFromCarte(const Carte& carte) {
    return const_cast<Champion*>(dynamic_cast<const Champion*>(&carte));
}