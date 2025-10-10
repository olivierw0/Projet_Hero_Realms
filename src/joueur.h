#ifndef JOUEUR_H
#define JOUEUR_H

#include <vector>
#include <memory>
#include "carte.h"
#include "champion.h"
#include "zone_de_carte.h"

class Joueur {
private:
    int id;
    int pv;
    int or_value;
    int combat;
    std::vector<ZoneDeCarte> zones;
    bool isDead;

public:
    // Constructeur
    Joueur(int id, int pv) : id(id), pv(pv), or_value(0), combat(0) {}

    // Méthodes pour accéder aux attributs
    int getId() const { return id; }
    int getPv() const { return pv; }
    int getOr() const { return or_value; }
    int getCombat() const { return combat; }
    const std::vector<ZoneDeCarte>& getZones() const { return zones; }

    void takeDamage(int amount);
    void heal(int amount);
    void addOr(int amount);
    bool spendOr(int amount); // False si pas assez d'or.
    void addCombat(int amount);

    // A chaque fin de tour : or & combat sont reset
    void resetCombat();
    void resetOr();

    // Ajouter une zone au joueur
    void ajouterZone(const ZoneDeCarte& zone) {
        zones.push_back(zone);
    }

    void ajouterZone(ZoneDeCarte&& zone);
    ZoneDeCarte* getZoneByType(TypeZone type);
    ZoneDeCarte* getZoneById(int zoneId);

};

#endif // JOUEUR_H