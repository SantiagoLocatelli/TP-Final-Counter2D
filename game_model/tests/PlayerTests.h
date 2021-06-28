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
        CPPUNIT_TEST(testIsHit);
        CPPUNIT_TEST(testInitialHealth);
        CPPUNIT_TEST(testRecvDamage);
        CPPUNIT_TEST_SUITE_END();
        
    protected:
        void testInitialPosition(){
            World w(5,5);
            Player &p = w.createPlayer(1,1);
            std::array<float, 2> pos = p.getPosition();
            CPPUNIT_ASSERT(pos[0] == 1.5f);
            CPPUNIT_ASSERT(pos[1] == 1.5f);
        }

        void testInitialHealth(){
            World w(5,5);
            Player &p = w.createPlayer(1,1);

            CPPUNIT_ASSERT(p.getHealth() == 100);
        }


        void testMovesRight(){
            World w(5,5);
            Player &p = w.createPlayer(1,1);
            p.toggle_movement(RIGHT);

            std::array<float, 2> prev_pos = p.getPosition();
            w.step();
            std::array<float, 2> new_pos = p.getPosition();
            CPPUNIT_ASSERT((new_pos[0]-prev_pos[0]) > 0);
            CPPUNIT_ASSERT((new_pos[1]-prev_pos[1]) == 0);
        }

        void testIsHit(){
            World w(5,5);
            Player &p = w.createPlayer(2,2);
            float distance = p.isHitBy(0,0,PI/4.0);
            CPPUNIT_ASSERT(distance > 1);

            distance = p.isHitBy(0,0,0);
            CPPUNIT_ASSERT(distance < 0);            
        }

        void testRecvDamage(){
            World w(5,5);
            Player &p = w.createPlayer(2,2);

            float old_health = p.getHealth();
            p.recvDamage(20);
            float new_health = p.getHealth();

            CPPUNIT_ASSERT((new_health-old_health) == -20);
        }
};

#endif
