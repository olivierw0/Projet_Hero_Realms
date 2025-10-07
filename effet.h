#ifndef EFFET_H
#define EFFET_H

#include <string>

class Effet {
private:
    int id;
    std::string type; // "or", "dmg", "pioche", "soin", "sacrifice"
    int valeur;
    std::string condition_type; // "aucune", "faction", "champion"
    std::string condition_valeur; // ex: "Imperial", "Necros", id de champion...
    std::string activation; // "toujours", "sacrifice"

public:
    Effet(int id, const std::string& type, int valeur, 
          const std::string& condition_type = "aucune", 
          const std::string& condition_valeur = "",
          const std::string& activation = "toujours");
    
    // Getters
    int getId() const { return id; }
    const std::string& getType() const { return type; }
    int getValeur() const { return valeur; }
    const std::string& getConditionType() const { return condition_type; }
    const std::string& getConditionValeur() const { return condition_valeur; }
    const std::string& getActivation() const { return activation; }
    
    // Setters
    void setValeur(int valeur) { this->valeur = valeur; }
    void setConditionType(const std::string& condition_type) { this->condition_type = condition_type; }
    void setConditionValeur(const std::string& condition_valeur) { this->condition_valeur = condition_valeur; }
    void setActivation(const std::string& activation) { this->activation = activation; }
    
    // Méthodes
    bool peutEtreActive() const;
    void afficher() const;
};

#endif // EFFET_H