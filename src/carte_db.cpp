#include "carte_db.h"
#include "carte.h"
#include "champion.h"
#include "effet.h"
#include <vector>

// =========================
// FACTION : JAUNE
// =========================

// Actions jaunes
Carte close_ranks(1, "Close Ranks", 3, TypeCarte::ACTION, FactionCarte::JAUNE,
    "Gain 5 Combat",
    { Effet(1, TypeEffet::DMG, 5) }
);

Carte command(2, "Command", 5, TypeCarte::ACTION, FactionCarte::JAUNE,
    "{Gain 2 gold} {Gain 3 combat} {Gain 4 health} {Piochez une carte}.",
    { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::DMG, 3), Effet(3, TypeEffet::SOIN, 4), Effet(4, TypeEffet::PIOCHE, 1) }
);

Carte domination(3, "Domination", 7, TypeCarte::ACTION, FactionCarte::JAUNE,
    "{Gain 6 combat} {Gain 6 health} Draw a card. <hr> {Jaune Ally}: Prepare a champion.",
    { Effet(1, TypeEffet::DMG, 6), Effet(2, TypeEffet::SOIN, 6), Effet(3, TypeEffet::PIOCHE, 1), Effet(4, TypeEffet::PREPARE_CHAMPION, 0, ConditionEffet::JAUNE_ALLY) }
);

Carte rally_the_troops(4, "Rally the Troops", 4, TypeCarte::ACTION, FactionCarte::JAUNE,
    "{Gain 5 combat} {Gain 5 health} <hr> {Jaune Ally}: Prepare a champion.",
    { Effet(1, TypeEffet::DMG, 5), Effet(2, TypeEffet::SOIN, 5), Effet(3, TypeEffet::PREPARE_CHAMPION, 0, ConditionEffet::JAUNE_ALLY) }
);

Carte recruit1(501, "Recruit", 2, TypeCarte::ACTION, FactionCarte::JAUNE,
    "{Gain 2 gold} {Gain 3 health} +{1 health} for each champion you have in play. <hr> {Jaune Ally}: {Gain 1 gold}",
    { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::SOIN, 3), Effet(3, TypeEffet::SOIN_per_CHAMP, 1), Effet(4, TypeEffet::OR, 1, ConditionEffet::JAUNE_ALLY) }
);
Carte recruit2(502, "Recruit", 2, TypeCarte::ACTION, FactionCarte::JAUNE,
    "{Gain 2 gold} {Gain 3 health} +{1 health} for each champion you have in play. <hr> {Jaune Ally}: {Gain 1 gold}",
    { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::SOIN, 3), Effet(3, TypeEffet::SOIN_per_CHAMP, 1), Effet(4, TypeEffet::OR, 1, ConditionEffet::JAUNE_ALLY) }
);
Carte recruit3(503, "Recruit", 2, TypeCarte::ACTION, FactionCarte::JAUNE,
    "{Gain 2 gold} {Gain 3 health} +{1 health} for each champion you have in play. <hr> {Jaune Ally}: {Gain 1 gold}",
    { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::SOIN, 3), Effet(3, TypeEffet::SOIN_per_CHAMP, 1), Effet(4, TypeEffet::OR, 1, ConditionEffet::JAUNE_ALLY) }
);

Carte taxation1(601, "Taxation", 1, TypeCarte::ACTION, FactionCarte::JAUNE,
    "{Gain 2 gold} <hr> {Jaune Ally}: {Gain 6 health}",
    { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::SOIN, 6, ConditionEffet::JAUNE_ALLY) }
);
Carte taxation2(602, "Taxation", 1, TypeCarte::ACTION, FactionCarte::JAUNE,
    "{Gain 2 gold} <hr> {Jaune Ally}: {Gain 6 health}",
        { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::SOIN, 6, ConditionEffet::JAUNE_ALLY) }
);
Carte taxation3(603, "Taxation", 1, TypeCarte::ACTION, FactionCarte::JAUNE,
    "{Gain 2 gold} <hr> {Jaune Ally}: {Gain 6 health}",
    { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::SOIN, 6, ConditionEffet::JAUNE_ALLY) }
);

Carte word_of_power(7, "Word of Power", 6, TypeCarte::ACTION, FactionCarte::JAUNE,
    "Draw two cards. <hr> {Jaune Ally}: {Gain 5 health} <hr> {Sacrifice}: {Gain 5 combat}",
    { Effet(1, TypeEffet::PIOCHE, 2), Effet(2, TypeEffet::SOIN, 5, ConditionEffet::JAUNE_ALLY), Effet(3, TypeEffet::DMG, 5, ConditionEffet::SACRIFICE) }
);

