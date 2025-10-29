#ifndef CHAMPION_H
#define CHAMPION_H

#include "carte.h"

class Champion : public Carte {
private:
    int pv;
    bool active;
    bool garde;
public:
    // Constructeurs
    Champion() : Carte(), pv(1), active(true), garde(false) {}
    
    Champion(int id, const std::string& nom, int cout, FactionCarte faction, 
             const std::string& description, const std::vector<Effet>& effets = {}, bool garde = false, int pv = 1)
        : Carte(id, nom, cout, TypeCarte::CHAMPION, faction, description, effets),
          pv(pv), active(true), garde(garde) {}
    
    // Getters (redéfinition de la méthode virtuelle)
    int getPV() const override { return pv; }
    bool getActive() const { return active; }
    bool hasGarde() const { return garde; }
    
    // Setters
    void setActive(bool etat) { active = etat; }
    void setPV(int nouveaux_pv) { pv = nouveaux_pv; }
    void setGarde(bool nouvelle_garde) { garde = nouvelle_garde; }

    void stun();
    bool expend();
};

#endif // CHAMPION_H