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
    { Effet(1, Effet::Effet::TypeEffet::DMG, 5) }
);

Carte command(2, "Command", 5, TypeCarte::ACTION, FactionCarte::JAUNE,
    "{Gain 2 gold} {Gain 3 combat} {Gain 4 health} {Piochez une carte}.",
    { Effet(1, Effet::TypeEffet::OR, 2), Effet(2, Effet::TypeEffet::DMG, 3), Effet(3, Effet::TypeEffet::SOIN, 4), Effet(4, Effet::TypeEffet::PIOCHE, 1) }
);

Carte domination(3, "Domination", 7, TypeCarte::ACTION, FactionCarte::JAUNE,
    "Gain 6 combat. Gain 6 health",
    { Effet(1, Effet::TypeEffet::DMG, 6), Effet(2, Effet::TypeEffet::SOIN, 6) }
);

Carte rally_the_troops(4, "Rally the Troops", 4, TypeCarte::ACTION, FactionCarte::JAUNE,
    "Gain 5 combat. Gain 5 health",
    { Effet(1, Effet::TypeEffet::DMG, 5), Effet(2, Effet::TypeEffet::SOIN, 5) }
);

Carte recruit(5, "Recruit", 2, TypeCarte::ACTION, FactionCarte::JAUNE,
    "Gain 2 gold. Gain 3 health",
    { Effet(1, Effet::TypeEffet::OR, 2), Effet(2, Effet::TypeEffet::SOIN, 3) }
);

Carte taxation(6, "Taxation", 1, TypeCarte::ACTION, FactionCarte::JAUNE,
    "Gain 2 gold",
    { Effet(1, Effet::TypeEffet::OR, 2) }
);

Carte word_of_power(7, "Word of Power", 6, TypeCarte::ACTION, FactionCarte::JAUNE,
    "Draw two cards",
    { Effet(1, Effet::TypeEffet::PIOCHE, 2) }
);

// Champions jaunes
Carte arkus_imperial_dragon(8, "Arkus, Imperial Dragon", 8, TypeCarte::CHAMPION, FactionCarte::JAUNE,
    "{Expend}: {Gain 5 combat} Draw a card. {Jaune Ally}: {Gain 6 health}",
    { Effet(1, Effet::TypeEffet::DMG, 5), Effet(2, Effet::TypeEffet::PIOCHE, 1), Effet(3, Effet::TypeEffet::SOIN, 6, Effet::ConditionEffet::JAUNE_ALLY) },
    true, 6
);

Carte darian_war_mage(9, "Darian, War Mage", 4, TypeCarte::CHAMPION, FactionCarte::JAUNE,
    "{Expend}: {Gain 3 combat} <i>or</i> {Gain 4 health}",
    { Effet(1, Effet::TypeEffet::DMG, 3), Effet(2, Effet::TypeEffet::SOIN, 4) }
);

Carte master_weyan(10, "Master Weyan", 4, TypeCarte::CHAMPION, FactionCarte::JAUNE,
    "{Expend}: {Gain 3 combat} +{1 combat} for each other champion you have in play.",
    { Effet(1, Effet::TypeEffet::DMG, 3), Effet(2, Effet::TypeEffet::DMG, 1, Effet::ConditionEffet::NB_CHAMPIONS) },
    true, 4 
);

Carte cristov_the_just(11, "Cristov, the Just", 5, TypeCarte::CHAMPION, FactionCarte::JAUNE,
    "{Expend}: {Gain 2 combat} {Gain 3 health} <hr> {Jaune Ally}: Draw a card.",
    { Effet(1, Effet::TypeEffet::DMG, 2), Effet(2, Effet::TypeEffet::SOIN, 3), Effet(3, Effet::TypeEffet::PIOCHE, 1, Effet::Effet::ConditionEffet::JAUNE_ALLY) },
    true, 5
);

