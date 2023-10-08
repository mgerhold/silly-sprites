#include "utils.hpp"
#include <fstream>
#include <sstream>

namespace sly {
    static constexpr auto whitespace_chars = " \f\n\r\t\v";

    [[nodiscard]] tl::optional<std::string> read_file(std::filesystem::path const& path) {
        auto file = std::ifstream{ path };
        if (not file) {
            return tl::nullopt;
        }

        return (std::ostringstream{} << file.rdbuf()).str();
    }

    [[nodiscard]] std::string ltrim(std::string s) {
        auto const pos = s.find_first_not_of(whitespace_chars);
        s.erase(0, pos);
        return s;
    }
    [[nodiscard]] std::string rtrim(std::string s) {
        auto const pos = s.find_last_not_of(whitespace_chars);
        s.erase(pos + 1);
        return s;
    }
    [[nodiscard]] std::string trim(std::string s) {
        return rtrim(ltrim(std::move(s)));
    }
} // namespace sly
