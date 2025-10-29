#include "carte.h"
#include "joueur.h"
#include <iostream>


// Constructeur par défaut
Carte::Carte() : id(0), nom(""), cout(0), type(TypeCarte::ACTION), faction(FactionCarte::NEUTRE), description("") {
    #ifdef DEBUG
        std::cout << "Construction de la carte par défaut" << std::endl;
    #endif
}

// Destructeur virtuel pour rendre la classe polymorphe
Carte::~Carte(){
    #ifdef DEBUG
        std::cout << "Destruction de la carte: " << nom << std::endl;
    #endif
}

// Constructeur avec paramètres
Carte::Carte(int id, const std::string& nom, int cout, TypeCarte type,
        FactionCarte faction, const std::string& description,
        const std::vector<Effet>& effets = {})
    : id(id), nom(nom), cout(cout), type(type), faction(faction),
        description(description), effets(effets) {
    #ifdef DEBUG
        std::cout << "Construction de la carte: " << nom << std::endl;
    #endif
}

int Carte::getId() const { return id; }
std::string Carte::getNom() const { return nom; }
int Carte::getCout() const { return cout; }
TypeCarte Carte::getType() const { return type; }
FactionCarte Carte::getFaction() const { return faction; }
std::string Carte::getDescription() const { return description; }
const std::vector<Effet>& Carte::getEffets() const { return effets; }

int Carte::getPV() const { return 0; }
