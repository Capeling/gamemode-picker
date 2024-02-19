#include <Geode/Geode.hpp>
#include "layer/GamemodeLayer.h"
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(CustomPauseLayer, PauseLayer) {

	void customSetup() {
		PauseLayer::customSetup();
		auto winSize = CCDirector::sharedDirector()->getWinSize();
		auto toolsMenu = CCMenu::create();
		auto sprSprite = CCSprite::createWithSpriteFrameName("accountBtn_settings_001.png");
		sprSprite->setScale(0.7);
		auto settingBtn = CCMenuItemSpriteExtra::create(sprSprite, this, menu_selector(CustomPauseLayer::onMode));
		toolsMenu->addChild(settingBtn);
		
		this->addChildAtPosition(toolsMenu, Anchor::Bottom, ccp(0,30), false);
	}
	void onMode(CCObject* sender) {
		GamemodeLayer::create("Edit Player")->show();
	}
};