#include "GamemodeLayer.h"
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

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
        log::info("{}", scale);
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
        log::info("playerspeed: {}", m_playerSpeed);
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

bool isCube(PlayerObject* player) {
    return !player->m_isShip && !player->m_isBall && !player->m_isBird && !player->m_isDart && !player->m_isRobot && !player->m_isSpider && !player->m_isSwing;
}

bool GamemodeLayer::setup(std::string const& value) {
    auto playLayer = GameManager::sharedState()->m_playLayer;
    auto player1 = static_cast<PlayerObjectExt*>(playLayer->m_player1);
    setTouchPriority(2);
    handleTouchPriority(this);
    player1->updateSpeedVar();  

    m_title = CCLabelBMFont::create(value.c_str(), "bigFont.fnt");
    m_bgSprite->addChildAtPosition(m_title, Anchor::Top, ccp(0, -22));
    m_selectMenu = CCMenu::create();
    m_combineMenu = CCMenu::create();
    m_speedMenu = CCMenu::create();
    m_togglesMenu = CCMenu::create();
    m_mainLayer->addChildAtPosition(m_combineMenu, Anchor::Center, ccp(0, -10), false);

    auto onMode = menu_selector(GamemodeLayer::onMode);
    m_cubeBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("gj_iconBtn_off_001.png"), CCSprite::createWithSpriteFrameName("gj_iconBtn_on_001.png"), this, onMode);
    m_cubeBtn->setTag(0);
    m_shipBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("gj_shipBtn_off_001.png"), CCSprite::createWithSpriteFrameName("gj_shipBtn_on_001.png"), this, onMode);
    m_shipBtn->setTag(1);
    m_ballBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("gj_ballBtn_off_001.png"), CCSprite::createWithSpriteFrameName("gj_ballBtn_on_001.png"), this, onMode);
    m_ballBtn->setTag(2);
    m_birdBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("gj_birdBtn_off_001.png"), CCSprite::createWithSpriteFrameName("gj_birdBtn_on_001.png"), this, onMode);
    m_birdBtn->setTag(3);
    m_dartBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("gj_dartBtn_off_001.png"), CCSprite::createWithSpriteFrameName("gj_dartBtn_on_001.png"), this, onMode);
    m_dartBtn->setTag(4);
    m_robotBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("gj_robotBtn_off_001.png"), CCSprite::createWithSpriteFrameName("gj_robotBtn_on_001.png"), this, onMode);
    m_robotBtn->setTag(5);
    m_spiderBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("gj_spiderBtn_off_001.png"), CCSprite::createWithSpriteFrameName("gj_spiderBtn_on_001.png"), this, onMode);
    m_spiderBtn->setTag(6);
    m_swingBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("gj_swingBtn_off_001.png"), CCSprite::createWithSpriteFrameName("gj_swingBtn_on_001.png"), this, onMode);
    m_swingBtn->setTag(7);

    m_selectMenu->addChild(m_cubeBtn);
    m_selectMenu->addChild(m_shipBtn);
    m_selectMenu->addChild(m_ballBtn);
    m_selectMenu->addChild(m_birdBtn);
    m_selectMenu->addChild(m_dartBtn);
    m_selectMenu->addChild(m_robotBtn);
    m_selectMenu->addChild(m_spiderBtn);
    m_selectMenu->addChild(m_swingBtn);
    m_selectMenu->setLayout(AxisLayout::create(Axis::Row)->setGap(5));

    auto onSpeed = menu_selector(GamemodeLayer::onSpeed);
    m_halfBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("halfOff.png"_spr), CCSprite::createWithSpriteFrameName("halfOn.png"_spr), this, onSpeed);
    m_halfBtn->setTag(0);
    m_normalBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("normalOff.png"_spr), CCSprite::createWithSpriteFrameName("normalOn.png"_spr), this, onSpeed);
    m_normalBtn->setTag(1);
    m_doubleBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("doubleOff.png"_spr), CCSprite::createWithSpriteFrameName("doubleOn.png"_spr), this, onSpeed);
    m_doubleBtn->setTag(2);
    m_threeBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("threeOff.png"_spr), CCSprite::createWithSpriteFrameName("threeOn.png"_spr), this, onSpeed);
    m_threeBtn->setTag(3);
    m_fourBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("fourOff.png"_spr), CCSprite::createWithSpriteFrameName("fourOn.png"_spr), this, onSpeed);
    m_fourBtn->setTag(4);

    m_speedMenu->addChild(m_halfBtn);
    m_speedMenu->addChild(m_normalBtn);
    m_speedMenu->addChild(m_doubleBtn);
    m_speedMenu->addChild(m_threeBtn);
    m_speedMenu->addChild(m_fourBtn);
    m_speedMenu->setLayout(AxisLayout::create(Axis::Row)->setGap(5));

    CCMenuItemToggler* platBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("platOff.png"_spr), CCSprite::createWithSpriteFrameName("platOn.png"_spr), this, onMode);
    platBtn->setTag(8);
    platBtn->toggle(player1->m_isPlatformer);
    CCMenuItemToggler* sizeBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("sizeOff.png"_spr), CCSprite::createWithSpriteFrameName("sizeOn.png"_spr), this, onMode);
    sizeBtn->setTag(9);
    sizeBtn->toggle(static_cast<PlayerObjectExt*>(player1)->m_fields->m_scale);
    m_flipBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("gravOff.png"_spr), CCSprite::createWithSpriteFrameName("gravOn.png"_spr), this, onSpeed);
    m_flipBtn->setTag(5);

    m_togglesMenu->addChild(platBtn);
    m_togglesMenu->addChild(sizeBtn);
    m_togglesMenu->addChild(m_flipBtn);
    m_togglesMenu->setLayout(AxisLayout::create(Axis::Row)->setGap(6));

    beginButtons(player1);
    m_combineMenu->addChild(m_togglesMenu);
    m_combineMenu->addChild(m_speedMenu);
    m_combineMenu->addChild(m_selectMenu);
    m_combineMenu->setLayout(AxisLayout::create(Axis::Column)->setGap(1));
    m_speedMenu->setScale(0.80);
    m_selectMenu->setScale(0.75);
    m_togglesMenu->setScale(0.85);

    return true;
}

