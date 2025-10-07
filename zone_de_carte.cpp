#include "zone_de_carte.h"
#include "carte.h"
#include <iostream>
#include <algorithm>
#include <random>

ZoneDeCarte::ZoneDeCarte(int id, const std::string& type, int owner_joueur_id, int owner_table_id)
    : id(id), type(type), owner_joueur_id(owner_joueur_id), owner_table_id(owner_table_id) {
}

void ZoneDeCarte::ajouterCarte(std::shared_ptr<Carte> carte, int ordre) {
}

std::shared_ptr<Carte> ZoneDeCarte::retirerCarte(int index) {
}

std::shared_ptr<Carte> ZoneDeCarte::retirerCarteParId(int carte_id) {
}

void ZoneDeCarte::melangerCartes() {
}

std::shared_ptr<Carte> ZoneDeCarte::piocher() {
}

void ZoneDeCarte::afficher() const {
}