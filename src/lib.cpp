#include "ThreeBody.h"
#include <fstream>
#include <sstream>
#include <unordered_map>


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


ThreeBody consume_ini(std::string ini_file) {

    std::unordered_map<std::string, std::string> data = read_ini(ini_file);
    ThreeBody tb;

    // m1
    tb.body1.mass = std::stod(data["Body1.mass"]);
    tb.body1.position = {
        std::stod(data["Body1.position_x"]),
        std::stod(data["Body1.position_y"]),
        std::stod(data["Body1.position_z"])
    };

    tb.body1.velocity = {
        std::stod(data["Body1.velocity_x"]),
        std::stod(data["Body1.velocity_y"]),
        std::stod(data["Body1.velocity_z"])
    };

    //m2
    tb.body2.mass = std::stod(data["Body2.mass"]);
    tb.body2.position = {
        std::stod(data["Body2.position_x"]),
        std::stod(data["Body2.position_y"]),
        std::stod(data["Body2.position_z"])
    };

    tb.body2.velocity = {
        std::stod(data["Body2.velocity_x"]),
        std::stod(data["Body2.velocity_y"]),
        std::stod(data["Body2.velocity_z"])
    };

    //m3
    tb.body3.mass = std::stod(data["Body3.mass"]);
    tb.body3.position = {
        std::stod(data["Body3.position_x"]),
        std::stod(data["Body3.position_y"]),
        std::stod(data["Body3.position_z"])
    };

    tb.body3.velocity = {
        std::stod(data["Body3.velocity_x"]),
        std::stod(data["Body3.velocity_y"]),
        std::stod(data["Body3.velocity_z"])
    };

    return tb;
}
