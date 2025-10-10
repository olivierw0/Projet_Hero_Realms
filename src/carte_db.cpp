#include "carte.h"
#include "champion.h"
#include "effet.h"
#include <vector>

// ========== BASE DE DONNEES DES CARTES HERO REALMS ==========

// ========== CARTES JAUNES (IMPERIALES) ==========

Carte close_ranks = {
    .id = 1,
    .nom = "Close Ranks",
    .cout = 3,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::JAUNE,
    .description = "Gain 2 gold. Gain 3 combat. Gain 4 health. Draw a card",
    .effets = { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::DMG, 3), Effet(3, TypeEffet::SOIN, 4), Effet(4, TypeEffet::PIOCHE, 1) }
};

// PAS VERIFIE /!\ RIEN N'EST BON
Carte command = {
    .id = 2,
    .nom = "Command",
    .cout = 5,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::JAUNE,
    .description = "Gain 5 combat. Gain 5 health",
    .effets = { Effet(1, TypeEffet::DMG, 5), Effet(2, TypeEffet::SOIN, 5) }
};

Carte domination = {
    .id = 3,
    .nom = "Domination",
    .cout = 6,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::JAUNE,
    .description = "Gain 9 combat. Gain 9 health",
    .effets = { Effet(1, TypeEffet::DMG, 9), Effet(2, TypeEffet::SOIN, 9) }
};

Carte rally_the_troops = {
    .id = 4,
    .nom = "Rally the Troops",
    .cout = 4,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::JAUNE,
    .description = "Gain 5 combat. Gain 5 health",
    .effets = { Effet(1, TypeEffet::DMG, 5), Effet(2, TypeEffet::SOIN, 5) }
};

Carte recruit = {
    .id = 5,
    .nom = "Recruit",
    .cout = 2,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::JAUNE,
    .description = "Gain 2 gold. Gain 1 health",
    .effets = { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::SOIN, 1) }
};

Carte taxation = {
    .id = 6,
    .nom = "Taxation",
    .cout = 1,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::JAUNE,
    .description = "Gain 2 gold",
    .effets = { Effet(1, TypeEffet::OR, 2) }
};

Carte tithe = {
    .id = 7,
    .nom = "Tithe",
    .cout = 3,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::JAUNE,
    .description = "Gain 3 gold",
    .effets = { Effet(1, TypeEffet::OR, 3) }
};

Carte word_of_power = {
    .id = 8,
    .nom = "Word of Power",
    .cout = 6,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::JAUNE,
    .description = "Draw two cards",
    .effets = { Effet(1, TypeEffet::PIOCHE, 2) }
};

// ========== CARTES BLEUES (GUILDE) ==========

Carte fire_bomb = {
    .id = 9,
    .nom = "Fire Bomb",
    .cout = 6,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::BLEU,
    .description = "Gain 5 combat. Target opponent. Draw a card. Sacrifice: Gain 6 combat",
    .effets = { Effet(1, TypeEffet::DMG, 5), Effet(2, TypeEffet::PIOCHE, 1), Effet(3, TypeEffet::DMG, 6, ConditionEffet::SACRIFICE) }
};

Carte influence = {
    .id = 10,
    .nom = "Influence",
    .cout = 1,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::BLEU,
    .description = "Gain 2 gold",
    .effets = { Effet(1, TypeEffet::OR, 2) }
};

// ========== CARTES ROUGES (NECROS) ==========

Carte dark_reward = {
    .id = 11,
    .nom = "Dark Reward",
    .cout = 5,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::ROUGE,
    .description = "Gain 3 gold",
    .effets = { Effet(1, TypeEffet::OR, 3) }
};

Carte influence_rouge = {
    .id = 12,
    .nom = "Influence",
    .cout = 2,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::ROUGE,
    .description = "Gain 3 gold. Sacrifice: Gain 3 combat",
    .effets = { Effet(1, TypeEffet::OR, 3), Effet(2, TypeEffet::DMG, 3, ConditionEffet::SACRIFICE) }
};

