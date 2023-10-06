#include "service/MatchService.hpp"
#include "repository/MatchRepository.hpp"
#include <vector>

MatchService::MatchService(MatchRepository& mr, std::vector<User>& u) 
    : matchRepo(mr), users(u)
    {}

void MatchService::checkAndProcessMatches() {
        
}
