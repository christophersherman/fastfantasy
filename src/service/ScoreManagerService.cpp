#include "service/ScoreManagerService.hpp"
#include "domain/Match.hpp"

ScoreManagerService::ScoreManagerService(const std::map<User, std::vector<Player>>& uatpitm, const Match& m) 
: usersAndTheirPlayersInTodaysMatch(uatpitm), match(m)
{
}

void ScoreManagerService::scoreMatch(MatchService& matchService) {

    for(const auto& userAndPlayers : this->usersAndTheirPlayersInTodaysMatch) {
        const User& user = userAndPlayers.first;
        const std::vector<Player>& players = userAndPlayers.second;

        for(const auto& player : players) {
            // Do something with 'user' and 'player'
            matchService.getFantasyPointsForPlayer(player);
        }
    }
}