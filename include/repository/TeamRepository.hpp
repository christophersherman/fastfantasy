#pragma once
#include <string>
#include <vector>
#include "domain/Team.hpp"
#include "utils/api_caller.hpp"

class TeamRepository {
private:
    std::vector<Team> teams;
    ApiCaller api_caller;
public:
    TeamRepository(const std::string& url, const std::string& key);
    void loadTeamFromRawData();
    Team getTeamByCity(const std::string& city_name);
    Team getTeamById(const std::string& city_id);
    Team getTeamByAbbrev(const std::string& team_abbrev);
};