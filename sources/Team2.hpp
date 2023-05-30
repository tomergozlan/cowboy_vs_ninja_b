//
// Created by tomergozlan on 5/30/23.
//

#ifndef COWBOY_VS_NINJA_B_TEAM2_HPP
#define COWBOY_VS_NINJA_B_TEAM2_HPP

#include "Character.hpp"
#include "Team.hpp"

namespace ariel {
    class Team2 : public Team {

    public:
        Team2(Character *leader);

        void attack(Team *enemyTeam) override;

        void print() override;
    };
}

#endif //COWBOY_VS_NINJA_B_TEAM2_HPP
