#include "repository/MatchRepository.hpp"
#include "domain/Match.hpp"
#include "repository/TeamRepository.hpp"
#include "service/MatchService.hpp"
#include "utils/api_caller.hpp"
#include <iostream>
#include <nlohmann/detail/json_pointer.hpp>
#include <spdlog/spdlog.h>
#include <vector>

MatchRepository::MatchRepository(ApiCaller& api, TeamRepository& tr)
: api_caller(api), teamRepo(tr)
{}

void MatchRepository::loadDailyMatchesFromRawData() {
    // std::string today_date = this->api_caller.getTodaysDate();
    std::string today_date = "20231008"; //test date 
    spdlog::info("Searching for games on the date {}", today_date); 
    nlohmann::json response = this->api_caller.getRawDailyMatches(today_date);
    if (response.contains("body") && response["body"].is_array()){
        for(const auto& auto_team: response["body"]) {
            if (auto_team.contains("away") && auto_team["away"].is_string()
               && auto_team.contains("home") && auto_team["home"].is_string()) 
            {
                Team away = teamRepo.getTeamByAbbrev(auto_team["away"]);
                Team home = teamRepo.getTeamByAbbrev(auto_team["home"]);
                Match match(away, home);
                this->today_matches.push_back(match);
                spdlog::info("Match {} against {} loaded into matchRepo", away.getTeamName(), home.getTeamName());
            
            } else {
               spdlog::error("Unexpected Match data");
           }
        }
    } else {
        spdlog::error("Response body not present or not array");
    }
    if(this->today_matches.empty()) {
        spdlog::info("No matches found for today, {}", today_date);
    }    
}

std::map<Player, double> MatchRepository::getPlayerStatsForMatch(const Match& m) {
    std::map<std::string, std::string> params;
    // std::string today_date = this->api_caller.getTodaysDate();
    std::string today_date = "20231008"; //test date 
    std::string concatenated = today_date + "_" + m.getTeam1().getTeamAbbrev() + "@" + m.getTeam2().getTeamAbbrev(); 
    spdlog::info("attempting to get updates for {}", "gameID" + concatenated); 
    params.insert({"gameID", concatenated}); 
    params.insert({"fantasyPoints", "true"});

    std::map<Player, double> playersAndPoints;
    nlohmann::json response = this->api_caller.getRawUpdatesForMatch(params);

    if (response.contains("body") && response["body"].contains("playerStats")){ 
        for(auto& [playerID, playerEntry] : response["body"]["playerStats"].items()) {
            
            std::string playerEntryName = playerEntry["longName"].get<std::string>();
            std::string fantasyPointsStr = playerEntry["fantasyPointsDefault"]["PPR"].get<std::string>();
            double fantasyPoints = std::stod(fantasyPointsStr);  // Convert the string to double
 
            if(m.getTeam1().getPlayerFromRosterByName(playerEntryName).has_value()){
                playersAndPoints.insert({m.getTeam1().getPlayerFromRosterByName(playerEntryName).value(), fantasyPoints});                
            } else if(m.getTeam2().getPlayerFromRosterByName(playerEntryName).has_value()){
                playersAndPoints.insert({m.getTeam2().getPlayerFromRosterByName(playerEntryName).value(), fantasyPoints});                
            } else {
                spdlog::error("somehow cannot find the API response player in the match roster");
            } 
        }
        return playersAndPoints; 
    }
 
    spdlog::error("Live box updates did not contain response body");
}
//todo this function cant return null for a player?
Match MatchRepository::getMatchForPlayer(const Player& p) {
    for (const auto& m : this->getTodaysMatches()){
        //idk why but the Roster results in the getTeamsAndRoster puts player team NAme as the name by abbreviation 
        if (m.getTeam1().getTeamAbbrev() == p.getTeamName() || m.getTeam2().getTeamAbbrev()== p.getTeamName()) {
            return m;
        }
    }
    spdlog::error("match not found today for {} ", p.getName());
}
const std::vector<Match>& MatchRepository::getTodaysMatches() const {
    return this->today_matches;
}
