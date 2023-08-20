#include "builtins.hpp"
#include <iostream>
#include <spdlog/spdlog.h>

void print(std::string const& text) {
    std::cout << text;
}

void println(std::string const& text) {
    std::cout << text << '\n';
}

void eprint(std::string const& text) {
    std::cerr << text;
}

void eprintln(std::string const& text) {
    std::cerr << text << '\n';
}

namespace logging {

    void trace(std::string const& text) {
        spdlog::trace(text);
    }

    void debug(std::string const& text) {
        spdlog::debug(text);
    }

    void info(std::string const& text) {
        spdlog::info(text);
    }

    void warning(std::string const& text) {
        spdlog::warn(text);
    }

    void error(std::string const& text) {
        spdlog::error(text);
    }

    void critical(std::string const& text) {
        spdlog::critical(text);
    }

} // namespace logging
