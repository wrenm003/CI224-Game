#include "GameAsset.h"

#ifndef TRIANGULARPYRAMIDASSET_H_
#define TRIANGULARPYRAMIDASSET_H_

class TriangularPyramidAsset : public GameAsset {
 public:
  TriangularPyramidAsset();
  ~TriangularPyramidAsset();

  virtual void update();
};

#endif // TRIANGULARPYRAMIDASSET_H_
