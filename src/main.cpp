#include <Geode/Geode.hpp>
#include "layer/GamemodeLayer.h"
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(CustomPauseLayer, PauseLayer) {

	void customSetup() {
		PauseLayer::customSetup();
		setTouchPriority(1);
		handleTouchPriority(this);

		bool pos = Mod::get()->getSettingValue<bool>("topRight");
		auto rightMenu = this->getChildByID("right-button-menu");
		auto bottomMenu = this->getChildByID("bottom-button-menu");
		auto winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite* sprSprite;
		CCMenuItemSpriteExtra* settingBtn;

		if(!pos) {
			sprSprite = CCSprite::createWithSpriteFrameName("accountBtn_settings_001.png");
			//sprSprite->setScale(0.7);
			settingBtn = CCMenuItemSpriteExtra::create(sprSprite, this, menu_selector(CustomPauseLayer::onMode));
			bottomMenu->addChild(settingBtn);
			bottomMenu->updateLayout();
		} else {
			sprSprite = CCSprite::createWithSpriteFrameName("GJ_editModeBtn_001.png");
			sprSprite->setScale(0.675);
			settingBtn = CCMenuItemSpriteExtra::create(sprSprite, this, menu_selector(CustomPauseLayer::onMode));
			rightMenu->addChild(settingBtn);
			rightMenu->updateLayout();
		}
		settingBtn->setID("gamemode-editor-button");
	}
	void onMode(CCObject* sender) {
		GamemodeLayer::create("Edit Player")->show();
	}
};