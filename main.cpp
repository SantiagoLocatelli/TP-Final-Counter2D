#include "World.h"
#include "yaml-cpp/yaml.h"
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>

int main(){
    YAML::Node yaml_mapa = YAML::LoadFile("mapa.yaml");

    std::vector<int> size = yaml_mapa["size"].as<std::vector<int>>();
    std::cout << "Creating world of size (" << size[0] << ", " << size[1] << ")\n";
    World world(size[0], size[1]);

    std::vector<int> spawn = yaml_mapa["spawn"].as<std::vector<int>>();
    std::cout << "Creating player in (" << spawn[0] << ", " << spawn[1] << ")\n";
    Player p = world.createPlayer(spawn[0], spawn[1]);


    YAML::Node boxes = yaml_mapa["boxes"];
    std::cout << "Adding boxes in:\n";
    for (YAML::iterator it = boxes.begin(); it != boxes.end(); ++it) {
        std::vector<int> box = it->as<std::vector<int>>();
        std::cout << "\t- [" << box[0] << ", " << box[1] <<"]\n";
        world.addBox(box[0], box[1]);
    }

    p.applyImpulse(1, 1);

    for (int i = 0; i < 25; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        world.step(0.5);
        b2Vec2 position = p.getPosition();
        printf("Jugador:\n\tx:%4.2f\n\ty:%4.2f\n", position.x, position.y); 
    }  

    return 0;
}
