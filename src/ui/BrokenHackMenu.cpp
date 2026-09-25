#include "BrokenHackMenu.hpp"

using namespace geode::prelude;

static BrokenHackMenu* s_instance = nullptr;

namespace bh {
    bool autoUpdate = true;
    bool search = false;
    bool language = false;
    bool theme = false;
    bool rulesets = false;
    bool altHotkey = false;
    bool iconHotkey = false;
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
    auto dim = CCLayerColor::create({0, 0, 0, 130});
    dim->setContentSize(winSize);
    this->addChild(dim);

    // Panel size - fits screen, not too big
    const float panelW = 220.f;
    const float panelH = 280.f;

    // Centered container
    auto container = CCNode::create();
    container->setPosition({winSize.width / 2.f, winSize.height / 2.f});
    this->addChild(container);

    // Dark panel body
    auto panel = CCLayerColor::create({32, 32, 36, 250}, panelW, panelH);
    panel->setPosition({-panelW / 2.f, -panelH / 2.f});
    container->addChild(panel);

    // Pink header
    auto header = CCLayerColor::create({200, 45, 85, 255}, panelW, 24.f);
    header->setPosition({0, panelH - 24.f});
    panel->addChild(header);

    // Title
    auto title = CCLabelBMFont::create("Broken Hack", "bigFont.fnt");
    title->setScale(0.35f);
    title->setPosition({panelW / 2.f, panelH - 12.f});
    title->setColor({255, 255, 255});
    panel->addChild(title);

    // Close X button
    auto closeSpr = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
    closeSpr->setScale(0.45f);
    auto closeBtn = CCMenuItemSpriteExtra::create(
        closeSpr, this, menu_selector(BrokenHackMenu::onClose)
    );
    auto closeMenu = CCMenu::createWithItem(closeBtn);
    closeMenu->setPosition({panelW - 14.f, panelH - 12.f});
    panel->addChild(closeMenu);

    // Options
    struct Opt {
        const char* name;
        bool* state;
        int tag;
    };

    std::vector<Opt> opts = {
        {"Search",                  &bh::search,         1},
        {"Auto-Update",             &bh::autoUpdate,     2},
        {"Language: en-GB",         &bh::language,       3},
        {"Theme",                   &bh::theme,          4},
        {"Rulesets",                &bh::rulesets,       5},
        {"Alt Hotkey",              &bh::altHotkey,      6},
        {"Icon Hotkey",             &bh::iconHotkey,     7},
        {"Interface Scale 1.0x",    &bh::interfaceScale, 8},
        {"Animations 250ms",        &bh::animations,     9},
        {"Sort Interface",          &bh::sortInterface, 10},
        {"Miscellaneous",           &bh::miscellaneous, 11},
    };

    auto menu = CCMenu::create();
    menu->setPosition({0, 0});
    panel->addChild(menu);

    float y = panelH - 40.f;
    for (auto const& o : opts) {
        // Label
        auto lbl = CCLabelBMFont::create(o.name, "chatFont.fnt");
        lbl->setScale(0.55f);
        lbl->setAnchorPoint({0.f, 0.5f});
        lbl->setPosition({10.f, y});
        lbl->setColor({220, 220, 220});
        panel->addChild(lbl);

        // Toggle checkbox
        auto off = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
        auto on  = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
        off->setScale(0.55f);
        on->setScale(0.55f);

        auto tog = CCMenuItemToggler::create(off, on, this, menu_selector(BrokenHackMenu::onToggle));
        tog->setTag(o.tag);
        tog->toggle(*o.state);
        tog->setPosition({panelW - 18.f, y});
        menu->addChild(tog);

        y -= 20.f;
    }

    // Footer
    auto foot = CCLabelBMFont::create("TAB to close", "chatFont.fnt");
    foot->setScale(0.4f);
    foot->setColor({130, 130, 130});
    foot->setPosition({panelW / 2.f, 12.f});
    panel->addChild(foot);

    return true;
}

void BrokenHackMenu::onToggle(CCObject* sender) {
    auto tog = static_cast<CCMenuItemToggler*>(sender);
    int tag = tog->getTag();

    switch (tag) {
        case 1:  bh::search         = !bh::search;         break;
        case 2:  bh::autoUpdate     = !bh::autoUpdate;     break;
        case 3:  bh::language       = !bh::language;       break;
        case 4:  bh::theme          = !bh::theme;          break;
        case 5:  bh::rulesets       = !bh::rulesets;       break;
        case 6:  bh::altHotkey      = !bh::altHotkey;      break;
        case 7:  bh::iconHotkey     = !bh::iconHotkey;     break;
        case 8:  bh::interfaceScale = !bh::interfaceScale; break;
        case 9:  bh::animations     = !bh::animations;     break;
        case 10: bh::sortInterface  = !bh::sortInterface;  break;
        case 11: bh::miscellaneous  = !bh::miscellaneous;  break;
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
    if (s_instance) scene->addChild(s_instance, 999);
}

void BrokenHackMenu::toggle() {
    if (s_instance) s_instance->onClose(nullptr);
    else open();
}

bool BrokenHackMenu::isOpen() {
    return s_instance != nullptr;
}
