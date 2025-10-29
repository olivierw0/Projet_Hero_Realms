#include "table_partie.h"
#include "joueur.h"
#include "carte.h"
#include "champion.h"
#include "effet.h"
#include "carte_db.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <cstdlib>
#include <map>
#include <string>

// =====================================================
// CONSTRUCTEUR / DESTRUCTEUR
// =====================================================

TablePartie::TablePartie(int id, int nb_gemmes) 
    : id(id), nb_gemmes(nb_gemmes), joueur_actuel_index(0),
      idx_marche(-1), idx_deck_marche(-1), idx_gemmes_feu(-1), idx_cartes_ecartees(-1) {
    #ifdef DEBUG
        std::cout << "Construction de la table de partie" << std::endl;
    #endif
}

TablePartie::~TablePartie() {
    joueurs.clear();
    zones_communes.clear();
    #ifdef DEBUG
        std::cout << "Destruction de la table de partie" << std::endl;
    #endif
}

// Méthodes Publiques
void TablePartie::initPartie() {
    std::cout << "\n=== Initialisation de la partie ===" << std::endl;
    
    // TODO : Demander les noms des joueurs
    ajouterJoueur(Joueur(1, 50));
    ajouterJoueur(Joueur(2, 50));

    // 1. Initialiser toutes les zones
    initZones();
    
    // 2. Initialiser le marché avec les cartes
    std::cout << "Initialisation du marché..." << std::endl;
    initMarche();
    
    // 3. Initialiser les decks et distribuer les cartes initiales
    std::cout << "Initialisation des decks et distribution des cartes..." << std::endl;
    int i = 0;
    for (auto& joueur : joueurs) {
        
        std::cout << "\nJoueur " << joueur.getId() << ":" << std::endl;
        joueur.initDeck(); // Ajouter les cartes de base au deck
        joueur.melangerDeck(); // Mélanger le deck
        joueur.piocher((3+i)<=5?3+i:5); // Piocher 3+i cartes
        i++;
        std::cout << "Deck: " << joueur.getZoneByType(TypeZone::DECK)->taille() << " cartes" << std::endl;
        std::cout << "Main: " << joueur.getNombreCartesEnMain() << " cartes" << std::endl;
    }
    // le premier joueur commence normalement avec 3 puis le deuxieme avec 4 
    // et a partir du 3e 5 cartes 
    std::cout << "\n=== Partie prête à commencer ===" << std::endl;
}
void TablePartie::afficherEtatPartie() const {
    #ifndef DEBUG
        clearTerminal();
    #endif

    if (joueurs.empty()) {
        std::cout << "Aucun joueur dans la partie." << std::endl;
        return;
    }

    const Joueur& joueur_actuel = joueurs[joueur_actuel_index];
    const Joueur& ennemi = joueurs[(joueur_actuel_index + 1) % joueurs.size()];

    // === JOUEUR ACTUEL ===
        // === JOUEUR ACTUEL ===
    std::cout << "\n" << BOLD_TEXT << "╔═══════════════ JOUEUR " << joueur_actuel.getId() << " ═══════════════╗" << RESET_COLOR << std::endl;
    std::cout << "PV: " << COLOR_HEALTH << joueur_actuel.getPv() << RESET_COLOR << " | ";
    std::cout << "OR: " << COLOR_OR << joueur_actuel.getOr() << " 💰" << RESET_COLOR << " | ";
    std::cout << "DMG: " << COLOR_DMG << joueur_actuel.getCombat() << " ⚔" << RESET_COLOR << std::endl;
    std::cout << BOLD_TEXT << "╚════════════════════════════════════════╝" << RESET_COLOR << std::endl;
    
    // === PV ENNEMI ===
    std::cout << "\n" << BOLD_TEXT << "═══ ENNEMI ═══" << RESET_COLOR << std::endl;
    std::cout << "Joueur " << ennemi.getId() << " - PV: " << COLOR_HEALTH << ennemi.getPv() << RESET_COLOR << std::endl;

    // === CHAMPIONS DU JOUEUR ===
    std::cout << "\n" << BOLD_TEXT << "═══ CHAMPIONS ═══" << RESET_COLOR << std::endl;
    afficherZoneJoueur(joueur_actuel, TypeZone::CHAMPIONS, true);

    // === CHAMPIONS ENNEMIS ===
    std::cout << "\n" << BOLD_TEXT << "═══ CHAMPIONS ENNEMIS ═══" << RESET_COLOR << std::endl;
    afficherZoneJoueur(ennemi, TypeZone::CHAMPIONS, true);
    
    // === CARTES MARCHÉ ===
    afficherMarche();

    // === DÉFAUSSE ===
    std::cout << "\n" << DIM_TEXT << "═══ DÉFAUSSE (" << joueur_actuel.getZoneByType(TypeZone::DEFAUSSE)->taille() << " cartes) ═══" << RESET_COLOR << std::endl;
    std::cout << "..." << std::endl;

    // === DÉFAUSSE ENNEMIE ===
    std::cout << "\n" << DIM_TEXT << "═══ DÉFAUSSE ENNEMIE (" << ennemi.getZoneByType(TypeZone::DEFAUSSE)->taille() << " cartes) ═══" << RESET_COLOR << std::endl;
    std::cout << "..." << std::endl;

    // === CARTES ÉCARTÉES ===
    std::cout << "\n" << DIM_TEXT << "═══ CARTES ÉCARTÉES ═══" << RESET_COLOR << std::endl;
    std::cout << "..." << std::endl;

        // === MAIN DU JOUEUR (AJOUTÉ ICI) ===
    std::cout << "\n" << BOLD_TEXT << "═══ MAIN ═══" << RESET_COLOR << std::endl;
    afficherZoneJoueur(joueur_actuel, TypeZone::MAIN, false);
}
bool TablePartie::acheterCarteMarche(int indice, Joueur& acheteur) {
    // Cas spécial : indice 6 = Fire Gem
    if (indice == 6) {
        if (idx_gemmes_feu < 0 || idx_gemmes_feu >= zones_communes.size()) {
            std::cout << "Erreur: zone gemmes non initialisée!" << std::endl;
            return false;
        }
        
        // Vérifier qu'il reste des gemmes
        if (zones_communes[idx_gemmes_feu].estVide()) {
            std::cout << "Plus de gemmes de feu disponibles!" << std::endl;
            return false;
        }
        
        // Le coût d'une Fire Gem est toujours 2 OR
        const int COUT_FIRE_GEM = 2;
        
        // Vérifier et dépenser l'or
        if (!acheteur.spendOr(COUT_FIRE_GEM)) {
            std::cout << "Pas assez d'or! Coût: " << COUT_FIRE_GEM 
                      << ", Or disponible: " << acheteur.getOr() << std::endl;
            return false;
        }
        
        // Récupérer une gemme de feu
        const auto& cartes = zones_communes[idx_gemmes_feu].getCartes();
        if (cartes.empty()) {
            std::cout << "Erreur: gemme invalide! cartes empty" << std::endl;
            return false;
        }
        if (cartes[0].first == nullptr) {
            std::cout << "Erreur: gemme invalide! carte[0] empty" << std::endl;
            return false;
        }
        
        Carte* gemme = cartes[0].first;
        int id_gemme = gemme->getId();
        
        // Déplacer la gemme vers la défausse du joueur
        ZoneDeCarte* defausse = acheteur.getZoneByType(TypeZone::DEFAUSSE);
        if (!defausse) {
            std::cout << "Erreur: défausse introuvable!" << std::endl;
            acheteur.addOr(COUT_FIRE_GEM); // Rembourser l'or dépensé
            return false;
        }
        
        // Déplacer la gemme achetée
        zones_communes[idx_gemmes_feu].deplacerCarte(id_gemme, *defausse, defausse->taille());
        
        std::cout << "Joueur " << acheteur.getId() << " a acheté: " << gemme->getNom() 
                  << " pour " << COUT_FIRE_GEM << " OR" << std::endl;
        std::cout << "Gemmes restantes: " << zones_communes[idx_gemmes_feu].taille() << std::endl;
        
        return true;
    }
    
    // Cas normal : indices 1-5 pour les cartes du marché
    if (idx_marche < 0 || idx_marche >= zones_communes.size()) {
        std::cout << "Erreur: zone marché non initialisée!" << std::endl;
        return false;
    }
    
    const auto& cartes = zones_communes[idx_marche].getCartes();
    if (indice < 1 || indice > static_cast<int>(cartes.size())) {
        std::cout << "Indice invalide! (1-5 pour marché, 6 pour Fire Gem)" << std::endl;
        return false;
    }
    
    Carte* carte = cartes[indice - 1].first;
    if (!carte) {
        std::cout << "Carte invalide!" << std::endl;
        return false;
    }
    
    // Vérifier et dépenser l'or
    if (!acheteur.spendOr(carte->getCout())) {
        std::cout << "Pas assez d'or! Coût: " << carte->getCout() 
                  << ", Or disponible: " << acheteur.getOr() << std::endl;
        return false;
    }
    
    // Déplacer la carte vers la défausse du joueur
    ZoneDeCarte* defausse = acheteur.getZoneByType(TypeZone::DEFAUSSE);
    if (!defausse) {
        std::cout << "Erreur: défausse introuvable!" << std::endl;
        return false;
    }
    
    // Déplacer la carte achetée
    zones_communes[idx_marche].deplacerCarte(carte->getId(), *defausse, defausse->taille());
    
    std::cout << "Joueur " << acheteur.getId() << " a acheté: " << carte->getNom() 
              << " pour " << carte->getCout() << " OR" << std::endl;
    
    // Réapprovisionner le marché
    remplirMarche();
    
    return true;
}
void TablePartie::endTurn() {
    Joueur& joueur_actuel = getJoueurActuel();
    Joueur& adversaire = getAdversaire();

    // 1. Infliger les dégâts aux champions adverses avec Garde
    std::cout << "\nInfliger les dégâts" << std::endl;
    adversaire.degatsFinTour(joueur_actuel.getCombat());
    
    // 3. Défausser toute la main du joueur actuel
    ZoneDeCarte* main = joueur_actuel.getZoneByType(TypeZone::MAIN);
    ZoneDeCarte* defausse = joueur_actuel.getZoneByType(TypeZone::DEFAUSSE);
    
    if (main && defausse) {
        std::cout << "\nDéfausse de " << main->taille() << " carte(s) restante(s)..." << std::endl;
        
        // Déplacer toutes les cartes de la main vers la défausse
        while (!main->estVide()) {
            const auto& cartes = main->getCartes();
            if (!cartes.empty() && cartes[0].first != nullptr) {
                main->deplacerCarte(cartes[0].first->getId(), *defausse, defausse->taille());
            }
        }
    }
    joueur_actuel.piocher(5);
    joueur_actuel.resetJoueur();
    joueur_actuel_index = (joueur_actuel_index + 1) % joueurs.size();
}

