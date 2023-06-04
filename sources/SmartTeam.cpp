//
// Created by tomergozlan on 6/1/23.
//

#include "SmartTeam.hpp"

namespace ariel {
    bool Compare::operator()(ariel::Character *character1, ariel::Character *character2) const {
        if (character1->getHitPoints() > character2->getHitPoints()) {
            return true;
        }
        if (character1->getHitPoints() < character2->getHitPoints()) {
            return false;
        }

        // Sort by character type: ninja > cowboy
        bool c1IsNinja = dynamic_cast<Ninja *>(character1) != nullptr;
        bool c2IsNinja = dynamic_cast<Ninja *>(character2) != nullptr;

        if (c1IsNinja && !c2IsNinja) {
            return true;
        }
        if (!c1IsNinja && c2IsNinja) {
            return false;
        }
    }

    SmartTeam::SmartTeam(ariel::Character *leader) : Team(leader) {}

    Point SmartTeam::askEnemyLocation(ariel::Character *enemy) {
        if (!enemy) {
            throw std::invalid_argument("Error: Invalid enemy character.");
        }
        return enemy->getLocation();
    }

    int SmartTeam::askEnemyHitPoints(ariel::Character *enemy) {
        if (!enemy) {
            throw std::invalid_argument("Error: Invalid enemy character.");
        }
        return enemy->getHitPoints();
    }

    void SmartTeam::attack(ariel::Team *enemyTeam) {
        if (!enemyTeam) {
            throw std::invalid_argument("Error: Invalid pointer to enemy team.");
        }
        if (this == enemyTeam) {
            throw std::runtime_error("Error: Team must attack the enemy team not herself.");
        }
        if (this->stillAlive() == 0 || enemyTeam->stillAlive() == 0) {
            throw std::runtime_error("Error: One of the teams was completely eliminated.");
        }
        if (!(this->leader->isAlive())) {
            Point leaderLocation = this->leader->getLocation();
            Character *newLeader = findClosestCharacter(leaderLocation, this->getFighters());
            this->setLeader(newLeader);
        }
        std::priority_queue < Character * , std::vector < Character * >, Compare > priortyTarget;
        for (Character *enemy: enemyTeam->getFighters()) {
            priortyTarget.push(enemy);
        }
        Character *victim = nullptr;
        if (!priortyTarget.empty()) {
            victim = priortyTarget.top();
            priortyTarget.pop();
            if (!victim->isAlive() && !priortyTarget.empty()) {
                victim = priortyTarget.top();
                priortyTarget.pop();
            } else {
                victim = nullptr;
            }
        }
        if (victim != nullptr) {
            if (!victim->isAlive()) {
                victim = priortyTarget.top();
                priortyTarget.pop();
            }
            int cowboyDamage = 0;
            for (Character *attacker: this->getFighters()) {
                if (Cowboy *cowboy = dynamic_cast<Cowboy *>(attacker)) {
                    cowboyDamage++;
                } else if (Ninja *ninja = dynamic_cast<Ninja *>(attacker)) {
                    ninjaDamage++;
                }
                cowboyDamage *= 10;

                if (attacker->isAlive() && victim->isAlive()) {
                    Point victimLocation = askEnemyLocation(victim);
                    int victimHitPoints = askEnemyHitPoints(victim);

                }

            }
        }


    }

}