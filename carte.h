#ifndef CARTE_H
#define CARTE_H

#include <string>
#include <vector>
#include <memory>

class Effet;

class Carte {
private:
    int id;
    std::string nom;
    int cout;
    std::string type; // action, objet, champion
    std::string faction;
    std::string description;
    std::vector<std::shared_ptr<Effet>> effets;

public:
    Carte(int id, const std::string& nom, int cout, const std::string& type, 
          const std::string& faction, const std::string& description);
    
    // Getters
    int getId() const { return id; }
    const std::string& getNom() const { return nom; }
    int getCout() const { return cout; }
    const std::string& getType() const { return type; }
    const std::string& getFaction() const { return faction; }
    const std::string& getDescription() const { return description; }
    const std::vector<std::shared_ptr<Effet>>& getEffets() const { return effets; }
    
    // Setters
    void setNom(const std::string& nom) { this->nom = nom; }
    void setCout(int cout) { this->cout = cout; }
    void setType(const std::string& type) { this->type = type; }
    void setFaction(const std::string& faction) { this->faction = faction; }
    void setDescription(const std::string& description) { this->description = description; }
    
    // Méthodes
    void ajouterEffet(std::shared_ptr<Effet> effet);
    virtual void afficher() const;
    
    virtual ~Carte() = default;
};

#endif // CARTE_H