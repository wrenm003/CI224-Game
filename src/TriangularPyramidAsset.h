#include "GameAsset.h"
#include "IInterpolator.h"

#ifndef TRIANGULARPYRAMIDASSET_H_
#define TRIANGULARPYRAMIDASSET_H_

class TriangularPyramidAsset : public GameAsset {
 public:
  TriangularPyramidAsset();
  ~TriangularPyramidAsset();

  virtual void update();
  virtual void draw();
  void setInterpolator(IInterpolator * li);
 private:
  IInterpolator *li;
};

#endif // TRIANGULARPYRAMIDASSET_H_