// Champions jaunes
Champion arkus_imperial_dragon(8, "Arkus, Imperial Dragon", 8, FactionCarte::JAUNE,
    "{Expend}: {Gain 5 combat} Draw a card. {Jaune Ally}: {Gain 6 health}",
    { 
        Effet(1, TypeEffet::EXPEND_CHAMPION, 0),
        Effet(2, TypeEffet::DMG, 5),
        Effet(3, TypeEffet::PIOCHE, 1),
        Effet(4, TypeEffet::SOIN, 6, ConditionEffet::JAUNE_ALLY)
    },
    true, 6
);

Champion darian_war_mage(9, "Darian, War Mage", 4, FactionCarte::JAUNE,
    "{Expend}: {Gain 3 combat} <i>or</i> {Gain 4 health}",
    { 
        Effet(1, TypeEffet::EXPEND_CHAMPION, 0),
        Effet(2, TypeEffet::DMG_ou_SOIN, 1)
    }
);

Champion master_weyan(10, "Master Weyan", 4, FactionCarte::JAUNE,
    "{Expend}: {Gain 3 combat} +{1 combat} for each other champion you have in play.",
    { 
        Effet(1, TypeEffet::EXPEND_CHAMPION, 0),
        Effet(2, TypeEffet::DMG, 3),
        Effet(3, TypeEffet::DMG, 1, ConditionEffet::NB_CHAMPIONS)
    },
    true, 4 
);

Champion cristov_the_just(11, "Cristov, the Just", 5, FactionCarte::JAUNE,
    "{Expend}: {Gain 2 combat} {Gain 3 health} <hr> {Jaune Ally}: Draw a card.",
    { 
        Effet(1, TypeEffet::EXPEND_CHAMPION, 0),
        Effet(2, TypeEffet::DMG, 2),
        Effet(3, TypeEffet::SOIN, 3),
        Effet(4, TypeEffet::PIOCHE, 1, ConditionEffet::JAUNE_ALLY)
    },
    true, 5
);

Champion kraka_high_priest(12, "Kraka, High Priest", 6, FactionCarte::JAUNE,
    "{Expend}: {Gain 2 health} Draw a card. <hr> {Jaune Ally}: Gain {2 health} for each champion you have in play.",
    { 
        Effet(1, TypeEffet::EXPEND_CHAMPION, 0),
        Effet(2, TypeEffet::SOIN, 2),
        Effet(3, TypeEffet::PIOCHE, 1),
        Effet(4, TypeEffet::SOIN_per_CHAMP, 2, ConditionEffet::JAUNE_ALLY)      // Quatrième effet : +2 PV par champion si allié jaune
    },
    true, 6
);

Champion tithe_priest1(1301, "Tithe Priest", 2, FactionCarte::JAUNE,
    "{Expend}: {Gain 1 gold} <i>or</i> Gain {1 health} for each champion you have in play.",
    { 
        Effet(1, TypeEffet::EXPEND_CHAMPION, 0),
        Effet(2, TypeEffet::OR_ou_SOIN_per_CHAMP, 1)
    },
    false, 3
);
Champion tithe_priest2(1302, "Tithe Priest", 2, FactionCarte::JAUNE,
    "{Expend}: {Gain 1 gold} <i>or</i> Gain {1 health} for each champion you have in play.",
    { 
        Effet(1, TypeEffet::EXPEND_CHAMPION, 0),
        Effet(2, TypeEffet::OR_ou_SOIN_per_CHAMP, 1)
    },
    false, 3
);

Champion man_at_arms1(1401, "Man-at-Arms", 3, FactionCarte::JAUNE,
    "{Expend}: {Gain 2 combat} +{1 combat} for each other guard you have in play.",
    {
        Effet(1, TypeEffet::EXPEND_CHAMPION, 0),
        Effet(2, TypeEffet::DMG, 2),
        Effet(3, TypeEffet::DMG, 1, ConditionEffet::NB_GARDES)
    },
    true, 4
);
Champion man_at_arms2(1402, "Man-at-Arms", 3, FactionCarte::JAUNE,
    "{Expend}: {Gain 2 combat} +{1 combat} for each other guard you have in play.",
    {
        Effet(1, TypeEffet::EXPEND_CHAMPION, 0),
        Effet(2, TypeEffet::DMG, 2),
        Effet(3, TypeEffet::DMG, 1, ConditionEffet::NB_GARDES)
    },
    true, 4
);

// =========================
// FACTION : BLEU
// =========================

// Actions bleues
Carte fire_bomb(
    20, "Fire Bomb", 8, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 8 combat} Stun target champion. Draw a card. <hr> {Sacrifice}: {Gain 5 combat}",
    { Effet(1, TypeEffet::DMG, 8), Effet(2, TypeEffet::STUN, 0), Effet(3, TypeEffet::PIOCHE, 1), Effet(4, TypeEffet::DMG, 5, ConditionEffet::SACRIFICE) }
);

Carte deception(
    21, "Deception", 5, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 2 gold}\nDraw a card.\n<hr>\n{Bleu Ally}: Put the next card you acquire this turn into your hand.",
    { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::PIOCHE, 1), Effet(3, TypeEffet::HAND_NEXT_ACQUIRED, 0, ConditionEffet::BLEU_ALLY) }
);

