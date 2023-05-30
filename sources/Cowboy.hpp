
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
