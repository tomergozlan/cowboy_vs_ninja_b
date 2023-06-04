//
// Created by tomergozlan on 6/1/23.
//

#ifndef COWBOY_VS_NINJA_B_SMARTTEAM_HPP
#define COWBOY_VS_NINJA_B_SMARTTEAM_HPP

#include "Team.hpp"
#include "Character.hpp"

namespace ariel {
    class Attackers{
    public:
        bool operator()(Character* character1,Character* character2) const;
    };

    class Compare{
    public:
        bool operator()(Character* character1,Character* character2) const;
    };

    class SmartTeam : public Team{

    public:
        SmartTeam(Character* leader);

        Point askEnemyLocation(Character* enemy);

        int askEnemyHitPoints(Character* enemy);


        void attack(Team *enemyTeam) override;

        void print() override;
    };

}

#endif //COWBOY_VS_NINJA_B_SMARTTEAM_HPP
