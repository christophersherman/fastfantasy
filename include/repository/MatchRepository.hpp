#pragma once
#include "domain/Match.hpp"
#include "nlohmann/json_fwd.hpp"
#include "repository/TeamRepository.hpp"
#include "utils/api_caller.hpp"
#include "spdlog/spdlog.h"
#include "nlohmann/json.hpp"

class MatchRepository {

private:
ApiCaller& api_caller;
std::vector<Match> today_matches;
TeamRepository& teamRepo;
public:
MatchRepository(ApiCaller&, TeamRepository& tr);
void loadDailyMatchesFromRawData();
const std::vector<Match>& getTodaysMatches() const;
std::map<Player, double> getPlayerStatsForMatch(const Match& m);
Match getMatchForPlayer(const Player& p);
};
