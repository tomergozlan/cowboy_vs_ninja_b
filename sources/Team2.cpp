/**
 * @file Team2.cpp
 * @brief Represents a group of fighters, consisting of ninjas and cowboys.
 * This class is a group of up to ten fighters, where a fighter can be a ninja or a warrior.
 * Each group is assigned a leader who is one of the fighters. When a group is created, it gets a leader pointer.
 * @note The order in attack,print,compering is like the team build not matter the type of the character.
 * @author Tomer Gozlan
 * @date 15/05/2023
 */

#include "Team2.hpp"

namespace ariel {

    Team2::Team2(ariel::Character *leader) : Team(leader) {}

    void Team2::attack(ariel::Team *enemyTeam) {
        if (!enemyTeam) {
            throw std::invalid_argument("Error: Invalid pointer to enemy team.");
        }
        if (this == enemyTeam) {
            throw std::runtime_error("Error: Team must attack the enemy team not herself.");
        }
        if (this->stillAlive() == 0 || enemyTeam->stillAlive() == 0) {
            throw std::runtime_error("Error: One of the teams was completely eliminated.");
        }
        if (!(this->getLeader()->isAlive())) {
            Point leaderLocation = this->getLeader()->getLocation();
            Character *newLeader = findClosestCharacter(leaderLocation, this->getFighters());
            this->setLeader(newLeader);
        }
        Character *victim = findClosestCharacter(this->getLeader()->getLocation(), enemyTeam->getFighters());

        for (Character *attacker: this->getFighters()) {
            if (attacker->isAlive() && victim->isAlive()) {
                if (Cowboy *cowboy = dynamic_cast<Cowboy *>(attacker)) {
                    if (cowboy->hasboolets()) {
                        cowboy->shoot(victim);
                    } else {
                        cowboy->reload();
                    }
                } else if (Ninja *ninja = dynamic_cast<Ninja *>(attacker)) {
                    if (ninja->isAlive()) {
                        double distance = ninja->getLocation().distance(victim->getLocation());
                        if (distance < 1) {
                            ninja->slash(victim);
                        } else {
                            ninja->move(victim);
                        }
                    }
                }
                if (this->stillAlive() == 0 || enemyTeam->stillAlive() == 0) {
                    return;
                }
                if (!victim->isAlive()) {
                    victim = findClosestCharacter(this->getLeader()->getLocation(), enemyTeam->getFighters());
                }
                if (!enemyTeam->getLeader()->isAlive()) {
                    Point enemyLeaderLocation = enemyTeam->getLeader()->getLocation();
                    Character *enemyNewLeader;
                    enemyNewLeader = findClosestCharacter(enemyLeaderLocation, this->getFighters());
                    enemyTeam->setLeader(enemyNewLeader);
                }
            }
        }
    }

    void Team2::print() {
        std::cout << "---------------------" << std::endl;
        std::cout << "Team " << this->getLeader()->getName() << std::endl;
        std::cout << "---------------------" << std::endl;
        std::cout << "Team Status: " << (stillAlive() ? "Alive" : "Defeated") << std::endl;
        std::cout << "Number of Team members: " << (stillAlive() ? std::to_string(stillAlive()) : "0") << std::endl;
        std::cout << "Team Members:" << std::endl;

        for (Character *member: this->getFighters()) {
            if (member->isAlive()) {
                if (Cowboy *cowboy = dynamic_cast<Cowboy *>(member)) {
                    std::cout << cowboy->print() << std::endl;
                }
                if (Ninja *ninja = dynamic_cast<Ninja *>(member)) {
                    std::cout << ninja->print() << std::endl;
                }
            }

        }
    }
}


