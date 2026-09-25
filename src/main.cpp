#include <Geode/Geode.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "ui/BrokenHackMenu.hpp"

using namespace geode::prelude;

// Toggle menu on TAB
class $modify(CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down, bool isKeyRepeat, double timestamp) {
        if (down && !isKeyRepeat && key == KEY_Tab) {
            BrokenHackMenu::toggle();
            return true; // consume key
        }
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, isKeyRepeat, timestamp);
    }
};

// Confirm mod loads
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        log::info("BrokenHack loaded!");
        log::info("Press TAB to open the Broken Hack menu.");

        return true;
    }
};
