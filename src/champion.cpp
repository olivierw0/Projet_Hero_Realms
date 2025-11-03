#include "champion.h"
#include <iostream>

// Getters & Setters
int Champion::getPV() const { return pv; }
bool Champion::getActive() const { return active; }
bool Champion::hasGarde() const { return garde; }
int Champion::getPVMax() const { return pvMax; }

void Champion::setActive(bool etat) { active = etat; }
void Champion::setPV(int nouveaux_pv) { pv = nouveaux_pv; }
void Champion::setGarde(bool nouvelle_garde) { garde = nouvelle_garde; }

Champion::Champion() : Carte(), pv(1), active(true), garde(false){}

Champion::Champion(int id, const std::string& nom, int cout, FactionCarte faction, 
            const std::string& description, const std::vector<Effet>& effets = {}, bool garde = false, int pv = 1)
    : Carte(id, nom, cout, TypeCarte::CHAMPION, faction, description, effets),
        pv(pv), pvMax(pv), active(true), garde(garde) {
    #ifdef DEBUG
        std::cout<<"Construction du champion: "<<getNom()<<std::endl;
    #endif
}

Champion::~Champion(){
    #ifdef DEBUG
        std::cout<<"Destruction du champion: "<<getNom()<<std::endl;
    #endif
}



// Méthode pour "expend" (taper) le champion et déclencher ses effets
bool Champion::expend() {
    if (active) {
        setActive(false); // Le champion devient inactif (tapé)
        return true;  // Effets peuvent être déclenchés
    }
    return false;     // Champion déjà tapé, pas d'effet
}

// STUN == met un champion à 0 PV
void Champion::stun() {
    setPV(0);
}