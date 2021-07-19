#include "GameConfig.h"

GameConfig::GameConfig():configFile(YAML::LoadFile("/usr/local/share/counter2d/resources/server/GameConfig.yaml")){}

float GameConfig::getWeapon(WeaponType type, std::string name){
    std::string weaponName;
    switch (type){
    case KNIFE:
        weaponName = "Knife";
        break;
    case PISTOL:
        weaponName = "Pistol";
        break;
    case SHOTGUN:
        weaponName = "Shotgun";
        break;
    case RIFLE:
        weaponName = "Rifle";
        break;
    case SNIPER:
        weaponName = "Sniper";
        break;
    case BOMB:
        weaponName = "Bomb";
        break;
    
    default:
        weaponName = ""; //No estan en el archivo todavia
    }

    return configFile["Weapons"][weaponName][name].as<float>();
}

float GameConfig::getPlayer(std::string name){
    return configFile["Player"][name].as<float>();
}

float GameConfig::getGame(std::string name){
    return configFile["Game"][name].as<float>();
}

