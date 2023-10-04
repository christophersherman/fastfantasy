#include "repository/MatchRepository.hpp"
#include "utils/api_caller.hpp"
#include <iostream>

MatchRepository::MatchRepository(const std::string& url, const std::string& key)
: api_caller(url, key)
{}

void MatchRepository::loadDailyMatchesFromRawData() {
    std::string today_date = this->api_caller.getTodaysDate(); 
    spdlog::info("Searching for games on the date {}", today_date); 
    this->api_caller.getRawDailyMatches(today_date);
}
