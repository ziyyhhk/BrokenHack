#include <Geode/Geode.hpp>

using namespace geode::prelude;

// Feature: Auto-Update
// Category: Broken Hack

namespace brokenhack::auto_update {

bool enabled = true;

void setEnabled(bool value) {
    enabled = value;
    log::debug("Auto-Update {}", enabled ? "on" : "off");
}

bool isEnabled() {
    return enabled;
}

} // namespace brokenhack::auto_update
