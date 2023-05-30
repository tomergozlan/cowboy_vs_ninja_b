//
// Created by tomergozlan on 5/29/23.
//

#ifndef COWBOY_VS_NINJA_B_YOUNGNINJA_HPP
#define COWBOY_VS_NINJA_B_YOUNGNINJA_HPP

#include "Ninja.hpp"
#include "Character.hpp"

namespace ariel {

    class YoungNinja : public Ninja {
    private:
        static const int YOUNG_NINJA_SPEED = 14;
        static const int YOUNG_NINJA_HIT_POINTS = 100;

    public:
        YoungNinja(const std::string &name, const Point &location) : Ninja(name, location, YOUNG_NINJA_SPEED,
                                                                           YOUNG_NINJA_HIT_POINTS) {}
    };
}

#endif //COWBOY_VS_NINJA_B_YOUNGNINJA_HPP