// Getters & Setters
int TablePartie::getId() const { return id; }
int TablePartie::getNbGemmes() const { return nb_gemmes; }
std::vector<Joueur>& TablePartie::getJoueurs() { return joueurs; }
const std::vector<ZoneDeCarte>& TablePartie::getZonesCommunes() const { return zones_communes; }
Joueur& TablePartie::getJoueurActuel() { return joueurs[joueur_actuel_index]; }
Joueur& TablePartie::getAdversaire() { return joueurs[1 - joueur_actuel_index]; }
int TablePartie::getJoueurActuelIndex() const { return joueur_actuel_index; }
ZoneDeCarte* TablePartie::getMarche() { return (idx_marche >= 0 && idx_marche < zones_communes.size()) ? &zones_communes[idx_marche] : nullptr; }
ZoneDeCarte* TablePartie::getDeckMarche() { return (idx_deck_marche >= 0 && idx_deck_marche < zones_communes.size()) ? &zones_communes[idx_deck_marche] : nullptr; }
ZoneDeCarte* TablePartie::getGemmesFeu() { return (idx_gemmes_feu >= 0 && idx_gemmes_feu < zones_communes.size()) ? &zones_communes[idx_gemmes_feu] : nullptr; }
ZoneDeCarte* TablePartie::getCartesEcartees() { return (idx_cartes_ecartees >= 0 && idx_cartes_ecartees < zones_communes.size()) ? &zones_communes[idx_cartes_ecartees] : nullptr; }

