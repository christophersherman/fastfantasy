#pragma once
#include "domain/Match.hpp"
#include "utils/api_caller.hpp"
#include "spdlog/spdlog.h"

class MatchRepository {

private:
ApiCaller api_caller;
std::vector<Match> today_matches;

public:
MatchRepository(const std::string& url, const std::string& key);
void loadDailyMatchesFromRawData();
std::vector<Match> getTodaysMatches();
};
