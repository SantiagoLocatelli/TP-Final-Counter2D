#include "stencil.h"

#define PI 3.14159265

Stencil::Stencil(SdlTexture& stencil, int screen_w, int screen_h, int level_w, int level_h)
    :stencil(stencil), level_w(level_w), level_h(level_h) {
    this->rect.w = screen_w;
    this->rect.h = screen_h;
    this->rect.x = 0;
    this->rect.y = 0;
    this->oldPosX = 0;
    this->oldPosY = 0;
}

void Stencil::centerStencil(SDL_Rect character) {
    this->rect.x = ( character.x + character.w / 2);
    this->rect.y = ( character.y + character.h / 2);
}

// /*
// typedef struct SDL_MouseMotionEvent
// {
//     Uint32 type;        /**< ::SDL_MOUSEMOTION */
//     Uint32 timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
//     Uint32 windowID;    /**< The window with mouse focus, if any */
//     Uint32 which;       /**< The mouse instance id, or SDL_TOUCH_MOUSEID */
//     Uint32 state;       /**< The current button state */
//     Sint32 x;           /**< X coordinate, relative to window */
//     Sint32 y;           /**< Y coordinate, relative to window */
//     Sint32 xrel;        /**< The relative motion in the X direction */
//     Sint32 yrel;        /**< The relative motion in the Y direction */
// } SDL_MouseMotionEvent;
// */

//     |
//     |
// ----|----
//     |
//     |
void Stencil::handleEvent(SDL_Event e){
    system("clear");
    printf("vel x relative: %i\n", e.motion.x);
    printf("vel y relative: %i\n", e.motion.y);
    
    //e.motion.x y e.motion.y dice la pos actual del mouse
    //e.motion.xrel y e.motion.yrel dice la vel relativa del mouse con respecto a su pos

    // si el mov relativo es negativo quiere decir que movio el
    // mouse para la izquierda de la pos del mouse

    // teorema del coseno

    // distancia del nuevo punto al personaje (a)
    double d_man_new = (double)(abs(this->rect.x - e.motion.x)+abs(this->rect.y - e.motion.y))/100; 
    printf("d_man_new: %f\n",d_man_new);
    
    // distancia del viejo punto al centro (b)
    double d_man_old = (double)(abs(this->rect.x - this->oldPosX)+abs(this->rect.y - this->oldPosY))/100;
    printf("d_man_old: %f\n",d_man_old);

    // distancia entre el punto viejo y el punto nuevo (c)
    double d_man_pts = (double)(abs(e.motion.x - this->oldPosX)+abs(e.motion.y - this->oldPosY))/100;
    printf("d_man_pts: %f\n",d_man_pts);

    if (d_man_pts > 0.2) {

        // cos(C) = (b^2 + a^2 - c^2) / 2(b*a)
        double result = (d_man_new*d_man_new) + (d_man_old*d_man_old) - (d_man_pts*d_man_pts);
        printf("resultado grados 1: %f\n",result);
        
        result = result / (double)(2*(d_man_new*d_man_old));
        printf("resultado grados 2: %f\n",result);
        result = acos(result)*180/PI; // acos devuelve en radianes
        printf("resultado grados 3: %f\n",result);
        this->degrees += result;
        this->oldPosX = e.motion.x;
        this->oldPosY = e.motion.y;
    }
}

void Stencil::render(int camX, int camY){
    this->stencil.setAlpha(150);
    this->stencil.render(this->rect.x - this->rect.w - camX, this->rect.y - this->rect.h - camY , this->rect.w*2, this->rect.h*2, NULL, degrees);
}
