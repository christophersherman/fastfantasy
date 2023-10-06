#pragma once
#include "../domain/Match.hpp"
#include "../domain/Player.hpp"
#include "../domain/Team.hpp"
#include <cpr/cpr.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <map>
#include <sstream> 
#include <iomanip> 
#include <ctime>
#include <cstdlib>

using json = nlohmann::json;

class ApiCaller {
private:
    std::string request_url;
    std::string api_token;

    json makeRequest(const std::string& endpoint) const;
    json makeRequest(const std::string& endpoint, const std::map<std::string, std::string>& params) const;

public:
    ApiCaller(const std::string& configPath);
    ApiCaller(const std::string& host, const std::string& key);
    int safeStringToInt(const std::string& str, int defaultValue = -1) const;
    std::string getTodaysDate() const; 
    json getRawTeams(const std::map<std::string, std::string>& params = {}) const;
    json getRawDailyMatches(const std::string& date) const;
    json getRawTeamsRosterById(const std::string& teamId) const;
    json getRawTeamsRosterByAbbrev(const std::string& team_abbrev) const;
};
