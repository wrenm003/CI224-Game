#include "BallisticInterpolator.h"

BallisticInterpolator::BallisticInterpolator(Vector3 launch, int fps) {
  this->launch = new Vector3(launch);
  this->G = new Vector3(0.0f, -9.8f, 0.0f);
  this->fps = fps;
  this->count = 0;
}

#include<iostream>
Vector3 BallisticInterpolator::update() {
  count++;
  float time = ((float)count)/((float)fps);
  if(0==count%fps)
    std::cout << time << " seconds" << std::endl;
  return ((*launch)*time) + ((*G) * ((1.0f/2.0f) * pow(((float)count/(float)fps), 2.0f)));
}
