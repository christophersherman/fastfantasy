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
using json = nlohmann::json;

class ApiCaller {
private:
    std::string request_url;
    std::string api_token;

    json makeRequest(const std::string& endpoint);
    json makeRequest(const std::string& endpoint, const std::map<std::string, std::string>& params);

public:
    ApiCaller(const std::string& configPath);
    ApiCaller(const std::string& host, const std::string& key);
    
    json getRawTeams();
    json getRawTeamsRoster(const std::string& teamId);
    json getRawDailyMatchs(const std::string& date);
};
