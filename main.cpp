#include <iostream>
#include <stdio.h>
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
  TeamRepository teamRepo(config["URL"], config["KEY"]);
  teamRepo.loadTeamFromRawData();

  for (auto bot : teamRepo.getTeams()) {
    teamRepo.loadTeamRosterFromRawData(bot);
  } 

  return 0;
}
