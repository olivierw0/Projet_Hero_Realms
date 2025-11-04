#include "effet.h"
#include "joueur.h"
#include "table_partie.h"
#include "console_colors.h"
#include <iostream>

// Constructeur avec paramètres
Effet::Effet(int id, TypeEffet type, int valeur, ConditionEffet condition)
    : id(id), type(type), valeur(valeur), condition(condition) {
    // Le constructeur initialise simplement les attributs
    // Les effets seront activés lors de l'appel à activerEffet()
}

// Méthode principale pour activer l'effet quand une carte est jouée
void Effet::activerEffet(Joueur& joueurActif, Joueur& adversaire, const Carte* source) const {
    // Vérifier si les conditions sont remplies
    if (!verifierConditions(joueurActif, source)) {
        std::cout << "Conditions non remplies pour l'effet " << id << std::endl;
        return;
    }

    // Si c'est un champion, on vérifie qu'il est actif avant d'appliquer l'effet
    if (source && source->getType() == TypeCarte::CHAMPION) {
        const Champion* champion = static_cast<const Champion*>(source);
        if (!champion->getActive()) {
            std::cout << "Ce champion est déjà expendu et ne peut pas utiliser ses effets." << std::endl;
            return;
        }
    }
    
    // Appliquer l'effet selon son type
    switch (type) {
        case TypeEffet::OR:
            joueurActif.addOr(valeur);
            std::cout << "Joueur " << joueurActif.getId() << " gagne " << ConsoleColors::colorizeOr(std::to_string(valeur) + " or") << std::endl;
            break;
            
        case TypeEffet::DMG:
            joueurActif.addCombat(valeur);
            std::cout << "Joueur " << joueurActif.getId() << " gagne " << ConsoleColors::colorizeDamage(std::to_string(valeur) + " points de combat") << std::endl;
            break;
            
        case TypeEffet::SOIN:
            joueurActif.heal(valeur);
            std::cout << "Joueur " << joueurActif.getId() << " récupère " << ConsoleColors::colorizeHeal(std::to_string(valeur) + " PV") << std::endl;
            break;
            
        case TypeEffet::PIOCHE:
            joueurActif.piocher(valeur);
            std::cout << "Joueur " << joueurActif.getId() << " pioche " << ConsoleColors::colorizeDraw(std::to_string(valeur) + " carte(s)") << std::endl;
            break;

        case TypeEffet::DMG_ou_SOIN:{
            
            // 1. Demander au joueur quel effet il souhaite appliquer

            int choix;
            std::cout << "Choisissez une option (1 ou 2): " << std::endl
            << "  1 - Gagner " << ConsoleColors::colorizeDamage("3 points de combat") << std::endl
            << "  2 - Récupérer " << ConsoleColors::colorizeHeal("4 PV") << std::endl
            << "Votre choix : ";
            std::cin >> choix;
            std::cout << std::endl;

            // Valider l'entrée
            while (choix != 1 && choix != 2) {
                std::cout << "Choix invalide. Veuillez choisir 1 ou 2: ";
                std::cin >> choix;
            }

            // 2. Appliquer l'effet choisi

            if (choix == 1) {
                joueurActif.addCombat(3);
                std::cout << "Joueur " << joueurActif.getId() << " gagne " << ConsoleColors::colorizeDamage("3 points de combat") << std::endl;
            } else if (choix == 2) {
                joueurActif.heal(4);
                std::cout << "Joueur " << joueurActif.getId() << " récupère " << ConsoleColors::colorizeHeal("4 PV") << std::endl;
            }
            break;
        }

        case TypeEffet::DRAW_DISCARD:
        {
            std::cout << "\nEffet de la carte " << source->getNom() << " activé..." << std::endl;
            // 1. Défausser la carte possédant l'effet

            ZoneDeCarte* main = joueurActif.getZoneByType(TypeZone::MAIN);
            main->deplacerCarte(source->getId(), *joueurActif.getZoneByType(TypeZone::DEFAUSSE), 1);

            // 2. Vérifier que le joueur actif a des cartes en main

            if (!main || main->estVide()) {
                std::cout << "🙁 Vous n'avez aucune carte en main, vous ne pouvez pas activer cet effet" << std::endl;
                break;
            }

            // 3. Déterminer le nombre de cartes à piocher et défausser

            // Demander au joueur actif combien de cartes il souhaite piocher et défausser
            int choix_valeur; 
            std::cout << "\nChoisissez un nombre de cartes à piocher et défausser (0 - " << valeur << ") : ";
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

            // 4. Piocher les cartes
            
            joueurActif.piocher(choix_valeur);
            std::cout << "Joueur " << joueurActif.getId() << " pioche " << ConsoleColors::colorizeDraw(std::to_string(choix_valeur) + " carte(s)") << std::endl;
            
            // 5. Défausser les cartes choisies par le joueur

            // Afficher la main actuelle
            std::cout << "\nVotre nouvelle main : " << std::endl;
            joueurActif.afficherMain();
            std::cout << std::endl;

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

            std::cout << "Joueur " << adversaire.getId() << " doit défausser " << ConsoleColors::colorizeAction(std::to_string(valeur) + " carte(s)") << "." << std::endl;

            for (int i = 0; i < valeur; i++) {
                // Afficher la main de l'adversaire
                adversaire.afficherMain();
                int indice_carte;
                std::cout << "Joueur " << adversaire.getId() << ", entrez l'indice de la carte à défausser (" << (i + 1) << "-" << static_cast<int>(mainAdversaire->taille()) << ") : ";
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
                std::cout << "Carte " << cartes_main[indice_carte - 1].first->getNom() << " défaussée." << std::endl;
            }
            break;
        }

        case TypeEffet::OR_ou_nDMG:{
            
            // 1. Demander au joueur quel effet il souhaite appliquer

            int choix;
            std::cout << "Choisissez une option (1 ou 2): " << std::endl
            << "  1 - Gagner " << ConsoleColors::colorizeOr("1 or") << std::endl
            << "  2 - Gagner " << ConsoleColors::colorizeDamage(std::to_string(valeur) + " points de combat") << std::endl;
            std::cout << "Votre choix : ";
            std::cin >> choix;

            // Valider l'entrée
            while (choix != 1 && choix != 2) {
                std::cout << "Choix invalide. Veuillez choisir 1 ou 2: ";
                std::cin >> choix;
            }

            // 2. Appliquer l'effet choisi

            if (choix == 1) {
                joueurActif.addOr(1);
                std::cout << "Joueur " << joueurActif.getId() << " gagne " << ConsoleColors::colorizeOr("1 or") << std::endl;
            } else if (choix == 2) {
                joueurActif.addCombat(valeur);
                std::cout << "Joueur " << joueurActif.getId() << " gagne " << ConsoleColors::colorizeDamage(std::to_string(valeur) + " points de combat") << std::endl;
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
                std::cout << "Votre choix : ";
                std::cin >> choix;
                std::cout << std::endl;
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
                    std::cout << "Joueur " << joueurActif.getId() << " récupère " << ConsoleColors::colorizeHeal(std::to_string(valeur*nbChampions) + " PV (" + std::to_string(nbChampions) + " champion(s) en jeu)") << std::endl;
                } else {
                    std::cout << "🙁 Aucun champion en jeu pour le joueur " << joueurActif.getId() << ". Aucun PV bonus récupéré." << std::endl;
                }
            }
            
            break;
        }

        case TypeEffet::PREPARE_CHAMPION:{
            // Préparer un champion (le rendre actif)
            std::cout << "\nChoisissez un de vos champions à préparer :" << std::endl;

            ZoneDeCarte* zoneChampions = joueurActif.getZoneByType(TypeZone::CHAMPIONS);
            if (!zoneChampions || zoneChampions->estVide()) {
                std::cout << "🙁 Aucun champion à préparer." << std::endl;
                break;
            }

            // Afficher les champions disponibles
            const auto& cartes = zoneChampions->getCartes();
            std::vector<Champion*> championsEpuises;
            for (const auto& paire : cartes) {
                Champion* champion = dynamic_cast<Champion*>(paire.first);
                if (champion && champion->getActive()) {
                    std::cout << "Champion " << ConsoleColors::colorizeAction(champion->getNom()) << " est déjà actif." << std::endl;
                }else if (champion) {
                    championsEpuises.push_back(champion);
                }
            }

            // Afficher les champions épuisés
            if (!championsEpuises.empty()) {
                std::cout << "Champions épuisés :" << std::endl;
                int i = 1;
                for (const auto& champion : championsEpuises) {
                    std::cout << (i) << " - " << ConsoleColors::colorizeAction(champion->getNom()) << std::endl;
                    i++;
                }
            }
            else {
                std::cout << "\n🙁 Aucun champion épuisé à préparer." << std::endl;
                break;
            }

            int choix;
            std::cout << "Entrez l'indice du champion à préparer : ";
            std::cin >> choix;
            std::cout << std::endl;

            // Valider l'indice
            while (choix < 1 || choix > static_cast<int>(championsEpuises.size())) {
                std::cout << "Indice invalide! Choisissez entre 1 et " << championsEpuises.size() << " : ";
                std::cin >> choix;
            }

            Champion* championChoisi = dynamic_cast<Champion*>(championsEpuises[choix - 1]);
            if (championChoisi) {
                championChoisi->setActive(true);
                std::cout << "Champion " << ConsoleColors::colorizeAction(championChoisi->getNom()) << " est maintenant préparé (actif)." << std::endl;
            }
            break;
        }
        
        case TypeEffet::SACRIFICE_HAND_DISCARD: {
            // Sacrifier jusqu'à [valeur] carte(s) de la main et/ou de la défausse pour activer l'effet associé
            char reponse;
            std::cout << "\nEffet de la carte " << source->getNom() << " activé..." << std::endl;
            std::cout << "\nVous pouvez " << ConsoleColors::colorizeAction("sacrifier jusqu'à " + std::to_string(valeur) + " carte(s) de votre main ou défausse.") << std::endl;
            for (int i = 0; i < valeur; ++i) {

                std::cout << "Voulez vous sacrifier une carte de votre main ou défausse ? (o/n) : ";
                std::cin >> reponse;

                while (reponse != 'o' && reponse != 'O' && reponse != 'n' && reponse != 'N') {
                    std::cout << "Réponse invalide! Entrez o pour Oui ou n pour Non : ";
                    std::cin >> reponse;
                }

                if (reponse == 'n' || reponse == 'N') {
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
                TablePartie* table = joueurActif.getTable();
                ZoneDeCarte* zoneDestination = table->getCartesEcartees();

                if (zoneOrigine == TypeZone::MAIN && main){
                    main->deplacerCarte(carteASacrifier->getId(), *zoneDestination, 1);
                } else if (zoneOrigine == TypeZone::DEFAUSSE && defausse) {
                    defausse->deplacerCarte(carteASacrifier->getId(), *zoneDestination, 1);
                }
                std::cout << "\nCarte " << carteASacrifier->getNom() << " sacrifiée." << std::endl;
            }
            break;
        }
            
        case TypeEffet::SOIN_per_CHAMP:{
            // Soigner le joueur actif de (valeur * nombre de champions en jeu)
            ZoneDeCarte* zoneChampions = joueurActif.getZoneByType(TypeZone::CHAMPIONS);
            int nbChampions = zoneChampions ? static_cast<int>(zoneChampions->taille()) : 0;

            if (nbChampions > 0) {
                joueurActif.heal(valeur * nbChampions);
                std::cout << "Joueur " << joueurActif.getId() << " récupère " << ConsoleColors::colorizeHeal(std::to_string(valeur * nbChampions) + " PV (" + std::to_string(valeur) + " par champion en jeu)") << std::endl;
            } else {
                std::cout << "🙁 Aucun champion en jeu pour le joueur " << joueurActif.getId() << ". Aucun PV bonus récupéré." << std::endl;
            }
            break;
        }

        case TypeEffet::STUN: {
            // Assommer un champion adverse

            ZoneDeCarte* zoneChampionsAdversaire = adversaire.getZoneByType(TypeZone::CHAMPIONS);
            if (!zoneChampionsAdversaire || zoneChampionsAdversaire->estVide()) {
                std::cout << "🙁 Aucun champion adverse à assommer." << std::endl;
                break;
            }

            std::cout << "Choisissez un champion adverse à assommer :" << std::endl;

            // Afficher les champions adverses disponibles
            const auto& cartes = zoneChampionsAdversaire->getCartes();
            for (size_t i = 0; i < cartes.size(); ++i) {
                std::cout << (i + 1) << "- " << ConsoleColors::colorizeAction(cartes[i].first->getNom()) << std::endl;
            }

            // Demander au joueur de choisir un champion parmi ceux proposés
            int choix_champion;
            std::cout << "Entrez l'indice du champion à assommer : ";
            std::cin >> choix_champion;

            // Valider l'indice
            while (choix_champion < 1 || choix_champion > static_cast<int>(cartes.size())) {
                std::cout << "Indice invalide! Choisissez entre 1 et " << cartes.size() << " : ";
                std::cin >> choix_champion;
            }

            // Assommer le champion choisi
            Carte* carteChoisie = cartes[choix_champion - 1].first;
            ZoneDeCarte* defausseAdversaire = adversaire.getZoneByType(TypeZone::DEFAUSSE);

            zoneChampionsAdversaire->deplacerCarte(carteChoisie->getId(), *defausseAdversaire, 1);
            std::cout << "Champion " << ConsoleColors::colorizeAction(carteChoisie->getNom()) << " est assommé et déplacé dans la défausse." << std::endl;

            break;
        }

        case TypeEffet::TOP_DECK_FROM_DISCARD: {
            // Remettre une carte de la défausse en haut du deck

            ZoneDeCarte* defausse = joueurActif.getZoneByType(TypeZone::DEFAUSSE);
            ZoneDeCarte* deck = joueurActif.getZoneByType(TypeZone::DECK);

            if (!defausse || defausse->estVide()) {
                std::cout << "La défausse est vide. Aucun carte à remettre en haut du deck." << std::endl;
                break;
            }

            // Afficher les cartes dans la défausse
            std::cout << "Choisissez une carte de votre défausse à remettre en haut du deck :" << std::endl;
            const auto& cartesDefausse = defausse->getCartes();
            for (size_t i = 0; i < cartesDefausse.size(); ++i) {
                std::cout << (i + 1) << "- " << cartesDefausse[i].first->getNom() << std::endl;
            }

            int choix_carte = -1;
            std::string saisie;
            while (true) {
                std::cout << "Entrez l'indice de la carte à remettre en haut du deck : ";
                std::cin >> saisie;
                try {
                    choix_carte = std::stoi(saisie);
                    if (choix_carte >= 1 && choix_carte <= static_cast<int>(cartesDefausse.size())) {
                        break; // Saisie correcte
                    } else {
                        std::cout << "Indice hors bornes ! Essayez à nouveau." << std::endl;
                    }
                } catch (std::invalid_argument&) {
                    std::cout << "Indice invalide ! Veuillez entrer un nombre." << std::endl;
                }
            }

            Carte* carteChoisie = cartesDefausse[choix_carte - 1].first;
            if (!carteChoisie) {
                std::cout << "Carte invalide sélectionnée." << std::endl;
                break;
            }
            #ifdef DEBUG
            std::cout << "[DEBUG] Carte choisie : " << carteChoisie->getNom() << " (ID: " << carteChoisie->getId() << ")" << std::endl;
            #endif
            defausse->deplacerCarte(carteChoisie->getId(), *deck, 0); // 0 pour le dessus du deck
            defausse->trierParOrdre();
            std::cout << "Carte " << carteChoisie->getNom() << " remise en haut du deck." << std::endl;

            break;
        }

        case TypeEffet::TOP_DECK_NEXT_ACQUIRED: {
            // La prochaine carte acquise pdt ce tour va en haut du deck
            joueurActif.setNextAcquiredTopDeck(true);
            std::cout << "La prochaine carte acquise pendant ce tour ira en haut du deck." << std::endl;
            break;
        }

        case TypeEffet::TOP_DECK_NEXT_ACQUIRED_ACTION: {
            // La prochaine action acquise pdt ce tour va en haut du deck
            joueurActif.setNextAcquiredTopDeckAction(true);
            std::cout << "La prochaine carte de type ACTION acquise pendant ce tour ira en haut du deck." << std::endl;
            break;
        }

        case TypeEffet::HAND_NEXT_ACQUIRED: {
            // La prochaine carte acquise pdt ce tour va dans la main
            joueurActif.setNextAcquiredHand(true);
            std::cout << "La prochaine carte acquise pendant ce tour ira dans la main." << std::endl;
            break;
        }

        case TypeEffet::DMG_per_CHAMPION:{
            // Infliger des dégâts à l'adversaire en fonction du nombre de champions en jeu (en excluant le champion source)
            ZoneDeCarte* zoneChampions = joueurActif.getZoneByType(TypeZone::CHAMPIONS);
            int nbChampions = zoneChampions ? static_cast<int>(zoneChampions->taille()) - 1 : 0;  // -1 pour exclure le champion qui active l'effet

            if (nbChampions > 0) {
                int totalDmg = valeur * nbChampions;
                joueurActif.addCombat(totalDmg);
                std::cout << "Joueur " << joueurActif.getId() << " recoit " << ConsoleColors::colorizeDamage(std::to_string(totalDmg) + " points de dégâts (" + std::to_string(valeur) + " par champion en jeu)") << std::endl;
            } else {
                std::cout << "Aucun autre champion en jeu pour le joueur " << joueurActif.getId() << ". Aucun point de dégât ajouté." << std::endl;
            }
            break;
        }

        case TypeEffet::DMG_per_GUARD:{
            // Gagner [valeur] points de combat en fonction du nombre de gardes en jeu
            ZoneDeCarte* zoneChampions = joueurActif.getZoneByType(TypeZone::CHAMPIONS);
            int nbGardes = 0;
            for (const auto& paire : zoneChampions->getCartes()) {
                Carte* carte = paire.first;
                if (carte->getType() == TypeCarte::CHAMPION) {
                    Champion* champion = static_cast<Champion*>(carte);
                    if (champion->hasGarde()) {
                        nbGardes++;
                    }
                }
            }

            if (nbGardes > 0) {
                int totalDmg = valeur * nbGardes;
                joueurActif.addCombat(totalDmg);
                std::cout << "Joueur " << joueurActif.getId() << " recoit " << ConsoleColors::colorizeDamage(std::to_string(totalDmg) + " points de dégâts (" + std::to_string(valeur) + " par garde en jeu)") << std::endl;
            } else {
                std::cout << "Aucune garde en jeu. Aucun point de dégât bonus ajouté." << std::endl;
            }
            break;
        }

        case TypeEffet::DMG_per_VERT_CARDS: {
            // Infliger des dégâts à l'adversaire en fonction du nombre de cartes vertes en jeu
            ZoneDeCarte* champs = joueurActif.getZoneByType(TypeZone::CHAMPIONS);
            ZoneDeCarte* main = joueurActif.getZoneByType(TypeZone::MAIN);
            int nbCartesVertes = -1;
            for (const auto& paire : champs->getCartes()) {
                Carte* carte = paire.first;
                if (carte->getFaction() == FactionCarte::VERT) {
                    nbCartesVertes++;
                }
            }
            for (const auto& paire : main->getCartes()) {
                Carte* carte = paire.first;
                if (carte->getFaction() == FactionCarte::VERT) {
                    nbCartesVertes++;
                }
            }

            if (nbCartesVertes > 0) {
                int totalDmg = valeur * nbCartesVertes;
                joueurActif.addCombat(totalDmg);
                std::cout << "Joueur " << joueurActif.getId() << " recoit " << ConsoleColors::colorizeDamage(std::to_string(totalDmg) + " points de dégâts (" + std::to_string(valeur) + " par carte verte en jeu)") << std::endl;
            } else {
                std::cout << "Aucune carte verte en jeu pour le joueur " << joueurActif.getId() << ". Aucun point de dégât ajouté." << std::endl;
            }
            break;
        }

        default:
            std::cout << "Effet non implémenté : " << static_cast<int>(type) << std::endl;
            break;
    }
}

