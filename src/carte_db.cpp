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
    .description = "Gain 5 Combat",
    .effets = { Effet(1, TypeEffet::DMG, 5) }
};

Carte command = {
    .id = 2,
    .nom = "Command",
    .cout = 5,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::JAUNE,
    .description = "{Gain 2 gold} {Gain 3 combat} {Gain 4 health} {Piochez une carte}.",
    .effets = { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::DMG, 3), Effet(3, TypeEffet::SOIN, 4), Effet(4, TypeEffet::PIOCHE, 1) }
};

Carte domination = {
    .id = 3,
    .nom = "Domination",
    .cout = 7,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::JAUNE,
    .description = "Gain 6 combat. Gain 6 health",
    .effets = { Effet(1, TypeEffet::DMG, 6), Effet(2, TypeEffet::SOIN, 6) }
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

// 3 cartes
Carte recruit = {
    .id = 5,
    .nom = "Recruit",
    .cout = 2,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::JAUNE,
    .description = "Gain 2 gold. Gain 3 health",
    .effets = { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::SOIN, 3) }
};

// 3 Cartes
Carte taxation = {
    .id = 6,
    .nom = "Taxation",
    .cout = 1,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::JAUNE,
    .description = "Gain 2 gold",
    .effets = { Effet(1, TypeEffet::OR, 2) }
};

Carte word_of_power = {
    .id = 7,
    .nom = "Word of Power",
    .cout = 6,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::JAUNE,
    .description = "Draw two cards",
    .effets = { Effet(1, TypeEffet::PIOCHE, 2) }
};

Carte arkus_imperial_dragon = {
    .id = 8,
    .nom = "Arkus, Imperial Dragon",
    .cout = 8,
    .type = TypeCarte::CHAMPION,
    .garde = true,
    .pv = 6,
    .faction = FactionCarte::JAUNE,
    .description = "{Expend}: {Gain 5 combat} Draw a card. {Jaune Ally}: {Gain 6 health}",
    .effets = { Effet(1, TypeEffet::DMG, 5), Effet(2, TypeEffet::PIOCHE, 1), Effet(3, TypeEffet::SOIN, 6, ConditionEffet::JAUNE_ALLY) }
};

////////////////////////////////////////////
/// OR
////////////////////////////////////////////
Carte darian_war_mage = {
    .id = 9,
    .nom = "Darian, War Mage",
    .cout = 4,
    .type = TypeCarte::CHAMPION,
    .faction = FactionCarte::JAUNE,
    .description = "{Expend}: {Gain 3 combat} <i>or</i> {Gain 4 health}",
    .effets = { Effet(1, TypeEffet::DMG, 3), Effet(2, TypeEffet::SOIN, 4) }
};

Carte master_weyan = {
    .id = 10,
    .nom = "Master Weyan",
    .cout = 4,
    .type = TypeCarte::CHAMPION,
    .pv = 4,
    .garde = true,
    .faction = FactionCarte::JAUNE,
    .description = "{Expend}: {Gain 3 combat} +{1 combat} for each other champion you have in play.",
    .effets = { Effet(1, TypeEffet::DMG, 3), Effet(2, TypeEffet::DMG, 1, ConditionEffet::NB_CHAMPIONS) }
};

Carte cristov_the_just = {
    .id = 11,
    .nom = "Cristov, the Just",
    .cout = 5,
    .type = TypeCarte::CHAMPION,
    .pv = 5,
    .garde = true,
    .faction = FactionCarte::JAUNE,
    .description = "{Expend}: {Gain 2 combat} {Gain 3 health} <hr> {Jaune Ally}: Draw a card.",
    .effets = { Effet(1, TypeEffet::DMG, 2), Effet(2, TypeEffet::SOIN, 3), Effet(3, TypeEffet::PIOCHE, 1, ConditionEffet::JAUNE_ALLY) }
};

