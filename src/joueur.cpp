#include <vector>
#include <memory>
#include "carte.h"
#include "champion.h"
#include "zone_de_carte.h"
#include "joueur.h"

void Joueur::takeDamage(int amount){
    pv -= amount;
    if(pv<0){ 
        pv = 0; 
        isDead = true;    
    }
}

void Joueur::heal(int amount){
    pv += amount;
}

void Joueur::addOr(int amount){
    or_value += amount;
}

bool Joueur::spendOr(int amount){
    int new_or_value = or_value - amount;

    if (new_or_value < 0){ return false; } // Pas assez d'or

    or_value = new_or_value;
    return true;
}

void Joueur::addCombat(int amount){
    combat += amount;
}

void Joueur::resetCombat(){
    combat = 0;
}

void Joueur::resetOr(){
    or_value = 0;
}

void Joueur::ajouterZone(ZoneDeCarte&& zone){
    zones.push_back(zone);
}

ZoneDeCarte* Joueur::getZoneByType(TypeZone type){
    for(ZoneDeCarte& zone : zones){
        if(zone.getType() == type){
            return &zone;
        }
    }
    return nullptr;
}

ZoneDeCarte* Joueur::getZoneById(int zoneId){
    for(ZoneDeCarte& zone : zones){
        if(zone.getId() == zoneId){
            return &zone;
        }
    }
    return nullptr;
}
