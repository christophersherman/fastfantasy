#include "repository/TeamRepository.hpp"
#include "domain/Team.hpp"
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

TeamRepository::TeamRepository(const std::string& url, const std::string& key)
    : api_caller(url, key)
    {}

const std::vector<Team> TeamRepository::getTeams() const {
    return this->teams;
}

void TeamRepository::loadTeamFromRawData() {
    nlohmann::json response = this->api_caller.getRawTeams();
    
    if (response.contains("body") && response["body"].is_array()) {
        for(const auto& team : response["body"]){
            if (team.contains("teamName") && team["teamName"].is_string() &&
                team.contains("teamID") && team["teamID"].is_string() &&
                team.contains("teamCity") && team["teamCity"].is_string() &&
                team.contains("teamAbv") && team["teamAbv"].is_string()) {
                
                Team t(team["teamName"].get<std::string>(), 
                       team["teamID"].get<std::string>(), 
                       team["teamCity"].get<std::string>(), 
                       team["teamAbv"].get<std::string>()); 
                       
                this->teams.push_back(t);
                spdlog::info("team {} saved to teamRepository", t.getTeamName());
            }
        }
    } else {
        spdlog::error("Response body not present or not array");
    }
}

void TeamRepository::loadTeamRosterFromRawData(Team& team) {
    nlohmann::json response = this->api_caller.getRawTeamsRosterByAbbrev(team.getTeamAbbrev());
    std::cout << response << std::endl;    
    if (response.contains("body") && response["body"].contains("roster") && response["body"]["roster"].is_array()){
        for(const auto& auto_team: response["body"]["roster"]){
                /*
                    name
                    jersey_num
                    position
                    team_name
                    age 
                */
            if (auto_team.contains("longName") && auto_team["longName"].is_string()
                && auto_team.contains("jerseyNum") && auto_team["jerseyNum"].is_string()
                && auto_team.contains("team") && auto_team["team"].is_string()
                && auto_team.contains("pos") && auto_team["pos"].is_string()
                && auto_team.contains("age") && auto_team["age"].is_string()) {
                
                //i need a helper function to safely convert since the string can be empty for random punters or something
                int jerseyNum = api_caller.safeStringToInt(auto_team["jerseyNum"].get<std::string>());
                int age = api_caller.safeStringToInt(auto_team["age"].get<std::string>());

                Player p(auto_team["longName"], jerseyNum, auto_team["pos"], auto_team["team"], age);
                team.addPlayerToRoster(p);

                spdlog::info("Player {} loaded into Team Roster", p.getName());
            
            } else {
                spdlog::error("Unexpected Team Roster data");
            }
        }
    } else {
        spdlog::error("Response body not present or not array");
    }  
}

Team TeamRepository::getTeamByCity(const std::string& city_name) const {
    for (const Team& t : this->teams ) {
        if (t.getTeamCity() == city_name) {
            return t;
        } 
    }
    spdlog::error("Team with city name {} not found in teamsRepository", city_name);
    throw std::runtime_error("Team not found");
    // c++17 can do optional<Team> like in spring boot... can return std::nullopt in that case.
}

Team TeamRepository::getTeamById(const std::string& team_id) const {
    for (const Team& t : this->teams ) {
        if (t.getTeamId() == team_id) {
            return t;
        }
    }
    spdlog::error("Team with ID {} not found in teamsRepository", team_id);
    throw std::runtime_error("Team not found");
}

Team TeamRepository::getTeamByAbbrev(const std::string& team_abbrev) const {
    for (const Team& t : this->teams) {
        if (t.getTeamAbbrev() == team_abbrev) {
            return t;
        }
    }
    spdlog::error("Team with abbrev {} not found in teamsRepository", team_abbrev);
    throw std::runtime_error("Team not found");
}

Team TeamRepository::getTeamByName(const std::string& team_name) const {
    for (const Team& t : this->teams) {
        if (t.getTeamName() == team_name) {
            return t;
        }
    }
    spdlog::error("Team with name {} not found in teamsRepository", team_name);
    throw std::runtime_error("Team not found");
}
