//
// Created by Tomer Gozlan on 16/05/2023.
//

#ifndef COWBOY_VS_NINJA_A_TEAM_HPP
#define COWBOY_VS_NINJA_A_TEAM_HPP

#include "Point.hpp"
#include "Character.hpp"
#include "Ninja.hpp"
#include "OldNinja.hpp"
#include "TrainedNinja.hpp"
#include "YoungNinja.hpp"
#include "Cowboy.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

namespace ariel {

    class Team {
    private:
        Character *leader;
        std::vector<Character *> fighters;

    public:
        Team(Character *leader);

        Character *getLeader() const;

        const std::vector<Character *> &getFighters() const;

         virtual ~Team();

        void add(Character *fighter);

        Character *findClosestCharacter(const Point &location, const std::vector<Character *> &fighters) const;

        virtual void attack(Team *enemyTeam);

        int stillAlive() const;

        void setLeader(Character* newLeader);

        virtual void print() ;

        // Make tidy make me write this
        Team(const Team &) = delete;

        Team &operator=(const Team &) = delete;

        Team(Team &&) = delete;

        Team &operator=(Team &&) = delete;
    };

}

#endif //COWBOY_VS_NINJA_A_TEAM_HPP
