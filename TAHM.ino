#include "myMCU.h"

myMCU gMCU;

void setup() {
  gMCU.init();
}

void loop() {
  gMCU.work();
}
