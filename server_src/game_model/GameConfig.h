#ifndef _GAME_CONFIG_H_
#define _GAME_CONFIG_H_

#include "../../common_src/Utils.h"
#include "yaml-cpp/yaml.h"
#include <string>
#include <map>

class GameConfig{
    private:
        YAML::Node configFile;

    public:
        GameConfig();

        float getWeapon(WeaponType type, std::string name);
        float getPlayer(std::string name);
        float getGame(std::string name);

        GameConfig(const GameConfig&) = delete;
        GameConfig& operator=(const GameConfig&) = delete;

};

#endif
