#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

class Capiml {
public:
  static std::string Read(const std::string pathfile) {
    std::ifstream inputFile(pathfile);
    if (!inputFile.is_open())
      exit(1);

    std::stringstream buff;
    buff << inputFile.rdbuf();

    return buff.str();
  }
};
