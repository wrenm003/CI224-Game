#include "GameAsset.h"

#ifndef Cube_H_
#define Cube_H_

class Cube : public GameAsset {
 public:
  Cube();
  Cube(float x, float y, float z);
    ~Cube();

  void MoveForward();

  virtual void update();
  virtual void draw();
  virtual void clean();

  enum vertices {
F0, F1, F2, F3, R1, R2, R3 , R4, };

 private:
};

#endif // Cube_H_
