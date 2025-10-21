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
    bool isActive() const { return active; }
    bool hasGarde() const { return garde; }
    
    // Setters
    void setActive(bool etat) { active = etat; }
    void activer() { active = true; }
    void desactiver() { active = false; }
    void changerEtat() { active = !active; }
    void setPV(int nouveaux_pv) { pv = nouveaux_pv; }
    void setGarde(bool nouvelle_garde) { garde = nouvelle_garde; }
    
    // Méthode pour "expend" (taper) le champion et déclencher ses effets
    bool expend() {
        if (active) {
            desactiver(); // Le champion devient inactif (tapé)
            return true;  // Effets peuvent être déclenchés
        }
        return false;     // Champion déjà tapé, pas d'effet
    }
    
    // Méthode pour "untap" le champion (début de tour)
    void untap() {
        activer();
    }
};

#endif // CHAMPION_H