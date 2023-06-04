/**
 * @file character.cpp
 * @brief Implements the Character class and its derived classes.
 * @author Tomer Gozlan
 * @date 16/05/2023
 */

#include "Character.hpp"

namespace ariel {

/**
 * @brief Constructs a Character object with the specified name and location.
 * @param name The name of the character.
 * @param location The location of the character.
 * @throw std::invalid_argument if the name is empty or if the location coordinates are negative.
 * @throw std::out_of_range If the hit points is over or under the range of 0-150.
 */
    Character::Character(const std::string &name, const ariel::Point &location, const int &hitPoints) :
            location(location), hitPoints(hitPoints), name(name), teamMember(false) {
        if (name.empty()) {
            throw std::invalid_argument("Error: Name cannot be empty.");
        }
        if (hitPoints < 0.0 || hitPoints > 150.0) {
            throw std::out_of_range("Error: hitPoints out of bounds.");
        }
        this->location = location;
        this->hitPoints = hitPoints;
        this->name = name;
        this->teamMember = false;
    }

/**
 * @brief Setter for the HitPoints field.
 * @param NewHitPoints - new value to set the field.
 * @throws std::invalid_argument if the provided hit points value is negative.
 */
    void Character::setHitPoints(int NewHitPoints) {
        if (NewHitPoints < 0) {
            throw std::invalid_argument("Error: Hit points must be a non-negative value.");
        }
        if (NewHitPoints > 150) {
            throw std::out_of_range("Error:hitPoints out of bounds.");
        }
        this->hitPoints = NewHitPoints;
    }

/**
 * @brief Checks if the character is alive.
 * @return True if the character has more than 0 hit points, indicating they are alive. False otherwise.
 */
    bool Character::isAlive() const {
        return (this->hitPoints > 0);
    }

/**
 * @brief Calculates the Euclidean distance between the current character and another character.
 * @param other A pointer to the other character.
 * @return The Euclidean distance between the current character and the other character.
 * @throw std::invalid_argument If the pointer to the other character is nullptr.
 */
    double Character::distance(const ariel::Character *other) const {
        if (!other) {
            throw std::invalid_argument("Error: Invalid pointer to character.");
        }
        return this->location.distance(other->getLocation());
    }

/**
 * @brief reduces damage to the character by subtracting the specified amount from its hit points.
 * @param amount The amount of damage to be inflicted.
 */
    void Character::hit(int amount) {
        if (amount < 0) {
            throw std::invalid_argument("Error: amount must be non-negative.");
        }

        this->hitPoints -= amount;

        if (this->hitPoints < 0) {
            this->hitPoints = 0;
        }
    }

/**
 * @brief Getter to the name field.
 * @return The name of the character.
 */
    std::string Character::getName() const {
        return this->name;
    }

/**
 * @brief Getter to the location field.
 * @return The location of the character.
 */
    Point Character::getLocation() const {
        return this->location;
    }

/**
 * @brief Getter to the hitPoints field.
 * @return The value of the character hitPoints.
 */
    int Character::getHitPoints() const {
        return this->hitPoints;
    }

/**
 * @brief Checks if the Character is a member of a team.
 * @return true if the Character is a team member, false otherwise.
 */
    bool Character::isTeamMember() const {
        return this->teamMember;
    }

/**
 * @brief Sets the team membership status of the Character.
 * @param newTeamMember The new team membership status of the Character.
 * Set to true if the Character is a team member, and false if the Character is not part of any team.
 */
    void Character::setTeamMember(bool newTeamMember) {
        this->teamMember = newTeamMember;
    }

/**
 * @brief Generates a string representation of the Character.
 * @return A string representation of the Character, including the name, hit points, and location.
 */
    std::string Character::print() const {
        std::string characterInfo = "name: " + name + ", HitPoints: " + std::to_string(hitPoints) + ", location: ";
        characterInfo += location.print();
        return characterInfo;
    }

/**
 * @brief Setter for the location of the character.
 * @param newLocation The new location to set
 * @throw std::out_of_range if the new location is out of bounds
 */
    void Character::setLocation(Point newLocation) {
        if (std::abs(newLocation.getX()) > DBL_MAX || std::abs(newLocation.getY()) > DBL_MAX) {
            throw std::out_of_range("Error: Invalid coordinates. Out of bounds.");
        }
        this->location = newLocation;
    }
}