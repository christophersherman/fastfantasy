#pragma once
#include "domain/Match.hpp"
#include "repository/MatchRepository.hpp"
#include "domain/User.hpp"

class MatchService {
private:
MatchRepository& matchRepo;
std::vector<User>& users;

public:
MatchService();
MatchService(MatchRepository& mr, std::vector<User>& u);
void checkAndProcessMatches();
};
