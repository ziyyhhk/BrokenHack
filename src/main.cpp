#include <Geode/Geode.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// Global menu state
static bool g_menuOpen = false;

// ============================================
// Category: Broken Hack  (first & only category for now)
// Settings style like the main MegaHack panel
// ============================================
namespace brokenhack {

bool autoUpdate = true;
bool searchEnabled = true;
std::string theme = "Dark";
float interfaceScale = 1.0f;
int animationsMs = 250;
bool sortInterface = false;

} // namespace brokenhack

// Toggle menu on TAB
class $modify(CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down, bool isKeyRepeat, double timestamp) {
        if (down && !isKeyRepeat && key == KEY_Tab) {
            g_menuOpen = !g_menuOpen;

            if (g_menuOpen) {
                log::info("BrokenHack menu opened");
                log::info("Category: Broken Hack");
                log::info("  Auto-Update: {}", brokenhack::autoUpdate);
                log::info("  Theme: {}", brokenhack::theme);
                log::info("  Interface Scale: {}x", brokenhack::interfaceScale);
                log::info("  Animations: {}ms", brokenhack::animationsMs);
            } else {
                log::info("BrokenHack menu closed");
            }
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
        log::info("Press TAB to open the menu.");
        log::info("First category: Broken Hack");

        return true;
    }
};
