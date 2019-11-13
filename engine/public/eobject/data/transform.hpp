#pragma once

#include <core/math.hpp>

namespace ENGH::EObject::Data {

class Transform {
public:
  ENGH::Math::Vec3 position;
  ENGH::Math::Quat rotation;
  ENGH::Math::Vec3 scale;

};

}
