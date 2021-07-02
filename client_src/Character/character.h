#ifndef __Character_H__
#define __Character_H__

#include "../../common_src/Sdl/sdl_renderer.h" 
#include "../../common_src/Sdl/sdl_texture.h"
#include "camera.h"
#include "stencil.h"
#include "animation.h"
#include <list>
#include "../../common_src/Protocol.h"
#include "levelInfo.h"
#include "../Events/gameMath.h"
#include "Weapon.h"


class Character{

    private:
		
		Animation an;
		SDL_Rect area;
		double degrees;
		// Weapon& weapon;

    public:
		Character(int width, int height, SdlTexture texture/*, Weapon& weapon*/);

		void update(const Prot_Player you, const LevelInfo level, float health = -1.0, uint16_t ammo = -1);
		void render(int camX, int camY);

		SDL_Rect getRect();
		int getPosX();
		int getPosY();

		Character& operator=(Character&&);
		Character(Character&& other);
};
#endif