// ========== CARTES VERTES (SAUVAGES) ==========

Carte natures_bounty = {
    .id = 13,
    .nom = "Nature's Bounty",
    .cout = 4,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::VERT,
    .description = "Gain 4 gold",
    .effets = { Effet(1, TypeEffet::OR, 4) }
};

Carte death_threat = {
    .id = 14,
    .nom = "Death Threat",
    .cout = 3,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::VERT,
    .description = "Gain 1 combat. Assassin",
    .effets = { Effet(1, TypeEffet::DMG, 1) }
};

// ========== CHAMPIONS ROUGES ==========

// Note: Les Champions nécessitent une syntaxe différente, utilisons des Cartes avec type CHAMPION
Carte tyrannus_the_destroyer = {
    .id = 101,
    .nom = "Tyrannus, the Destroyer",
    .cout = 8,
    .type = TypeCarte::CHAMPION,
    .faction = FactionCarte::ROUGE,
    .description = "Expend: Gain 4 combat",
    .effets = { Effet(1, TypeEffet::DMG, 4) }
};

Carte arkus_imperial_dragon = {
    .id = 102,
    .nom = "Arkus, Imperial Dragon",
    .cout = 5,
    .type = TypeCarte::CHAMPION,
    .faction = FactionCarte::JAUNE,
    .description = "Expend: Gain 5 combat. Draw a card",
    .effets = { Effet(1, TypeEffet::DMG, 5), Effet(2, TypeEffet::PIOCHE, 1) }
};

Carte broelyn_loreweaver = {
    .id = 103,
    .nom = "Broelyn Loreweaver",
    .cout = 4,
    .type = TypeCarte::CHAMPION,
    .faction = FactionCarte::VERT,
    .description = "Expend: Gain 2 gold",
    .effets = { Effet(1, TypeEffet::OR, 2) }
};

Carte spark_giant = {
    .id = 104,
    .nom = "Spark Giant",
    .cout = 7,
    .type = TypeCarte::CHAMPION,
    .faction = FactionCarte::JAUNE,
    .description = "Expend: Gain 6 combat",
    .effets = { Effet(1, TypeEffet::DMG, 6) }
};

Carte parov_the_enforcer = {
    .id = 105,
    .nom = "Parov, the Enforcer",
    .cout = 5,
    .type = TypeCarte::CHAMPION,
    .faction = FactionCarte::BLEU,
    .description = "Expend: Gain 3 combat",
    .effets = { Effet(1, TypeEffet::DMG, 3) }
};

Carte krythos_master_vampire = {
    .id = 106,
    .nom = "Krythos, Master Vampire",
    .cout = 5,
    .type = TypeCarte::CHAMPION,
    .faction = FactionCarte::ROUGE,
    .description = "Expend: Gain 3 health",
    .effets = { Effet(1, TypeEffet::SOIN, 3) }
};

Carte myros_thin_mage = {
    .id = 107,
    .nom = "Myros, Thin Mage",
    .cout = 5,
    .type = TypeCarte::CHAMPION,
    .faction = FactionCarte::BLEU,
    .description = "Expend: Gain 3 gold",
    .effets = { Effet(1, TypeEffet::OR, 3) }
};

Carte rayla_endweaver = {
    .id = 108,
    .nom = "Rayla Endweaver",
    .cout = 4,
    .type = TypeCarte::CHAMPION,
    .faction = FactionCarte::ROUGE,
    .description = "Expend: Gain 3 combat",
    .effets = { Effet(1, TypeEffet::DMG, 3) }
};

// ========== OBJETS ==========

Carte fire_gem = {
    .id = 201,
    .nom = "Fire Gem",
    .cout = 2,
    .type = TypeCarte::OBJET,
    .faction = FactionCarte::NEUTRE,
    .description = "Gain 2 gold. Sacrifice: Gain 3 combat",
    .effets = { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::DMG, 3, ConditionEffet::SACRIFICE) }
};

