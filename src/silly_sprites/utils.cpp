#include "utils.hpp"
#include <fstream>
#include <sstream>

[[nodiscard]] tl::optional<std::string> sly::read_file(std::filesystem::path const& path) {
    auto file = std::ifstream{ path };
    if (not file) {
        return tl::nullopt;
    }

    return (std::ostringstream{} << file.rdbuf()).str();
}
