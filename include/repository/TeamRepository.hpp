#pragma once
#include <string>
#include <vector>
#include "domain/Team.hpp"
#include "utils/api_caller.hpp"
#include "nlohmann/json_fwd.hpp"
#include "utils/api_caller.hpp"
#include <cstddef>
#include <nlohmann/json.hpp>
#include <iostream>
#include <stdexcept>
#include "spdlog/spdlog.h"

class TeamRepository {
private:
    std::vector<Team> teams;
    ApiCaller api_caller;
public:
    TeamRepository(const std::string& url, const std::string& key);
    void loadTeamsFromRawData(const std::map<std::string, std::string>& params = {});
    void loadTeamAndRosterFromRawData();
    void loadTeamRosterFromRawData(Team& team); 
    Team populateTeamRoster(Team& team, nlohmann::json rosterResponse);
    const std::vector<Team>& getTeams() const; 
    Team getTeamByCity(const std::string& city_name) const;
    Team getTeamById(const std::string& city_id) const;
    Team getTeamByAbbrev(const std::string& team_abbrev) const;
    Team getTeamByName(const std::string& team_name) const;

    //explore the idea of returning non-const references for quick modifications
};
