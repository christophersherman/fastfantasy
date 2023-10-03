#include "domain/Match.hpp"

Match::Match(const Team& t1, const Team& t2)
    : team1(t1)
    , team2(t2)
{
    // Do any additional initialization if required.
}

Match::Match(const Team& t1, const Team& t2, int w)
    : team1(t1)
    , team2(t2)
    , weight(w)
{
    // Do any additional initialization if required.
}

const Team& Match::getTeam1() const
{
    return team1;
}

const Team& Match::getTeam2() const
{
    return team2;
}

int Match::getWeight() const
{
    return weight;
}

void Match::setWeight(int w)
{
    weight = w;
}
