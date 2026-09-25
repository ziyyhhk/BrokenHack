#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class BrokenHackMenu : public CCLayer {
protected:
    bool init() override;
    void keyBackClicked() override;
    void onClose(CCObject*);

    // Feature toggles UI callbacks
    void onAutoUpdate(CCObject*);
    void onTheme(CCObject*);
    void onInterfaceScale(CCObject*);
    void onAnimations(CCObject*);

public:
    static BrokenHackMenu* create();
    static void open();
    static void toggle();
    static bool isOpen();
};
