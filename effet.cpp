#include "effet.h"
#include <iostream>

Effet::Effet(int id, const std::string& type, int valeur, 
             const std::string& condition_type, const std::string& condition_valeur,
             const std::string& activation)
    : id(id), type(type), valeur(valeur), condition_type(condition_type), 
      condition_valeur(condition_valeur), activation(activation) {
}

bool Effet::peutEtreActive() const {
    // Logique simple - peut être étendue selon les besoins
    return activation == "toujours" || activation == "sacrifice";
}

void Effet::afficher() const {
    std::cout << type << " +" << valeur;
    
    if (condition_type != "aucune") {
        std::cout << " (condition: " << condition_type;
        if (!condition_valeur.empty()) {
            std::cout << " = " << condition_valeur;
        }
        std::cout << ")";
    }
    
    if (activation != "toujours") {
        std::cout << " [" << activation << "]";
    }
    
    std::cout << std::endl;
}