Carte bribe1(
    2201, "Bribe", 3, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 3 gold}\n<hr>\n{Bleu Ally}: Put the next action you acquire this turn on top of your deck.",
    { Effet(1, TypeEffet::OR, 3), Effet(2, TypeEffet::TOP_DECK_NEXT_ACQUIRED_ACTION, 0, ConditionEffet::BLEU_ALLY) }
);
Carte bribe2(
    2202, "Bribe", 3, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 3 gold}\n<hr>\n{Bleu Ally}: Put the next action you acquire this turn on top of your deck.",
    { Effet(1, TypeEffet::OR, 3), Effet(2, TypeEffet::TOP_DECK_NEXT_ACQUIRED_ACTION, 0, ConditionEffet::BLEU_ALLY) }
);
Carte bribe3(
    2203, "Bribe", 3, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 3 gold}\n<hr>\n{Bleu Ally}: Put the next action you acquire this turn on top of your deck.",
    { Effet(1, TypeEffet::OR, 3), Effet(2, TypeEffet::TOP_DECK_NEXT_ACQUIRED_ACTION, 0, ConditionEffet::BLEU_ALLY) }
);

Carte profit1(
    2301, "Profit", 1, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 2 gold}\n<hr>\n{Bleu Ally}: {Gain 4 combat}",
    { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::DMG, 4, ConditionEffet::BLEU_ALLY) }
);
Carte profit2(
    2302, "Profit", 1, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 2 gold}\n<hr>\n{Bleu Ally}: {Gain 4 combat}",
    { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::DMG, 4, ConditionEffet::BLEU_ALLY) }
);
Carte profit3(
    2303, "Profit", 1, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 2 gold}\n<hr>\n{Bleu Ally}: {Gain 4 combat}",
    { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::DMG, 4, ConditionEffet::BLEU_ALLY) }
);

Carte death_threat(
    24, "Death Threat", 3, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 1 combat}\nDraw a card.\n<hr>\n{Bleu Ally}: Stun target champion.",
    { Effet(1, TypeEffet::DMG, 1), Effet(2, TypeEffet::PIOCHE, 1), Effet(3, TypeEffet::STUN, 0, ConditionEffet::BLEU_ALLY) }
);

Carte hit_job(
    25, "Hit Job", 4, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 7 combat}\n<hr>\n{Bleu Ally}: Stun target champion.",
    { Effet(1, TypeEffet::DMG, 7), Effet(2, TypeEffet::STUN, 0, ConditionEffet::BLEU_ALLY) }
);

Carte intimidation1(
    2601, "Intimidation", 6, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 5 combat}\n<hr>\n{Bleu Ally}: {Gain 2 gold}",
    { Effet(1, TypeEffet::DMG, 5), Effet(2, TypeEffet::OR, 2, ConditionEffet::BLEU_ALLY) }
);
Carte intimidation2(
    2602, "Intimidation", 6, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 5 combat}\n<hr>\n{Bleu Ally}: {Gain 2 gold}",
    { Effet(1, TypeEffet::DMG, 5), Effet(2, TypeEffet::OR, 2, ConditionEffet::BLEU_ALLY) }
);

Carte smash_and_grab(
    27, "Smash and Grab", 6, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 6 combat}\nYou may put a card from your discard pile on top of your deck.",
    { Effet(1, TypeEffet::DMG, 6), Effet(2, TypeEffet::TOP_DECK_FROM_DISCARD, 0) }
);

// Champions bleus
Champion rake_master_assassin(
    28, "Rake Master Assassin", 7, FactionCarte::BLEU,
    "{Expend}: {Gain 4 combat} You may stun target champion.",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::DMG, 4), Effet(3, TypeEffet::STUN, 0) },
    false, 7
);

Champion myros_thin_mage(
    29, "Myros, Thin Mage", 5, FactionCarte::BLEU,
    "{Expend}: {Gain 3 gold}\n<hr>\n{Bleu Ally}: {Gain 4 combat}",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::OR, 3), Effet(3, TypeEffet::DMG, 4, ConditionEffet::BLEU_ALLY) },
    true, 3
);

Champion parov_the_enforcer(
    30, "Parov, the Enforcer", 5, FactionCarte::BLEU,
    "{Expend}: {Gain 3 combat}\n<hr>\n{Bleu Ally}: Draw a card.",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::DMG, 3), Effet(3, TypeEffet::PIOCHE, 1, ConditionEffet::BLEU_ALLY) },
    true, 5
);

Champion rasmus_the_smuggler(
    31, "Rasmus, the Smuggler", 4, FactionCarte::BLEU,
    "{Expend}: {Gain 2 gold}\n<hr>\n{Bleu Ally}: Put the next card you acquire this turn on top of your deck.",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::OR, 2), Effet(3, TypeEffet::TOP_DECK_NEXT_ACQUIRED, 0, ConditionEffet::BLEU_ALLY) },
    false, 5
);

