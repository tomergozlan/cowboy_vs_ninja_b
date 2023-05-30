//
// Created by tomergozlan on 5/30/23.
//

#ifndef COWBOY_VS_NINJA_B_TRAINEDNINJA_HPP
#define COWBOY_VS_NINJA_B_TRAINEDNINJA_HPP

#include "Ninja.hpp"
#include "Character.hpp"

namespace ariel{
    class TrainedNinja : public Ninja {
    private:
        static const int TRAINED_NINJA_SPEED = 12;
        static const int TRAINED_NINJA_HIT_POINTS = 120;
    public:
        TrainedNinja(const std::string &name, const Point &location) : Ninja(name, location, TRAINED_NINJA_SPEED,
                                                                             TRAINED_NINJA_HIT_POINTS) {}
    };

}

#endif //COWBOY_VS_NINJA_B_TRAINEDNINJA_HPP