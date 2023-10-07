#pragma once

#include "Team.hpp"
#include <string>
#include <vector>

class Match {
private:
    Team team1;
    Team team2;
    int weight = 0; // Default initialization

public:
    Match() = default; // Default constructor
    Match(const Team& team1, const Team& team2);
    Match(const Team& team1, const Team& team2, int weight);

    // Getters
    const Team& getTeam1() const;
    const Team& getTeam2() const;
    int getWeight() const;

    // Optional setters and other methods
    void setWeight(int w);

};
