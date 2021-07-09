#ifndef _TEXTURE_MAP_H_
#define _TEXTURE_MAP_H_

#include <string>
#include <map>

struct TextureInfo{
    std::string texturePath;
    bool isBox;
};

class TextureMap{
    private:
        std::map<int, TextureInfo> map;

    public:
        TextureMap();
        TextureInfo operator[](int key);
        int size();
};

#endif
