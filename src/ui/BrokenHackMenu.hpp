#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class BrokenHackMenu : public CCLayer {
protected:
    bool init() override;
    void keyBackClicked() override;
    void onClose(CCObject*);

    // Builds one vertical category column
    CCNode* createColumn(std::string const& title, std::vector<std::string> const& items, float width);

public:
    static BrokenHackMenu* create();
    static void open();
    static void toggle();
    static bool isOpen();
};
