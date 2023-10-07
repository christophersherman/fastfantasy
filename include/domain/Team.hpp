#pragma once

#include <string>
#include <vector>
#include "domain/Player.hpp"

class Team {
private:
    std::string team_name;
    std::string team_id;
    std::string team_city;
    std::string team_abbrev;
    std::vector<Player> roster;

public:
 
    Team();
    Team(const std::string& team_name);
    Team(const std::string& name, const std::string& id, const std::string& city, const std::string& abbrev);
    Team(const std::string& name, const std::string& id);

    // Getters, setters, and other method declarations would go here...
    std::string getTeamName() const;
    std::string getTeamId() const;
    std::string getTeamCity() const;
    std::string getTeamAbbrev() const;
    void addPlayerToRoster(Player& p);
    const std::vector<Player>& getRoster() const;
    std::optional<Player> getPlayerFromRosterByName(const std::string& name) const;
};