Champion street_thug1(
    3201, "Street Thug", 3, FactionCarte::BLEU,
    "{Expend}: {Gain 1 gold} <i>or</i> {Gain 2 combat}",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::OR_ou_2DMG, 1) },
    false, 4
);
Champion street_thug2(
    3202, "Street Thug", 3, FactionCarte::BLEU,
    "{Expend}: {Gain 1 gold} <i>or</i> {Gain 2 combat}",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::OR_ou_2DMG, 1) },
    false, 4
);

Champion borg_ogre_mercenary(
    33, "Borg, Ogre Mercenary", 6, FactionCarte::BLEU,
    "{Expend}: {Gain 4 combat}",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::DMG, 4) },
    true, 6
);

// =========================
// FACTION : ROUGE
// =========================

// Actions rouges
Carte dark_reward(40, "Dark Reward", 5, TypeCarte::ACTION, FactionCarte::ROUGE,
    "{Gain 3 gold}\nYou may sacrifice a card in your hand or discard pile.\n<hr>\n{Rouge Ally}: {Gain 6 combat}",
    { Effet(1, TypeEffet::OR, 3), Effet(2, TypeEffet::DMG, 6, ConditionEffet::ROUGE_ALLY), Effet(3, TypeEffet::SACRIFICE_HAND_DISCARD, 1) }
);

Carte influence1(4101, "Influence", 2, TypeCarte::ACTION, FactionCarte::ROUGE,
    "{Gain 3 gold}\n<hr>\n{Sacrifice}: {Gain 3 combat}",
    { Effet(1, TypeEffet::OR, 3), Effet(2, TypeEffet::DMG, 3, ConditionEffet::SACRIFICE) }
);
Carte influence2(4102, "Influence", 2, TypeCarte::ACTION, FactionCarte::ROUGE,
    "{Gain 3 gold}\n<hr>\n{Sacrifice}: {Gain 3 combat}",
    { Effet(1, TypeEffet::OR, 3), Effet(2, TypeEffet::DMG, 3, ConditionEffet::SACRIFICE) }
);
Carte influence3(4103, "Influence", 2, TypeCarte::ACTION, FactionCarte::ROUGE,
    "{Gain 3 gold}\n<hr>\n{Sacrifice}: {Gain 3 combat}",
    { Effet(1, TypeEffet::OR, 3), Effet(2, TypeEffet::DMG, 3, ConditionEffet::SACRIFICE) }
);

Carte death_touch1(4201, "Death Touch", 1, TypeCarte::ACTION, FactionCarte::ROUGE,
    "{Gain 2 combat}\nYou may sacrifice a card in your hand or discard pile.\n<hr>\n{Rouge Ally}: {Gain 2 combat}",
    { Effet(1, TypeEffet::DMG, 2), Effet(2, TypeEffet::DMG, 2, ConditionEffet::ROUGE_ALLY), Effet(3, TypeEffet::SACRIFICE_HAND_DISCARD, 1) }
);
Carte death_touch2(4202, "Death Touch", 1, TypeCarte::ACTION, FactionCarte::ROUGE,
    "{Gain 2 combat}\nYou may sacrifice a card in your hand or discard pile.\n<hr>\n{Rouge Ally}: {Gain 2 combat}",
    { Effet(1, TypeEffet::DMG, 2), Effet(2, TypeEffet::DMG, 2, ConditionEffet::ROUGE_ALLY), Effet(3, TypeEffet::SACRIFICE_HAND_DISCARD, 1) }
);
Carte death_touch3(4203, "Death Touch", 1, TypeCarte::ACTION, FactionCarte::ROUGE,
    "{Gain 2 combat}\nYou may sacrifice a card in your hand or discard pile.\n<hr>\n{Rouge Ally}: {Gain 2 combat}",
    { Effet(1, TypeEffet::DMG, 2), Effet(2, TypeEffet::DMG, 2, ConditionEffet::ROUGE_ALLY), Effet(3, TypeEffet::SACRIFICE_HAND_DISCARD, 1) }
);

Carte life_drain(43, "Life Drain", 6, TypeCarte::ACTION, FactionCarte::ROUGE,
    "{Gain 8 combat}\nYou may sacrifice a card in your hand or discard pile.\n<hr>\n{Rouge Ally}: Draw a card.",
    { Effet(1, TypeEffet::DMG, 8), Effet(2, TypeEffet::PIOCHE, 1, ConditionEffet::ROUGE_ALLY), Effet(3, TypeEffet::SACRIFICE_HAND_DISCARD, 1) }
);

