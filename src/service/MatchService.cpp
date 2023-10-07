#include "service/MatchService.hpp"
#include "repository/MatchRepository.hpp"
#include "service/ScoreManagerService.hpp"
#include <vector>

MatchService::MatchService(MatchRepository& mr, std::vector<User>& u) 
    : matchRepo(mr), users(u)
    //add the ScoreManagerService as an injected depen
    {}

void MatchService::checkAndProcessMatches() {
    this->matchRepo.loadDailyMatchesFromRawData(); 
    const std::vector<Match>& today_matches = this->matchRepo.getTodaysMatches();        

    for (auto auto_match : today_matches)  {
        int weight = 0; 
        std::map<User, std::vector<Player>> usersAndTheirPlayersInTodaysMatch;
        for (auto userBot : this->users) {
            std::vector<Player> usersPlayersInTodaysMatch;
            /*
                does the user have players in the match?
            */
            //if Team.lookup Match.away / home roster contains user playerList 
            const std::vector<Player>& p = auto_match.getTeam1().getRoster();
            const std::vector<Player>& p2 = auto_match.getTeam2().getRoster();
            std::vector<Player> concatenated(p);
            concatenated.insert(concatenated.end(), p2.begin(), p2.end());
            for(auto auto_user_roster_player : userBot.getPlayerList()) {
                if(std::find(concatenated.begin(), concatenated.end(), auto_user_roster_player) != concatenated.end()) {
                    weight++;
                    usersPlayersInTodaysMatch.push_back(auto_user_roster_player);
                    spdlog::info("Player {} found in today's match!", auto_user_roster_player.getName());
                }
            } 
            usersAndTheirPlayersInTodaysMatch.insert({userBot, usersPlayersInTodaysMatch});
        }
        //call the scoreManagerService
        //or just this function???
        //to-do refactor and rethink this approach 
        this->getTheScoresForAllPlayersPerUser(usersAndTheirPlayersInTodaysMatch);
    }
}

void MatchService::getTheScoresForAllPlayersPerUser(std::map<User, std::vector<Player>>& uatpitm) {

    for(const auto& userAndPlayers : uatpitm) {
        const User& user = userAndPlayers.first;
        const std::vector<Player>& players = userAndPlayers.second;

        for(const auto& player : players) {
            // Do something with 'user' and 'player'
            double currentFantasyPoints = this->getFantasyPointsForPlayer(player);
            spdlog::info("Player {} currently has {} points in their match", player.getName(), currentFantasyPoints);
        }
    }
}

double MatchService::getFantasyPointsForPlayer(const Player& p) {
    std::map<Player, double> matchResults = this->matchRepo.getPlayerStatsForMatch(this->matchRepo.getMatchForPlayer(p));

    auto it = matchResults.find(p);
    if (it != matchResults.end()) {
        return it->second;  // returns the double value for player p
    } else {
        // Handle the case where the player is not in the map
        spdlog::error("Player {} was not found in their own match results as expected", p.getName());
        return 0.0;
    }
}
//define a getGameTime method