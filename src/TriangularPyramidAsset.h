#include "GameAsset.h"
#include "LinearInterpolator.h"

#ifndef TRIANGULARPYRAMIDASSET_H_
#define TRIANGULARPYRAMIDASSET_H_

class TriangularPyramidAsset : public GameAsset {
 public:
  TriangularPyramidAsset();
  ~TriangularPyramidAsset();

  virtual void update();
  virtual void draw();
  void setInterpolator(LinearInterpolator * li);
 private:
  LinearInterpolator *li;
};

#endif // TRIANGULARPYRAMIDASSET_H_
