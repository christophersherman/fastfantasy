#include <iostream>
#include <stdio.h>
#include "utils/api_caller.hpp"
#include <map>
#include <utility>
#include <fstream> 


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
  std::cout << config["URL"] << std::endl;
  ApiCaller api_caller_instance(config["URL"], config["KEY"]);
  std::cout << api_caller_instance.getRawTeams();
  return 0;
}
