#include "BrokenHackMenu.hpp"

using namespace geode::prelude;

static BrokenHackMenu* s_instance = nullptr;

// Create one vertical column (like Global / Level / Bypass in MegaHack)
CCNode* BrokenHackMenu::createColumn(std::string const& title, std::vector<std::string> const& items, float width) {
    auto col = CCNode::create();
    col->setContentSize({width, 320.f});

    // Column background
    auto bg = CCScale9Sprite::create("GJ_square02.png");
    bg->setContentSize({width, 320.f});
    bg->setPosition({width / 2, 160.f});
    bg->setColor({25, 25, 28});
    bg->setOpacity(240);
    col->addChild(bg);

    // Category title (pink accent like MegaHack)
    auto titleBg = CCLayerColor::create({180, 40, 70, 255}, width, 22.f);
    titleBg->setPosition({0, 298.f});
    col->addChild(titleBg);

    auto titleLbl = CCLabelBMFont::create(title.c_str(), "bigFont.fnt");
    titleLbl->setScale(0.32f);
    titleLbl->setPosition({width / 2, 309.f});
    col->addChild(titleLbl);

    // Feature rows
    float y = 280.f;
    for (auto const& name : items) {
        auto row = CCNode::create();

        auto label = CCLabelBMFont::create(name.c_str(), "chatFont.fnt");
        label->setScale(0.55f);
        label->setAnchorPoint({0.f, 0.5f});
        label->setPosition({8.f, 0.f});
        label->setColor({220, 220, 220});
        row->addChild(label);

        // Checkbox placeholder (off state)
        auto box = CCScale9Sprite::create("GJ_button_05.png");
        box->setContentSize({14.f, 14.f});
        box->setPosition({width - 16.f, 0.f});
        box->setColor({60, 60, 65});
        row->addChild(box);

        row->setPosition({0, y});
        col->addChild(row);
        y -= 18.f;
    }

    return col;
}

