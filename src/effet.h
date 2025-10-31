#ifndef EFFET_H
#define EFFET_H

#include <string>
enum class TypeEffet {
    DMG, //OK
    DMG_ou_SOIN, // valeurs fixe (différentes entre DMG et SOIN) à définir dans l'effet - OK
    DRAW_DISCARD, // OK
    FORCE_DISCARD_OPPONENT, // OK
    HAND_NEXT_ACQUIRED, // OK
    OR, // OK
    OR_ou_nDMG, // Choisir entre 1 or et n Points de combat - OK
    OR_ou_SOIN_per_CHAMP, // valeur fixe à 1 (un seul champion a cette capacité) - OK
    PIOCHE, // OK
    PREPARE_CHAMPION, // OK
    SACRIFICE_HAND_DISCARD,  // OK
    SOIN, // OK
    SOIN_per_CHAMP, // OK
    STUN, // OK
    TOP_DECK_FROM_DISCARD, // OK
    TOP_DECK_NEXT_ACQUIRED, 
    TOP_DECK_NEXT_ACQUIRED_ACTION, 
    DMG_per_VERT_CARDS,            // Nombre de cartes vertes en jeu
    DMG_per_CHAMPION,                    // Nombre de champions en jeu
    DMG_per_GUARD                        // Nombre de gardes en jeu
};

enum class ConditionEffet {
    AUCUNE,                          // Aucune condition
    ROUGE_ALLY,                      // Allié rouge requis
    JAUNE_ALLY,                      // Allié jaune requis  
    VERT_ALLY,                       // Allié vert requis
    BLEU_ALLY,                       // Allié bleu requis
    SACRIFICE,                       // Condition de sacrifice
    SACRIFICE_TO_MARCHE,             // Condition de sacrifice pour la zone de marche
    COND_SACRIFICE_HAND_DISCARD,     // Sacrifice depuis la main ou la défausse

};

class Effet {

private:
    int id;
    TypeEffet type;
    int valeur;
    ConditionEffet condition; 

public:
    // Constructeur par défaut
    Effet() : id(0), type(TypeEffet::OR), valeur(0), condition(ConditionEffet::AUCUNE) {}

    // Constructeur avec paramètres
    Effet(int id, TypeEffet type, int valeur, ConditionEffet condition = ConditionEffet::AUCUNE);

    // Getters
    int getId() const { return id; }
    TypeEffet getType() const { return type; }
    int getValeur() const { return valeur; }
    ConditionEffet getCondition() const { return condition; }

    // Activation de l'effet
    void activerEffet(class Joueur& joueurActif, class Joueur& adversaire, const class Carte* source = nullptr) const;

    // Méthode pour vérifier si les conditions de l'effet sont remplies
    bool verifierConditions(class Joueur& joueurActif, const class Carte* source = nullptr) const;
};

#endif // EFFET_H