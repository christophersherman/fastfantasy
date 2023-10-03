#include "domain/Team.hpp"

Team::Team()
    : team_name("")
    , team_id("")
    , team_city("")
    , team_abbrev("")
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

// Implementations of other methods would go here...
