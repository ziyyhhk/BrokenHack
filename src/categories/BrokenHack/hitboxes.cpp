#include <Geode/Geode.hpp>

using namespace geode::prelude;

// Feature: Show Hitboxes
// Category: Broken Hack

namespace brokenhack::hitboxes {

bool enabled = false;

void setEnabled(bool value) {
    enabled = value;
    log::debug("Show Hitboxes {}", enabled ? "enabled" : "disabled");
}

bool isEnabled() {
    return enabled;
}

} // namespace brokenhack::hitboxes
