#ifndef __TEXTURE_MAP_H__
#define __TEXTURE_MAP_H__
#include <map>
#include <memory>
#include "../Sdl/game_object.h"
class TextureMap{
    private:
        std::map<int, std::unique_ptr<GameObject>> map;
    public:
        TextureMap();
        void insert(int key, std::unique_ptr<GameObject> value);
        std::unique_ptr<GameObject> operator[](int key);
};
#endif
