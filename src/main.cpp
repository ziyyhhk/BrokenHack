#include <Geode/Geode.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// Global state for the menu
static bool g_menuOpen = false;
static int g_currentCategory = 0; // 0 = Broken Hack

// Simple feature toggles for the first category "Broken Hack"
static bool g_noclip = false;
static bool g_showHitboxes = false;
static bool g_speedhack = false;
static float g_speedValue = 1.0f;
static bool g_practiceMusic = false;
static bool g_hideAttempts = false;
static bool g_autoClicker = false;

// Draw a very basic menu (placeholder for full MegaHack-style UI)
void drawBrokenHackMenu() {
    // This is a temporary text-based indicator.
    // Full ImGui / custom multi-column UI will be added next.
    if (!g_menuOpen) return;

    // For now we just log and use a simple popup-style approach later.
    // Real UI will use ImGui or Geode nodes to match the screenshot layout.
}

// Toggle menu on TAB
class $modify(CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down, bool isKeyRepeat) {
        if (down && !isKeyRepeat && key == KEY_Tab) {
            g_menuOpen = !g_menuOpen;

            if (g_menuOpen) {
                log::info("BrokenHack menu opened (Category: Broken Hack)");
                // Temporary feedback so user knows it works
                Notification::create("BrokenHack opened (TAB)", NotificationIcon::Success)->show();
            } else {
                log::info("BrokenHack menu closed");
                Notification::create("BrokenHack closed", NotificationIcon::Info)->show();
            }
            return true; // consume the key
        }
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, isKeyRepeat);
    }
};

// Hook MenuLayer just to confirm the mod loads
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        log::info("BrokenHack loaded successfully!");
        log::info("Press TAB to open the menu.");
        log::info("First category: Broken Hack");

        return true;
    }
};

// Placeholder for future feature hooks
// Example: Noclip, Speedhack, Hitboxes etc. will go in separate files later
