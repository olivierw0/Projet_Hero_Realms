#ifndef EFFET_H
#define EFFET_H

#include <string>

class Effet {

enum class TypeEffet {
    OR,                              // Gain d'or
    DMG,                             // Dégâts de combat
    PIOCHE,                          // Piocher des cartes
    SOIN,                            // Gagner de la santé
    ADV_DEFAUSSE,                    // Adversaire défausse
    PREPARE_CHAMPION,                // Préparer un champion
    STUN,                            // Étourdir un champion
    HAND_NEXT_ACQUIRED,              // Mettre la prochaine carte acquise en main
    TOP_DECK_NEXT_ACQUIRED_ACTION,   // Mettre la prochaine action acquise sur le dessus du deck
    TOP_DECK_FROM_DISCARD,           // Prendre une carte de la défausse et la mettre sur le dessus du deck
    TOP_DECK_NEXT_ACQUIRED,          // Mettre la prochaine carte acquise sur le dessus du deck
    SACRIFICE,                       // Effet de sacrifice
    FORCE_DISCARD_OPPONENT,          // Forcer l'adversaire à défausser
    DRAW_DISCARD                     // Piocher et défausser
};

enum class ConditionEffet {
    AUCUNE,                          // Aucune condition
    DEFAUSSE,                        // Condition liée à la défausse
    ROUGE_ALLY,                      // Allié rouge requis
    JAUNE_ALLY,                      // Allié jaune requis  
    VERT_ALLY,                       // Allié vert requis
    BLEU_ALLY,                       // Allié bleu requis
    SACRIFICE,                       // Condition de sacrifice
    NB_CHAMPIONS,                    // Nombre de champions en jeu
    NB_GARDES,                       // Nombre de gardes en jeu
    SACRIFICE_HAND_DISCARD,          // Sacrifice depuis la main ou la défausse
    NB_VERT_CARDS_IN_PLAY           // Nombre de cartes vertes en jeu
};

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

    // Méthode principale pour activer l'effet quand une carte est jouée
    void activerEffet(class Joueur& joueurActif, class Joueur& adversaire) const;

private:
    // Méthode pour vérifier si les conditions de l'effet sont remplies
    bool verifierConditions(const class Joueur& joueurActif, const class Joueur& adversaire) const;
};

#endif // EFFET_H