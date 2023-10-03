#pragma once

#include <string>
#include <vector>

class Team {
private:
    std::string team_name;
    std::string team_id;
    std::string team_city;
    std::string team_abbrev;

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
};
