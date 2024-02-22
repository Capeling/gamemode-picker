#include <Geode/Geode.hpp>
#include "layer/GamemodeLayer.h"
#include <Geode/modify/PauseLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
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

$execute {
	using namespace keybinds;

	//speeds
	BindManager::get()->registerBindable({
		"cube"_spr,
		"Change to Cube",
		"Changes to the Cube Gamemode",
		{ Keybind::create(KEY_One, Modifier::Shift) },
		Category::PLAY
	});

	BindManager::get()->registerBindable({
		"ship"_spr,
		"Change to Ship",
		"Changes to the Ship Gamemode",
		{ Keybind::create(KEY_Two, Modifier::Shift) },
		Category::PLAY
	});

	BindManager::get()->registerBindable({
		"ball"_spr,
		"Change to Ball",
		"Changes to the Ball Gamemode",
		{ Keybind::create(KEY_Three, Modifier::Shift) },
		Category::PLAY
	});

	BindManager::get()->registerBindable({
		"ufo"_spr,
		"Change to UFO",
		"Changes to the UFO Gamemode",
		{ Keybind::create(KEY_Four, Modifier::Shift) },
		Category::PLAY
	});

	BindManager::get()->registerBindable({
		"wave"_spr,
		"Change to Wave",
		"Changes to the Wave Gamemode",
		{ Keybind::create(KEY_Five, Modifier::Shift) },
		Category::PLAY
	});

	BindManager::get()->registerBindable({
		"robot"_spr,
		"Change to Robot",
		"Changes to the Robot Gamemode",
		{ Keybind::create(KEY_Six, Modifier::Shift) },
		Category::PLAY
	});

	BindManager::get()->registerBindable({
		"spider"_spr,
		"Change to Spider",
		"Changes to the Spider Gamemode",
		{ Keybind::create(KEY_Seven, Modifier::Shift) },
		Category::PLAY
	});

	BindManager::get()->registerBindable({
		"swing"_spr,
		"Change to Swing",
		"Changes to the Swing Gamemode",
		{ Keybind::create(KEY_Eight, Modifier::Shift) },
		Category::PLAY
	});

	//toggles
	BindManager::get()->registerBindable({
		"plat"_spr,
		"Toggle Platformer",
		"Toggles the Platformer Gamemode",
		{ Keybind::create(KEY_One, Modifier::Control) },
		Category::PLAY
	});

	BindManager::get()->registerBindable({
		"size"_spr,
		"Toggle Size",
		"Toggles the Player Size",
		{ Keybind::create(KEY_Two, Modifier::Control) },
		Category::PLAY
	});

	BindManager::get()->registerBindable({
		"grav"_spr,
		"Toggle Gravity",
		"Toggles the Player Gravity",
		{ Keybind::create(KEY_Three, Modifier::Control) },
		Category::PLAY
	});

	//speeds
	BindManager::get()->registerBindable({
		"half"_spr,
		"Half Speed",
		"Changes the player speed to 0.7 (Half Speed Portal)",
		{ Keybind::create(KEY_One, Modifier::Alt) },
		Category::PLAY
	});

	BindManager::get()->registerBindable({
		"normal"_spr,
		"Normal Speed",
		"Changes the player speed to 0.9 (Normal Speed Portal)",
		{ Keybind::create(KEY_Two, Modifier::Alt) },
		Category::PLAY
	});
	
	BindManager::get()->registerBindable({
		"double"_spr,
		"2X Speed",
		"Changes the player speed to 1.1 (2X Portal)",
		{ Keybind::create(KEY_Three, Modifier::Alt) },
		Category::PLAY
	});

	BindManager::get()->registerBindable({
		"three"_spr,
		"3X Speed",
		"Changes the player speed to 1.3 (3X Portal)",
		{ Keybind::create(KEY_Four, Modifier::Alt) },
		Category::PLAY
	});

	BindManager::get()->registerBindable({
		"four"_spr,
		"4X Speed",
		"Changes the player speed to 1.6 (4X Portal)",
		{ Keybind::create(KEY_Five, Modifier::Alt) },
		Category::PLAY
	});
}