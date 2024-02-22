#include <Geode/Geode.hpp>
#include "layer/GamemodeLayer.h"

namespace Helper {
    void changeGamemode(int gamemode) {
        auto playLayer = PlayLayer::get();
        auto player1 = playLayer->m_player1;
        switch(gamemode) {
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
            case 8: player1->m_isPlatformer = !player1->m_isPlatformer;
        }
        auto obj = TeleportPortalObject::create("edit_eGameRotBtn_001.png", true);
        obj->m_cameraIsFreeMode = true;
        playLayer->updateCameraMode(obj, false);
    }

    void changeToggle(int toggle) {
        auto playLayer = PlayLayer::get();
        auto player1 = static_cast<PlayerObjectExt*>(playLayer->m_player1);

        switch(toggle) {
            case 0: player1->togglePlayerScale(!player1->m_fields->m_scale, true); break;
            case 1: player1->flipGravity(!player1->m_fields->m_flipped, true); break;
            default: break;
        }
    }
    void changeSpeed(int speed) {
        auto playLayer = PlayLayer::get();
        auto player1 = static_cast<PlayerObjectExt*>(playLayer->m_player1);

        switch(speed) {
            case 0: player1->changePlayerSpeed(GJPlayerSpeed::Half); break;
            case 1: player1->changePlayerSpeed(GJPlayerSpeed::Default); break;
            case 2: player1->changePlayerSpeed(GJPlayerSpeed::Double); break;
            case 3: player1->changePlayerSpeed(GJPlayerSpeed::Three); break;
            case 4: player1->changePlayerSpeed(GJPlayerSpeed::Four); break;
    }
    }
}