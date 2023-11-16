#include <iostream>
#include "application.h"

int main(){
  firefly_sim::Application app;
  
  /*
  for (auto &firefly : swarm){
    firefly->~Firefly();
  }

  swarm.clear();
  */

  while(app.isWindowOpen()){
    app.update();
  }

  return 0;
}