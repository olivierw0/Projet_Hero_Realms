#ifndef CARTE_H
#define CARTE_H

#include <string>
#include <vector>
#include <memory>
#include "effet.h"

// Énumérations pour les types et factions de cartes
enum class TypeCarte {
    ACTION,
    OBJET,
    CHAMPION
};

enum class FactionCarte {
    ROUGE,      // Faction de Nécros
    BLEU,       // Faction de la Guilde
    VERT,       // Faction Sauvage
    JAUNE,      // Faction Impériale
    NEUTRE      // Cartes de Base
};

class Carte {
private:
    int id;        // ID unique de cette carte
    std::string nom;
    int cout;
    TypeCarte type;
    FactionCarte faction;
    std::string description;
    std::vector<Effet> effets;

public:
    // Constructeur par défaut
    Carte();
    
    // Destructeur virtuel pour rendre la classe polymorphe
    virtual ~Carte();

    // Constructeur avec paramètres
    Carte(int id, const std::string& nom, int cout, TypeCarte type,
          FactionCarte faction, const std::string& description,
          const std::vector<Effet>& effets);

    // Méthodes pour accéder aux attributs
    int getId() const;
    std::string getNom() const;
    int getCout() const;
    TypeCarte getType() const;
    FactionCarte getFaction() const;
    std::string getDescription() const;
    const std::vector<Effet>& getEffets() const;

    // Méthode virtuelle pour les PV (redéfinie dans Champion)
    virtual int getPV() const;

};

#endif // CARTE_H