Carte kraka_high_priest(12, "Kraka, High Priest", 6, TypeCarte::CHAMPION, FactionCarte::JAUNE,
    "{Expend}: {Gain 2 health} Draw a card. <hr> {Jaune Ally}: Gain {2 health} for each champion you have in play.",
    { Effet(1, Effet::TypeEffet::SOIN, 2), Effet(2, Effet::TypeEffet::PIOCHE, 1), Effet(3, Effet::TypeEffet::SOIN, 2, Effet::Effet::ConditionEffet::JAUNE_ALLY), Effet(4, Effet::TypeEffet::SOIN, 1, Effet::ConditionEffet::NB_CHAMPIONS) },
    true, 6
);

Carte tithe_priest(13, "Tithe Priest", 2, TypeCarte::CHAMPION, FactionCarte::JAUNE,
    "{Expend}: {Gain 1 gold} <i>or</i> Gain {1 health} for each champion you have in play.",
    { Effet(1, Effet::TypeEffet::PIOCHE, 2) },
    false, 3
);

Carte man_at_arms(14, "Man-at-Arms", 3, TypeCarte::CHAMPION, FactionCarte::JAUNE,
    "{Expend}: {Gain 2 combat} +{1 combat} for each other guard you have in play.",
    { Effet(1, Effet::TypeEffet::DMG, 2), Effet(2, Effet::TypeEffet::DMG, 1, Effet::ConditionEffet::NB_GARDES) },
    true, 4
);

// =========================
// FACTION : BLEU
// =========================

// Actions bleues
Carte fire_bomb(
    20, "Fire Bomb", 8, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 8 combat} Stun target champion. Draw a card. <hr> {Sacrifice}: {Gain 5 combat}",
    { Effet(1, Effet::TypeEffet::DMG, 8), Effet(2, Effet::TypeEffet::STUN, 0), Effet(3, Effet::TypeEffet::PIOCHE, 1), Effet(4, Effet::TypeEffet::DMG, 5, Effet::ConditionEffet::SACRIFICE) }
);

Carte deception(
    21, "Deception", 5, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 2 gold}\nDraw a card.\n<hr>\n{Bleu Ally}: Put the next card you acquire this turn into your hand.",
    { Effet(1, Effet::TypeEffet::OR, 2), Effet(2, Effet::TypeEffet::PIOCHE, 1), Effet(3, Effet::TypeEffet::HAND_NEXT_ACQUIRED, 0, Effet::ConditionEffet::BLEU_ALLY) }
);

Carte bribe(
    22, "Bribe", 3, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 3 gold}\n<hr>\n{Bleu Ally}: Put the next action you acquire this turn on top of your deck.",
    { Effet(1, Effet::TypeEffet::OR, 3), Effet(2, Effet::TypeEffet::TOP_DECK_NEXT_ACQUIRED_ACTION, 0, Effet::ConditionEffet::BLEU_ALLY) }
);

Carte profit(
    23, "Profit", 1, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 2 gold}\n<hr>\n{Bleu Ally}: {Gain 4 combat}",
    { Effet(1, Effet::TypeEffet::OR, 2), Effet(2, Effet::TypeEffet::DMG, 4, Effet::ConditionEffet::BLEU_ALLY) }
);

Carte death_threat(
    24, "Death Threat", 3, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 1 combat}\nDraw a card.\n<hr>\n{Bleu Ally}: Stun target champion.",
    { Effet(1, Effet::TypeEffet::DMG, 1), Effet(2, Effet::TypeEffet::PIOCHE, 1), Effet(3, Effet::TypeEffet::STUN, 0, Effet::ConditionEffet::BLEU_ALLY) }
);

Carte hit_job(
    25, "Hit Job", 4, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 7 combat}\n<hr>\n{Bleu Ally}: Stun target champion.",
    { Effet(1, Effet::TypeEffet::DMG, 7), Effet(2, Effet::TypeEffet::STUN, 0, Effet::ConditionEffet::BLEU_ALLY) }
);

Carte intimidation(
    26, "Intimidation", 6, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 5 combat}\n<hr>\n{Bleu Ally}: {Gain 2 gold}",
    { Effet(1, Effet::TypeEffet::DMG, 5), Effet(2, Effet::TypeEffet::OR, 2, Effet::ConditionEffet::BLEU_ALLY) }
);

