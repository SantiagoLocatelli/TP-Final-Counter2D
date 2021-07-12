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

        //TODO: Que estos metodos no devuelvan un map, sino que le pases un string y te devuelvan directamente el float.
        std::map<std::string, float> getWeapon(WeaponType type);
        std::map<std::string, float> getPlayer();
        std::map<std::string, float> getGame();

        GameConfig(const GameConfig&) = delete;
        GameConfig& operator=(const GameConfig&) = delete;

};

#endif
