/**
 * @file SmartTeam.cpp
 * @brief Implementation of the SmartTeam class and related functions.
 * @author Tomer Gozlan
 * @date 17/05/2023
 */

#include "SmartTeam.hpp"
#include <vector>
#include <numeric>

namespace ariel {
/**
 * @brief Compare function for character priority in the priority queue.
 * @param character1 The first character to compare.
 * @param character2 The second character to compare.
 * @return true if character1 has higher priority, false otherwise.
 */
    bool Compare::operator()(ariel::Character *character1, ariel::Character *character2) const {
        if (character1->getHitPoints() > character2->getHitPoints()) {
            return true;
        }
        if (character1->getHitPoints() < character2->getHitPoints()) {
            return false;
        }

        bool c1IsNinja = dynamic_cast<Ninja *>(character1) != nullptr;
        bool c2IsNinja = dynamic_cast<Ninja *>(character2) != nullptr;

        if (c1IsNinja && !c2IsNinja) {
            return true;
        }
        if (!c1IsNinja && c2IsNinja) {
            return false;
        }
        return false;
    }

/**
 * @brief Constructor for SmartTeam class.
 * @param leader The initial leader of the team.
 */
    SmartTeam::SmartTeam(ariel::Character *leader) : Team(leader) {}

/**
 * @brief Get the location of the enemy character.
 * @param enemy The enemy character.
 * @return The location of the enemy character.
 * @throws std::invalid_argument if enemy is an invalid pointer.
 */
    Point SmartTeam::askEnemyLocation(ariel::Character *enemy) {
        if (!enemy) {
            throw std::invalid_argument("Error: Invalid enemy character.");
        }
        return enemy->getLocation();
    }

/**
 * @brief Get the hit points of the enemy character.
 * @param enemy The enemy character.
 * @return The hit points of the enemy character.
 * @throws std::invalid_argument if enemy is an invalid pointer.
 */
    int SmartTeam::askEnemyHitPoints(ariel::Character *enemy) {
        if (!enemy) {
            throw std::invalid_argument("Error: Invalid enemy character.");
        }
        return enemy->getHitPoints();
    }

