#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class BrokenHackMenu : public CCLayer {
protected:
    bool init() override;
    void keyBackClicked() override;
    void onClose(CCObject*);

    // One floating category window
    CCNode* makeWindow(
        std::string const& title,
        std::vector<std::string> const& rows,
        float width,
        float height
    );

public:
    static BrokenHackMenu* create();
    static void open();
    static void toggle();
    static bool isOpen();
};
