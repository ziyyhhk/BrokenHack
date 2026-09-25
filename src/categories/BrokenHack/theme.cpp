#include <Geode/Geode.hpp>

using namespace geode::prelude;

// Feature: Theme
// Category: Broken Hack

namespace brokenhack::theme {

std::string current = "Dark";

void setTheme(std::string const& name) {
    current = name;
    log::debug("Theme set to {}", current);
}

std::string getTheme() {
    return current;
}

} // namespace brokenhack::theme
