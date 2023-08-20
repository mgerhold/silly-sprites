#pragma once

#include <iostream>
#include <string>

void print(std::string const& text);
void println(std::string const& text);
void eprint(std::string const& text);
void eprintln(std::string const& text);

namespace logging {
    void trace(std::string const& text);
    void debug(std::string const& text);
    void info(std::string const& text);
    void warning(std::string const& text);
    void error(std::string const& text);
    void critical(std::string const& text);
} // namespace logging
