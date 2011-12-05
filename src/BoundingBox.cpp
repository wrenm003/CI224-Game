#include "BoundingBox.h"

BoundingBox::BoundingBox(const Point3 & c, const float extent_x, const float extent_y, const float extent_z) {
  this->c = Point3(c);
  this->h_x = Vector3(extent_x/2.0, 0.0, 0.0);
  this->h_y = Vector3(0.0, extent_y/2.0, 0.0);
  this->h_z = Vector3(0.0, 0.0, extent_z/2.0);
}

bool BoundingBox::collidesWith(const BoundingBox & b) {
  return false;
}
