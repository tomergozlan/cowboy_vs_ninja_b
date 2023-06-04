/**
 * @file Ninja.cpp
 * @brief Implementation of the Ninja class
 * @date 5/29/23
 * @author Tomer Gozlan
 */

#include "Ninja.hpp"

namespace ariel{

/**
 * @brief Constructor for the Ninja class.
 * @param name The name of the ninja.
 * @param location The initial location of the ninja.
 * @param speed The speed of the ninja.
 * @param hitPoints The hit points of the ninja.
 */
Ninja::Ninja(const std::string& name, const Point& location, int speed , int hitPoints) : Character(name, location,hitPoints) , speed(speed) {
    if (speed < 0) {
        throw std::invalid_argument("Error: Speed cannot be negative.");
    }
    if (hitPoints < 0) {
        throw std::invalid_argument("Error: Hit points cannot be negative.");
    }
    this->speed = speed;
}
/**
 * @brief Moves the Ninja towards the enemy by a distance equal to its speed.
 * @param enemy A pointer to the enemy Character.
 * @throws std::invalid_argument If the enemy pointer is invalid or the distance is invalid.
 */

void Ninja::move(ariel::Character *enemy) {
    if (!enemy) {
        throw std::invalid_argument("Error: Invalid pointer to enemy character.");
    }
    if (!isAlive()) {
        return;
    }
    double distance = getLocation().distance(enemy->getLocation());
    if (distance <= 0) {
        throw std::invalid_argument("Error: Invalid distance to enemy.");
    }
    double movement = this->speed;
    if (movement > distance) {
        movement = distance;
    }
    Point newLocation = Point::moveTowards(getLocation(), enemy->getLocation(), movement);
    setLocation(newLocation);
}
/**
 * @brief Performs a slash attack on the enemy character.
 * @param enemy A pointer to the enemy character.
 * @throws std::invalid_argument if the enemy pointer is invalid.
 * @throws std::runtime_error if the ninja is already dead or the ninja try to slash himself.
 */
void Ninja::slash(ariel::Character *enemy) {
    if (!enemy) {
        throw std::invalid_argument("Error: Invalid pointer to enemy character.");
    }
    if(this==enemy){
        throw std::runtime_error("Error: Ninja can't slash himself.");
    }
    if (!isAlive() || !(enemy->isAlive())) {
        throw std::runtime_error("Error: Ninja is already dead.");
    }
    double distance = getLocation().distance(enemy->getLocation());
    if (distance < 1) {
        enemy->hit(40);
    }
}

/**
 * @brief Generates a string representation of the Ninja.
 * @return A string representation of the Ninja.
 */
std::string Ninja::print() const {
    return " N, " + Character::print();
}
}