// Méthodes Privées
void TablePartie::initZones() {    
    // Réserver la capacité pour les zones communes
    zones_communes.reserve(4);  // 4 zones : MARCHE, DECK_MARCHE, GEMMES_FEU, ECARTEES
    
    // Initialiser les zones communes (construction directe dans le vector)
    creerZoneCommune(100, TypeZone::MARCHE);        // idx 0 - Marché visible (5 cartes)
    creerZoneCommune(101, TypeZone::DECK);          // idx 1 - Pile du marché
    creerZoneCommune(102, TypeZone::MARCHE);        // idx 2 - Gemmes de feu
    creerZoneCommune(103, TypeZone::ECARTEES);      // idx 3 - Cartes écartées
    
    // Définir les indices
    idx_marche = 0;
    idx_deck_marche = 1;
    idx_gemmes_feu = 2;
    idx_cartes_ecartees = 3;
}
void TablePartie::initMarche() {
    // Les zones communes doivent déjà être créées par initZones()
    if (idx_marche < 0 || idx_deck_marche < 0 || idx_gemmes_feu < 0 || idx_cartes_ecartees < 0) {
        std::cout << "ERREUR: Les zones communes n'ont pas été initialisées!" << std::endl;
        return;
    }
    
    // Remplir le deck du marché
    if (idx_deck_marche >= 0 && idx_deck_marche < zones_communes.size()) {
        std::vector<Carte*> deckInitial = creerDeckMarche();
        std::cout << "Ajout de " << deckInitial.size() << " cartes au deck du marché..." << std::endl;
        for (const auto& carte : deckInitial) {
            zones_communes[idx_deck_marche].ajouterCarte(carte, static_cast<int>(zones_communes[idx_deck_marche].taille()));
        }
        
        // Mélanger la pile
        zones_communes[idx_deck_marche].melangerCartes();
        std::cout << "Deck du marché mélangé: " << zones_communes[idx_deck_marche].taille() << " cartes" << std::endl;
    }
    
    // Piocher 5 cartes pour le marché visible
    remplirMarche();
    std::cout << "Marché visible rempli: " << zones_communes[idx_marche].taille() << " cartes" << std::endl;
    
    // Ajouter les gemmes de feu (objets toujours disponibles)
    if (idx_gemmes_feu >= 0 && idx_gemmes_feu < zones_communes.size()) {
        for (int i = 0; i < 16; i++) {
            zones_communes[idx_gemmes_feu].ajouterCarte(getCarteById(i+2001), i);
        }
        std::cout << "Gemmes de feu ajoutées: " << zones_communes[idx_gemmes_feu].taille() << " gemmes" << std::endl;
    }
}