Carte smash_and_grab(
    27, "Smash and Grab", 6, TypeCarte::ACTION, FactionCarte::BLEU,
    "{Gain 6 combat}\nYou may put a card from your discard pile on top of your deck.",
    { Effet(1, Effet::TypeEffet::DMG, 6), Effet(2, Effet::TypeEffet::TOP_DECK_FROM_DISCARD, 0) }
);

// Champions bleus
Carte rake_master_assassin(
    28, "Rake Master Assassin", 7, TypeCarte::CHAMPION, FactionCarte::BLEU,
    "{Expend}: {Gain 4 combat} You may stun target champion.",
    { Effet(1, Effet::TypeEffet::DMG, 4), Effet(2, Effet::TypeEffet::STUN, 0) },
    false, 7
);

Carte myros_thin_mage(
    29, "Myros, Thin Mage", 5, TypeCarte::CHAMPION, FactionCarte::BLEU,
    "{Expend}: {Gain 3 gold}\n<hr>\n{Bleu Ally}: {Gain 4 combat}",
    { Effet(1, Effet::TypeEffet::OR, 3), Effet(2, Effet::TypeEffet::DMG, 4, Effet::ConditionEffet::BLEU_ALLY) },
    true, 3
);

Carte parov_the_enforcer(
    30, "Parov, the Enforcer", 5, TypeCarte::CHAMPION, FactionCarte::BLEU,
    "{Expend}: {Gain 3 combat}\n<hr>\n{Bleu Ally}: Draw a card.",
    { Effet(1, Effet::TypeEffet::DMG, 3), Effet(2, Effet::TypeEffet::PIOCHE, 1, Effet::ConditionEffet::BLEU_ALLY) },
    true, 5
);

Carte rasmus_the_smuggler(
    31, "Rasmus, the Smuggler", 4, TypeCarte::CHAMPION, FactionCarte::BLEU,
    "{Expend}: {Gain 2 gold}\n<hr>\n{Bleu Ally}: Put the next card you acquire this turn on top of your deck.",
    { Effet(1, Effet::TypeEffet::OR, 2), Effet(2, Effet::TypeEffet::TOP_DECK_NEXT_ACQUIRED, 0, Effet::ConditionEffet::BLEU_ALLY) },
    false, 5
);

Carte street_thug(
    32, "Street Thug", 3, TypeCarte::CHAMPION, FactionCarte::BLEU,
    "{Expend}: {Gain 1 gold} <i>or</i> {Gain 2 combat}",
    { Effet(1, Effet::TypeEffet::OR, 1), Effet(2, Effet::TypeEffet::DMG, 2) },
    false, 4
);

Carte borg_ogre_mercenary(
    33, "Borg, Ogre Mercenary", 6, TypeCarte::CHAMPION, FactionCarte::BLEU,
    "{Expend}: {Gain 4 combat}",
    { Effet(1, Effet::TypeEffet::DMG, 4) },
    true, 6
);

// =========================
// FACTION : ROUGE
// =========================

// Actions rouges
Carte dark_reward(40, "Dark Reward", 5, TypeCarte::ACTION, FactionCarte::ROUGE,
    "{Gain 3 gold}\nYou may sacrifice a card in your hand or discard pile.\n<hr>\n{Rouge Ally}: {Gain 6 combat}",
    { Effet(1, Effet::TypeEffet::OR, 3), Effet(2, Effet::TypeEffet::DMG, 6, Effet::ConditionEffet::ROUGE_ALLY), Effet(3, Effet::ConditionEffet::SACRIFICE_HAND_DISCARD, {0,1}) }
);

Carte influence(41, "Influence", 2, TypeCarte::ACTION, FactionCarte::ROUGE,
    "{Gain 3 gold}\n<hr>\n{Sacrifice}: {Gain 3 combat}",
    { Effet(1, Effet::TypeEffet::OR, 3), Effet(2, Effet::TypeEffet::DMG, 3, Effet::ConditionEffet::SACRIFICE) }
);

