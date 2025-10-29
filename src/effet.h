#ifndef EFFET_H
#define EFFET_H

#include <string>
enum class TypeEffet {
    EXPEND_CHAMPION,  // Taper les champions (à tester)
    DMG, //OK
    DMG_ou_SOIN, // valeurs fixe (différentes entre DMG et SOIN) à définir dans l'effet (à tester)
    DRAW_DISCARD, // (à tester)
    FORCE_DISCARD_OPPONENT, // (à tester)
    HAND_NEXT_ACQUIRED, // (à tester)
    OR, // OK
    OR_ou_nDMG, // Choisir entre 1 or et n Points de combat (à tester)
    OR_ou_SOIN_per_CHAMP, // valeur fixe à 1 (un seul champion a cette capacité) (à tester)
    PIOCHE, // OK
    PREPARE_CHAMPION, // (à tester)
    SACRIFICE_HAND_DISCARD,  // (à tester)
    SOIN, // OK
    SOIN_per_CHAMP, // (à tester)
    STUN, // (à tester)
    TOP_DECK_FROM_DISCARD,  // (à tester)
    TOP_DECK_NEXT_ACQUIRED, // (à tester)
    TOP_DECK_NEXT_ACQUIRED_ACTION // (à tester)
};

enum class ConditionEffet {
    AUCUNE,                          // Aucune condition
    ROUGE_ALLY,                      // Allié rouge requis
    JAUNE_ALLY,                      // Allié jaune requis  
    VERT_ALLY,                       // Allié vert requis
    BLEU_ALLY,                       // Allié bleu requis
    SACRIFICE,                       // Condition de sacrifice
    SACRIFICE_TO_MARCHE,            // Condition de sacrifice pour la zone de marche
    NB_CHAMPIONS,                    // Nombre de champions en jeu
    NB_GARDES,                       // Nombre de gardes en jeu
    SACRIFICE_HAND_DISCARD,          // Sacrifice depuis la main ou la défausse
    NB_VERT_CARDS_IN_PLAY            // Nombre de cartes vertes en jeu
};

class Effet {

private:
    int id;
    TypeEffet type;
    int valeur;
    ConditionEffet condition; 
    int param;

public:
    // Constructeur par défaut
    Effet() : id(0), type(TypeEffet::OR), valeur(0), condition(ConditionEffet::AUCUNE), param(0) {}

    // Constructeur avec paramètres
    Effet(int id, TypeEffet type, int valeur, ConditionEffet condition = ConditionEffet::AUCUNE, int param = 0);

    // Getters
    int getId() const { return id; }
    TypeEffet getType() const { return type; }
    int getValeur() const { return valeur; }
    ConditionEffet getCondition() const { return condition; }

    // Activation de l'effet
    void activerEffet(class Joueur& joueurActif, class Joueur& adversaire, const class Carte* source = nullptr) const;

    // Méthode pour vérifier si les conditions de l'effet sont remplies
    bool verifierConditions(const class Joueur& joueurActif, const class Joueur& adversaire) const;
};

#endif // EFFET_H