    /**
    * @brief Perform an attack by the SmartTeam on an enemyTeam.
    * @param enemyTeam A pointer to the enemy team to be attacked.
    * @throws std::invalid_argument if enemyTeam is an invalid pointer.
    * @throws std::runtime_error if the current team is the same as enemyTeam, or if either team has been completely eliminated.
    */
    void SmartTeam::attack(ariel::Team *enemyTeam) {

        // Check if enemyTeam pointer is valid
        if (!enemyTeam) {
            throw std::invalid_argument("Error: Invalid pointer to enemy team.");
        }

        // Check if attacking the same team
        if (this == enemyTeam) {
            throw std::runtime_error("Error: Team must attack the enemy team, not itself.");
        }

        // Check if any team has been completely eliminated
        if (this->stillAlive() == 0 || enemyTeam->stillAlive() == 0) {
            throw std::runtime_error("Error: One of the teams was completely eliminated.");
        }

        // Check if the leader of the attacking team is alive
        if (!(getLeader()->isAlive())) {
            Point leaderLocation = getLeader()->getLocation();
            Character *newLeader = findClosestCharacter(leaderLocation, this->getFighters());
            this->setLeader(newLeader);
        }

        // Create a priority queue to store enemy characters based on a comparison functor
        std::priority_queue < Character * , std::vector < Character * >, Compare > priorityTarget;

        // Push all enemy characters into the priority queue
        for (Character *enemy: enemyTeam->getFighters()) {
            priorityTarget.push(enemy);
        }

        Character *victim = nullptr;

        // Get the top character from the priority queue as the initial victim
        if (!priorityTarget.empty()) {
            victim = priorityTarget.top();
            priorityTarget.pop();

            // If the initial victim is not alive, get the next character from the priority queue
            if (!victim->isAlive() && !priorityTarget.empty()) {
                victim = priorityTarget.top();
                priorityTarget.pop();
            } else {
                victim = nullptr;
            }
        }

        // Proceed with the attack if a valid victim is available
        if (victim != nullptr) {

            // If the initial victim is not alive, get the next character from the priority queue
            if (!victim->isAlive()) {
                victim = priorityTarget.top();
                priorityTarget.pop();
            }

            int cowboyCounter = 0;
            int cowboyDamage = 0;
            int safeDistance = 14;
            std::vector<int> speeds = {8, 12, 14};

            // Calculate the average speed of the ninjas
            double sum = std::accumulate(speeds.begin(), speeds.end(), 0);
            double averageSpeed = sum / speeds.size();

            // Iterate over the attackers in the current team
            for (Character *attacker: this->getFighters()) {

                // Count the number of cowboys and ninjas
                if (Cowboy *cowboy = dynamic_cast<Cowboy *>(attacker)) {
                    cowboyCounter++;

                    // Calculate the cowboy damage based on the number of cowboys
                    cowboyDamage = cowboyCounter * 10;

                    if (attacker->isAlive() && victim->isAlive()) {
                        Point victimLocation = askEnemyLocation(victim);
                        int victimHitPoints = askEnemyHitPoints(victim);

                        if (victimHitPoints <= cowboyDamage) {

                            // Loop while there are cowboys left to attack
                            while (cowboyCounter) {

                                if (Cowboy *cowboy = dynamic_cast<Cowboy *>(attacker)) {
                                    if (cowboy->hasboolets()) {
                                        cowboy->shoot(victim);
                                    } else {
                                        cowboy->reload();
                                    }

                                    cowboyCounter--;

                                    // Get the next character from the priority queue as the new victim if the current victim is eliminated
                                    if (!victim->isAlive()) {
                                        victim = priorityTarget.top();
                                        priorityTarget.pop();
                                    }

                                } else if (Ninja *ninja = dynamic_cast<Ninja *>(attacker)) {

                                    int victimDistance = ninja->getLocation().distance(askEnemyLocation(victim));

                                    if (victimDistance < 1) {
                                        ninja->slash(victim);
                                    } else {
                                        // Move the ninja towards the victim if the distance minus the average speed is greater than or equal to 1
                                        if (victimDistance - averageSpeed >= 1) {
                                            ninja->move(victim);
                                        }
                                    }
                                }
                            }
                        } else {

                            // Attack the victim without considering safe distance for ninjas
                            if (Cowboy *cowboy = dynamic_cast<Cowboy *>(attacker)) {
                                if (cowboy->hasboolets()) {
                                    cowboy->shoot(victim);
                                } else {
                                    cowboy->reload();
                                }
                            } else if (Ninja *ninja = dynamic_cast<Ninja *>(attacker)) {

                                int victimDistance = ninja->getLocation().distance(askEnemyLocation(victim));

                                if (victimDistance < 1) {
                                    ninja->slash(victim);
                                } else {
                                    // Move the ninja towards the victim if the distance minus the average speed is greater than or equal to 1
                                    if (victimDistance - averageSpeed >= 1) {
                                        ninja->move(victim);
                                    }
                                }
                            }
                        }

                        // Check if either team has been completely eliminated
                        if (this->stillAlive() == 0 || enemyTeam->stillAlive() == 0) {
                            return;
                        }

                        // Get the next character from the priority queue as the new victim if the current victim is eliminated
                        if (!victim->isAlive()) {
                            victim = priorityTarget.top();
                            priorityTarget.pop();
                        }

                        // Check if the enemy team's leader is not alive
                        if (!enemyTeam->getLeader()->isAlive()) {
                            Point enemyLeaderLocation = enemyTeam->getLeader()->getLocation();
                            Character *enemyNewLeader;
                            enemyNewLeader = findClosestCharacter(enemyLeaderLocation, this->getFighters());
                            enemyTeam->setLeader(enemyNewLeader);
                        }
                    }
                }
            }
        }
    }

/**
 * @brief Print the information about the team and its members.
 * Displays the team leader, team status (alive or defeated), number of team members,
 * and details of each team member.
 */
    void SmartTeam::print() {
        std::cout << "---------------------" << std::endl;
        std::cout << "Team " << this->getLeader()->getName() << std::endl;
        std::cout << "---------------------" << std::endl;
        std::cout << "Team Status: " << (stillAlive() ? "Alive" : "Defeated") << std::endl;
        std::cout << "Number of Team members: " << (stillAlive() ? std::to_string(stillAlive()) : "0")
                  << std::endl;
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