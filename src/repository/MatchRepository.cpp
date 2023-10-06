#include "repository/MatchRepository.hpp"
#include "domain/Match.hpp"
#include "repository/TeamRepository.hpp"
#include "utils/api_caller.hpp"
#include <iostream>
#include <nlohmann/detail/json_pointer.hpp>
#include <spdlog/spdlog.h>
#include <vector>

MatchRepository::MatchRepository(const std::string& url, const std::string& key)
: api_caller(url, key)
{}

void MatchRepository::loadDailyMatchesFromRawData(const TeamRepository& teamRepo) {
    //std::string today_date = this->api_caller.getTodaysDate(); 
    std::string today_date = "20231005";
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
}

const std::vector<Match> MatchRepository::getTodaysMatches() const {
    return this->today_matches;
}
