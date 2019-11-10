#pragma once

#include <core/math.hpp>

using ENGH::Math::Vec3;

namespace ENGH::EObject::Data {

class Transform {
  Vec3 lastPosition;
  Vec3 lastRotation;
  Vec3 lastScale;
public:
  Vec3 position;
  Vec3 rotation; // TODO Update to quaternion
  Vec3 scale;

};

}
