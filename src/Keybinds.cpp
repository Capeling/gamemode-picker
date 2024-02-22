#include <Geode/Geode.hpp>
#include "layer/GamemodeLayer.h"
#include "Helper.hpp"

#ifdef GEODE_IS_WINDOWS 

#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <Geode/modify/UILayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>

using namespace geode::prelude;
using namespace keybinds;

struct $modify(UILayer) {
    bool init(GJBaseGameLayer* gameLayer) {
        if(!UILayer::init(gameLayer))
            return false;
        Loader::get()->queueInMainThread([this] {

            if(!PlayLayer::get()) return;

            //gamemodes
            this->defineKeybind("cube"_spr, [this] {
                Helper::changeGamemode(0);
            });
            this->defineKeybind("ship"_spr, [this] {
                Helper::changeGamemode(1);
            });
            this->defineKeybind("ball"_spr, [this] {
                Helper::changeGamemode(2);
            });
            this->defineKeybind("ufo"_spr, [this] {
                Helper::changeGamemode(3);
            });
            this->defineKeybind("wave"_spr, [this] {
                Helper::changeGamemode(4);
            });
            this->defineKeybind("robot"_spr, [this] {
                Helper::changeGamemode(5);
            });
            this->defineKeybind("spider"_spr, [this] {
                Helper::changeGamemode(6);
            });
            this->defineKeybind("swing"_spr, [this] {
                Helper::changeGamemode(7);
            });

            //toggles
            this->defineKeybind("plat"_spr, [this] {
                Helper::changeGamemode(8);
            });
            this->defineKeybind("size"_spr, [this] {
                Helper::changeToggle(0);
            });
            this->defineKeybind("grav"_spr, [this] {
                Helper::changeToggle(1);
            });

            //speeds
            this->defineKeybind("half"_spr, [this] {
                Helper::changeSpeed(0);
            });
            this->defineKeybind("normal"_spr, [this] {
                Helper::changeSpeed(1);
            });
            this->defineKeybind("double"_spr, [this] {
                Helper::changeSpeed(2);
            });
            this->defineKeybind("three"_spr, [this] {
                Helper::changeSpeed(3);
            });
            this->defineKeybind("four"_spr, [this] {
                Helper::changeSpeed(4);
            });
        });
        return true;
    }

    //thanks betteredit
    void defineKeybind(const char* id, std::function<void()> callback) {
        this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
            if (event->isDown()) {
               callback();
            }
            return ListenerResult::Propagate;
        }, id);
    }
};
#endif