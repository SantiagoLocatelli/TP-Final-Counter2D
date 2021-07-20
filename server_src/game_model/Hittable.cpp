#include "Hittable.h"
#include <array>

b2Vec2 Hittable::getPosition(){
    return fixture->GetBody()->GetPosition();
}