Carte kraka_high_priest = {
    .id = 12,
    .nom = "Kraka, High Priest",
    .cout = 6,
    .type = TypeCarte::CHAMPION,
    .pv = 6,
    .faction = FactionCarte::JAUNE,
    .description = "{Expend}: {Gain 2 health} Draw a card. <hr> {Jaune Ally}: Gain {2 health} for each champion you have in play.",
    .effets = { Effet(1, TypeEffet::SOIN, 2), Effet(2, TypeEffet::PIOCHE, 1), Effet(3, TypeEffet::SOIN, 2, ConditionEffet::JAUNE_ALLY), Effet(4, TypeEffet::SOIN, 1, ConditionEffet::NB_CHAMPIONS) }
};

// 2 cartes
//////////////////
////////// OR
///////////////
Carte tithe_priest = {
    .id = 13,
    .nom = "Tithe Priest",
    .cout = 2,
    .type = TypeCarte::CHAMPION,
    .pv = 3,
    .faction = FactionCarte::JAUNE,
    .description = "{Expend}: {Gain 1 gold} <i>or</i> Gain {1 health} for each champion you have in play.",
    .effets = { Effet(1, TypeEffet::PIOCHE, 2) }
};

Carte man_at_arms = {
    .id = 14,
    .nom = "Man-at-Arms",
    .cout = 3,
    .type = TypeCarte::CHAMPION,
    .pv = 4,
    .garde = true,
    .faction = FactionCarte::JAUNE,
    .description = "{Expend}: {Gain 2 combat} +{1 combat} for each other guard you have in play.",
    .effets = { Effet(1, TypeEffet::DMG, 2), Effet(2, TypeEffet::DMG, 1, ConditionEffet::NB_GARDES) }
};

// ========== CARTES BLEUES (GUILDE) ==========

Carte fire_bomb = {
    .id = 20,
    .nom = "Fire Bomb",
    .cout = 8,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::BLEU,
    .description = "{Gain 8 combat} Stun target champion. Draw a card. <hr> {Sacrifice}: {Gain 5 combat}",
    .effets = { Effet(1, TypeEffet::DMG, 8), Effet(2, TypeEffet::STUN, 0), Effet(3, TypeEffet::PIOCHE, 1), Effet(4, TypeEffet::DMG, 5, ConditionEffet::SACRIFICE) }
};

/// ACHETE DANS LA MAIN 
Carte deception = {
    .id = 21,
    .nom = "Deception",
    .cout = 5,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::BLEU,
    .description = "{Gain 2 gold}
Draw a card.
<hr>
{Bleu Ally}: Put the next card you acquire this turn into your hand.",
    .effets = { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::PIOCHE, 1), Effet(3, TypeEffet::HAND_NEXT_ACQUIRED, 0, ConditionEffet::BLEU_ALLY) }
};

//3 cartes
Carte bribe = {
    .id = 21,
    .nom = "Bribe",
    .cout = 3,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::BLEU,
    .description = "{Gain 3 gold}
<hr>
{Bleu Ally}: Put the next action you acquire this turn on top of your deck.",
    .effets = { Effet(1, TypeEffet::OR, 3), Effet(2, TypeEffet::TOP_DECK_NEXT_ACQUIRED_ACTION, 0, ConditionEffet::BLEU_ALLY) }
};

//3 cartes
Carte profit = {
    .id = 22,
    .nom = "Profit",
    .cout = 1,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::BLEU,
    .description = "{Gain 2 gold}
<hr>
{Bleu Ally}: {Gain 4 combat}",
    .effets = { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::DMG, 4, ConditionEffet::BLEU_ALLY) }
};

Carte death_threat = {
    .id = 23,
    .nom = "Death Threat",
    .cout = 3,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::BLEU,
    .description = "{Gain 1 combat}
Draw a card.
<hr>
{Bleu Ally}: Stun target champion.",
    .effets = { Effet(1, TypeEffet::DMG, 1), Effet(2, TypeEffet::PIOCHE, 1), Effet(3, TypeEffet::STUN, 0, ConditionEffet::BLEU_ALLY) }
};

