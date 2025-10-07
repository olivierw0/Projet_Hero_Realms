#include "effet.h"
#include <iostream>

Effet::Effet(int id, const std::string& type, int valeur, 
             const std::string& condition_type, const std::string& condition_valeur,
             const std::string& activation)
    : id(id), type(type), valeur(valeur), condition_type(condition_type), 
      condition_valeur(condition_valeur), activation(activation) {
}

bool Effet::peutEtreActive() const {
}

void Effet::afficher() const {
}