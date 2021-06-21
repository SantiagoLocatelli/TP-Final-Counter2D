#include "stencil.h"

#define PI 3.14159265

typedef struct coordenada{
    int x, y;
}coordenada_t;

Stencil::Stencil(SdlTexture& stencil, int screen_w, int screen_h)
    :stencil(stencil) {
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

int productoEscalar(coordenada_t coord1, coordenada_t coord2){
    return ((coord1.x*coord2.x)+(coord1.y*coord2.y));
}

int modulo(coordenada_t coord){
    return sqrt((coord.x*coord.x) + (coord.y*coord.y));
}

bool coordsIguales(coordenada_t coord1, coordenada_t coord2){
    return ((coord1.x == coord2.x) && (coord1.y == coord2.y));
}

void Stencil::handleEvent(SDL_Event e){
    system("clear");
    printf("vel x relative: %i\n", e.motion.x);
    printf("vel y relative: %i\n", e.motion.y);


    /*
    recordando que centramos el stencil en el personale.
    la idea es pensar en tres puntos, para generar dos lineas.
    se sabe que si los degrees son 0, entonces el stencil mira para la derecha.
    por lo que imaginamos un eje de coordenadas con la pos del stencil como centro,
    la pos del stencil es nuestro primer punto, el segundo viene a ser la pos del mouse,
    y el tercer punto lo generamos con la pos en y del personaje, y la pos en x del mouse.
    y calculamos los angulos entre esas dos lineas
    */
    coordenada_t origen = {0, 0};
    coordenada_t mouse = {e.motion.x, e.motion.y};
    coordenada_t stn = {this->rect.x, this->rect.y};
    coordenada_t newCoord = {mouse.x, stn.y};
    // para obtener los vectores dobe restar los puntos
    coordenada_t newVec = {newCoord.x - stn.x, newCoord.y - stn.y};
    coordenada_t mouseVec = {mouse.x - stn.x, mouse.y - stn.y};

    if (!coordsIguales(origen, mouseVec) && !coordsIguales(origen, newVec)) {

        int modulo_newVec = modulo(newVec);
        int modulo_mouseVec = modulo(mouseVec);
        double result = (double)productoEscalar(newVec, mouseVec)/ (modulo_newVec*modulo_mouseVec);
        if ((modulo_newVec == modulo_mouseVec) && (mouseVec.x < 0)) {
            this->degrees = 180;
        }
        printf("pord esca: %i\n", productoEscalar(newVec,mouseVec));
        printf("mod vec 1: %i\n", modulo(newVec));
        printf("mod vec 2: %i\n", modulo(mouseVec));
        printf("resultado entero: %i\n", productoEscalar(newVec, mouseVec)/(modulo(newVec)*modulo(mouseVec)));
        printf("result 1: %f\n", result);

        // acos devuelve el resultado en radianes
        result = acos(result)*180/PI;
        this->degrees = result;
        if (mouseVec.x < 0 && mouseVec.y < 0) {
            this->degrees += 180;
        } else if (mouseVec.x < 0 && mouseVec.y > 0) {
            this->degrees = 180 - this->degrees;
        } else if (mouseVec.x > 0 && mouseVec.y < 0) {
            this->degrees = 360 - this->degrees;
        }
        //printf("grados: %f\n", this->degrees);
    } else if (mouseVec.y > 0) {
        this->degrees = 90;
    } else {
        this->degrees = 270;
    }

    //e.motion.x y e.motion.y dice la pos actual del mouse
    //e.motion.xrel y e.motion.yrel dice la vel relativa del mouse con respecto a su pos

    // si el mov relativo es negativo quiere decir que movio el
    // mouse para la izquierda de la pos del mouse

    // teorema del coseno

    // distancia del nuevo punto al personaje (a)
    // double d_man_new = (double)(abs(this->rect.x - e.motion.x)+abs(this->rect.y - e.motion.y))/100; 
    // printf("d_man_new: %f\n",d_man_new);
    
    // // distancia del viejo punto al centro (b)
    // double d_man_old = (double)(abs(this->rect.x - this->oldPosX)+abs(this->rect.y - this->oldPosY))/100;
    // printf("d_man_old: %f\n",d_man_old);

    // // distancia entre el punto viejo y el punto nuevo (c)
    // double d_man_pts = (double)(abs(e.motion.x - this->oldPosX)+abs(e.motion.y - this->oldPosY))/100;
    // printf("d_man_pts: %f\n",d_man_pts);

    // if (d_man_pts > 0.2) {

    //     // cos(C) = (b^2 + a^2 - c^2) / 2(b*a)
    //     double result = (d_man_new*d_man_new) + (d_man_old*d_man_old) - (d_man_pts*d_man_pts);
    //     printf("resultado grados 1: %f\n",result);
        
    //     result = result / (double)(2*(d_man_new*d_man_old));
    //     printf("resultado grados 2: %f\n",result);
    //     result = acos(result)*180/PI; // acos devuelve en radianes
    //     printf("resultado grados 3: %f\n",result);
    //     this->degrees += result;
    //     this->oldPosX = e.motion.x;
    //     this->oldPosY = e.motion.y;
    // }
}

void Stencil::render(int camX, int camY){
    this->stencil.setAlpha(150);
    this->stencil.render(this->rect.x - this->rect.w - camX, this->rect.y - this->rect.h - camY , this->rect.w*2, this->rect.h*2, NULL, degrees);
}