Carte hit_job = {
    .id = 24,
    .nom = "Hit Job",
    .cout = 4,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::BLEU,
    .description = "{Gain 7 combat}
<hr>
{Bleu Ally}: Stun target champion.",
    .effets = { Effet(1, TypeEffet::DMG, 7), Effet(2, TypeEffet::STUN, 0, ConditionEffet::BLEU_ALLY) }
};

//2 cartes
Carte intimidation = {
    .id = 25,
    .nom = "Intimidation",
    .cout = 6,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::BLEU,
    .description = "{Gain 5 combat}
<hr>
{Bleu Ally}: {Gain 2 gold}",
    .effets = { Effet(1, TypeEffet::DMG, 5), Effet(2, TypeEffet::OR, 2, ConditionEffet::BLEU_ALLY) }
};

Carte smash_and_grab = {
    .id = 26,
    .nom = "Smash and Grab",
    .cout = 6,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::BLEU,
    .description = "{Gain 6 combat}
You may put a card from your discard pile on top of your deck.",
    .effets = { Effet(1, TypeEffet::DMG, 6), Effet(2, TypeEffet::TOP_DECK_FROM_DISCARD, 0) }
};

Carte rake_master_assassin = {
    .id = 27,
    .nom = "Rake Master Assassin",
    .cout = 7,
    .type = TypeCarte::CHAMPION,
    .pv = 7,
    .faction = FactionCarte::BLEU,
    .description = "{Expend}: {Gain 4 combat} You may stun target champion.",
    .effets = { Effet(1, TypeEffet::DMG, 4), Effet(2, TypeEffet::STUN, 0) }
};

Carte myros_thin_mage = {
    .id = 28,
    .nom = "Myros, Thin Mage",
    .cout = 5,
    .type = TypeCarte::CHAMPION,
    .pv = 3,
    .garde = true,
    .faction = FactionCarte::BLEU,
    .description = "{Expend}: {Gain 3 gold}
<hr>
{Bleu Ally}: {Gain 4 combat}",
    .effets = { Effet(1, TypeEffet::OR, 3), Effet(2, TypeEffet::PIOCHE, 1, ConditionEffet::BLEU_ALLY) }

};

Carte parov_the_enforcer = {
    .id = 29,
    .nom = "Parov, the Enforcer",
    .cout = 5,
    .type = TypeCarte::CHAMPION,
    .pv = 5,
    .garde = true,
    .faction = FactionCarte::BLEU,
    .description = "{Expend}: {Gain 3 combat}
<hr>
{Bleu Ally}: Draw a card.",
    .effets = { Effet(1, TypeEffet::DMG, 3), Effet(2, TypeEffet::PIOCHE, 1, ConditionEffet::BLEU_ALLY) }
};

Carte rasmus_the_smuggler = {
    .id = 30,
    .nom = "Rasmus, the Smuggler",
    .cout = 4,
    .type = TypeCarte::CHAMPION,
    .pv = 5,
    .faction = FactionCarte::BLEU,
    .description = "{Expend}: {Gain 2 gold}
<hr>
{Bleu Ally}: Put the next card you acquire this turn on top of your deck.",
    .effets = { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::TOP_DECK_NEXT_ACQUIRED, 0, ConditionEffet::BLEU_ALLY) }
};

// 2 cartes
Carte street_thug = {
    .id = 31,
    .nom = "Street Thug",
    .cout = 3,
    .type = TypeCarte::CHAMPION,
    .pv = 4,
    .faction = FactionCarte::BLEU,
    .description = "{Expend}: {Gain 1 gold} <i>or</i> {Gain 2 combat}",
    .effets = { Effet(1, TypeEffet::OR, 1), Effet(2, TypeEffet::DMG, 2) }
};