void TablePartie::ajouterJoueur(const Joueur& joueur) { 
    joueurs.push_back(joueur); 
    joueurs.back().setTable(this); // Associer la table au joueur
}
void TablePartie::creerZoneCommune(int id, TypeZone type) {
    zones_communes.emplace_back(id, type, nullptr, this);
}

void TablePartie::afficherZoneJoueur(const Joueur& joueur, TypeZone type_zone, bool est_champion) const {
    int indice = 1; // Pour numéroter les cartes de la main
    int indice_champion = 1; // Pour numéroter les champions
    for (const auto& zone : joueur.getZones()) {
        if (zone.getType() == type_zone) {
            for (const auto& paire_carte : zone.getCartes()) {
                if (paire_carte.first != nullptr) {
                    // Si c'est la main, afficher avec un indice mais SANS le coût
                    if (type_zone == TypeZone::MAIN) {
                        afficherCarteFormatee(paire_carte.first, indice, false); // false = pas de coût
                        indice++;
                    } else if (type_zone == TypeZone::CHAMPIONS) {
                        afficherChampionFormate(static_cast<const Champion*>(paire_carte.first), indice_champion);
                        indice_champion++;
                    } else {
                        afficherCarteFormatee(paire_carte.first, -1, true); // true = avec coût
                    }
                }
            }
            if (zone.getCartes().empty()) {
                std::cout << DIM_TEXT << "  (vide)" << RESET_COLOR << std::endl;
            }
            return;
        }
    }
}
void TablePartie::afficherMarche() const {
    std::cout << "\n" << BOLD_TEXT << "╔════════════════════ MARCHÉ ═══════════════════════╗" << RESET_COLOR << std::endl;
    
    if (idx_marche >= 0 && idx_marche < static_cast<int>(zones_communes.size())) {
        const auto& cartesMarche = zones_communes[idx_marche].getCartes();
        
        for (size_t i = 0; i < cartesMarche.size() && i < 5; ++i) {
            if (cartesMarche[i].first != nullptr) {
                afficherCarteFormatee(cartesMarche[i].first, i + 1, true);
                
                // Ligne de séparation
                if (i < 5) {
                    std::cout << DIM_TEXT << "  ────────────────────────────────────────────────" << RESET_COLOR << std::endl << std::endl;
                }
            }
        }
    }
    
    // Afficher les gemmes de feu
    Carte* gemme = getCarteById(2001);
    if (gemme) {
        afficherCarteFormatee(gemme, 6, true);
    }
    
    if (idx_gemmes_feu >= 0 && idx_gemmes_feu < static_cast<int>(zones_communes.size())) {
        int nb_gemmes = zones_communes[idx_gemmes_feu].taille();
        std::cout << "  " << DIM_TEXT << "[" << nb_gemmes << " restantes]" << RESET_COLOR << std::endl;
    }
    
    std::cout << BOLD_TEXT << "╚═══════════════════════════════════════════════════╝" << RESET_COLOR << "\n" << std::endl;
}
void TablePartie::remplirMarche() {
    if (idx_marche < 0 || idx_deck_marche < 0) return;
    
    // Déplacer des cartes de la pile vers le marché jusqu'à avoir 5 cartes
    while (zones_communes[idx_marche].taille() < 5 && !zones_communes[idx_deck_marche].estVide()) {
        const auto& cartes = zones_communes[idx_deck_marche].getCartes();
        if (!cartes.empty() && cartes[0].first != nullptr) {
            zones_communes[idx_deck_marche].deplacerCarte(cartes[0].first->getId(), zones_communes[idx_marche], zones_communes[idx_marche].taille());
        }
    }
}

