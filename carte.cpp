#include "carte.h"
#include "effet.h"
#include <iostream>

Carte::Carte(int id, const std::string& nom, int cout, TypeCarte type, 
             FactionCarte faction, const std::string& description)
    : id(id), nom(nom), cout(cout), type(type), faction(faction), description(description) {
}

void Carte::ajouterEffet(std::shared_ptr<Effet> effet) {
    effets.push_back(effet);
}

void Carte::afficher() const {
    std::cout << "=== " << nom << " ===" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Coût: " << cout << std::endl;
    std::cout << "Type: " << typeToString(type) << std::endl;
    std::cout << "Faction: " << factionToString(faction) << std::endl;
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

// Méthodes de conversion Type -> String
std::string Carte::typeToString(TypeCarte type) {
    switch (type) {
        case TypeCarte::ACTION:
            return "Action";
        case TypeCarte::OBJET:
            return "Objet";
        case TypeCarte::CHAMPION:
            return "Champion";
        default:
            return "Inconnu";
    }
}

// Méthodes de conversion Faction -> String
std::string Carte::factionToString(FactionCarte faction) {
    switch (faction) {
        case FactionCarte::ROUGE:
            return "Rouge";
        case FactionCarte::BLEU:
            return "Bleu";
        case FactionCarte::VERT:
            return "Vert";
        case FactionCarte::JAUNE:
            return "Jaune";
        case FactionCarte::NEUTRE:
            return "Neutre";
        default:
            return "Inconnue";
    }
}

// Méthodes de conversion String -> Type
TypeCarte Carte::stringToType(const std::string& str) {
    if (str == "Action" || str == "action") {
        return TypeCarte::ACTION;
    } else if (str == "Objet" || str == "objet") {
        return TypeCarte::OBJET;
    } else if (str == "Champion" || str == "champion") {
        return TypeCarte::CHAMPION;
    }
    return TypeCarte::ACTION; // valeur par défaut
}

// Méthodes de conversion String -> Faction
FactionCarte Carte::stringToFaction(const std::string& str) {
    if (str == "Rouge" || str == "rouge") {
        return FactionCarte::ROUGE;
    } else if (str == "Bleu" || str == "bleu") {
        return FactionCarte::BLEU;
    } else if (str == "Vert" || str == "vert") {
        return FactionCarte::VERT;
    } else if (str == "Jaune" || str == "jaune") {
        return FactionCarte::JAUNE;
    } else if (str == "Neutre" || str == "neutre") {
        return FactionCarte::NEUTRE;
    }
    return FactionCarte::NEUTRE; // valeur par défaut
}