Carte death_touch(42, "Death Touch", 1, TypeCarte::ACTION, FactionCarte::ROUGE,
    "{Gain 2 combat}\nYou may sacrifice a card in your hand or discard pile.\n<hr>\n{Rouge Ally}: {Gain 2 combat}",
    { Effet(1, Effet::TypeEffet::DMG, 2), Effet(2, Effet::TypeEffet::DMG, 2, Effet::ConditionEffet::ROUGE_ALLY), Effet(3, Effet::ConditionEffet::SACRIFICE_HAND_DISCARD, {0,1}) }
);

Carte life_drain(43, "Life Drain", 6, TypeCarte::ACTION, FactionCarte::ROUGE,
    "{Gain 8 combat}\nYou may sacrifice a card in your hand or discard pile.\n<hr>\n{Rouge Ally}: Draw a card.",
    { Effet(1, Effet::TypeEffet::DMG, 8), Effet(2, Effet::TypeEffet::PIOCHE, 1, Effet::ConditionEffet::ROUGE_ALLY), Effet(3, Effet::ConditionEffet::SACRIFICE_HAND_DISCARD, {0,1}) }
);

Carte the_rot(44, "The Rot", 3, TypeCarte::ACTION, FactionCarte::ROUGE,
    "{Gain 4 combat}\nYou may sacrifice a card in your hand or discard pile.\n<hr>\n{Rouge Ally}: {Gain 3 combat}",
    { Effet(1, Effet::TypeEffet::DMG, 4), Effet(2, Effet::TypeEffet::DMG, 3, Effet::ConditionEffet::ROUGE_ALLY), Effet(3, Effet::ConditionEffet::SACRIFICE_HAND_DISCARD, {0,1}) }
);

Carte dark_energy(45, "Dark Energy", 4, TypeCarte::ACTION, FactionCarte::ROUGE,
    "{Gain 7 combat}\n<hr>\n{Rouge Ally}: Draw a card.",
    { Effet(1, Effet::TypeEffet::DMG, 7), Effet(2, Effet::TypeEffet::PIOCHE, 1, Effet::ConditionEffet::ROUGE_ALLY) }
);

// Champions rouges
Carte tyrannor_the_devorer(46, "Tyrannor, the Devorer", 8, TypeCarte::CHAMPION, FactionCarte::ROUGE,
    "{Expend}: {Gain 4 combat}\nYou may sacrifice up to two cards in your hand and/or discard pile.\n<hr>\n{Rouge Ally}: Draw a card.",
    { Effet(1, Effet::TypeEffet::DMG, 5), Effet(2, Effet::TypeEffet::SACRIFICE_HAND_DISCARD, {0,1}) },
    true, 6
);

Carte cult_priest(47, "Cult Priest", 3, TypeCarte::CHAMPION, FactionCarte::ROUGE,
    "{Expend}: {Gain 1 gold} <i>or</i> {Gain 1 combat}\n<hr>\n{Rouge Ally}: {Gain 4 combat}",
    { Effet(1, Effet::TypeEffet::OR, 1), Effet(2, Effet::TypeEffet::SOIN, 2, Effet::ConditionEffet::NB_CHAMPIONS) },
    false, 4
);

Carte death_cultist(48, "Death Cultist", 2, TypeCarte::CHAMPION, FactionCarte::ROUGE,
    "{Expend}: {Gain 2 combat}",
    { Effet(1, Effet::TypeEffet::DMG, 2), Effet(2, Effet::TypeEffet::SOIN, 2, Effet::ConditionEffet::ROUGE_ALLY) },
    true, 3
);

Carte rayla_endweaver(49, "Rayla Endweaver", 4, TypeCarte::CHAMPION, FactionCarte::ROUGE,
    "{Expend}: {Gain 3 combat}\n<hr>\n{Rouge Ally}: Draw a card.",
    { Effet(1, Effet::TypeEffet::DMG, 3), Effet(2, Effet::TypeEffet::PIOCHE, 1, Effet::ConditionEffet::ROUGE_ALLY) },
    false, 4
);

