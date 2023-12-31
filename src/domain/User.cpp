#include "domain/User.hpp"
#include "domain/Player.hpp"
#include <vector>

User::User(const std::string& name) 
: name(name)
{
}

void User::draftPlayer(const Player& player) {
    this->playerList.push_back(player);
}

void User::dropPlayer(const Player& player) {
    //vector stuff to remove player from list
    //std::remove will put all objects in vec matching to the end, then remove them all
    this->playerList.erase(std::remove(this->playerList.begin(), this->playerList.end(), player), this->playerList.end());
}

const std::vector<Player>& User::getPlayerList() const {
    return this->playerList;
}

bool operator<(const User& lhs, const User& rhs) {
    return lhs.name < rhs.name;
}