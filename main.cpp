#include <iostream>
#include <stdio.h>
#include "repository/MatchRepository.hpp"
#include "utils/api_caller.hpp"
#include <map>
#include <utility>
#include <fstream> 
#include "repository/TeamRepository.hpp"

std::map<std::string, std::string> loadConfig(const std::string& filename) {
  std::map<std::string, std::string> config;
  std::ifstream file(filename);
  std::string line;
  while (std::getline(file, line)) {
      size_t pos = line.find('=');
      if (pos != std::string::npos) {
          std::string key = line.substr(0, pos);
          std::string value = line.substr(pos + 1);
          config[key] = value;
      }
  }
  return config;
}

int main() {
  auto config = loadConfig("config.conf");
  //load all the teams into a repo 
  TeamRepository teamRepo(config["URL"], config["KEY"]);
  // teamRepo.loadTeamAndRosterFromRawData();
  teamRepo.loadTeamsFromRawData();
  //load all the players into each team 
  //for (auto bot : teamRepo.getTeams()) {
  //  teamRepo.loadTeamRosterFromRawData(bot);
  //}
  Team tester = teamRepo.getTeamByAbbrev("KC");
  teamRepo.loadTeamRosterFromRawData(tester);
  // MatchRepository matchRepo(config["URL"], config["KEY"]);
  // matchRepo.loadDailyMatchesFromRawData(teamRepo);
  return 0;
}
