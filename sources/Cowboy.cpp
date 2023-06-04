/**
 * @class Cowboy
 * @brief Represents a cowboy character in the game.
 * The Cowboy class is a derived class of the Character class. It represents a cowboy character with
 * shooting abilities. It has a limited number of bullets and can shoot enemies to cause damage.
 * @author Tomer Gozlan.
 * @date 15/05/2023
 */

#include "Cowboy.hpp"

namespace ariel {
/**
* @brief Constructor for the Cowboy class.
* @param name The name of the cowboy.
* @param location The location of the cowboy on the game board.
* @throws std::invalid_argument if the name is empty.
* @throw std::out_of_range if the hit points over 110 or less then 0.
*/
    Cowboy::Cowboy(const std::string &name, const ariel::Point &location) : Character(name, location, 110) {
        if (name.empty()) {
            throw std::invalid_argument("Error: Name cannot be empty.");
        }
        if (this->getHitPoints() < 0 || this->getHitPoints() > 110) {
            throw std::out_of_range("Error: hitPoints of Cowboy out of bounds.");
        }
        this->bullets = 6;
    }

/**
 * @brief Shoots the enemy character, causing damage and consuming a bullet.
 * @param enemy A pointer to the enemy character to shoot.
 * @throw std::invalid_argument If the enemy pointer is nullptr.
 * @throw std::runtimer_error If cowboy try shoot himself.
 * @throw std::out_of_range If the cowboy is out of bullets.
 * @throw std::runtime_error If the enemy is already dead.
 */
    void Cowboy::shoot(Character *other) {
        if (other == nullptr)
            throw std::invalid_argument("error: enemey can't be null");
        if (this == other)
            throw std::runtime_error("error: can't shoot myself");
        if (!(this->isAlive()) || !(other->isAlive()))
            throw std::runtime_error("error: me or enemy - already dead");
        if (this->hasboolets()) {
            this->bullets--;
            other->hit(10);
        }
    }

/**
* @brief Checks if the cowboy has bullets left.
* @return True if the cowboy has bullets, false otherwise.
*/
    bool Cowboy::hasboolets() const {
        return (this->bullets > 0);
    }

/**
 * @brief Reloads the cowboy's gun with six new bullets.
 * @throw std::runtimer_error If the cowboy is not alive and try to reload.
 */
    void Cowboy::reload() {
        if (!(this->isAlive())) {
            throw std::runtime_error("Error: Cowboy is not alive. Cannot reload.");
        }
        this->bullets = 6;
    }

/**
 * @brief Retrieves the number of bullets the Cowboy has.
 * @return The number of bullets the Cowboy has.
 */
    int Cowboy::getBullets() const {
        return this->bullets;
    }

/**
 * @brief Prints the information about the cowboy.
 * This function prints the name, hit points, and location of the cowboy.
 * @note If the cowboy is dead, the hit points and location will not be printed.
 */
    std::string Cowboy::print() const {
        return "C, " + Character::print();
    }
}