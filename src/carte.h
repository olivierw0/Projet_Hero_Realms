#ifndef CARTE_H
#define CARTE_H

#include <string>
#include <vector>
#include <memory>

class Effet;

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
    Carte() : id(0), nom(""), cout(0), type(TypeCarte::ACTION), faction(FactionCarte::NEUTRE), description("") {}

    // Constructeur avec paramètres
    Carte(int id, const std::string& nom, int cout, TypeCarte type,
          FactionCarte faction, const std::string& description,
          const std::vector<Effet>& effets = {})
        : id(id), nom(nom), cout(cout), type(type), faction(faction),
          description(description), effets(effets) {}

    // Méthodes pour accéder aux attributs
    int getId() const { return id; }
    std::string getNom() const { return nom; }
    int getCout() const { return cout; }
    TypeCarte getType() const { return type; }
    FactionCarte getFaction() const { return faction; }
    std::string getDescription() const { return description; }
    const std::vector<Effet>& getEffets() const { return effets; }


};

#endif // CARTE_H