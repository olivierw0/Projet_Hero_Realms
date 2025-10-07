#include "table_partie.h"
#include "joueur.h"
#include <iostream>

TablePartie::TablePartie(int id, int nb_gemmes) : id(id), nb_gemmes(nb_gemmes) {
}

void TablePartie::ajouterJoueur(std::shared_ptr<Joueur> joueur) {
}

void TablePartie::ajouterZoneCommune(std::shared_ptr<ZoneDeCarte> zone) {
}

std::shared_ptr<ZoneDeCarte> TablePartie::getZoneCommune(const std::string& type) {

}

void TablePartie::initialiserPartie() {

}

void TablePartie::afficher() const {

}