Carte the_rot1(4401, "The Rot", 3, TypeCarte::ACTION, FactionCarte::ROUGE,
    "{Gain 4 combat}\nYou may sacrifice a card in your hand or discard pile.\n<hr>\n{Rouge Ally}: {Gain 3 combat}",
    { Effet(1, TypeEffet::DMG, 4), Effet(2, TypeEffet::DMG, 3, ConditionEffet::ROUGE_ALLY), Effet(3, TypeEffet::SACRIFICE_HAND_DISCARD, 1) }
);
Carte the_rot2(4402, "The Rot", 3, TypeCarte::ACTION, FactionCarte::ROUGE,
    "{Gain 4 combat}\nYou may sacrifice a card in your hand or discard pile.\n<hr>\n{Rouge Ally}: {Gain 3 combat}",
    { Effet(1, TypeEffet::DMG, 4), Effet(2, TypeEffet::DMG, 3, ConditionEffet::ROUGE_ALLY), Effet(3, TypeEffet::SACRIFICE_HAND_DISCARD, 1) }
);

Carte dark_energy(45, "Dark Energy", 4, TypeCarte::ACTION, FactionCarte::ROUGE,
    "{Gain 7 combat}\n<hr>\n{Rouge Ally}: Draw a card.",
    { Effet(1, TypeEffet::DMG, 7), Effet(2, TypeEffet::PIOCHE, 1, ConditionEffet::ROUGE_ALLY) }
);

// Champions rouges
Champion tyrannor_the_devorer(46, "Tyrannor, the Devorer", 8, FactionCarte::ROUGE,
    "{Expend}: {Gain 4 combat}\nYou may sacrifice up to two cards in your hand and/or discard pile.\n<hr>\n{Rouge Ally}: Draw a card.",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::DMG, 4), Effet(3, TypeEffet::SACRIFICE_HAND_DISCARD, 2), Effet(4, TypeEffet::PIOCHE, 1, ConditionEffet::ROUGE_ALLY) },
    true, 6
);  

Champion cult_priest1(4701, "Cult Priest", 3, FactionCarte::ROUGE,
    "{Expend}: {Gain 1 gold} <i>or</i> {Gain 1 combat}\n<hr>\n{Rouge Ally}: {Gain 4 combat}",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::OR_ou_DMG, 1), Effet(3, TypeEffet::DMG, 4, ConditionEffet::ROUGE_ALLY) },
    false, 4
);
Champion cult_priest2(4702, "Cult Priest", 3, FactionCarte::ROUGE,
    "{Expend}: {Gain 1 gold} <i>or</i> {Gain 1 combat}\n<hr>\n{Rouge Ally}: {Gain 4 combat}",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::OR_ou_DMG, 1), Effet(3, TypeEffet::DMG, 4, ConditionEffet::ROUGE_ALLY) },
    false, 4
);

Champion death_cultist1(4801, "Death Cultist", 2, FactionCarte::ROUGE,
    "{Expend}: {Gain 2 combat}",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::DMG, 2), Effet(3, TypeEffet::SOIN, 2, ConditionEffet::ROUGE_ALLY) },
    true, 3
);
Champion death_cultist2(4802, "Death Cultist", 2, FactionCarte::ROUGE,
    "{Expend}: {Gain 2 combat}",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::DMG, 2), Effet(3, TypeEffet::SOIN, 2, ConditionEffet::ROUGE_ALLY) },
    true, 3
);

Champion rayla_endweaver(49, "Rayla Endweaver", 4, FactionCarte::ROUGE,
    "{Expend}: {Gain 3 combat}\n<hr>\n{Rouge Ally}: Draw a card.",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::DMG, 3), Effet(3, TypeEffet::PIOCHE, 1, ConditionEffet::ROUGE_ALLY) },
    false, 4
);

Champion varrick_the_necromancer(50, "Varrick, the Necromancer", 5, FactionCarte::ROUGE,
    "{Expend}: Take a champion from your discard pile and put it on top of your deck.\n<hr>\n{Rouge Ally}: Draw a card.",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::TOP_DECK_FROM_DISCARD, 0), Effet(3, TypeEffet::PIOCHE, 1, ConditionEffet::ROUGE_ALLY) },
    false, 3
);

Champion krythos_master_vampire(51, "Krythos, Master Vampire", 7, FactionCarte::ROUGE,
    "{Expend}: {Gain 3 combat}\nYou may sacrifice a card in your hand or discard pile.\nIf you do, gain an additional {3 combat}.",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::DMG, 3), Effet(3, TypeEffet::DMG, 3, ConditionEffet::SACRIFICE_HAND_DISCARD, 1) },
    true, 6
);

Champion lys_the_unseen(52, "Lys, the Unseen", 6, FactionCarte::ROUGE,
    "{Expend}: {Gain 2 combat}\nYou may sacrifice a card in your hand or discard pile.\nIf you do, gain an additional {2 combat}.",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::DMG, 2), Effet(3, TypeEffet::DMG, 2, ConditionEffet::SACRIFICE_HAND_DISCARD, 1) },
    true, 5
);

// =========================
// FACTION : VERT
// =========================

