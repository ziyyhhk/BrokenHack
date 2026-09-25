#include <Geode/Geode.hpp>

using namespace geode::prelude;

// Feature: Speedhack
// Category: Broken Hack

namespace brokenhack::speedhack {

bool enabled = false;
float value = 1.0f;

void setEnabled(bool v) {
    enabled = v;
    log::debug("Speedhack {}", enabled ? "enabled" : "disabled");
}

void setValue(float v) {
    value = v;
    log::debug("Speedhack value set to {}", value);
}

bool isEnabled() {
    return enabled;
}

float getValue() {
    return value;
}

} // namespace brokenhack::speedhack