Carte varrick_the_necromancer(50, "Varrick, the Necromancer", 5, TypeCarte::CHAMPION, FactionCarte::ROUGE,
    "{Expend}: Take a champion from your discard pile and put it on top of your deck.\n<hr>\n{Rouge Ally}: Draw a card.",
    { Effet(1, Effet::TypeEffet::TOP_DECK_FROM_DISCARD, 0), Effet(2, Effet::TypeEffet::PIOCHE, 1, Effet::ConditionEffet::ROUGE_ALLY) },
    false, 3
);

Carte krythos_master_vampire(51, "Krythos, Master Vampire", 7, TypeCarte::CHAMPION, FactionCarte::ROUGE,
    "{Expend}: {Gain 3 combat}\nYou may sacrifice a card in your hand or discard pile.\nIf you do, gain an additional {3 combat}.",
    { Effet(1, Effet::TypeEffet::DMG, 3), Effet(2, Effet::TypeEffet::DMG, 3, Effet::ConditionEffet::SACRIFICE_HAND_DISCARD, {0,1}) },
    true, 6
);

Carte lys_the_unseen(52, "Lys, the Unseen", 6, TypeCarte::CHAMPION, FactionCarte::ROUGE,
    "{Expend}: {Gain 2 combat}\nYou may sacrifice a card in your hand or discard pile.\nIf you do, gain an additional {2 combat}.",
    { Effet(1, Effet::TypeEffet::DMG, 2), Effet(2, Effet::TypeEffet::DMG, 2, Effet::ConditionEffet::SACRIFICE_HAND_DISCARD, {0,1}) },
    true, 5
);

// =========================
// FACTION : VERT
// =========================

// Actions vertes
Carte natures_bounty(60, "Nature's Bounty", 4, TypeCarte::ACTION, FactionCarte::VERT,
    "{Gain 4 gold}\n{Vert Ally}: Target opponent discards a card.\n{Sacrifice}: {Gain 4 combat}",
    { Effet(1, Effet::TypeEffet::OR, 4), Effet(2, Effet::TypeEffet::FORCE_DISCARD_OPPONENT, 1, Effet::ConditionEffet::VERT_ALLY), Effet(3, Effet::TypeEffet::DMG, 4, Effet::ConditionEffet::SACRIFICE) }
);

Carte elven_gift(61, "Elven Gift", 2, TypeCarte::ACTION, FactionCarte::VERT,
    "{Gain 2 gold}\nYou may draw a card. If you do, discard a card.<hr>\n{Vert Ally}: {Gain 4 combat}",
    { Effet(1, Effet::TypeEffet::OR, 2), Effet(2, Effet::TypeEffet::DRAW_DISCARD, {0,1}), Effet(3, Effet::TypeEffet::DMG, 4, Effet::ConditionEffet::VERT_ALLY) }
);

Carte elven_curse(62, "Elven Curse", 3, TypeCarte::ACTION, FactionCarte::VERT,
    "{Gain 6 combat}\nTarget opponent discards a card.\n{Vert Ally}: {Gain 3 combat}",
    { Effet(1, Effet::TypeEffet::DMG, 6), Effet(2, Effet::TypeEffet::FORCE_DISCARD_OPPONENT, 1), Effet(3, Effet::TypeEffet::DMG, 3, Effet::ConditionEffet::VERT_ALLY) }
);

Carte rampage(63, "Rampage", 6, TypeCarte::ACTION, FactionCarte::VERT,
    "{Gain 6 combat}\nYou may draw up to two cards, then discard that many cards.",
    { Effet(1, Effet::TypeEffet::DMG, 6), Effet(2, Effet::TypeEffet::DRAW_DISCARD, {0,1,2}) }
);

Carte spark(64, "Spark", 1, TypeCarte::ACTION, FactionCarte::VERT,
    "{Gain 3 combat}\nTarget opponent discards a card.\n{Vert Ally}: {Gain 2 combat}",
    { Effet(1, Effet::TypeEffet::DMG, 3), Effet(2, Effet::TypeEffet::FORCE_DISCARD_OPPONENT, 1), Effet(3, Effet::TypeEffet::DMG, 2, Effet::ConditionEffet::VERT_ALLY) }
);