// Méthode pour vérifier si les conditions de l'effet sont remplies
bool Effet::verifierConditions(Joueur& joueurActif, const Carte* source) const {
    switch (condition) {
        case ConditionEffet::AUCUNE:
            return true; // Aucune condition, toujours activable
            break;
        case ConditionEffet::SACRIFICE:{
            // Mettre la carte dans la zone d'écart
            if (source) {
                ZoneDeCarte* zoneEcartees = joueurActif.getTable()->getCartesEcartees();
                ZoneDeCarte* main = joueurActif.getZoneByType(TypeZone::MAIN);

                if (main && zoneEcartees) {
                    main->deplacerCarte(source->getId(), *zoneEcartees, 1);
                    std::cout << "Carte " << source->getNom() << " sacrifiée et déplacée dans la zone d'écart." << std::endl;
                    return true;
                } else {
                    std::cout << "Erreur: Impossible de trouver la carte à sacrifier ou la zone d'écart!" << std::endl;
                    return false;
                }
            } else {
                std::cout << "Erreur: Carte à sacrifier non fournie !" << std::endl;
                return false;
            }
        }

        case ConditionEffet::SACRIFICE_TO_MARCHE:{ // pour les gemmes de feu
            // Mettre la carte dans la zone d'écart
            if (source) {
                ZoneDeCarte* marche = joueurActif.getTable()->getGemmesFeu();
                ZoneDeCarte* main = joueurActif.getZoneByType(TypeZone::MAIN);
                
                #ifdef DEBUG
                if (!marche) {
                    std::cout << "DEBUG: La zone du marché est introuvable!" << std::endl;
                }
                if (!main) {
                    std::cout << "DEBUG: La zone de la main est introuvable!" << std::endl;
                }
                #endif

                if (main && marche) {
                    main->deplacerCarte(source->getId(), *marche, 1);
                    std::cout << "Carte " << source->getNom() << " sacrifiée et déplacée dans la zone d'écart." << std::endl;
                    return true;
                } else {
                    std::cout << "Erreur: Impossible de trouver la carte à sacrifier ou la zone d'écart!" << std::endl;
                    return false;
                }
            } else {
                std::cout << "Erreur: Carte à sacrifier non fournie !" << std::endl;
                return false;
            }
        }
        
        case ConditionEffet::COND_SACRIFICE_HAND_DISCARD:{
            char reponse;
            bool conditionRemplie = false;

            std::cout << "Voulez vous sacrifier une carte de votre main ou défausse ? (o/n) : ";
            std::cin >> reponse;

            while (reponse != 'o' && reponse != 'O' && reponse != 'n' && reponse != 'N') {
                std::cout << "Réponse invalide! Entrez o pour Oui ou n pour Non : ";
                std::cin >> reponse;
            }
            
            if (reponse != 'o' && reponse != 'O') {
                std::cout << "Fin du sacrifice de cartes." << std::endl;
                return conditionRemplie;
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
            else {
                return false; // Pas de main, ne peut pas sacrifier
            }
            
            if (defausse) {
                const auto& cartesDefausse = defausse->getCartes();
                for (const auto& paire : cartesDefausse) {
                    cartesDisponibles.emplace_back(paire.first, TypeZone::DEFAUSSE);
                }
            }
            
            if(cartesDisponibles.empty()) {
                break;
            }
            
            // Afficher les options
            for (size_t j = 0; j < cartesDisponibles.size(); j++) {
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
            ZoneDeCarte* zoneDestination = joueurActif.getTable()->getCartesEcartees();

            if (zoneOrigine == TypeZone::MAIN && main){
                main->deplacerCarte(carteASacrifier->getId(), *zoneDestination, 1);
                conditionRemplie = true;
            } else if (zoneOrigine == TypeZone::DEFAUSSE && defausse) {
                defausse->deplacerCarte(carteASacrifier->getId(), *zoneDestination, 1);
                conditionRemplie = true;
            }
            
            return conditionRemplie;
        }

        case ConditionEffet::ROUGE_ALLY:{
            const ZoneDeCarte* champions = joueurActif.getZoneByType(TypeZone::CHAMPIONS);
            const ZoneDeCarte* main = joueurActif.getZoneByType(TypeZone::MAIN);
            if (!champions) {
                std::cout << "Erreur: zone des champions introuvable!" << std::endl;
                return false;
            }
            if (!main) {
                std::cout << "Erreur: zone de la main introuvable!" << std::endl;
                return false;
            }

            for (const auto& paire : champions->getCartes()) {
                const Carte* carte = paire.first;
                if (source && source->getId() == carte->getId()) {
                    continue; // Ignorer la carte source
                }
                if (carte->getFaction() == FactionCarte::ROUGE) {
                    return true; // Condition remplie
                }
            }
            for (const auto& paire : main->getCartes()) {
                const Carte* carte = paire.first;
                if (source && source->getId() == carte->getId()) {
                    continue; // Ignorer la carte source
                }
                if (carte->getFaction() == FactionCarte::ROUGE) {
                    return true; // Condition remplie
                }
            }
            return false; // Aucun allié rouge trouvé
        }

        case ConditionEffet::JAUNE_ALLY:{
            const ZoneDeCarte* champions = joueurActif.getZoneByType(TypeZone::CHAMPIONS);
            const ZoneDeCarte* main = joueurActif.getZoneByType(TypeZone::MAIN);
            if (!champions) {
                std::cout << "Erreur: zone des champions introuvable!" << std::endl;
                return false;
            }
            if (!main) {
                std::cout << "Erreur: zone de la main introuvable!" << std::endl;
                return false;
            }

            for (const auto& paire : champions->getCartes()) {
                const Carte* carte = paire.first;
                if (source && source->getId() == carte->getId()) {
                    continue; // Ignorer la carte source
                }
                if (carte->getFaction() == FactionCarte::JAUNE) {
                    return true; // Condition remplie
                }
            }
            for (const auto& paire : main->getCartes()) {
                const Carte* carte = paire.first;
                if (source && source->getId() == carte->getId()) {
                    continue; // Ignorer la carte source
                }
                if (carte->getFaction() == FactionCarte::JAUNE) {
                    return true; // Condition remplie
                }
            }
            return false; // Aucun allié jaune trouvé
        }
        case ConditionEffet::VERT_ALLY:{
            const ZoneDeCarte* champions = joueurActif.getZoneByType(TypeZone::CHAMPIONS);
            const ZoneDeCarte* main = joueurActif.getZoneByType(TypeZone::MAIN);
            if (!champions) {
                std::cout << "Erreur: zone des champions introuvable!" << std::endl;
                return false;
            }
            if (!main) {
                std::cout << "Erreur: zone de la main introuvable!" << std::endl;
                return false;
            }

            for (const auto& paire : champions->getCartes()) {
                const Carte* carte = paire.first;
                if (source && source->getId() == carte->getId()) {
                    continue; // Ignorer la carte source
                }
                if (carte->getFaction() == FactionCarte::VERT) {
                    return true; // Condition remplie
                }
            }
            for (const auto& paire : main->getCartes()) {
                const Carte* carte = paire.first;
                if (source && source->getId() == carte->getId()) {
                    continue; // Ignorer la carte source
                }
                if (carte->getFaction() == FactionCarte::VERT) {
                    return true; // Condition remplie
                }
            }
            return false; // Aucun allié vert trouvé
        }
        case ConditionEffet::BLEU_ALLY:{
            const ZoneDeCarte* champions = joueurActif.getZoneByType(TypeZone::CHAMPIONS);
            const ZoneDeCarte* main = joueurActif.getZoneByType(TypeZone::MAIN);
            if (!champions) {
                std::cout << "Erreur: zone des champions introuvable!" << std::endl;
                return false;
            }
            if (!main) {
                std::cout << "Erreur: zone de la main introuvable!" << std::endl;
                return false;
            }

            for (const auto& paire : champions->getCartes()) {
                const Carte* carte = paire.first;
                if (source && source->getId() == carte->getId()) {
                    continue; // Ignorer la carte source
                }
                if (carte->getFaction() == FactionCarte::BLEU) {
                    return true; // Condition remplie
                }
            }
            for (const auto& paire : main->getCartes()) {
                const Carte* carte = paire.first;
                if (source && source->getId() == carte->getId()) {
                    continue; // Ignorer la carte source
                }
                if (carte->getFaction() == FactionCarte::BLEU) {
                    return true; // Condition remplie
                }
            }
            return false; // Aucun allié bleu trouvé
        }
        default:
            return false;
    }
    return false;
}