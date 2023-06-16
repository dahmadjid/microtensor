#include <fstream>
#include "files.h"

namespace io {

std::optional<std::vector<std::string>> read_text_file(std::string_view s) {
    std::vector<std::string> result;
    std::ifstream f(s.data());   
    if (f.is_open()) {
        std::string line;
        while (std::getline(f, line)) { // Read each line
            result.emplace_back(line);
        }   
        return result;

    };
    fmt::println("Failed to read file {}", s);
    return {};
}

}