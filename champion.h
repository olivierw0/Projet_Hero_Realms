#ifndef CHAMPION_H
#define CHAMPION_H

#include "carte.h"

class Champion : public Carte {
private:
    int pv;
    bool active;
    bool garde;

public:
    Champion(int id, const std::string& nom, int cout, FactionCarte faction,
             const std::string& description, int pv, bool garde = false);
    
    // Getters
    int getPv() const { return pv; }
    bool isActive() const { return active; }
    bool hasGarde() const { return garde; }
    
    // Setters
    void setPv(int pv) { this->pv = pv; }
    void setActive(bool active) { this->active = active; }
    void setGarde(bool garde) { this->garde = garde; }
    
    // Méthodes
    void recevoirDegats(int degats);
    void detruire();
    
    void activer();
    void desactiver();
    void afficher() const override;
    
    ~Champion() override = default;
};

#endif // CHAMPION_H