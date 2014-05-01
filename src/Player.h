#include "GameAsset.h"

#ifndef Player_H_
#define Player_H_

class Player : public GameAsset {
 public:
  Player();
  Player(float x, float y, float z);
    ~Player();

  virtual void update();
  virtual void draw();
  virtual void clean();

  enum vertices {
F0, F1, F2, F3, };

 private:
};

#endif // Player_H_
