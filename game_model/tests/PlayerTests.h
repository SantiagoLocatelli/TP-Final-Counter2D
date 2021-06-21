#ifndef _PLAYER_TESTS_H_
#define _PLAYER_TESTS_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../World.h"
#include "../Player.h"

#define PI 3.14159

class PlayerTests: public CppUnit::TestFixture{
    public:
        CPPUNIT_TEST_SUITE(PlayerTests);
        CPPUNIT_TEST(testInitialPosition);
        CPPUNIT_TEST(testMovesRight);
        CPPUNIT_TEST(testBoxStopsMovement);
        CPPUNIT_TEST(testPlayerCollision);
        CPPUNIT_TEST(testIsHit);
        CPPUNIT_TEST_SUITE_END();
        
    protected:
        void testInitialPosition(){
            World w(5,5);
            Player &p = w.createPlayer(1,1);
            std::array<float, 2> pos = p.getPosition();
            CPPUNIT_ASSERT(pos[0] == 1.5f);
            CPPUNIT_ASSERT(pos[1] == 1.5f);
        }

        void testMovesRight(){
            World w(5,5);
            Player &p = w.createPlayer(1,1);
            p.applyImpulse(1, 0);

            std::array<float, 2> prev_pos = p.getPosition();
            w.step();
            std::array<float, 2> new_pos = p.getPosition();
            CPPUNIT_ASSERT((new_pos[0]-prev_pos[0]) > 0);
            CPPUNIT_ASSERT((new_pos[1]-prev_pos[1]) == 0);
        }

        void testBoxStopsMovement(){
            World w(10,10);
            w.addBox(3, 0);
            Player &p = w.createPlayer(0,0);
            p.applyImpulse(10, 0);


            std::array<float, 2> prev_pos = p.getPosition();
            for (int i = 0; i < 30; i++){
                w.step();
            }
            std::array<float, 2> new_pos = p.getPosition();
            CPPUNIT_ASSERT(new_pos[0] < 3);
            CPPUNIT_ASSERT((new_pos[1]-prev_pos[1]) == 0);
        }

        void testPlayerCollision(){
            World w(5,5);
            Player &p1 = w.createPlayer(0,0);
            Player &p2 = w.createPlayer(1,0);

            std::array<float, 2> prev_p1 = p1.getPosition();
            std::array<float, 2> prev_p2 = p2.getPosition();

            p1.applyImpulse(5, 0);

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

        void testIsHit(){
            World w(5,5);
            Player &p = w.createPlayer(2,2);
            float distance = p.isHitBy(0,0,PI/4.0);
            CPPUNIT_ASSERT(distance > 1);

            distance = p.isHitBy(0,0,0);
            CPPUNIT_ASSERT(distance < 0);            
        }
};

#endif
