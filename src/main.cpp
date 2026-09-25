#include <Geode/Geode.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <imgui-cocos.hpp>
#include <imgui.h>

using namespace geode::prelude;

static bool g_menuOpen = false;

// Broken Hack category state
namespace bh {
    bool autoUpdate = true;
    bool search = false;
    bool language = false;
    bool theme = false;
    bool rulesets = false;
    bool altHotkey = false;
    bool iconHotkey = false;
    float interfaceScale = 1.0f;
    int animationsMs = 250;
    bool sortInterface = false;
    bool miscellaneous = false;
}

static void applyMegaHackStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Dark MegaHack-like theme
    colors[ImGuiCol_WindowBg]             = ImVec4(0.12f, 0.12f, 0.14f, 0.96f);
    colors[ImGuiCol_ChildBg]              = ImVec4(0.14f, 0.14f, 0.16f, 1.00f);
    colors[ImGuiCol_PopupBg]              = ImVec4(0.12f, 0.12f, 0.14f, 0.96f);
    colors[ImGuiCol_Border]               = ImVec4(0.25f, 0.25f, 0.28f, 0.50f);
    colors[ImGuiCol_FrameBg]              = ImVec4(0.18f, 0.18f, 0.20f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]       = ImVec4(0.25f, 0.25f, 0.28f, 1.00f);
    colors[ImGuiCol_FrameBgActive]        = ImVec4(0.30f, 0.30f, 0.33f, 1.00f);
    colors[ImGuiCol_TitleBg]              = ImVec4(0.78f, 0.18f, 0.33f, 1.00f); // pink header
    colors[ImGuiCol_TitleBgActive]        = ImVec4(0.85f, 0.22f, 0.38f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]     = ImVec4(0.78f, 0.18f, 0.33f, 0.75f);
    colors[ImGuiCol_CheckMark]            = ImVec4(0.90f, 0.30f, 0.45f, 1.00f);
    colors[ImGuiCol_SliderGrab]           = ImVec4(0.80f, 0.25f, 0.40f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]     = ImVec4(0.90f, 0.35f, 0.50f, 1.00f);
    colors[ImGuiCol_Button]               = ImVec4(0.22f, 0.22f, 0.25f, 1.00f);
    colors[ImGuiCol_ButtonHovered]        = ImVec4(0.30f, 0.30f, 0.34f, 1.00f);
    colors[ImGuiCol_ButtonActive]         = ImVec4(0.78f, 0.18f, 0.33f, 1.00f);
    colors[ImGuiCol_Header]               = ImVec4(0.78f, 0.18f, 0.33f, 0.60f);
    colors[ImGuiCol_HeaderHovered]        = ImVec4(0.85f, 0.22f, 0.38f, 0.80f);
    colors[ImGuiCol_HeaderActive]         = ImVec4(0.90f, 0.30f, 0.45f, 1.00f);
    colors[ImGuiCol_Text]                 = ImVec4(0.92f, 0.92f, 0.94f, 1.00f);
    colors[ImGuiCol_TextDisabled]         = ImVec4(0.50f, 0.50f, 0.52f, 1.00f);

    style.WindowRounding = 4.0f;
    style.FrameRounding  = 3.0f;
    style.GrabRounding   = 3.0f;
    style.WindowPadding  = ImVec2(10, 10);
    style.FramePadding   = ImVec2(6, 4);
    style.ItemSpacing    = ImVec2(8, 6);
}

static void drawMenu() {
    if (!g_menuOpen) return;

    ImGui::SetNextWindowSize(ImVec2(260, 340), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(40, 40), ImGuiCond_FirstUseEver);

    ImGui::Begin("Broken Hack", &g_menuOpen, ImGuiWindowFlags_NoCollapse);

    ImGui::Checkbox("Search", &bh::search);
    ImGui::Checkbox("Auto-Update", &bh::autoUpdate);
    ImGui::Checkbox("Language: en-GB", &bh::language);
    ImGui::Checkbox("Theme", &bh::theme);
    ImGui::Checkbox("Rulesets", &bh::rulesets);
    ImGui::Checkbox("Alt Hotkey", &bh::altHotkey);
    ImGui::Checkbox("Icon Hotkey", &bh::iconHotkey);

    ImGui::Separator();

    ImGui::Text("Interface Scale");
    ImGui::SliderFloat("##scale", &bh::interfaceScale, 0.5f, 2.0f, "%.1fx");

    ImGui::Text("Animations");
    ImGui::SliderInt("##anim", &bh::animationsMs, 0, 500, "%d ms");

    ImGui::Separator();

    ImGui::Checkbox("Sort Interface", &bh::sortInterface);
    ImGui::Checkbox("Miscellaneous", &bh::miscellaneous);

    ImGui::Spacing();
    ImGui::TextDisabled("Press TAB to close");

    ImGui::End();
}

$on_mod(Loaded) {
    ImGuiCocos::get().setup([] {
        applyMegaHackStyle();
    }).draw([] {
        drawMenu();
    });

    log::info("BrokenHack loaded (ImGui)");
    log::info("Press TAB to open Broken Hack menu");
}

class $modify(CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down, bool isKeyRepeat, double timestamp) {
        if (down && !isKeyRepeat && key == KEY_Tab) {
            g_menuOpen = !g_menuOpen;
            return true;
        }
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, isKeyRepeat, timestamp);
    }
};
