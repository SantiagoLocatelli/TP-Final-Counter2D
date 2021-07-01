#include <cppunit/ui/text/TestRunner.h>
#include "PlayerTests.h"
#include "WorldTests.h"
#include "WeaponTests.h"

int main(){
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(PlayerTests::suite());
  runner.addTest(WorldTests::suite());
  runner.addTest(WeaponTests::suite());
  runner.run();
  return 0;
}
