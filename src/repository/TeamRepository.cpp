#include "repository/TeamRepository.hpp"

TeamRepository::TeamRepository(const std::string& url, const std::string& key)
    : api_caller(url, key)
    {}

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
