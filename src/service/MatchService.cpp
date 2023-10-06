#include "service/MatchService.hpp"
#include "repository/MatchRepository.hpp"
#include <vector>

MatchService::MatchService(MatchRepository& mr, std::vector<User>& u) 
    : matchRepo(mr), users(u)
    {}

void MatchService::checkAndProcessMatches() {
    this->matchRepo.loadDailyMatchesFromRawData(); 
    const std::vector<Match>& today_matches = this->matchRepo.getTodaysMatches();        

    for (auto auto_match : today_matches)  {
        int weight = 0; 
        for (auto userBot : this->users) {
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
                    spdlog::info("Player {} found in today's match!", auto_user_roster_player.getName());
                }
            } 
        }
    }
}
