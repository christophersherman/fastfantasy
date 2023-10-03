#include "domain/Player.hpp"

// Constructors
Player::Player(const std::string& name)
    : name(name)
    , fantasy_points(0.0f)
    , jersey_num(0)
    , position("")
    , team_name("")
    , age(0)
{
}

Player::Player(const std::string& name, float fantasy_points, int jersey_num, const std::string& position, const std::string& team_name, int age)
    : name(name)
    , fantasy_points(fantasy_points)
    , jersey_num(jersey_num)
    , position(position)
    , team_name(team_name)
    , age(age)
{
}

// Setters
void Player::setName(const std::string& name)
{
    this->name = name;
}

void Player::setFantasyPoints(float fantasy_points)
{
    this->fantasy_points = fantasy_points;
}

void Player::setJerseyNumber(int jersey_num)
{
    this->jersey_num = jersey_num;
}

void Player::setPosition(const std::string& position)
{
    this->position = position;
}

void Player::setTeamName(const std::string& team_name)
{
    this->team_name = team_name;
}

void Player::setAge(int age)
{
    this->age = age;
}

// Getters
std::string Player::getName() const
{
    return name;
}

std::string Player::getPosition() const
{
    return position;
}

std::string Player::getTeamName() const
{
    return team_name;
}

float Player::getFantasyPoints() const
{
    return fantasy_points;
}

int Player::getJerseyNumber() const
{
    return jersey_num;
}

int Player::getAge() const
{
    return age;
}
