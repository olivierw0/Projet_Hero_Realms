#ifndef CARTE_DB_H
#define CARTE_DB_H

#include "carte.h"
#include <vector>
#include <string>

// Base de données des cartes
extern std::vector<const Carte*> carte_db;

// Fonctions d'accès à la base de données
const Carte* getCarteById(int id);
const Carte* getCarteByName(const std::string& nom);
int getQuantiteById(int id);
std::vector<const Carte*> creerDeckDeBase();

#endif // CARTE_DB_H