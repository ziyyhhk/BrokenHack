#include <Geode/Geode.hpp>

using namespace geode::prelude;

// Feature: Interface Scale
// Category: Broken Hack

namespace brokenhack::interface_scale {

float scale = 1.0f;

void setScale(float value) {
    scale = value;
    log::debug("Interface Scale set to {}x", scale);
}

float getScale() {
    return scale;
}

} // namespace brokenhack::interface_scale
