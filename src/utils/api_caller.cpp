#include "utils/api_caller.hpp"
#include <bits/chrono.h>
#include <cpr/parameters.h>
#include <cpr/response.h>
#include <chrono> 
#include <iostream> 
#include "spdlog/spdlog.h"

ApiCaller::ApiCaller(const std::string& host, const std::string& key)
    : request_url(host)
    , api_token(key)
{
}

json ApiCaller::makeRequest(const std::string& endpoint, const std::map<std::string, std::string>& params)
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

json ApiCaller::makeRequest(const std::string& endpoint) {
    std::map<std::string, std::string> empty_params;
    return makeRequest(endpoint, empty_params);
}

json ApiCaller::getRawTeams() {
    return makeRequest("getNFLTeams"); 
}

json ApiCaller::getRawTeamsRoster(const std::string& teamId) {
    return NULL;
}
