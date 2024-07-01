#include "ThreeBody.h"
#include <fstream>
#include <sstream>
#include <unordered_map>


ThreeBody consume_ini(std::string ini_file) {
     
}

// Parse the ini file and generate a map of the data.
std::unordered_map<std::string, std::string> read_ini(const std::string filename) {

    std::unordered_map<std::string, std::string> data;
    std::ifstream file(filename);
    std::string line, section;

    while (std::getline(file, line))
    {
        if(line.empty() || line[0] == ';' || line[0] == '#') continue; // ignore empties and comments.
        if (line[0] == '[' && line.back() == ']') {
            section = line.substr(1, line.size() - 2);
        } else {
            std::istringstream iss(line);
            std::string key, value;
            if(std::getline(iss, key, '=') && std::getline(iss, value)) { // parse out key value pairs
                data[section + "." + key] = value;
            }
        }
    }

    return data;
    
}