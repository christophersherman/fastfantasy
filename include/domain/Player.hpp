#pragma once

#include <string>
#include <vector>

class Player {
private:
    std::string name;
    float fantasy_points;
    int jersey_num;
    std::string position;
    std::string team_name; // Consider making this a struct: team_name, team_id
    int age;

public:
    // Constructors
    Player(const std::string& name);
    Player(const std::string& name, float fantasy_points, int jersey_num, const std::string& position, const std::string& team_name, int age);

    // Setters
    void setName(const std::string& name);
    void setFantasyPoints(float fantasy_points);
    void setJerseyNumber(int jersey_num);
    void setPosition(const std::string& position);
    void setTeamName(const std::string& team_name);
    void setAge(int age);

    // Getters
    std::string getName() const;
    std::string getPosition() const;
    std::string getTeamName() const;
    float getFantasyPoints() const;
    int getJerseyNumber() const;
    int getAge() const;
};