Carte borg_ogre_mercenary = {
    .id = 32,
    .nom = "Borg, Ogre Mercenary",
    .cout = 6,
    .type = TypeCarte::CHAMPION,
    .pv = 6,
    .garde = true,
    .faction = FactionCarte::BLEU,
    .description = "{Expend}: {Gain 4 combat}",
    .effets = { Effet(1, TypeEffet::DMG, 4) }
};

// ========== CARTES ROUGES (NECROS) ==========

Carte dark_reward = {
    .id = 40,
    .nom = "Dark Reward",
    .cout = 5,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::ROUGE,
    .description = "{Gain 3 gold}
You may sacrifice a card in your hand or discard pile.
<hr>
{Rouge Ally}: {Gain 6 combat}",
    .effets = { Effet(1, TypeEffet::OR, 3), Effet(2, TypeEffet::DMG, 6, ConditionEffet::ROUGE_ALLY), Effet(3, TypeEffet::SACRIFICE, 0) }
};

// 3 cartes
Carte influence = {
    .id = 41,
    .nom = "Influence",
    .cout = 2,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::ROUGE,
    .description = "{Gain 3 gold}
<hr>
{Sacrifice}: {Gain 3 combat}",
    .effets = { Effet(1, TypeEffet::OR, 3), Effet(2, TypeEffet::DMG, 3, ConditionEffet::SACRIFICE) }
};

// 3 cartes
Carte death_touch = {
    .id = 42,
    .nom = "Death Touch",
    .cout = 1,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::ROUGE,
    .description = "{Gain 2 combat}
You may sacrifice a card in your hand or discard pile.
<hr>
{Rouge Ally}: {Gain 2 combat}",
    .effets = { Effet(1, TypeEffet::DMG, 2), Effet(2, TypeEffet::DMG, 2, ConditionEffet::ROUGE_ALLY), Effet(3, TypeEffet::SACRIFICE, 0) }
};

Carte life_drain = {
    .id = 43,
    .nom = "Life Drain",
    .cout = 6,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::ROUGE,
    .description = "{Gain 8 combat}
You may sacrifice a card in your hand or discard pile.
<hr>
{Rouge Ally}: Draw a card.",
    .effets = { Effet(1, TypeEffet::DMG, 8), Effet(2, TypeEffet::PIOCHE, 1, ConditionEffet::ROUGE_ALLY), Effet(3, TypeEffet::SACRIFICE, 0) }
};

// 2 cartes
Carte the_rot = {
    .id = 44,
    .nom = "The Rot",
    .cout = 3,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::ROUGE,
    .description = "{Gain 4 combat}
You may sacrifice a card in your hand or discard pile.
<hr>
{Rouge Ally}: {Gain 3 combat}"
    .effets = { Effet(1, TypeEffet::DMG, 4), Effet(2, TypeEffet::DMG, 3, ConditionEffet::ROUGE_ALLY), Effet(3, TypeEffet::SACRIFICE, 0) }
};

Carte dark_energy = {
    .id = 45,
    .nom = "Dark Energy",
    .cout = 4,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::ROUGE,
    .description = "{Gain 7 combat}
<hr>
{Rouge Ally}: Draw a card.",
    .effets = { Effet(1, TypeEffet::DMG, 7), Effet(2, TypeEffet::PIOCHE, 1, ConditionEffet::ROUGE_ALLY) }
};

Carte tyrannor_the_devorer = {
    .id = 46,
    .nom = "Tyrannor, the Devorer",
    .cout = 8,
    .type = TypeCarte::CHAMPION,
    .pv = 6,
    .garde = true,
    .faction = FactionCarte::ROUGE,
    .description = "{Expend}: {Gain 4 combat}
You may sacrifice up to two cards in your hand and/or discard pile.
<hr>
{Rouge Ally}: Draw a card.",
    .effets = { Effet(1, TypeEffet::DMG, 5), Effet(2, TypeEffet::SACRIFICE, 0) }
};