// Actions vertes
Carte natures_bounty(60, "Nature's Bounty", 4, TypeCarte::ACTION, FactionCarte::VERT,
    "{Gain 4 gold}\n{Vert Ally}: Target opponent discards a card.\n{Sacrifice}: {Gain 4 combat}",
    { Effet(1, TypeEffet::OR, 4), Effet(2, TypeEffet::FORCE_DISCARD_OPPONENT, 1, ConditionEffet::VERT_ALLY), Effet(3, TypeEffet::DMG, 4, ConditionEffet::SACRIFICE) }
);

Carte elven_gift1(6101, "Elven Gift", 2, TypeCarte::ACTION, FactionCarte::VERT,
    "{Gain 2 gold}\nYou may draw a card. If you do, discard a card.<hr>\n{Vert Ally}: {Gain 4 combat}",
    { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::DRAW_DISCARD, 1), Effet(3, TypeEffet::DMG, 4, ConditionEffet::VERT_ALLY) }
);
Carte elven_gift2(6102, "Elven Gift", 2, TypeCarte::ACTION, FactionCarte::VERT,
    "{Gain 2 gold}\nYou may draw a card. If you do, discard a card.<hr>\n{Vert Ally}: {Gain 4 combat}",
    { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::DRAW_DISCARD, 1), Effet(3, TypeEffet::DMG, 4, ConditionEffet::VERT_ALLY) }
);
Carte elven_gift3(6103, "Elven Gift", 2, TypeCarte::ACTION, FactionCarte::VERT,
    "{Gain 2 gold}\nYou may draw a card. If you do, discard a card.<hr>\n{Vert Ally}: {Gain 4 combat}",
    { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::DRAW_DISCARD, 1), Effet(3, TypeEffet::DMG, 4, ConditionEffet::VERT_ALLY) }
);

Carte elven_curse1(6201, "Elven Curse", 3, TypeCarte::ACTION, FactionCarte::VERT,
    "{Gain 6 combat}\nTarget opponent discards a card.\n{Vert Ally}: {Gain 3 combat}",
    { Effet(1, TypeEffet::DMG, 6), Effet(2, TypeEffet::FORCE_DISCARD_OPPONENT, 1), Effet(3, TypeEffet::DMG, 3, ConditionEffet::VERT_ALLY) }
);
Carte elven_curse2(6202, "Elven Curse", 3, TypeCarte::ACTION, FactionCarte::VERT,
    "{Gain 6 combat}\nTarget opponent discards a card.\n{Vert Ally}: {Gain 3 combat}",
    { Effet(1, TypeEffet::DMG, 6), Effet(2, TypeEffet::FORCE_DISCARD_OPPONENT, 1), Effet(3, TypeEffet::DMG, 3, ConditionEffet::VERT_ALLY) }
);

Carte rampage(63, "Rampage", 6, TypeCarte::ACTION, FactionCarte::VERT,
    "{Gain 6 combat}\nYou may draw up to two cards, then discard that many cards.",
    { Effet(1, TypeEffet::DMG, 6), Effet(2, TypeEffet::DRAW_DISCARD, 2) }
);

Carte spark1(6401, "Spark", 1, TypeCarte::ACTION, FactionCarte::VERT,
    "{Gain 3 combat}\nTarget opponent discards a card.\n{Vert Ally}: {Gain 2 combat}",
    { Effet(1, TypeEffet::DMG, 3), Effet(2, TypeEffet::FORCE_DISCARD_OPPONENT, 1), Effet(3, TypeEffet::DMG, 2, ConditionEffet::VERT_ALLY) }
);
Carte spark2(6402, "Spark", 1, TypeCarte::ACTION, FactionCarte::VERT,
    "{Gain 3 combat}\nTarget opponent discards a card.\n{Vert Ally}: {Gain 2 combat}",
    { Effet(1, TypeEffet::DMG, 3), Effet(2, TypeEffet::FORCE_DISCARD_OPPONENT, 1), Effet(3, TypeEffet::DMG, 2, ConditionEffet::VERT_ALLY) }
);
Carte spark3(6403, "Spark", 1, TypeCarte::ACTION, FactionCarte::VERT,
    "{Gain 3 combat}\nTarget opponent discards a card.\n{Vert Ally}: {Gain 2 combat}",
    { Effet(1, TypeEffet::DMG, 3), Effet(2, TypeEffet::FORCE_DISCARD_OPPONENT, 1), Effet(3, TypeEffet::DMG, 2, ConditionEffet::VERT_ALLY) }
);

Carte wolf_form(65, "Wolf Form", 5, TypeCarte::ACTION, FactionCarte::VERT,
    "{Gain 8 combat}\nTarget opponent discards a card.\n<hr>\n{Sacrifice}: Target opponent discards a card.",
    { Effet(1, TypeEffet::DMG, 8), Effet(2, TypeEffet::FORCE_DISCARD_OPPONENT, 1), Effet(3, TypeEffet::FORCE_DISCARD_OPPONENT, 1, ConditionEffet::SACRIFICE) }
);

