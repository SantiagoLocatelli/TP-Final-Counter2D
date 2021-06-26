#ifndef _WORLD_TESTS_H_
#define _WORLD_TESTS_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../World.h"
#include "../Player.h"

class WorldTests: public CppUnit::TestFixture{
    public:
        CPPUNIT_TEST_SUITE(WorldTests);
        CPPUNIT_TEST(testInitialPlayerPosition);
        CPPUNIT_TEST_SUITE_END();

    protected:
        void testInitialPlayerPosition(){
            World w(5,5);
            Player &p = w.createPlayer(0,0);

            CPPUNIT_ASSERT(p.getPosition()[0] == 0.5);
            CPPUNIT_ASSERT(p.getPosition()[1] == 0.5);
        }
};

#endif
