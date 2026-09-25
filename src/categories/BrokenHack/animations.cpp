#include <Geode/Geode.hpp>

using namespace geode::prelude;

// Feature: Animations (ms)
// Category: Broken Hack

namespace brokenhack::animations {

int durationMs = 250;

void setDuration(int ms) {
    durationMs = ms;
    log::debug("Animations set to {}ms", durationMs);
}

int getDuration() {
    return durationMs;
}

} // namespace brokenhack::animations
