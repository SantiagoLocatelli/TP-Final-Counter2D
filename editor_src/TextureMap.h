#ifndef __TEXTURE_MAP_H__
#define __TEXTURE_MAP_H__
#include <map>
#include <memory>
class TextureMap{
    private:
        std::map<int, std::string> map;
    public:
        void insert(int key, std::string value);
        std::string operator[](int key);
        int size();
};
#endif
