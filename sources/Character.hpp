/**
 * @file Character.hpp
 * @brief Defines the Character class and its subclasses Cowboy, Ninja, YoungNinja, TrainedNinja, and OldNinja.
 * @author Tomer Gozlan
 * @date 15/05/2023
 */

#ifndef COWBOY_VS_NINJA_A_CHARACTER_HPP
#define COWBOY_VS_NINJA_A_CHARACTER_HPP

#include <iostream>
#include <string>
#include "Point.hpp"

namespace ariel {

    class Character {
    private:
        Point location;
        int hitPoints;
        std::string name;
        bool teamMember;

    public:
        Character(const std::string &name, const Point &location, const int &hitPoints);

        virtual ~Character() = default;

        void setHitPoints(int NewHitPoints);

        bool isAlive() const;

        double distance(const Character *other) const;

        void hit(int amount);

        std::string getName() const;

        Point getLocation() const;

        int getHitPoints() const;

        bool isTeamMember() const;

        void setTeamMember(bool newTeamMember);

        void setLocation(Point newLocation);

        virtual std::string print() const = 0;


        // Make tidy make me do that
        Character(const Character &other) = default;

        Character &operator=(const Character &other) = default;

        Character(Character &&other) = default;

        Character &operator=(Character &&other) = default;
    };

}

#endif // COWBOY_VS_NINJA_A_CHARACTER_HPP
