#ifndef __Character_H__
#define __Character_H__

#include "../../common_src/Sdl/sdl_texture.h"
#include "../../common_src/Protocol.h"
#include "../levelInfo.h"
#include "animation.h"


class Character{

    private:
		
		Animation an;
		PlayerInfo player;

    public:
		Character(PlayerInfo player, SdlTexture& texture);
		Character();

		void update(PlayerInfo info);
		void render(int camX, int camY);

		SDL_Rect getRect();
		int getPosX();
		int getPosY();
		bool isDead();
		WeaponType getIdWeapon();
		float getDegrees();

		Character& operator=(Character&&);
		Character(Character&& other);
};
#endif
