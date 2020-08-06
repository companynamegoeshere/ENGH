#pragma once

#include <core/engine.hpp>

namespace ENGH::EObject {

class EObject {
public:
  virtual void SetDefaults() {};

  virtual ~EObject() = 0;
};

}