void GamemodeLayer::updateToggleButtons() {
    m_cubeBtn->setEnabled(!m_cubeBtn->m_toggled);
    m_shipBtn->setEnabled(!m_shipBtn->m_toggled);
    m_ballBtn->setEnabled(!m_ballBtn->m_toggled);
    m_birdBtn->setEnabled(!m_birdBtn->m_toggled);
    m_dartBtn->setEnabled(!m_dartBtn->m_toggled);
    m_robotBtn->setEnabled(!m_robotBtn->m_toggled);
    m_spiderBtn->setEnabled(!m_spiderBtn->m_toggled);
    m_swingBtn->setEnabled(!m_swingBtn->m_toggled);

    m_halfBtn->setEnabled(!m_halfBtn->m_toggled);
    m_normalBtn->setEnabled(!m_normalBtn->m_toggled);
    m_doubleBtn->setEnabled(!m_doubleBtn->m_toggled);
    m_threeBtn->setEnabled(!m_threeBtn->m_toggled);
    m_fourBtn->setEnabled(!m_fourBtn->m_toggled);
}

void GamemodeLayer::onSpeed(CCObject* sender) {
    int tag = sender->getTag();
    auto playLayer = GameManager::sharedState()->m_playLayer;
    auto player1 = static_cast<PlayerObjectExt*>(playLayer->m_player1);
    switch(tag) {
        case 0: player1->changePlayerSpeed(GJPlayerSpeed::Half); break;
        case 1: player1->changePlayerSpeed(GJPlayerSpeed::Default); break;
        case 2: player1->changePlayerSpeed(GJPlayerSpeed::Double); break;
        case 3: player1->changePlayerSpeed(GJPlayerSpeed::Three); break;
        case 4: player1->changePlayerSpeed(GJPlayerSpeed::Four); break;
        case 5: player1->flipGravity(!player1->m_fields->m_flipped, true); break;
    }
    updateButtons(player1);
    updateToggleButtons();
}

