#include "utils/api_caller.hpp"
#include <chrono>
#include <cpr/parameters.h>
#include <cpr/response.h>
#include <chrono> 
#include <iostream> 
#include <string_view>
#include "spdlog/spdlog.h"

ApiCaller::ApiCaller(const std::string& host, const std::string& key)
    : request_url(host)
    , api_token(key)
{
}

json ApiCaller::makeRequest(const std::string& endpoint, const std::map<std::string, std::string>& params) const
{

    //iterate over the params map and populate cpr with its contents
    cpr::Parameters cpr_params;
    for (const auto& [key, value] : params) { 
        cpr_params.Add({key, value}); 
    }
    //start measuring response time 
    auto start = std::chrono::high_resolution_clock::now();

    cpr::Response response = cpr::Get(cpr::Url { "https://" + request_url + "/" + endpoint }, 
    cpr::Header { 
        { "X-RapidAPI-Key", api_token },
        { "X-RapidAPI-Host", request_url }
    }, 
    cpr::Parameters{cpr_params});

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    spdlog::info("Response time : {}ms", duration); 
    if (response.status_code == 200) { // OK
        return nlohmann::json::parse(response.text);
    } else {
        // handle error
        return nlohmann::json();
    }
}

json ApiCaller::makeRequest(const std::string& endpoint) const {
    std::map<std::string, std::string> empty_params;
    return this->makeRequest(endpoint, empty_params);
}

json ApiCaller::getRawTeams(const std::map<std::string, std::string>& params) const {
    return this->makeRequest("getNFLTeams", params); 
}

json ApiCaller::getRawTeamsRosterById(const std::string& team_id) const {
    /*
    optional params. looks like you only need teamID OR teamAbv.
    teamID: '6',
    teamAbv: 'CHI',
    getStats: 'true'
    archiveDate: xxx 
    */

    std::map<std::string, std::string> params;
    params.insert({"teamID", team_id});
    return this->makeRequest("getNFLTeamRoster", params);
}

json ApiCaller::getRawTeamsRosterByAbbrev(const std::string& team_abbrev) const {
    /*
    optional params. looks like you only need teamID OR teamAbv.
    teamID: '6',
    teamAbv: 'CHI',
    getStats: 'true'
    archiveDate: xxx 
    */
    
    std::map<std::string, std::string> params;
    params.insert({"teamAbv", team_abbrev});
    return this->makeRequest("getNFLTeamRoster", params);
}

json ApiCaller::getRawDailyMatches(const std::string& date) const {
    std::map<std::string, std::string> params;
    params.insert({"gameDate", date});
    return this->makeRequest("getNFLGamesForDate", params);
}

int ApiCaller::safeStringToInt(const std::string& str, int defaultValue) const {
    try {
        return std::stoi(str);
    } catch (const std::invalid_argument& e) {
        return defaultValue;
    }
}

//todo re-write me 
std::string ApiCaller::getTodaysDate() const {
    using namespace std::chrono;

    // Hardcoded UTC offset in seconds for New York's standard time
    int offset = -18000;  // For UTC-5

    // Get current UTC time
    auto now = system_clock::now();
    
    // Adjust the current time for New York's offset
    auto newYorkTime = now + seconds(offset);

    // Convert time_point to tm
    std::time_t time_t_val = system_clock::to_time_t(newYorkTime);
    std::tm* tm_val = std::gmtime(&time_t_val); 

    // Format date
    char buf[9];
    if (std::strftime(buf, sizeof(buf), "%Y%m%d", tm_val) == 0) {
        // Date formatting failed
        std::cerr << "Date formatting failed." << std::endl;
        return "";
    }
    
    return std::string(buf);
}
 
json ApiCaller::getRawUpdatesForMatch(const std::map<std::string, std::string>& params) const {
    return this->makeRequest("getNFLBoxScore", params);
}
