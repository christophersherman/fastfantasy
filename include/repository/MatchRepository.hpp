#pragma once
#include "domain/Match.hpp"
#include "repository/TeamRepository.hpp"
#include "utils/api_caller.hpp"
#include "spdlog/spdlog.h"
#include "nlohmann/json.hpp"

class MatchRepository {

private:
ApiCaller api_caller;
std::vector<Match> today_matches;

public:
MatchRepository(const std::string& url, const std::string& key);
void loadDailyMatchesFromRawData(const TeamRepository& teamRepo);
std::vector<Match> getTodaysMatches();
};
