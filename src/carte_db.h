#ifndef CARTE_DB_H
#define CARTE_DB_H

#include "carte.h"
#include <vector>
#include <string>
#include <memory>

// Base de données des cartes - chaque carte est unique en mémoire
extern std::vector<Carte*> carte_db;

// Fonctions d'accès à la base de données
Carte* getCarteById(int id);
Carte* getCarteByName(const std::string& nom);
std::vector<Carte*> creerDeckDeBase();

#endif // CARTE_DB_H