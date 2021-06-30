#include "GameManager.h"
#include "yaml-cpp/yaml.h"
#include <vector>
#include <utility>

GameManager::GameManager(const std::string &yaml_file){
    YAML::Node yaml_mapa = YAML::LoadFile(yaml_file);

    std::vector<int> size = yaml_mapa["size"].as<std::vector<int>>();
    world = new World(size[0], size[1]);

    std::vector<int> spawn = yaml_mapa["spawn"].as<std::vector<int>>();
    player = &world->createPlayer(spawn[0], spawn[1]);

    YAML::Node boxes = yaml_mapa["boxes"];
    for (YAML::iterator it = boxes.begin(); it != boxes.end(); ++it) {
        std::vector<int> box = it->as<std::vector<int>>();
        world->addBox(box[0], box[1]);
    }
}

void GameManager::move_player(Direction dir){
    const std::lock_guard<std::mutex> lock(m);

    player->toggle_movement(dir);
}

void GameManager::get_player_position(float &x, float &y){
    const std::lock_guard<std::mutex> lock(m);
    std::array<float, 2> pos = player->getPosition();
    x = pos[0];
    y = pos[1];
}

void GameManager::step_world(){
    const std::lock_guard<std::mutex> lock(m);
    world->step();
}

GameManager::~GameManager(){
    delete player;
    delete world;
}
