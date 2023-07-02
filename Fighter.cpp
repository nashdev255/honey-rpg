#include "Fighter.hpp"

Fighter :: Fighter(std::string const name, ElementalAttribute const elementalAttribute, int const maxhp, int const atk, int const def, int const spd) : Character(name, elementalAttribute, maxhp, atk, def, spd), exp(0) {
    this->updateReqExp();
    this->buildAttackMethod();
}

void Fighter :: buildAttackMethod() {
    const int power = this->atk;
    const ElementalAttributeList fighterElement = elementalAttribute.getElement();
    this->attackMethod[0].setParams("punchAttack", ElementalAttributeList::None, power);
    this->attackMethod[1].setParams("kickAttack", ElementalAttributeList::None, power*1.5);
    this->attackMethod[2].setParams("elementalAttack", fighterElement, power*0.8);
    this->attackMethod[3].setParams("elementalStorm", fighterElement, power*2);
}

void Fighter :: attack(Monster& monster) {
    std::cout << "Select how to " << name << " attack." << std::endl;
    displayAttackMethods();
    
    int method = this->attackMethod.size()+1;

    std::cout << "> ";
    while(this->attackMethod.size() < method) {
        std::cin >> method;
        if(this->attackMethod.size() < method) {
            std::cout << "Select How to " << this->name << " attack." << std::endl;
            std::cout << "> ";
        }
    }
    method--;

    this->selectedAttackMethod = this->attackMethod[method];

    std::cout << this->name << "'s " << this->selectedAttackMethod.getName() << "!!!" << std::endl;
    selectedAttackMethod.action(*this, monster);
}

void Fighter :: displayAttackMethods() {
    std::cout << "<methods>" << std::endl;
    for(int i=0;i<attackMethod.size();i++) {
        std::cout << i+1 << " : " << this->attackMethod[i].getName() << std::endl;
    }
}

void Fighter :: damagedMessage(int const damagePoint) {
    std::cout << this->name << " took " << damagePoint << " points of damage." << std::endl;
}

void Fighter :: deadMessage() {
    std::cout << this->name << " has ran out of energy..." << std::endl;
}

void Fighter :: updateReqExp() {
    this->reqExp = calcReqExpAmount();
}

void Fighter :: updateExp() {
    this->exp = this->exp - this->reqExp;
}

void Fighter :: updateLevel() {
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

void Fighter :: levelUp() {
    this->level++;
    updateSkillPoint();
}

void Fighter :: earnExpFromEnemy(int dropExpAmount) {
    this->exp = this->exp + dropExpAmount;
}

int Fighter :: calcReqExpAmount() {
    const int totalReqExpAmount = this->level*100;
    return totalReqExpAmount;
}

void Fighter :: updateSkillPoint() {
    const int skillPointIncreaseAmount = 5;
    const int totalSkillPoint = this->skillPoint + skillPointIncreaseAmount;
    std::cout << "SKILL POINTS INCREASED : " << this->skillPoint << " > " << totalSkillPoint;
    this->skillPoint = totalSkillPoint;
}

void Fighter :: assignSkillPoint() {
    std::cout << "assign skill points" << std::endl;
    
}
