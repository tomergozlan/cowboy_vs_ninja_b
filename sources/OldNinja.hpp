//
// Created by tomergozlan on 5/30/23.
//

#ifndef COWBOY_VS_NINJA_B_OLDNINJA_HPP
#define COWBOY_VS_NINJA_B_OLDNINJA_HPP

#include "Ninja.hpp"
#include "Character.hpp"

namespace ariel{
    class OldNinja : public Ninja {
    private:
        static const int OLD_NINJA_SPEED = 8;
        static const int OLD_NINJA_HIT_POINTS = 150;
    public:
        OldNinja(const std::string &name, const Point &location) : Ninja(name, location, OLD_NINJA_SPEED,OLD_NINJA_HIT_POINTS) {}
    };
}

#endif //COWBOY_VS_NINJA_B_OLDNINJA_HPP