// 2 cartes
Carte cult_priest = {
    .id = 47,
    .nom = "Cult Priest",
    .cout = 3,
    .type = TypeCarte::CHAMPION,
    .pv = 4,
    .faction = FactionCarte::ROUGE,
    .description = "{Expend}: {Gain 1 gold} <i>or</i> {Gain 1 combat}
<hr>
{Rouge Ally}: {Gain 4 combat}",
    .effets = { Effet(1, TypeEffet::OR, 1), Effet(2, TypeEffet::SOIN, 2, ConditionEffet::NB_CHAMPIONS) }
};

// 2 cartes
Carte death_cultist = {
    .id = 48,
    .nom = "Death Cultist",
    .cout = 2,
    .type = TypeCarte::CHAMPION,
    .pv = 3,
    .garde = true,
    .faction = FactionCarte::ROUGE,
    .description = "{Expend}: {Gain 2 combat}",
    .effets = { Effet(1, TypeEffet::DMG, 2), Effet(2, TypeEffet::SOIN, 2, ConditionEffet::ROUGE_ALLY) }
};

Carte rayla_endweaver = {
    .id = 49,
    .nom = "Rayla Endweaver",
    .cout = 4,
    .type = TypeCarte::CHAMPION,
    .pv = 4,
    .faction = FactionCarte::ROUGE,
    .description = "{Expend}: {Gain 3 combat}
<hr>
{Rouge Ally}: Draw a card.",
    .effets = { Effet(1, TypeEffet::DMG, 3), Effet(2, TypeEffet::PIOCHE, 1, ConditionEffet::ROUGE_ALLY) }
};

Carte varrick_the_necromancer = {
    .id = 50,
    .nom = "Varrick, the Necromancer",
    .cout = 5,
    .type = TypeCarte::CHAMPION,
    .pv = 3,
    .faction = FactionCarte::ROUGE,
    .description = "{Expend}: Take a champion from your discard pile and put it on top of your deck.
<hr>
{Rouge Ally}: Draw a card.",
    .effets = { Effet(1, TypeEffet::TOP_DECK_FROM_DISCARD, 0), Effet(2, TypeEffet::PIOCHE, 1, ConditionEffet::ROUGE_ALLY) }
};

// /!\ Note: Krythos a une mécanique spéciale, il nécessite une syntaxe différente
// pour gérer le sacrifice d'une carte dans la main ou la pile de défausse.
Carte krythos_master_vampire = {
    .id = 51,
    .nom = "Krythos, Master Vampire",
    .cout = 7,
    .type = TypeCarte::CHAMPION,
    .pv = 6,
    .garde = true,
    .faction = FactionCarte::ROUGE,
    .description = "{Expend}: {Gain 3 combat}
You may sacrifice a card in your hand or discard pile.
If you do, gain an additional {3 combat}.",
    .effets = { Effet(1, TypeEffet::DMG, 3), Effet(2, TypeEffet::DMG, 3, ConditionEffet::SACRIFICE), Effet(3, TypeEffet::SACRIFICE, 0) }
};

// /!\ Note: Lys a une mécanique spéciale, il nécessite une syntaxe différente
// pour gérer le sacrifice d'une carte dans la main ou la pile de défausse.
Carte lys_the_unseen = {
    .id = 52,
    .nom = "Lys, the Unseen",
    .cout = 6,
    .type = TypeCarte::CHAMPION,
    .pv = 5,
    .garde = true,
    .faction = FactionCarte::ROUGE,
    .description = "{Expend}: {Gain 2 combat}
You may sacrifice a card in your hand or discard pile.
If you do, gain an additional {2 combat}.",
    .effets = { Effet(1, TypeEffet::DMG, 2), Effet(2, TypeEffet::DMG, 2, ConditionEffet::SACRIFICE), Effet(3, TypeEffet::SACRIFICE, 0) }
};

// ========== CARTES VERTES (SAUVAGES) ==========

Carte natures_bounty = {
    .id = 60,
    .nom = "Nature's Bounty",
    .cout = 4,
    .type = TypeCarte::ACTION,
    .faction = FactionCarte::VERT,
    .description = 

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