// Afficher une carte de manière formatée
void TablePartie::afficherCarteFormatee(const Carte* carte, int indice, bool afficherCout) const {
    if (!carte) return;
    
    const char* couleur = getCouleurFaction(carte->getFaction());
    
    // Ligne d'index (optionnel)
    if (indice >= 0) {
        std::cout << BOLD_TEXT << "[" << indice << "] " << RESET_COLOR;
    }
    
     // Coût (optionnel)
    if (afficherCout) {
        std::cout << "(" << COLOR_OR << carte->getCout() << " 💰" << RESET_COLOR << ") ";
    }
    
    // Nom de la carte
    std::cout << couleur  << carte->getNom() << RESET_COLOR;
    
    // Type et faction
    std::cout << " " << DIM_TEXT << "(" << factionToString(carte->getFaction()) 
              << " • " << typeCarteToString(carte->getType()) << ")" << RESET_COLOR;
    
    // Pour les champions, afficher les PV et le statut Guard
    const Champion* champion = dynamic_cast<const Champion*>(carte);
    if (champion) {
        std::cout << " " << DIM_TEXT << "[";
        if (champion->hasGarde()) {
            std::cout << "🛡️ ";
        }
        std::cout << champion->getPV() << " PV]" << RESET_COLOR;
    }
    
    std::cout << std::endl;
    
    // Effets formatés
    std::string effetsFormated = formaterListeEffets(carte->getEffets());
    std::cout << "  " << effetsFormated << std::endl;
}
void TablePartie::afficherChampionFormate(const Champion* champion, int indice) const {
    if (!champion) return;
    
    const char* couleur = getCouleurFaction(champion->getFaction());
    
    // Ligne d'index
    if (indice >= 0) {
        std::cout << BOLD_TEXT << "[" << indice << "] " << RESET_COLOR;
    }
    
    // Statut (Actif/Inactif)
    if (champion->getActive()) {
        std::cout << "✅ ";
    } else {
        std::cout << DIM_TEXT << "💤 " << RESET_COLOR;
    }
    
    // Nom du champion (coloré selon faction)
    std::cout << couleur << BOLD_TEXT << champion->getNom() << RESET_COLOR;
    
    // PV en GRAND et AVANT
    std::cout << " " << BOLD_TEXT << "[" << COLOR_HEALTH << champion->getPV() << " ❤ " << RESET_COLOR << BOLD_TEXT << "]" << RESET_COLOR;
    
    // Garde (si applicable)
    if (champion->hasGarde()) {
        std::cout << " " << BOLD_TEXT << "🛡️ GARDE" << RESET_COLOR;
    }
    
    // Type et faction (en petit)
    std::cout << " " << DIM_TEXT << "(" << factionToString(champion->getFaction()) << ")" << RESET_COLOR;
    
    std::cout << std::endl;
    
    // Effets (uniquement si actif ou pour information)
    if (champion->getActive()) {
        std::string effetsFormated = formaterListeEffets(champion->getEffets());
        std::cout << "  " << effetsFormated << std::endl;
    } else {
        std::cout << "  " << DIM_TEXT << "(Champion inactif - ne peut pas être activé ce tour)" << RESET_COLOR << std::endl;
    }
}

