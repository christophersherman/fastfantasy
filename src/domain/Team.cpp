#include "domain/Team.hpp"
#include <vector>

Team::Team()
    : team_name("")
    , team_id("")
    , team_city("")
    , team_abbrev("")
    , roster()
{
}

Team::Team(const std::string& name)
    : team_name(name)
{
}

Team::Team(const std::string& name, const std::string& id,
    const std::string& city, const std::string& abbrev)
    : team_name(name)
    , team_id(id)
    , team_city(city)
    , team_abbrev(abbrev)
{
}

Team::Team(const std::string& name, const std::string& id)
    : team_name(name)
    , team_id(id)
    , team_city("")
    , team_abbrev("")
{
}
void Team::addPlayerToRoster(Player& p){
    this->roster.push_back(p);
}

// Implementations of other methods would go here...
std::string Team::getTeamName() const {
    return this->team_name;
}

std::string Team::getTeamId() const { 
    return this->team_id;
}

std::string Team::getTeamAbbrev() const {
    return this->team_abbrev;
}

std::string Team::getTeamCity() const {
    return this->team_city;
}

const std::vector<Player>& Team::getRoster() const {
    return this->roster;
}

std::optional<Player> Team::getPlayerFromRosterByName(const std::string& name) const {
    for (const Player& p : roster) {  // Use direct member access rather than getter
        if(p.getName() == name) {
            return p;
        }
    }
    return std::nullopt;  // Player was not found
}
