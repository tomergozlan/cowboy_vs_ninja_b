/**
 * @file Ninja.hpp
 * @brief Represents a ninja character in the game.
 * The Ninja class is a derived class of the Character class. It represents a ninja character with
 * fast movement and slashing abilities. It can move towards an enemy and perform a powerful slash attack.
 * @author Tomer Gozlan
 * @date 16/05/2023
 */

#ifndef COWBOY_VS_NINJA_B_NINJA_HPP
#define COWBOY_VS_NINJA_B_NINJA_HPP

#include <iostream>
#include <string>
#include "Character.hpp"
#include "Point.hpp"

namespace ariel {

    class Ninja : public Character {
    private:
        int speed;

    public:
        Ninja(const std::string &name, const Point &location, int speed, int hitPoints);

        void move(Character *enemy);

        void slash(Character *enemy);

        std::string print() const override;

    };
}

#endif //COWBOY_VS_NINJA_B_NINJA_HPP