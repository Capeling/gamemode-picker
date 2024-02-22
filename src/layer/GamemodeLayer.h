#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

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

enum class GJPlayerSpeed {
    Half = 0,
    Default = 1,
    Double = 2,
    Three = 3,
    Four = 4
};

class $modify(PlayerObjectExt, PlayerObject) {

	bool m_scale = false;
    bool m_flipped = false;
    GJPlayerSpeed m_speed = GJPlayerSpeed::Default;

	void togglePlayerScale(bool scale, bool unk) {
        // log::info("{}", scale);
		PlayerObject::togglePlayerScale(scale, unk);
        m_fields->m_scale = scale;
	}

    void flipGravity(bool flip, bool unk) {
        PlayerObject::flipGravity(flip, unk);
        m_fields->m_flipped = flip;
    }

    bool init(int p0, int p1, GJBaseGameLayer* p2, cocos2d::CCLayer* p3, bool p4) {
        if(!PlayerObject::init(p0, p1, p2, p3, p4))
            return false;
        // log::info("playerspeed: {}", m_playerSpeed);
        updateSpeedVar();
        return true;
    }

    void updateSpeedVar() {
        if(m_playerSpeed == 0.7f) m_fields->m_speed = GJPlayerSpeed::Half;
        if(m_playerSpeed == 0.9f) m_fields->m_speed = GJPlayerSpeed::Default;
        if(m_playerSpeed == 1.1f) m_fields->m_speed = GJPlayerSpeed::Double;
        if(m_playerSpeed == 1.3f) m_fields->m_speed = GJPlayerSpeed::Three;
        if(m_playerSpeed == 1.6f) m_fields->m_speed = GJPlayerSpeed::Four;
    }

    void changePlayerSpeed(GJPlayerSpeed speed) {
        m_fields->m_speed = speed;
        m_playerSpeed = speedToFloat(speed);
    }

    GJPlayerSpeed getPlayerSpeed() {
        return m_fields->m_speed;
    }

    bool isSpeed(GJPlayerSpeed speed) {
        return m_fields->m_speed == speed;
    }

    float speedToFloat(GJPlayerSpeed speed) {
        switch(speed) {
            case GJPlayerSpeed::Half: return 0.7f; break;
            case GJPlayerSpeed::Default: return 0.9f; break;
            case GJPlayerSpeed::Double: return  1.1f; break;
            case GJPlayerSpeed::Three: return 1.3f; break;
            case GJPlayerSpeed::Four: return 1.6f; break;
            default: return 0.9f;
        }
    }
};