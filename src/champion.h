#ifndef CHAMPION_H
#define CHAMPION_H

#include "carte.h"

class Champion : public Carte {
private:
    int pv;
    bool active;
    bool garde;

public:
    // Constructeurs & Destructeur
    Champion();
    Champion(int id, const std::string& nom, int cout, FactionCarte faction, 
             const std::string& description, const std::vector<Effet>& effets, bool garde, int pv);
    virtual ~Champion();

    // Getters & Setters
    int getPV() const override;
    bool getActive() const;
    bool hasGarde() const;

    void setActive(bool etat);
    void setPV(int nouveaux_pv);
    void setGarde(bool nouvelle_garde);

    bool expend();
    void stun();
};

#endif // CHAMPION_H