// =====================================================
// MÉTHODES DE FORMATAGE 
// =====================================================

// Formater un type d'effet avec sa valeur
std::string TablePartie::formaterTypeEffet(TypeEffet type, int valeur) const {
    std::string result;
    
    switch(type) {
        case TypeEffet::OR:
            result = std::string(COLOR_OR) + "💰 +" + std::to_string(valeur) + " OR" + RESET_COLOR;
            break;
            
        case TypeEffet::DMG:
            result = std::string(COLOR_DMG) + "⚔  +" + std::to_string(valeur) + " Combat" + RESET_COLOR;
            break;
            
        case TypeEffet::SOIN:
            result = std::string(COLOR_HEALTH) + "❤  +" + std::to_string(valeur) + " Santé" + RESET_COLOR;
            break;
            
        case TypeEffet::PIOCHE:
            result = std::string(COLOR_CARD) + "📖 Piocher " + std::to_string(valeur) + 
                    (valeur > 1 ? " cartes" : " carte") + RESET_COLOR;
            break;
            
        case TypeEffet::STUN:
            result = "😵 Étourdir un champion";
            break;
            
        case TypeEffet::FORCE_DISCARD_OPPONENT:
            result = "🎯 Adversaire défausse " + std::to_string(valeur) + 
                    (valeur > 1 ? " cartes" : " carte");
            break;
            
        case TypeEffet::EXPEND_CHAMPION:
            result = std::string(DIM_TEXT) + "⟳ Taper:" + RESET_COLOR;
            break;
            
        case TypeEffet::PREPARE_CHAMPION:
            result = "🔄 Préparer un champion";
            break;
            
        case TypeEffet::SACRIFICE_HAND_DISCARD:
            result = std::string(COLOR_SACRIFICE) + "✝  Sacrifier jusqu'à " + std::to_string(valeur) + 
                    " carte(s) (main/défausse)" + RESET_COLOR;
            break;
            
        case TypeEffet::DRAW_DISCARD:
            result = std::string(COLOR_CARD) + "📖 Piocher jusqu'à " + std::to_string(valeur) + 
                    " carte(s), puis défausser autant" + RESET_COLOR;
            break;
            
        case TypeEffet::TOP_DECK_FROM_DISCARD:
            result = "♻️ Carte de défausse → dessus du deck";
            break;
            
        case TypeEffet::TOP_DECK_NEXT_ACQUIRED:
            result = "⬆️ Prochaine carte acquise → dessus du deck";
            break;
            
        case TypeEffet::TOP_DECK_NEXT_ACQUIRED_ACTION:
            result = "⬆️ Prochaine ACTION acquise → dessus du deck";
            break;
            
        case TypeEffet::HAND_NEXT_ACQUIRED:
            result = "👋 Prochaine carte acquise → main";
            break;
            
        case TypeEffet::DMG_ou_SOIN:
            result = std::string(COLOR_DMG) + "⚔  +3 Combat" + RESET_COLOR + 
                    " " + ITALIC_TEXT + "ou" + RESET_COLOR + " " +
                    std::string(COLOR_HEALTH) + "❤  +4 Santé" + RESET_COLOR;
            break;
            
        case TypeEffet::OR_ou_nDMG:
            result = std::string(COLOR_OR) + "💰 +1 OR" + RESET_COLOR + 
                    " " + ITALIC_TEXT + "ou" + RESET_COLOR + " " +
                    std::string(COLOR_DMG) + "⚔  +" + std::to_string(valeur) + " Combat" + RESET_COLOR;
            break;
            
        case TypeEffet::OR_ou_SOIN_per_CHAMP:
            result = std::string(COLOR_OR) + "💰 +" + std::to_string(valeur) + " OR" + RESET_COLOR + 
                    " " + ITALIC_TEXT + "ou" + RESET_COLOR + " " +
                    std::string(COLOR_HEALTH) + "❤  +" + std::to_string(valeur) + " Santé/Champion" + RESET_COLOR;
            break;
            
        case TypeEffet::SOIN_per_CHAMP:
            result = std::string(COLOR_HEALTH) + "❤  +" + std::to_string(valeur) + " Santé par champion" + RESET_COLOR;
            break;
            
        default:
            result = "❓ Effet inconnu";
            break;
    }
    
    return result;
}