void GamemodeLayer::onMode(CCObject* sender) {
    int tag = sender->getTag();
    auto playLayer = GameManager::sharedState()->m_playLayer;
    auto player1 = static_cast<PlayerObjectExt*>(playLayer->m_player1);
    switch(tag) {
        case 0:
        player1->toggleFlyMode(false, false);
        player1->toggleRollMode(false, false);
        player1->toggleBirdMode(false, false);
        player1->toggleDartMode(false, false);
        player1->toggleRobotMode(false, false);
        player1->toggleSpiderMode(false, false);
        player1->toggleSwingMode(false, false);
        break;
        case 1: player1->toggleFlyMode(true, true); break; 
        case 2: player1->toggleRollMode(true, true); break;
        case 3: player1->toggleBirdMode(true, true); break;
        case 4: player1->toggleDartMode(true, true); break;
        case 5: player1->toggleRobotMode(true, true); break;
        case 6: player1->toggleSpiderMode(true, true); break;
        case 7: player1->toggleSwingMode(true, true); break;
        case 8: player1->m_isPlatformer = !player1->m_isPlatformer; break;
        case 9: player1->togglePlayerScale(!static_cast<CCMenuItemToggler*>(sender)->m_toggled, true); break;
    }
    log::info("player speed: {}", player1->m_playerSpeed);
    auto obj = TeleportPortalObject::create("edit_eGameRotBtn_001.png", true);
    obj->m_cameraIsFreeMode = true;
    playLayer->updateCameraMode(obj, false);
    updateButtons(player1);
    updateToggleButtons();
}

void GamemodeLayer::updateButtons(PlayerObject* player1) {

    PlayerObjectExt* playerExt1 = static_cast<PlayerObjectExt*>(player1);

    if(!isCube(player1)) m_cubeBtn->toggle(isCube(playerExt1));
    if(!player1->m_isShip) m_shipBtn->toggle(playerExt1->m_isShip);
    if(!player1->m_isBall) m_ballBtn->toggle(playerExt1->m_isBall);
    if(!player1->m_isBird) m_birdBtn->toggle(playerExt1->m_isBird);
    if(!player1->m_isDart) m_dartBtn->toggle(playerExt1->m_isDart);
    if(!player1->m_isRobot) m_robotBtn->toggle(playerExt1->m_isRobot);
    if(!player1->m_isSpider) m_spiderBtn->toggle(playerExt1->m_isSpider);
    if(!player1->m_isSwing) m_swingBtn->toggle(playerExt1->m_isSwing);

    if(!playerExt1->isSpeed(GJPlayerSpeed::Half)) m_halfBtn->toggle(playerExt1->isSpeed(GJPlayerSpeed::Half));
    if(!playerExt1->isSpeed(GJPlayerSpeed::Default)) m_normalBtn->toggle(playerExt1->isSpeed(GJPlayerSpeed::Default));
    if(!playerExt1->isSpeed(GJPlayerSpeed::Double)) m_doubleBtn->toggle(playerExt1->isSpeed(GJPlayerSpeed::Double));
    if(!playerExt1->isSpeed(GJPlayerSpeed::Three)) m_threeBtn->toggle(playerExt1->isSpeed(GJPlayerSpeed::Three));
    if(!playerExt1->isSpeed(GJPlayerSpeed::Four)) m_fourBtn->toggle(playerExt1->isSpeed(GJPlayerSpeed::Four));
    if(!playerExt1->m_flipped) m_flipBtn->toggle(playerExt1->m_fields->m_flipped);
}

void GamemodeLayer::beginButtons(PlayerObject* player1) {

    PlayerObjectExt* playerExt1 = static_cast<PlayerObjectExt*>(player1);

    m_cubeBtn->toggle(isCube(playerExt1));
    m_shipBtn->toggle(playerExt1->m_isShip);
    m_ballBtn->toggle(playerExt1->m_isBall);
    m_birdBtn->toggle(playerExt1->m_isBird);
    m_dartBtn->toggle(playerExt1->m_isDart);
    m_robotBtn->toggle(playerExt1->m_isRobot);
    m_spiderBtn->toggle(playerExt1->m_isSpider);
    m_swingBtn->toggle(playerExt1->m_isSwing);

    m_halfBtn->toggle(playerExt1->isSpeed(GJPlayerSpeed::Half));
    m_normalBtn->toggle(playerExt1->isSpeed(GJPlayerSpeed::Default));
    m_doubleBtn->toggle(playerExt1->isSpeed(GJPlayerSpeed::Double));
    m_threeBtn->toggle(playerExt1->isSpeed(GJPlayerSpeed::Three));
    m_fourBtn->toggle(playerExt1->isSpeed(GJPlayerSpeed::Four));
    m_flipBtn->toggle(playerExt1->m_fields->m_flipped);
}

GamemodeLayer* GamemodeLayer::create(std::string const& text) {
    auto ret = new GamemodeLayer();
    if (ret && ret->initAnchored(360.f, 170.f, text, "GJ_square02.png")) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}