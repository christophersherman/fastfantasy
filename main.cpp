#include <iostream>
#include <stdio.h>
#include "repository/MatchRepository.hpp"
#include "service/MatchService.hpp"
#include "utils/api_caller.hpp"
#include <map>
#include <utility>
#include <fstream> 
#include "repository/TeamRepository.hpp"
#include "service/MatchService.hpp"

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
  // inject the api_caller into matchRepo instead of making a new one  
  auto config = loadConfig("config.conf");
  ApiCaller apic(config["URL"], config["KEY"]);
  
  TeamRepository teamRepo(apic);
  teamRepo.loadTeamAndRosterFromRawData();

  MatchRepository matchRepo(apic, teamRepo);
  User sherm("sherman");
  sherm.draftPlayer(teamRepo.getTeamByName("Bears").getPlayerFromRosterByName("Justin Fields").value());
  std::vector<User> userVec;
  userVec.push_back(sherm); 
  MatchService matchServ(matchRepo, userVec);
  matchServ.checkAndProcessMatches(); 
  return 0;
}