// Formater une condition d'effet
std::string TablePartie::formaterCondition(ConditionEffet condition) const {
    switch(condition) {
        case ConditionEffet::AUCUNE:
            return "";
            
        case ConditionEffet::JAUNE_ALLY:
            return std::string(COLOR_JAUNE) + "★ Allié IMPÉRIAL:" + RESET_COLOR;

        case ConditionEffet::BLEU_ALLY:
            return std::string(COLOR_BLEU) + "★ Allié GUILDE:" + RESET_COLOR;
            
        case ConditionEffet::ROUGE_ALLY:
            return std::string(COLOR_ROUGE) + "★ Allié NÉCRO:" + RESET_COLOR;

        case ConditionEffet::VERT_ALLY:
            return std::string(COLOR_VERT) + "★ Allié SAUVAGE:" + RESET_COLOR;
            
        case ConditionEffet::SACRIFICE:
            return std::string(COLOR_SACRIFICE) + "✝  Sacrifier:" + RESET_COLOR;
        case ConditionEffet::SACRIFICE_TO_MARCHE:
            return std::string(COLOR_SACRIFICE) + "✝  Sacrifier:" + RESET_COLOR;
        case ConditionEffet::COND_SACRIFICE_HAND_DISCARD:
            return std::string(COLOR_SACRIFICE) + "✝  Sacrifier jusqu'à 1 carte(s) (main ou défausse) :" ;
        case ConditionEffet::NB_CHAMPIONS:
            return std::string(DIM_TEXT) + "(par champion en jeu)" + RESET_COLOR;
            
        case ConditionEffet::NB_GARDES:
            return std::string(DIM_TEXT) + "(par garde en jeu)" + RESET_COLOR;
            
        case ConditionEffet::NB_VERT_CARDS_IN_PLAY:
            return std::string(DIM_TEXT) + "(par carte " + COLOR_VERT + "SAUVAGE" + RESET_COLOR + DIM_TEXT + " en jeu)" + RESET_COLOR;
            
        default:
            return "";
    }
}

// Formater un effet complet avec sa condition
std::string TablePartie::formaterEffet(const Effet& effet, bool avecCondition) const {
    std::string result;
    
    if (avecCondition && effet.getCondition() != ConditionEffet::AUCUNE) {
        result = formaterCondition(effet.getCondition()) + " ";
    }

    result += formaterTypeEffet(effet.getType(), effet.getValeur());

    return result;
}

// Formater une liste d'effets en les regroupant par condition
std::string TablePartie::formaterListeEffets(const std::vector<Effet>& effets) const {
    std::string result;
    std::map<ConditionEffet, std::vector<Effet>> effetsParCondition;
    
    for (const auto& effet : effets) {
        if (effet.getType() != TypeEffet::EXPEND_CHAMPION) {
            effetsParCondition[effet.getCondition()].push_back(effet);
        }
    }
    
    if (effetsParCondition.count(ConditionEffet::AUCUNE) > 0) {
        for (const auto& effet : effetsParCondition[ConditionEffet::AUCUNE]) {
            if (!result.empty()) result += " • ";
            result += formaterEffet(effet, false);
        }
        effetsParCondition.erase(ConditionEffet::AUCUNE);
    }
    
    for (const auto& [condition, effetsGroupe] : effetsParCondition) {
        if (!result.empty()) {
            result += "\n  " + std::string(DIM_TEXT) + "─────────────" + RESET_COLOR + "\n  ";
        }
        
        result += formaterCondition(condition);
        
        for (size_t i = 0; i < effetsGroupe.size(); ++i) {
            if (i == 0) result += " ";
            else result += " • ";
            result += formaterTypeEffet(effetsGroupe[i].getType(), effetsGroupe[i].getValeur());
        }
    }
    
    return result;
}

