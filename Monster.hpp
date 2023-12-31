#pragma once
#include "./GeneralMethod.hpp"
#include "./Character.hpp"
#include "./Fighter.hpp"

class Fighter;

class Monster : public Character {
    private:
        int dropExpAmount;

    public:
        Monster() {};
        Monster(std::string name, ElementalAttribute element, int maxhp, int atk, int def, int spd, int dropExpAmount);
        virtual ~Monster() {};

        virtual void damagedMessage(int const damagePoint);
        virtual void deadMessage();

        void initAttackMethod();
        void randomAttack(Fighter& fighter);

        int getDropExpAmount();
        void setDropExpAmount(int dropExpAmount);

};

inline Monster :: Monster(std::string const name, ElementalAttribute const element, int const maxhp, int const atk, int const def, int const spd, int dropExpAmount) : Character(name, element, maxhp, atk, def, spd), dropExpAmount(dropExpAmount) {
    this->initAttackMethod();
}

inline int Monster :: getDropExpAmount() {
    return this->dropExpAmount;
}

inline void  Monster :: setDropExpAmount(int dropExpAmount) {
    this->dropExpAmount = dropExpAmount;
}
