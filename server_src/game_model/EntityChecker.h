#ifndef _ENTITY_CHECKER_H_
#define _ENTITY_CHECKER_H_
#include <box2d/box2d.h>


class EntityChecker: public b2QueryCallback{
    private:
        b2World &world;
        bool hasEntities;
        bool ReportFixture(b2Fixture *fixture) override;
    public:
        explicit EntityChecker(b2World &world);
        bool areaHasEntities(b2Vec2 p1, b2Vec2 p2);
};

#endif