Carte wolf_form(65, "Wolf Form", 5, TypeCarte::ACTION, FactionCarte::VERT,
    "{Gain 8 combat}\nTarget opponent discards a card.\n<hr>\n{Sacrifice}: Target opponent discards a card.",
    { Effet(1, Effet::TypeEffet::DMG, 8), Effet(2, Effet::TypeEffet::FORCE_DISCARD_OPPONENT, 1), Effet(3, Effet::TypeEffet::FORCE_DISCARD_OPPONENT, 1, Effet::ConditionEffet::SACRIFICE) }
);

// Champions verts
Carte broelyn_loreweaver(66, "Broelyn, Loreweaver", 4, TypeCarte::CHAMPION, FactionCarte::VERT,
    "{Expend}: {Gain 2 gold}\n<hr>\n{Vert Ally}: Target opponent discards a card.",
    { Effet(1, Effet::TypeEffet::OR, 2), Effet(2, Effet::TypeEffet::FORCE_DISCARD_OPPONENT, 1, Effet::ConditionEffet::VERT_ALLY) },
    false, 6
);

Carte grak_storm_giant(67, "Grak, Storm Giant", 8, TypeCarte::CHAMPION, FactionCarte::VERT,
    "{Expend}: {Gain 6 combat}\nYou may draw a card. If you do, discard a card.\n<hr>\n{Vert Ally}: Draw a card, then discard a card.",
    { Effet(1, Effet::TypeEffet::DMG, 6), Effet(2, Effet::TypeEffet::DRAW_DISCARD, {0,1}), Effet(3, Effet::TypeEffet::DRAW_DISCARD, 1, Effet::ConditionEffet::VERT_ALLY) },
    true, 7
);

Carte dire_wolf(68, "Dire Wolf", 5, TypeCarte::CHAMPION, FactionCarte::VERT,
    "{Expend}: {Gain 3 combat}\n<hr>\n{Vert Ally}: {Gain 4 combat}",
    { Effet(1, Effet::TypeEffet::DMG, 3), Effet(2, Effet::TypeEffet::DMG, 4, Effet::ConditionEffet::VERT_ALLY) },
    true, 5
);

Carte wolf_shaman(69, "Wolf Shaman", 2, TypeCarte::CHAMPION, FactionCarte::VERT,
    "{Expend}: {Gain 2 combat}\n+{1 combat} for each other {Vert} card you have in play.",
    { Effet(1, Effet::TypeEffet::DMG, 2), Effet(2, Effet::TypeEffet::DMG, 1, Effet::ConditionEffet::NB_VERT_CARDS_IN_PLAY) },
    false, 4
);

Carte cron_the_berserker(70, "Cron, the Berserker", 6, TypeCarte::CHAMPION, FactionCarte::VERT,
    "{Expend}: {Gain 5 combat}\n<hr>\n{Vert Ally}: Draw a card.",
    { Effet(1, Effet::TypeEffet::DMG, 5), Effet(2, Effet::TypeEffet::PIOCHE, 1, Effet::ConditionEffet::VERT_ALLY) },
    true, 6
);

Carte orc_grunt(71, "Orc Grunt", 3, TypeCarte::CHAMPION, FactionCarte::VERT,
    "{Expend}: {Gain 2 combat}\n<hr>\n{Vert Ally}: Draw a card.",
    { Effet(1, Effet::TypeEffet::DMG, 2), Effet(2, Effet::TypeEffet::PIOCHE, 1, Effet::ConditionEffet::VERT_ALLY) },
    true, 3
);

Carte torgern_rocksplitter(72, "Torgern Rocksplitter", 7, TypeCarte::CHAMPION, FactionCarte::VERT,
    "{Expend}: {Gain 4 combat}\nTarget opponent discards a card.",
    { Effet(1, Effet::TypeEffet::DMG, 4), Effet(2, Effet::TypeEffet::FORCE_DISCARD_OPPONENT, 1) },
    true, 7
);


