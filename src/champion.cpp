#include "champion.h"

// Implémentations des méthodes de Champion si nécessaire

// Méthode pour "expend" (taper) le champion et déclencher ses effets
bool expend() {
    if (active) {
        desactiver(); // Le champion devient inactif (tapé)
        return true;  // Effets peuvent être déclenchés
    }
    return false;     // Champion déjà tapé, pas d'effet
}

// STUN == met un champion à 0 PV
void stun() {
    setPV(0);
}