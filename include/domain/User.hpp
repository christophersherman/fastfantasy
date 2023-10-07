#pragma once 
#include <vector>
#include <string>
#include "utils/api_caller.hpp"
#include "repository/TeamRepository.hpp"

class User {
private:
    std::vector<Player> playerList;
    std::string name;
public:
    User(const std::string& name);
    void draftPlayer(const Player& player);
    void dropPlayer(const Player& player);
    //in the future make a user service to get players via other attributes?
    const std::vector<Player>& getPlayerList() const;
    friend bool operator<(const User& lhs, const User& rhs);
};
