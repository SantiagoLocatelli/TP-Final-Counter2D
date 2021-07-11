#include "GameConfig.h"

GameConfig::GameConfig():configFile(YAML::LoadFile("../../server_src/game_model/GameConfig.yaml")){}

std::map<std::string, float> GameConfig::getWeapon(WeaponType type){
    std::string name;
    switch (type){
    case KNIFE:
        name = "Knife";
        break;
    case PISTOL:
        name = "Pistol";
        break;
    case SHOTGUN:
        name = "Shotgun";
        break;
    case RIFLE:
        name = "Rifle";
        break;
    case SNIPER:
        name = "Sniper";
        break;
    default:
        name = ""; //No estan en el archivo todavia
    }

    return configFile["Weapons"][name].as<std::map<std::string, float>>();
}

std::map<std::string, float> GameConfig::getPlayer(){
    return configFile["Player"].as<std::map<std::string, float>>();
}

std::map<std::string, float> GameConfig::getGame(){
    return configFile["Game"].as<std::map<std::string, float>>();
}

