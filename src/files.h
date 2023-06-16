#pragma once
#include <vector>
#include <string_view>
#include <fmt/format.h>
#include <optional> 

namespace io {
    std::optional<std::vector<std::string>> read_text_file(std::string_view);
}