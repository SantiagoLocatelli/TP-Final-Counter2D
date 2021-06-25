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
        CPPUNIT_TEST(testBoxStopsMovement);
        CPPUNIT_TEST(testPlayerCollision);
        CPPUNIT_TEST(testPlayerNoRebota);
        CPPUNIT_TEST_SUITE_END();

    protected:
        void testInitialPlayerPosition(){
            World w(5,5);
            Player &p = w.createPlayer(0,0);

            CPPUNIT_ASSERT(p.getPosition()[0] == 0.5);
            CPPUNIT_ASSERT(p.getPosition()[1] == 0.5);
        }

        void testBoxStopsMovement(){
            World w(10,10);
            w.addBox(2, 0);
            Player &p = w.createPlayer(0,0);
            p.toggle_movement(RIGHT);


            std::array<float, 2> prev_pos = p.getPosition();
            for (int i = 0; i < 30; i++){
                w.step();
            }
            std::array<float, 2> new_pos = p.getPosition();
            CPPUNIT_ASSERT(new_pos[0] < 2);
            CPPUNIT_ASSERT((new_pos[1]-prev_pos[1]) == 0);
        }

        void testPlayerCollision(){
            World w(5,5);
            Player &p1 = w.createPlayer(0,0);
            Player &p2 = w.createPlayer(1,0);

            std::array<float, 2> prev_p1 = p1.getPosition();
            std::array<float, 2> prev_p2 = p2.getPosition();

            p1.toggle_movement(RIGHT);

            for (int i = 0; i < 30; i++){
                w.step();
            }

            std::array<float, 2> new_p1 = p1.getPosition();
            std::array<float, 2> new_p2 = p2.getPosition();

            CPPUNIT_ASSERT((new_p1[0]-prev_p1[0]) > 0);
            CPPUNIT_ASSERT((new_p1[1]-prev_p1[1]) == 0);
            CPPUNIT_ASSERT((new_p2[0]-prev_p2[0]) > 0);
            CPPUNIT_ASSERT((new_p2[1]-prev_p2[1]) == 0);
        }
};

#endif
