#include "BrokenHackMenu.hpp"

using namespace geode::prelude;

static BrokenHackMenu* s_instance = nullptr;

bool BrokenHackMenu::init() {
    if (!CCLayer::init()) return false;

    this->setKeypadEnabled(true);
    this->setTouchEnabled(true);

    auto winSize = CCDirector::get()->getWinSize();

    // Dark background overlay
    auto bg = CCLayerColor::create({0, 0, 0, 150});
    bg->setContentSize(winSize);
    this->addChild(bg);

    // Main panel (MegaHack-style dark box)
    auto panel = CCScale9Sprite::create("GJ_square02.png");
    panel->setContentSize({320.f, 280.f});
    panel->setPosition(winSize / 2);
    panel->setColor({40, 40, 45});
    this->addChild(panel);

    // Title bar
    auto titleBg = CCScale9Sprite::create("GJ_button_01.png");
    titleBg->setContentSize({320.f, 32.f});
    titleBg->setPosition({160.f, 264.f});
    titleBg->setColor({220, 50, 90}); // pink/red like MegaHack tabs
    panel->addChild(titleBg);

    auto title = CCLabelBMFont::create("Broken Hack", "bigFont.fnt");
    title->setScale(0.45f);
    title->setPosition({160.f, 264.f});
    panel->addChild(title);

    // Close button
    auto closeBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"),
        this,
        menu_selector(BrokenHackMenu::onClose)
    );
    closeBtn->setScale(0.6f);
    auto closeMenu = CCMenu::createWithItem(closeBtn);
    closeMenu->setPosition({300.f, 264.f});
    panel->addChild(closeMenu);

    // Feature list (first category content)
    float y = 220.f;
    auto addToggle = [&](const char* name, SEL_MenuHandler callback) {
        auto label = CCLabelBMFont::create(name, "bigFont.fnt");
        label->setScale(0.35f);
        label->setAnchorPoint({0.f, 0.5f});
        label->setPosition({30.f, y});
        panel->addChild(label);

        auto btn = CCMenuItemToggler::create(
            CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png"),
            CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png"),
            this,
            callback
        );
        btn->setScale(0.7f);
        auto menu = CCMenu::createWithItem(btn);
        menu->setPosition({280.f, y});
        panel->addChild(menu);

        y -= 36.f;
    };

    addToggle("Auto-Update", menu_selector(BrokenHackMenu::onAutoUpdate));
    addToggle("Search", menu_selector(BrokenHackMenu::onAutoUpdate)); // placeholder
    addToggle("Theme", menu_selector(BrokenHackMenu::onTheme));
    addToggle("Interface Scale", menu_selector(BrokenHackMenu::onInterfaceScale));
    addToggle("Animations (ms)", menu_selector(BrokenHackMenu::onAnimations));

    // Info text
    auto info = CCLabelBMFont::create("Press TAB to close", "chatFont.fnt");
    info->setScale(0.5f);
    info->setColor({150, 150, 150});
    info->setPosition({160.f, 25.f});
    panel->addChild(info);

    return true;
}

void BrokenHackMenu::keyBackClicked() {
    this->onClose(nullptr);
}

void BrokenHackMenu::onClose(CCObject*) {
    this->removeFromParent();
    s_instance = nullptr;
}

void BrokenHackMenu::onAutoUpdate(CCObject*) {
    log::info("Auto-Update toggled");
}

void BrokenHackMenu::onTheme(CCObject*) {
    log::info("Theme toggled");
}

void BrokenHackMenu::onInterfaceScale(CCObject*) {
    log::info("Interface Scale toggled");
}

void BrokenHackMenu::onAnimations(CCObject*) {
    log::info("Animations toggled");
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
