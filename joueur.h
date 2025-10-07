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
    std::vector<std::shared_ptr<ZoneDeCarte>> zones;

public:
    Joueur(int id, int pv = 50);
    
    // Getters
    int getId() const { return id; }
    int getPv() const { return pv; }
    int getOr() const { return or_value; }
    int getCombat() const { return combat; }
    const std::vector<std::shared_ptr<ZoneDeCarte>>& getZones() const { return zones; }
    
    // Setters
    void setPv(int pv) { this->pv = pv; }
    void setOr(int or_val) { this->or_value = or_val; }
    void setCombat(int combat) { this->combat = combat; }
    
    // Méthodes
    void ajouterOr(int quantite);
    void depenser(int quantite);
    void ajouterCombat(int quantite);
    void recevoirDegats(int degats);
    void soigner(int soin);
    void ajouterZone(std::shared_ptr<ZoneDeCarte> zone);
    std::shared_ptr<ZoneDeCarte> getZone(const std::string& type);
    void afficher() const;
    
    ~Joueur() = default;
};

#endif // JOUEUR_H