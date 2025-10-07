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
    int id;
    std::string nom;
    int cout;
    TypeCarte type;
    FactionCarte faction;
    std::string description;
    std::vector<std::shared_ptr<Effet>> effets;

public:
    Carte(int id, const std::string& nom, int cout, TypeCarte type, 
          FactionCarte faction, const std::string& description);
    
    // Getters
    int getId() const { return id; }
    const std::string& getNom() const { return nom; }
    int getCout() const { return cout; }
    TypeCarte getType() const { return type; }
    FactionCarte getFaction() const { return faction; }
    const std::string& getDescription() const { return description; }
    const std::vector<std::shared_ptr<Effet>>& getEffets() const { return effets; }
    
    // Setters
    void setNom(const std::string& nom) { this->nom = nom; }
    void setCout(int cout) { this->cout = cout; }
    void setType(TypeCarte type) { this->type = type; }
    void setFaction(FactionCarte faction) { this->faction = faction; }
    void setDescription(const std::string& description) { this->description = description; }
    
    // Méthodes utilitaires pour conversion string
    static std::string typeToString(TypeCarte type);
    static std::string factionToString(FactionCarte faction);
    static TypeCarte stringToType(const std::string& str);
    static FactionCarte stringToFaction(const std::string& str);
    
    // Méthodes
    void ajouterEffet(std::shared_ptr<Effet> effet);
    virtual void afficher() const;
    
    virtual ~Carte() = default;
};

#endif // CARTE_H