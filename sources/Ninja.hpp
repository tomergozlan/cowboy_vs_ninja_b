
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
