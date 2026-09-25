#include "BrokenHackMenu.hpp"

using namespace geode::prelude;

static BrokenHackMenu* s_instance = nullptr;

// Colors matching MegaHack dark theme
static ccColor3B const kHeaderPink = {200, 45, 85};
static ccColor3B const kPanelDark  = {35, 35, 38};
static ccColor3B const kRowDark    = {42, 42, 46};
static ccColor3B const kTextLight  = {220, 220, 220};

CCNode* BrokenHackMenu::makeWindow(
    std::string const& title,
    std::vector<std::string> const& rows,
    float width,
    float height
) {
    auto win = CCNode::create();
    win->setContentSize({width, height});

    // Panel background (solid dark)
    auto bg = CCLayerColor::create(
        {kPanelDark.r, kPanelDark.g, kPanelDark.b, 245},
        width, height
    );
    win->addChild(bg);

    // Thin border line at top of content
    auto border = CCLayerColor::create({20, 20, 22, 255}, width, 1.f);
    border->setPosition({0, height - 22.f});
    win->addChild(border);

    // Pink header bar
    auto header = CCLayerColor::create(
        {kHeaderPink.r, kHeaderPink.g, kHeaderPink.b, 255},
        width, 20.f
    );
    header->setPosition({0, height - 20.f});
    win->addChild(header);

    // Category title (centered in header)
    auto titleLbl = CCLabelBMFont::create(title.c_str(), "bigFont.fnt");
    titleLbl->setScale(0.28f);
    titleLbl->setPosition({width / 2.f, height - 10.f});
    titleLbl->setColor({255, 255, 255});
    win->addChild(titleLbl);

    // Rows
    float y = height - 34.f;
    const float rowH = 16.f;

    for (size_t i = 0; i < rows.size(); ++i) {
        // Alternating subtle row background for readability
        if (i % 2 == 0) {
            auto rowBg = CCLayerColor::create(
                {kRowDark.r, kRowDark.g, kRowDark.b, 180},
                width - 4.f, rowH
            );
            rowBg->setPosition({2.f, y - rowH / 2.f});
            win->addChild(rowBg);
        }

        auto label = CCLabelBMFont::create(rows[i].c_str(), "chatFont.fnt");
        label->setScale(0.5f);
        label->setAnchorPoint({0.f, 0.5f});
        label->setPosition({6.f, y});
        label->setColor(kTextLight);
        win->addChild(label);

        // Small checkbox square on the right
        auto box = CCLayerColor::create({55, 55, 60, 255}, 10.f, 10.f);
        box->setPosition({width - 16.f, y - 5.f});
        win->addChild(box);

        y -= rowH + 1.f;
    }

    return win;
}

bool BrokenHackMenu::init() {
    if (!CCLayer::init()) return false;

    this->setKeypadEnabled(true);
    this->setTouchEnabled(true);

    auto winSize = CCDirector::get()->getWinSize();

    // Dim overlay
    auto dim = CCLayerColor::create({0, 0, 0, 100});
    dim->setContentSize(winSize);
    this->addChild(dim);

    // ---- Category windows (MegaHack layout style) ----
    // First window = Broken Hack (your main category with the options you wanted)
    struct WindowDef {
        std::string title;
        std::vector<std::string> rows;
        float w;
        float h;
    };

    std::vector<WindowDef> windows = {
        // Column 1 - Broken Hack (main settings like MegaHack left panel)
        {
            "Broken Hack",
            {
                "Search",
                "Auto-Update",
                "Language: en-GB",
                "Contribute Translations",
                "Theme",
                "Rulesets",
                "Alt Hotkey",
                "Icon Hotkey",
                "Interface Scale 1.0x",
                "Animations 250ms",
                "Sort Interface",
                "Miscellaneous",
            },
            150.f, 230.f
        },
        // Column 2 - Screenshot style sub panel
        {
            "Screenshot",
            {
                "Screenshot",
                "Mode: Save & copy",
            },
            130.f, 70.f
        },
        // Column 3 - Speedhack
        {
            "Speedhack",
            {
                "Speed 1.0x",
                "Enabled",
                "Speedhack Audio",
                "Classic Mode",
            },
            130.f, 100.f
        },
        // Column 4 - Bypass
        {
            "Bypass",
            {
                "Anti-Kick",
                "Challenge Level",
                "Keymaster",
                "Main Levels",
                "Music Customiser",
                "Slider Limit",
                "Text Length",
                "Treasure Room",
                "Unlock Icons",
                "Unlock Shops",
                "Unlock Vaults",
            },
            140.f, 210.f
        },
        // Column 5 - Creator
        {
            "Creator",
            {
                "Accurate Save",
                "Copy Hack",
                "Custom Object Bypass",
                "Default Song Bypass",
                "Editor Extension",
                "Free Scroll",
                "Hide UI",
                "Level Edit",
                "Multiple Editor Trails",
                "No C Mark",
                "Place Over",
                "Smooth Editor Trail",
                "Toolbox Button Bypass",
                "Trigger Value Bypass",
                "Verify Hack",
            },
            150.f, 270.f
        },
    };

    // Layout: place windows in a horizontal row, centered
    float totalW = 0.f;
    float maxH = 0.f;
    for (auto const& w : windows) {
        totalW += w.w + 6.f;
        if (w.h > maxH) maxH = w.h;
    }

    float startX = (winSize.width - totalW) / 2.f;
    float baseY  = (winSize.height - maxH) / 2.f;
    float x = startX;

    for (auto const& def : windows) {
        auto node = makeWindow(def.title, def.rows, def.w, def.h);
        // Align tops
        node->setPosition({x, baseY + (maxH - def.h)});
        this->addChild(node);
        x += def.w + 6.f;
    }

    // Small close hint at bottom
    auto hint = CCLabelBMFont::create("TAB = close", "chatFont.fnt");
    hint->setScale(0.4f);
    hint->setColor({120, 120, 120});
    hint->setPosition({winSize.width / 2, 20.f});
    this->addChild(hint);

    return true;
}

void BrokenHackMenu::keyBackClicked() {
    this->onClose(nullptr);
}

void BrokenHackMenu::onClose(CCObject*) {
    this->removeFromParent();
    s_instance = nullptr;
}

BrokenHackMenu* BrokenHackMenu::create() {
    auto ret = new BrokenHackMenu();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void BrokenHackMenu::open() {
    if (s_instance) return;
    auto scene = CCDirector::get()->getRunningScene();
    if (!scene) return;

    s_instance = BrokenHackMenu::create();
    if (s_instance) {
        scene->addChild(s_instance, 999);
    }
}

void BrokenHackMenu::toggle() {
    if (s_instance) {
        s_instance->onClose(nullptr);
    } else {
        open();
    }
}

bool BrokenHackMenu::isOpen() {
    return s_instance != nullptr;
}
