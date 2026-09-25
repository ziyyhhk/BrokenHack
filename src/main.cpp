#include <Geode/Geode.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// Global state for the menu
static bool g_menuOpen = false;

// Simple feature toggles for the first category "Broken Hack"
static bool g_noclip = false;
static bool g_showHitboxes = false;
static bool g_speedhack = false;
static float g_speedValue = 1.0f;
static bool g_practiceMusic = false;
static bool g_hideAttempts = false;
static bool g_autoClicker = false;

// Toggle menu on TAB
class $modify(CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down, bool isKeyRepeat) {
        if (down && !isKeyRepeat && key == KEY_Tab) {
            g_menuOpen = !g_menuOpen;

            if (g_menuOpen) {
                log::info("BrokenHack menu opened (Category: Broken Hack)");
            } else {
                log::info("BrokenHack menu closed");
            }
            // Consume the key so it doesn't do anything else
            return true;
        }
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, isKeyRepeat);
    }
};

// Hook MenuLayer to confirm the mod loads
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        log::info("BrokenHack loaded successfully!");
        log::info("Press TAB to open the menu.");
        log::info("First category: Broken Hack");

        return true;
    }
};
