#ifndef _WEAPON_TESTS_H_
#define _WEAPON_TESTS_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../World.h"
#include "../Player.h"
#include "../Weapon.h"

#define PI 3.14159

class WeaponTests: public CppUnit::TestFixture{
    public:
        CPPUNIT_TEST_SUITE(WeaponTests);
        CPPUNIT_TEST(testActivate);
        CPPUNIT_TEST_SUITE_END();
    
    protected:
        void testActivate(){
            World w(5,5);
            Player &p1 = w.createPlayer(0,0);
            Player &p2 = w.createPlayer(1,1);

            Weapon gun(p1, w);
            float old_health = p2.getHealth();
            gun.activate(PI/4.0);
            float new_health = p2.getHealth();

            CPPUNIT_ASSERT((new_health - old_health) < 0);

            old_health = p2.getHealth();
            gun.activate(0);
            new_health = p2.getHealth();

            CPPUNIT_ASSERT((new_health - old_health) == 0);
        }
};

#endif