// Champions verts
Champion broelyn_loreweaver(66, "Broelyn, Loreweaver", 4,  FactionCarte::VERT,
    "{Expend}: {Gain 2 gold}\n<hr>\n{Vert Ally}: Target opponent discards a card.",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::OR, 2), Effet(3, TypeEffet::FORCE_DISCARD_OPPONENT, 1, ConditionEffet::VERT_ALLY) },
    false, 6
);

Champion grak_storm_giant(67, "Grak, Storm Giant", 8,  FactionCarte::VERT,
    "{Expend}: {Gain 6 combat}\nYou may draw a card. If you do, discard a card.\n<hr>\n{Vert Ally}: Draw a card, then discard a card.",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::DMG, 6), Effet(3, TypeEffet::DRAW_DISCARD, 1), Effet(4, TypeEffet::DRAW_DISCARD, 1, ConditionEffet::VERT_ALLY) },
    true, 7
);

Champion dire_wolf(68, "Dire Wolf", 5,  FactionCarte::VERT,
    "{Expend}: {Gain 3 combat}\n<hr>\n{Vert Ally}: {Gain 4 combat}",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::DMG, 3), Effet(3, TypeEffet::DMG, 4, ConditionEffet::VERT_ALLY) },
    true, 5
);

Champion wolf_shaman1(6901, "Wolf Shaman", 2,  FactionCarte::VERT,
    "{Expend}: {Gain 2 combat}\n+{1 combat} for each other {Vert} card you have in play.",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::DMG, 2), Effet(3, TypeEffet::DMG, 1, ConditionEffet::NB_VERT_CARDS_IN_PLAY) },
    false, 4
);
Champion wolf_shaman2(6902, "Wolf Shaman", 2,  FactionCarte::VERT,
    "{Expend}: {Gain 2 combat}\n+{1 combat} for each other {Vert} card you have in play.",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::DMG, 2), Effet(3, TypeEffet::DMG, 1, ConditionEffet::NB_VERT_CARDS_IN_PLAY) },
    false, 4
);

Champion cron_the_berserker(70, "Cron, the Berserker", 6,  FactionCarte::VERT,
    "{Expend}: {Gain 5 combat}\n<hr>\n{Vert Ally}: Draw a card.",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::DMG, 5), Effet(3, TypeEffet::PIOCHE, 1, ConditionEffet::VERT_ALLY) },
    true, 6
);

Champion orc_grunt1(7101, "Orc Grunt", 3,  FactionCarte::VERT,
    "{Expend}: {Gain 2 combat}\n<hr>\n{Vert Ally}: Draw a card.",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::DMG, 2), Effet(3, TypeEffet::PIOCHE, 1, ConditionEffet::VERT_ALLY) },
    true, 3
);
Champion orc_grunt2(7102, "Orc Grunt", 3,  FactionCarte::VERT,
    "{Expend}: {Gain 2 combat}\n<hr>\n{Vert Ally}: Draw a card.",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::DMG, 2), Effet(3, TypeEffet::PIOCHE, 1, ConditionEffet::VERT_ALLY) },
    true, 3
);

Champion torgern_rocksplitter(72, "Torgern Rocksplitter", 7,  FactionCarte::VERT,
    "{Expend}: {Gain 4 combat}\nTarget opponent discards a card.",
    { Effet(1, TypeEffet::EXPEND_CHAMPION, 0), Effet(2, TypeEffet::DMG, 4), Effet(3, TypeEffet::FORCE_DISCARD_OPPONENT, 1) },
    true, 7
);


// =========================
// OBJETS (NEUTRES)
// =========================

Carte fire_gem(201, "Fire Gem", 2, TypeCarte::OBJET, FactionCarte::NEUTRE,
    "Gain 2 gold. Sacrifice: Gain 3 combat",
    { Effet(1, TypeEffet::OR, 2), Effet(2, TypeEffet::DMG, 3, ConditionEffet::SACRIFICE_TO_MARCHE) }
);

Carte ruby(202, "Ruby", 0, TypeCarte::OBJET, FactionCarte::NEUTRE,
    "Gain 2 gold",
    { Effet(1, TypeEffet::OR, 2) }
);

Carte dagger(203, "Dagger", 0, TypeCarte::OBJET, FactionCarte::NEUTRE,
    "Gain 1 combat",
    { Effet(1, TypeEffet::DMG, 1) }
);

Carte shortsword(204, "Shortsword", 0, TypeCarte::OBJET, FactionCarte::NEUTRE,
    "Gain 2 combat",
    { Effet(1, TypeEffet::DMG, 2) }
);

// 7 cartes Gold distinctes pour le deck de base
Carte gold1(205, "Gold", 0, TypeCarte::OBJET, FactionCarte::NEUTRE,
    "Gain 1 gold",
    { Effet(1, TypeEffet::OR, 1) }
);

Carte gold2(206, "Gold", 0, TypeCarte::OBJET, FactionCarte::NEUTRE,
    "Gain 1 gold",
    { Effet(1, TypeEffet::OR, 1) }
);