// =========================
// OBJETS (NEUTRES)
// =========================

Carte fire_gem(201, "Fire Gem", 2, TypeCarte::OBJET, FactionCarte::NEUTRE,
    "Gain 2 gold. Sacrifice: Gain 3 combat",
    { Effet(1, Effet::TypeEffet::OR, 2), Effet(2, Effet::TypeEffet::DMG, 3, Effet::ConditionEffet::SACRIFICE_TO_MARCHE) }
);

Carte ruby(202, "Ruby", 0, TypeCarte::OBJET, FactionCarte::NEUTRE,
    "Gain 2 gold",
    { Effet(1, Effet::TypeEffet::OR, 2) }
);

Carte dagger(203, "Dagger", 0, TypeCarte::OBJET, FactionCarte::NEUTRE,
    "Gain 1 combat",
    { Effet(1, Effet::TypeEffet::DMG, 1) }
);

Carte shortsword(204, "Shortsword", 0, TypeCarte::OBJET, FactionCarte::NEUTRE,
    "Gain 2 combat",
    { Effet(1, Effet::TypeEffet::DMG, 2) }
);

Carte gold(205, "Gold", 0, TypeCarte::OBJET, FactionCarte::NEUTRE,
    "Gain 1 gold",
    { Effet(1, Effet::TypeEffet::OR, 1) }
);

// Entrées carte_db pour la faction jaune (quantités : par défaut 1,
// explicitement mises si présentes dans la base originale)
std::vector<CarteAvecQuantite> carte_db = {
    { close_ranks, 1 },
    { command, 1 },
    { domination, 1 },
    { rally_the_troops, 1 },
    { recruit, 3 },           // indiqué "3 cartes" dans la base
    { taxation, 3 },          // indiqué "3 cartes" dans la base
    { word_of_power, 1 },
    { arkus_imperial_dragon, 1 },
    { darian_war_mage, 1 },
    { master_weyan, 1 },
    { cristov_the_just, 1 },
    { kraka_high_priest, 1 },
    { tithe_priest, 2 },      // indiqué "2 cartes" dans la base
    { man_at_arms, 2 }        // indiqué "2 cartes" dans la base
};


// Ajout au deck carte_db
carte_db.insert(carte_db.end(), {
    { fire_bomb, 1 },
    { deception, 1 },
    { bribe, 3 },
    { profit, 3 },
    { death_threat, 1 },
    { hit_job, 1 },
    { intimidation, 2 },
    { smash_and_grab, 1 },
    { rake_master_assassin, 1 },
    { myros_thin_mage, 1 },
    { parov_the_enforcer, 1 },
    { rasmus_the_smuggler, 1 },
    { street_thug, 2 },
    { borg_ogre_mercenary, 1 }
});


// Ajout au deck carte_db
carte_db.insert(carte_db.end(), {
    { dark_reward, 1 },
    { influence, 3 },
    { death_touch, 3 },
    { life_drain, 1 },
    { the_rot, 2 },
    { dark_energy, 1 },
    { tyrannor_the_devorer, 1 },
    { cult_priest, 2 },
    { death_cultist, 2 },
    { rayla_endweaver, 1 },
    { varrick_the_necromancer, 1 },
    { krythos_master_vampire, 1 },
    { lys_the_unseen, 1 }
});


// Ajout au deck carte_db
carte_db.insert(carte_db.end(), {
    { natures_bounty, 1 },
    { elven_gift, 3 },
    { elven_curse, 2 },
    { rampage, 1 },
    { spark, 3 },
    { wolf_form, 1 },
    { broelyn_loreweaver, 1 },
    { grak_storm_giant, 1 },
    { dire_wolf, 1 },
    { wolf_shaman, 2 },
    { cron_the_berserker, 1 },
    { orc_grunt, 2 },
    { torgern_rocksplitter, 1 }
});

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


// 7 or + 1 dague + 1 ruby + 1 shortsword
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