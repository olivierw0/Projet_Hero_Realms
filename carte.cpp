#include "carte.h"
#include "effet.h"
#include <iostream>

Carte::Carte(int id, const std::string& nom, int cout, const std::string& type, 
             const std::string& faction, const std::string& description)
    : id(id), nom(nom), cout(cout), type(type), faction(faction), description(description) {
}

void Carte::ajouterEffet(std::shared_ptr<Effet> effet) {
    effets.push_back(effet);
}

void Carte::afficher() const {
    std::cout << "=== " << nom << " ===" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Coût: " << cout << std::endl;
    std::cout << "Type: " << type << std::endl;
    std::cout << "Faction: " << faction << std::endl;
    std::cout << "Description: " << description << std::endl;
    
    if (!effets.empty()) {
        std::cout << "Effets:" << std::endl;
        for (const auto& effet : effets) {
            std::cout << "  ";
            effet->afficher();
        }
    }
    std::cout << std::endl;
}