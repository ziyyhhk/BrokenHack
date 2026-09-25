#include "BrokenHackMenu.hpp"

using namespace geode::prelude;

static BrokenHackMenu* s_instance = nullptr;

// Simple state for the first category options
namespace bh {
    bool autoUpdate = true;
    bool search = true;
    bool theme = false;
    bool interfaceScale = false;
    bool animations = true;
    bool sortInterface = false;
    bool miscellaneous = false;
}

bool BrokenHackMenu::init() {
    if (!CCLayer::init()) return false;

    this->setKeypadEnabled(true);
    this->setTouchEnabled(true);

    auto winSize = CCDirector::get()->getWinSize();

    // Dim background
    auto dim = CCLayerColor::create({0, 0, 0, 140});
    dim->setContentSize(winSize);
    this->addChild(dim);

    // Main panel size
    const float panelW = 280.f;
    const float panelH = 260.f;

    // Solid dark panel
    auto panel = CCScale9Sprite::create("GJ_square02.png");
    panel->setContentSize({panelW, panelH});
    panel->setPosition(winSize / 2);
    panel->setColor({28, 28, 32});
    panel->setOpacity(255);
    this->addChild(panel);

    // Pink title bar
    auto titleBar = CCLayerColor::create({200, 45, 80, 255}, panelW, 28.f);
    titleBar->setPosition({0, panelH - 28.f});
    panel->addChild(titleBar);

    auto title = CCLabelBMFont::create("Broken Hack", "bigFont.fnt");
    title->setScale(0.4f);
    title->setPosition({panelW / 2, panelH - 14.f});
    panel->addChild(title);

    // Close button
    auto closeSpr = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
    closeSpr->setScale(0.5f);
    auto closeBtn = CCMenuItemSpriteExtra::create(
        closeSpr, this, menu_selector(BrokenHackMenu::onClose)
    );
    auto closeMenu = CCMenu::createWithItem(closeBtn);
    closeMenu->setPosition({panelW - 16.f, panelH - 14.f});
    panel->addChild(closeMenu);

    // Options list
    struct Option {
        const char* name;
        bool* state;
        int tag;
    };

    std::vector<Option> options = {
        {"Auto-Update",       &bh::autoUpdate,     1},
        {"Search",            &bh::search,         2},
        {"Theme",             &bh::theme,          3},
        {"Interface Scale",   &bh::interfaceScale, 4},
        {"Animations (ms)",   &bh::animations,     5},
        {"Sort Interface",    &bh::sortInterface,  6},
        {"Miscellaneous",     &bh::miscellaneous,  7},
    };

    float y = panelH - 50.f;
    auto toggleMenu = CCMenu::create();
    toggleMenu->setPosition({0, 0});
    panel->addChild(toggleMenu);

    for (auto const& opt : options) {
        // Label
        auto label = CCLabelBMFont::create(opt.name, "bigFont.fnt");
        label->setScale(0.32f);
        label->setAnchorPoint({0.f, 0.5f});
        label->setPosition({18.f, y});
        label->setColor({230, 230, 230});
        panel->addChild(label);

        // Toggle
        auto off = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
        auto on  = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
        off->setScale(0.65f);
        on->setScale(0.65f);

        auto toggler = CCMenuItemToggler::create(
            off, on, this, menu_selector(BrokenHackMenu::onToggle)
        );
        toggler->setTag(opt.tag);
        toggler->toggle(*opt.state);
        toggler->setPosition({panelW - 28.f, y});
        toggleMenu->addChild(toggler);

        y -= 28.f;
    }

    // Footer
    auto footer = CCLabelBMFont::create("Press TAB to close", "chatFont.fnt");
    footer->setScale(0.45f);
    footer->setColor({140, 140, 140});
    footer->setPosition({panelW / 2, 16.f});
    panel->addChild(footer);

    return true;
}

void BrokenHackMenu::onToggle(CCObject* sender) {
    auto toggler = static_cast<CCMenuItemToggler*>(sender);
    int tag = toggler->getTag();
    bool on = !toggler->isToggled(); // state after click is inverted by the toggler itself after callback in some cases

    // CCMenuItemToggler toggles AFTER the callback, so use !isToggled for new state
    // Safer: just flip based on current visual
    switch (tag) {
        case 1: bh::autoUpdate     = !bh::autoUpdate;     log::info("Auto-Update: {}", bh::autoUpdate); break;
        case 2: bh::search         = !bh::search;         log::info("Search: {}", bh::search); break;
        case 3: bh::theme          = !bh::theme;          log::info("Theme: {}", bh::theme); break;
        case 4: bh::interfaceScale = !bh::interfaceScale; log::info("Interface Scale: {}", bh::interfaceScale); break;
        case 5: bh::animations     = !bh::animations;     log::info("Animations: {}", bh::animations); break;
        case 6: bh::sortInterface  = !bh::sortInterface;  log::info("Sort Interface: {}", bh::sortInterface); break;
        case 7: bh::miscellaneous  = !bh::miscellaneous;  log::info("Miscellaneous: {}", bh::miscellaneous); break;
    }
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