Carte ruby = {
    .id = 202,
    .nom = "Ruby",
    .cout = 2,
    .type = TypeCarte::OBJET,
    .faction = FactionCarte::NEUTRE,
    .description = "Gain 2 gold",
    .effets = { Effet(1, TypeEffet::OR, 2) }
};

Carte dagger = {
    .id = 203,
    .nom = "Dagger",
    .cout = 0,
    .type = TypeCarte::OBJET,
    .faction = FactionCarte::NEUTRE,
    .description = "Gain 1 combat",
    .effets = { Effet(1, TypeEffet::DMG, 1) }
};

Carte shortsword = {
    .id = 204,
    .nom = "Shortsword",
    .cout = 0,
    .type = TypeCarte::OBJET,
    .faction = FactionCarte::NEUTRE,
    .description = "Gain 2 combat",
    .effets = { Effet(1, TypeEffet::DMG, 2) }
};

// ========== CARTES DE BASE (DECK INITIAL) ==========

Carte gold = {
    .id = 300,
    .nom = "Gold",
    .cout = 0,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::NEUTRE,
    .description = "Gain 1 gold",
    .effets = { Effet(1, TypeEffet::OR, 1) }
};

// ========== TABLEAU DES CARTES AVEC QUANTITES ==========

struct CarteAvecQuantite {
    Carte carte;
    int quantite;
};

// Base de données complète avec quantités
std::vector<CarteAvecQuantite> database_cartes = {
    // Cartes de base (deck initial)
    {gold, 7},          // 7 cartes Or par joueur
    {dagger, 1},        // 1 dagues par joueur
    {shortsword, 1},   // 1 Épées courtes
    {ruby, 1},         // 1 Rubis

    // Marché - Cartes toujours disponibles
    {fire_gem, 16},     // 16 Gemmes de feu
    
    // Cartes Jaunes (Impériales)
    {close_ranks, 2},
    {command, 2},
    {domination, 1},
    {rally_the_troops, 2},
    {recruit, 2},
    {taxation, 2},
    {tithe, 2},
    {word_of_power, 1},
    
    // Cartes Bleues (Guilde)
    {fire_bomb, 1},
    {influence, 2},
    
    // Cartes Rouges (Nécros)
    {dark_reward, 1},
    {influence_rouge, 2},
    
    // Cartes Vertes (Sauvages)
    {natures_bounty, 2},
    {death_threat, 2},
    
    // Champions
    {tyrannus_the_destroyer, 1},
    {arkus_imperial_dragon, 1},
    {broelyn_loreweaver, 1},
    {spark_giant, 1},
    {parov_the_enforcer, 1},
    {krythos_master_vampire, 1},
    {myros_thin_mage, 1},
    {rayla_endweaver, 1}
};

// ========== FONCTIONS D'ACCES ==========

// Obtenir une carte par son ID
const Carte* getCarteById(int id) {
    for (const auto& item : database_cartes) {
        if (item.carte.getId() == id) {
            return &item.carte;
        }
    }
    return nullptr;
}

// Obtenir une carte par son nom
const Carte* getCarteByName(const std::string& nom) {
    for (const auto& item : database_cartes) {
        if (item.carte.getNom() == nom) {
            return &item.carte;
        }
    }
    return nullptr;
}

// Obtenir la quantité d'une carte
int getQuantiteById(int id) {
    for (const auto& item : database_cartes) {
        if (item.carte.getId() == id) {
            return item.quantite;
        }
    }
    return 0;
}


// Créer un deck de base pour un joueur (8 Or + 2 Dagues)
std::vector<const Carte*> creerDeckDeBase() {
    std::vector<const Carte*> deck;
    
    // Ajouter 7 cartes Or
    for (int i = 0; i < 7; i++) {
        deck.push_back(&gold);
    }
    
    // Ajouter 1 dague, 1 ruby et 1 shortsword
    deck.push_back(&dagger);
    deck.push_back(&ruby);
    deck.push_back(&shortsword);
    
    
    return deck;
}