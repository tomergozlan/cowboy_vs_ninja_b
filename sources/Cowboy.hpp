/**
 * @file Cowboy.hpp
 * @brief Contains the declaration of the Cowboy class.
 * This file defines the Cowboy class, which is a derived class of the Character class. It represents a
 * cowboy character in a game. The Cowboy class provides methods for shooting, reloading, and managing bullets.
 * @author Tomer Gozlan.
 * @date 15/05/2023
 */

#ifndef COWBOY_VS_NINJA_B_COWBOY_HPP
#define COWBOY_VS_NINJA_B_COWBOY_HPP

#include <iostream>
#include <string>
#include "Character.hpp"
#include "Point.hpp"

namespace ariel {

    class Cowboy : public Character {
    private:
        int bullets;

    public:
        Cowboy(const std::string &name, const Point &location);

        void shoot(Character *enemy);

        bool hasboolets() const;

        void reload();

        int getBullets() const;

        std::string print() const override;
    };
}
#endif //COWBOY_VS_NINJA_B_COWBOY_HPP