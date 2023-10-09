#include "service/MatchService.hpp"
#include "repository/MatchRepository.hpp"
#include "service/ScoreManagerService.hpp"
#include <unordered_set>
#include <vector>

MatchService::MatchService(MatchRepository& mr, std::vector<User>& u) 
    : matchRepo(mr), users(u)
    //add the ScoreManagerService as an injected depen
    {}

void MatchService::checkAndProcessMatches() {
    this->matchRepo.loadDailyMatchesFromRawData();
    const std::vector<Match>& today_matches = this->matchRepo.getTodaysMatches();

    for (const auto& single_match : today_matches) {
        auto usersAndTheirPlayersInTodaysMatch = getUsersPlayersInMatch(single_match);
        this->getTheScoresForAllPlayersPerUser(usersAndTheirPlayersInTodaysMatch);
    }
}

std::map<User, std::vector<Player>> MatchService::getUsersPlayersInMatch(const Match& single_match) {
    std::map<User, std::vector<Player>> usersAndTheirPlayersInTodaysMatch;

    // Create an unordered_set for quick player lookups.
    std::unordered_set<Player> allPlayersInMatch;
    const auto& team1Roster = single_match.getTeam1().getRoster();
    const auto& team2Roster = single_match.getTeam2().getRoster();
    allPlayersInMatch.insert(team1Roster.begin(), team1Roster.end());
    allPlayersInMatch.insert(team2Roster.begin(), team2Roster.end());

    for (const auto& userBot : this->users) {
        std::vector<Player> usersPlayersInTodaysMatch;

        for (const auto& player : userBot.getPlayerList()) {
            if (allPlayersInMatch.count(player)) {
                usersPlayersInTodaysMatch.push_back(player);
                spdlog::info("Player {} found in today's match!", player.getName());
            }
        }

        usersAndTheirPlayersInTodaysMatch[userBot] = usersPlayersInTodaysMatch;
    }

    return usersAndTheirPlayersInTodaysMatch;
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
