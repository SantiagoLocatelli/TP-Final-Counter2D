#ifndef __Character_H__
#define __Character_H__

#include "../../common_src/Sdl/sdl_texture.h"
#include "../../common_src/Protocol.h"
#include "../Events/gameMath.h"
#include "../levelInfo.h"
#include "animation.h"
#include "Weapon.h"


class Character{

    private:
		
		Animation an;
		SDL_Rect area;
		double degrees;
		bool dead;
		int idWeapon = 0;

    public:
		Character(int width, int height, SdlTexture& texture);
		Character();

		void update(const ProtPlayer you, const LevelInfo level, float health = -1.0, uint16_t ammo = -1);
		void render(int camX, int camY);

		SDL_Rect getRect();
		int getPosX();
		int getPosY();
		bool isDead();
		int getIdWeapon();
		float getDegrees();

		Character& operator=(Character&&);
		Character(Character&& other);
};
#endif