bool BrokenHackMenu::init() {
    if (!CCLayer::init()) return false;

    this->setKeypadEnabled(true);
    this->setTouchEnabled(true);

    auto winSize = CCDirector::get()->getWinSize();

    // Semi-transparent fullscreen dim
    auto dim = CCLayerColor::create({0, 0, 0, 120});
    dim->setContentSize(winSize);
    this->addChild(dim);

    // Container for all columns (horizontal row)
    auto container = CCNode::create();
    this->addChild(container);

    // Column definitions matching MegaHack layout
    struct Cat {
        std::string name;
        std::vector<std::string> items;
        float width;
    };

    std::vector<Cat> categories = {
        {"Global", {
            "FPS Bypass", "TPS Bypass", "Physics Bypass",
            "Pitch Shift", "Audio Speed", "Sync with Speedhack",
            "Vertical Sync", "Auto Safe Mode", "Click Between Steps",
            "Click On Steps", "Compact Object Levels", "Compact Profile Comments",
            "Discord RPC", "Lock Cursor", "No Short Numbers",
            "Safe Mode", "Show Tips", "Transition Speed",
            "Transparent Lists", "Click Between Frames"
        }, 145.f},

        {"Level", {
            "0% Practice Completion", "Accurate Percentage",
            "All Modes in Platformer", "All Passable",
            "Always Show Coins", "Auto LDM", "Auto Pickup Coins",
            "Auto Practice Mode", "Auto Song Download",
            "Checkpoint Delay", "Confirm Full Restart",
            "Confirm Practice Mode", "Confirm Restart",
            "Force Platformer", "Freeze Attempts",
            "Hide Level Complete VFX", "Hide Pause Menu",
            "Hitbox Multiplier", "Instant Mirror", "Layout Mode",
            "Legacy Pulse", "Legacy Reverse Physics", "Legacy Trail",
            "Match Percent/Time Fonts", "Mute Level SFX",
            "No End Shake", "No Mirror", "No Music Fade Out",
            "No Object Glow", "No Particles", "No Portal Lightning",
            "No Shaders", "Pause Countdown", "Pause During Complete",
            "Practice Coins", "Practice Fix", "Random Seed",
            "Show Hitboxes", "Hitboxes On Death", "Show Triggers"
        }, 155.f},

        {"Bypass", {
            "Allow Low Volume", "Character Filter Bypass",
            "Character Limit Bypass", "Checkpoint Limit",
            "Quick Chests", "Instant Complete",
            "Level Kick", "Menu Gameplay",
            "Music Customizer", "Pause Buffering",
            "Practice Music Sync", "Show Spam Comments",
            "Unlock Main Levels", "Unlock Icons",
            "Unlock Paths", "Unlock Shops", "Unlock Vaults"
        }, 145.f},

        {"Player", {
            "Always Show Trail", "AutoClicker", "Auto Kill",
            "Ball Rotation Bug", "Click Teleport", "Custom Wave Trail",
            "Force Ghost Trail", "Force Wave Trail",
            "Frame Stepper", "Hide Player", "Jump Hack",
            "Mute Level Audio on Death", "Mute Rewards SFX on Death",
            "No Death Effect", "No Ghost Trail", "No Hide Trigger",
            "No Platformer Jump Anim", "No Respawn Flash",
            "No Robot Dash", "No Spider Dash", "No Trail",
            "No Vehicle Particles", "No Wave Trail Behind",
            "Noclip", "Shipcopter", "Show Trajectory",
            "Solid Wave Trail", "Wave Trail On Death", "Respawn Delay"
        }, 155.f},

        {"Bot", {
            "Disabled", "Record", "Playback",
            "Mesmerizer", "Practice Fix Mode",
            "Ignore Inputs", "New", "Save", "Load", "Delete",
            "Open Replays Folder"
        }, 130.f},

        {"Creator", {
            "Custom Object Bypass", "Default Song Bypass",
            "Free Scroll", "Hide Triggers", "Hide UI",
            "Level Copy Bypass", "Level Edit", "No (C) Mark",
            "Reset Percent on Save", "Slider Limit",
            "Smooth Editor Trail", "Verify Bypass"
        }, 145.f},

        {"Labels", {
            "Show Labels", "Show in Editor",
            "Cheat Indicator", "Import Label",
            "Add New Label", "Level Time", "Presets",
            "FPS", "Run From", "Attempt", "Percentage",
            "Level Time", "Best Run", "Clock", "CPS",
            "Noclip Accuracy", "Noclip Deaths",
            "Testmode", "New Label"
        }, 130.f},

        {"Interface", {
            "Gruvbox Theme", "UI Scale", "DPI Scaling",
            "Font", "Font Size", "Reload Fonts",
            "Tabbed", "Layout Type", "Style",
            "Enable Blur", "Animate Windows",
            "Center Horizontally", "Accent Color",
            "Background Color", "Language", "Search",
            "Search Auto Focus"
        }, 135.f},

        {"Shortcuts", {
            "P1 Jump", "P2 Jump", "Open Clipsy",
            "Show Options", "Uncomplete Level",
            "Restart Level", "Toggle Practice Mode",
            "Place Checkpoint", "Remove Checkpoint",
            "Inject DLL", "Save Folder",
            "Reset BG Volume", "Reset SFX Volume",
            "Account Secret Coins", "Show Level Password",
            "Open Graphics Settings",
            "Internal Recorder", "Start Recording",
            "Stop Recording", "Framerate", "Endscreen Duration",
            "Bitrate", "Resolution X", "Resolution Y",
            "Hide Preview", "Codec", "Colorspace Arg",
            "Presets", "CPU", "NVIDIA", "AMD"
        }, 145.f},
    };

    float totalWidth = 0.f;
    for (auto const& c : categories) totalWidth += c.width + 4.f;

    float x = 0.f;
    for (auto const& c : categories) {
        auto col = createColumn(c.name, c.items, c.width);
        col->setPosition({x, 0.f});
        container->addChild(col);
        x += c.width + 4.f;
    }

    // Center the whole menu on screen
    container->setPosition({
        (winSize.width - totalWidth) / 2.f,
        (winSize.height - 320.f) / 2.f
    });

    // Top bar with mod name + close
    auto topBar = CCScale9Sprite::create("GJ_square02.png");
    topBar->setContentSize({totalWidth, 28.f});
    topBar->setPosition({winSize.width / 2, winSize.height / 2 + 175.f});
    topBar->setColor({30, 30, 35});
    this->addChild(topBar);

    auto modTitle = CCLabelBMFont::create("BrokenHack", "bigFont.fnt");
    modTitle->setScale(0.4f);
    modTitle->setPosition({winSize.width / 2 - 40.f, winSize.height / 2 + 175.f});
    this->addChild(modTitle);

    auto closeBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"),
        this,
        menu_selector(BrokenHackMenu::onClose)
    );
    closeBtn->setScale(0.55f);
    auto closeMenu = CCMenu::createWithItem(closeBtn);
    closeMenu->setPosition({winSize.width / 2 + totalWidth / 2 - 18.f, winSize.height / 2 + 175.f});
    this->addChild(closeMenu);

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
