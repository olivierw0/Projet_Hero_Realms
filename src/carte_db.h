#ifndef CARTE_DB_H
#define CARTE_DB_H

#include "carte.h"
#include <vector>
#include <string>
#include <memory>

// Base de données des cartes
extern std::vector<Carte*> carte_db;

// Fonctions d'accès à la base de données
Carte* getCarteById(int id);
Carte* getCarteByName(const std::string& nom);
std::vector<Carte*> initCarteDB();
std::vector<Carte*> creerDeckDeBase();
std::vector<Carte*> creerDeckMarche();

#endif // CARTE_DB_H