#include "utils.hpp"
#include <fstream>
#include <sstream>

namespace sly {
    [[nodiscard]] tl::optional<std::string> read_file(std::filesystem::path const& path) {
        auto file = std::ifstream{ path };
        if (not file) {
            return tl::nullopt;
        }

        return (std::ostringstream{} << file.rdbuf()).str();
    }

    [[nodiscard]] std::string ltrim(std::string s) {
        auto const it = std::find_if(s.cbegin(), s.cend(), [](char const c) {
            return not std::isspace(static_cast<unsigned char>(c));
        });
        s.erase(s.cbegin(), it);
        return s;
    }
    [[nodiscard]] std::string rtrim(std::string s) {
        auto const it = std::find_if(s.crbegin(), s.crend(), [](char const c) {
            return not std::isspace(static_cast<unsigned char>(c));
        });
        s.erase(it.base(), s.cend());
        return s;
    }
    [[nodiscard]] std::string trim(std::string s) {
        return rtrim(ltrim(std::move(s)));
    }
} // namespace sly