Carte gold3(207, "Gold", 0, TypeCarte::OBJET, FactionCarte::NEUTRE,
    "Gain 1 gold",
    { Effet(1, TypeEffet::OR, 1) }
);

Carte gold4(208, "Gold", 0, TypeCarte::OBJET, FactionCarte::NEUTRE,
    "Gain 1 gold",
    { Effet(1, TypeEffet::OR, 1) }
);

Carte gold5(209, "Gold", 0, TypeCarte::OBJET, FactionCarte::NEUTRE,
    "Gain 1 gold",
    { Effet(1, TypeEffet::OR, 1) }
);

Carte gold6(210, "Gold", 0, TypeCarte::OBJET, FactionCarte::NEUTRE,
    "Gain 1 gold",
    { Effet(1, TypeEffet::OR, 1) }
);

Carte gold7(211, "Gold", 0, TypeCarte::OBJET, FactionCarte::NEUTRE,
    "Gain 1 gold",
    { Effet(1, TypeEffet::OR, 1) }
);

std::vector<Carte*> initCarteDB() {
    std::vector<Carte*> carte_db = {
        // JAUNES
        &close_ranks,
        &command,
        &domination,
        &rally_the_troops,
        &recruit1,           // indiqué "3 cartes" dans la base
        &recruit2,           // indiqué "3 cartes" dans la base
        &recruit3,           // indiqué "3 cartes" dans la base
        &taxation1,          // indiqué "3 cartes" dans la base
        &taxation2,          // indiqué "3 cartes" dans la base
        &taxation3,          // indiqué "3 cartes" dans la base
        &word_of_power,
        &arkus_imperial_dragon,
        &darian_war_mage,
        &master_weyan,
        &cristov_the_just,
        &kraka_high_priest,
        &tithe_priest1,      // indiqué "2 cartes" dans la base
        &tithe_priest2,      // indiqué "2 cartes" dans la base
        &man_at_arms1,       // indiqué "2 cartes" dans la base
        &man_at_arms2,        // indiqué "2 cartes" dans la base

        // BLEU
        &fire_bomb,
        &deception,
        &bribe1,
        &bribe2,
        &bribe3,
        &profit1,
        &profit2,
        &profit3,
        &death_threat,
        &hit_job,
        &intimidation1,
        &intimidation2,
        &smash_and_grab,
        &rake_master_assassin,
        &myros_thin_mage,
        &parov_the_enforcer,
        &rasmus_the_smuggler,
        &street_thug1,
        &street_thug2,
        &borg_ogre_mercenary,

        // ROUGE
        &dark_reward,
        &influence1,
        &influence2,
        &influence3,
        &death_touch1,
        &death_touch2,
        &death_touch3,
        &life_drain,
        &the_rot1,
        &the_rot2,
        &dark_energy,
        &tyrannor_the_devorer,
        &cult_priest1,
        &cult_priest2,
        &death_cultist1,
        &death_cultist2,
        &rayla_endweaver,
        &varrick_the_necromancer,
        &krythos_master_vampire,
        &lys_the_unseen,

        // VERT
        &natures_bounty,
        &elven_gift1,
        &elven_gift2,
        &elven_gift3,
        &elven_curse1,
        &elven_curse2,
        &rampage,
        &spark1,
        &spark2,
        &spark3,
        &wolf_form,
        &broelyn_loreweaver,
        &grak_storm_giant,
        &dire_wolf,
        &wolf_shaman1,
        &wolf_shaman2,
        &cron_the_berserker,
        &orc_grunt1,
        &orc_grunt2,
        &torgern_rocksplitter,

        &fire_gem
    };

    return carte_db;
}

std::vector<Carte*> creerDeckMarche() {
    std::vector<Carte*> deck_marche;
    for (auto carte : carte_db) {
        int id = carte->getId();
        // Exclure la carte Fire Gem (id 201) du deck de la marche
        if (id != 201 ) {
            deck_marche.push_back(carte);
        }
    }
    return deck_marche;
}

std::vector<Carte*> carte_db = initCarteDB();

// ========== FONCTIONS D'ACCES ==========

// Obtenir une carte par son ID
Carte* getCarteById(int id) {
    for (auto carte : carte_db) {
        if (carte->getId() == id) {
            return carte;
        }
    }
    return nullptr;
}

// Obtenir une carte par son nom
Carte* getCarteByName(const std::string& nom) {
    for (auto carte : carte_db) {
        if (carte->getNom() == nom) {
            return carte;
        }
    }
    return nullptr;
}

// 7 or + 1 dague + 1 ruby + 1 shortsword
std::vector<Carte*> creerDeckDeBase() {
    std::vector<Carte*> deck={
        &gold1,
        &gold2,
        &gold3,
        &gold4,
        &gold5,
        &gold6,
        &gold7,
        &dagger,
        &ruby,
        &shortsword
    };

    return deck;
}