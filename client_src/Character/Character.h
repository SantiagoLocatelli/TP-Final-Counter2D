#ifndef __Character_H__
#define __Character_H__

#include "../../common_src/Sdl/sdl_texture.h"
#include "../../common_src/Protocol.h"
#include "../LevelInfo.h"
#include "Weapon.h"

class Character{

    private:
		
		SdlTexture& texture;
		PlayerInfo player;
		Weapon* weapon;
		int delay = 0;

		SDL_Rect getSourceTexture();

    public:
		Character(PlayerInfo player, SdlTexture& texture, Weapon* weapon);

		void update(PlayerInfo info, Weapon* weapon);
		void render(Coordinate cam);
		SDL_Rect getRect();
		int getPosX();
		int getPosY();
		bool isDead();
		float getDegrees();
		PlayerInfo getInfo();
		WeaponType getWeaponType();
		int quantityWeapons(std::array<WeaponType, 4> weapons);

		Character& operator=(const Character&);
		Character(const Character& other);
};
#endif
