#pragma once
#include "./Character.hpp"

void Character :: showStatus() {
    std::cout << "<Status>" << std::endl;
    std::cout << "NAME : " << this->name << std::endl;
    std::cout << "LEVEL : " << this->level << std::endl;
    std::cout << "ELEMENT : " << this->elementalAttribute.getElementAsString(this->elementalAttribute.getElement()) << std::endl;
    std::cout << "HP : " << this->coloredHp() << '/' << this->maxhp << std::endl;
    std::cout << "ATK : " << this->atk << std::endl;
    std::cout << "DEF : " << this->def << std::endl;
    std::cout << "SPD : " << this->spd << std::endl;
    std::cout << std::endl;
}

void Character :: damaged(Character attacker) {
    const int baseDamageAmount = attacker.getSelectedAttackMethod().getPower();
    const double damageMagnification = calcDamageMagnification(attacker);
    const int totalDamageAmount = baseDamageAmount * damageMagnification;

    this->hp -= totalDamageAmount;
    this->damagedMessage(totalDamageAmount);

    if(0 < this->hp) return;
    this->dead();
}

double Character :: calcDamageMagnification(Character attacker) {
    const ElementalReaction elementalReaction = this->elementalAttribute.ElementalReact(attacker.getSelectedAttackMethod().getElement());
    if(elementalReaction == NoneReact) { std::cout << "debug" << std::endl; return 1.0; } 
    if(elementalReaction == Saturate) return 0.5;
    return 1.8;
}

std::string Character :: coloredHp() {
    double redRatio = 0.2;
    double yellowRatio = 0.5;
    // default green

    double restHpRatio = double(this->hp) / double(this->maxhp);

    std::string coloredHp = "\x1b[38;2;127;255;0m" + std::to_string(this->hp) + "\x1b[m";

    if(restHpRatio < redRatio) {
        coloredHp = "\x1b[38;2;255;69;0m" + std::to_string(this->hp) + "\x1b[m";
    } else if(restHpRatio < yellowRatio) {
        coloredHp = "\x1b[38;2;255;255;205m"  + std::to_string(this->hp) + "\x1b[m";
    }

    return coloredHp;
}

void Character :: dead() {
    this->hp = 0;
    this->deadMessage();
}

void Character :: updateReqExp() {
    this->reqExp = calcReqExpAmount();
}

void Character :: updateExp() {
    this->exp = this->exp - this->reqExp;
}

void Character :: updateLevel() {
    while(this->reqExp <= this->exp) {
        if(this->level == this->maxLevel) {
            break;
        }

        updateExp();
        levelUp();
        updateReqExp();

        std::cout << "LEVELUP!!! : " << this->level-1 << " > " << this->level << std::endl;
    }
}

void Character :: levelUp() {
    this->level++;
}

void Character :: earnExpFromEnemy(int dropExpAmount) {
    this->exp = this->exp + dropExpAmount;
}

int Character :: calcReqExpAmount() {
    const int totalReqExpAmount = this->level*100;
    return totalReqExpAmount;
}