// Helper pour obtenir la couleur de faction
const char* TablePartie::getCouleurFaction(FactionCarte faction) const {
    switch(faction) {
        case FactionCarte::JAUNE: return COLOR_JAUNE;
        case FactionCarte::BLEU: return COLOR_BLEU;
        case FactionCarte::ROUGE: return COLOR_ROUGE;
        case FactionCarte::VERT: return COLOR_VERT;
        case FactionCarte::NEUTRE: return COLOR_GRIS;
        default: return RESET_COLOR;
    }
}

// Helper pour convertir faction en string
std::string TablePartie::factionToString(FactionCarte faction) const {
    switch(faction) {
        case FactionCarte::JAUNE: return "IMPÉRIAL";
        case FactionCarte::BLEU: return "GUILDE";
        case FactionCarte::ROUGE: return "NÉCRO";
        case FactionCarte::VERT: return "SAUVAGE";
        case FactionCarte::NEUTRE: return "NEUTRE";
        default: return "INCONNU";
    }
}

// Helper pour convertir type de carte en string
std::string TablePartie::typeCarteToString(TypeCarte type) const {
    switch(type) {
        case TypeCarte::ACTION: return "ACTION";
        case TypeCarte::OBJET: return "OBJET";
        case TypeCarte::CHAMPION: return "CHAMPION";
        default: return "INCONNU";
    }
}



void TablePartie::afficherDeckMarche() const {
    
    #ifndef DEBUG
        clearTerminal();
    #endif

    if (idx_deck_marche < 0 || idx_deck_marche >= zones_communes.size()) {
        std::cout << "Erreur: deck marché introuvable!" << std::endl;
        return;
    }
    
    const auto& cartes = zones_communes[idx_deck_marche].getCartes();
    
    std::cout << "\n" << BOLD_TEXT << "═══════════════ DECK DU MARCHÉ ═══════════════" << RESET_COLOR << std::endl;
    std::cout << "Total de cartes: " << cartes.size() << std::endl;
    std::cout << DIM_TEXT << "──────────────────────────────────────────────" << RESET_COLOR << std::endl;
    
    int numero = 1;
    for (const auto& paire_carte : cartes) {
        if (paire_carte.first) {
            Carte* carte = paire_carte.first;
            const char* couleur = getCouleurFaction(carte->getFaction());
            
            std::cout << "[" << numero << "] ID:" << carte->getId() << " - "
                      << couleur << BOLD_TEXT << carte->getNom() << RESET_COLOR
                      << " - " << factionToString(carte->getFaction()) << std::endl;
            numero++;
        }
    }
    
    std::cout << DIM_TEXT << "══════════════════════════════════════════════" << RESET_COLOR << "\n" << std::endl;
}

bool TablePartie::piocheCarteSpecifique(int idCarte, Joueur& joueur) {
    if (!joueur.isGodMode()) {
        std::cout << "Erreur: Cette commande est réservée au GOD MODE!" << std::endl;
        return false;
    }
    
    if (idx_deck_marche < 0 || idx_deck_marche >= zones_communes.size()) {
        std::cout << "Erreur: deck marché introuvable!" << std::endl;
        return false;
    }
    
    ZoneDeCarte* deck = &zones_communes[idx_deck_marche];
    ZoneDeCarte* defausse = joueur.getZoneByType(TypeZone::DEFAUSSE);
    ZoneDeCarte* main = joueur.getZoneByType(TypeZone::MAIN);

    if (!defausse || !main) {
        std::cout << "Erreur: défausse ou main introuvable!" << std::endl;
        return false;
    }
    
    // Chercher la carte par ID
    const auto& cartes = deck->getCartes();
    for (const auto& paire_carte : cartes) {
        if (paire_carte.first && paire_carte.first->getId() == idCarte) {
            Carte* carte = paire_carte.first;

            // Déplacer vers la main du joueur
            deck->deplacerCarte(idCarte, *main, main->taille());

            std::cout << "[GOD MODE] Carte " << carte->getNom()
                      << " (ID:" << idCarte << ") ajoutée à votre main!" << std::endl;
            return true;
        }
    }
    
    std::cout << "Carte avec l'ID " << idCarte << " introuvable dans le deck!" << std::endl;
    return false;
}