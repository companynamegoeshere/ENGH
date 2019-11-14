#pragma once

#include <core/math.hpp>

namespace ENGH::EObject::Data {

class Transform {
public:
  Transform();

  ENGH::Math::Vec3 position;
  ENGH::Math::Quat rotation;
  ENGH::Math::Vec3 scale;

  ENGH::Math::Mat4 ToMatrix() const;

};

}
