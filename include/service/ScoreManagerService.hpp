#pragma once

#include "service/MatchService.hpp"
#include <map>
class ScoreManagerService{

private:
const std::map<User, std::vector<Player>>& usersAndTheirPlayersInTodaysMatch;
const Match& match;

public:
ScoreManagerService() = default;
ScoreManagerService(const std::map<User, std::vector<Player>>& uatpitm, const Match& m);
void scoreMatch(MatchService& ms );
};