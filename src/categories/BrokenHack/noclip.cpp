#include <Geode/Geode.hpp>

using namespace geode::prelude;

// Feature: Noclip
// Category: Broken Hack

namespace brokenhack::noclip {

bool enabled = false;

void setEnabled(bool value) {
    enabled = value;
    log::debug("Noclip {}", enabled ? "enabled" : "disabled");
}

bool isEnabled() {
    return enabled;
}

} // namespace brokenhack::noclip
