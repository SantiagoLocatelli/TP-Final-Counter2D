#ifndef __Character_H__
#define __Character_H__

#include "../../common_src/Sdl/sdl_texture.h"
#include "../../common_src/Protocol.h"
#include "../levelInfo.h"
#include "Weapon.h"

class Character{

    private:
		
		SdlTexture& texture;
		PlayerInfo player;
		Weapon weapon;

		SDL_Rect getSourceTexture();

    public:
		Character(PlayerInfo player, SdlTexture& texture, Weapon weapon);

		void update(PlayerInfo info, Weapon weapon);
		void render(int camX, int camY);

		SDL_Rect getRect();
		int getPosX();
		int getPosY();
		bool isDead();
		float getDegrees();

		Character& operator=(Character&&);
		Character(Character&& other);
};
#endif
