#pragma once
#include <Geode/Geode.hpp>

class GamemodeLayer : public geode::Popup<std::string const&> {
protected:
    bool setup(std::string const& value) override;
    cocos2d::CCMenu* m_selectMenu;
    cocos2d::CCMenu* m_speedMenu;
    cocos2d::CCMenu* m_togglesMenu;
    cocos2d::CCMenu* m_combineMenu;

    CCMenuItemToggler* m_cubeBtn;
    CCMenuItemToggler* m_shipBtn;
    CCMenuItemToggler* m_ballBtn;
    CCMenuItemToggler* m_birdBtn;
    CCMenuItemToggler* m_dartBtn;
    CCMenuItemToggler* m_robotBtn;
    CCMenuItemToggler* m_spiderBtn;
    CCMenuItemToggler* m_swingBtn;

    CCMenuItemToggler* m_halfBtn;
    CCMenuItemToggler* m_normalBtn;
    CCMenuItemToggler* m_doubleBtn;
    CCMenuItemToggler* m_threeBtn;
    CCMenuItemToggler* m_fourBtn;
    CCMenuItemToggler* m_flipBtn;

public:
    static GamemodeLayer* create(std::string const& text);
    static GamemodeLayer* get();
    void onMode(CCObject* sender);
    void onSpeed(CCObject* sender);
    void updateButtons(PlayerObject* player1);
    void beginButtons(PlayerObject* player1);
    void updateToggleButtons();
};