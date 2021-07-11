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
        std::map<std::string, float> getWeapon(WeaponType type);
        std::map<std::string, float> getPlayer();
};

#endif
