#pragma once

#include <core/math.hpp>

using ENGH::Math::Matrix4;
using ENGH::Math::Quat;
using ENGH::Math::Vec3;

namespace ENGH::EObject::Data {

class Transform {
public:
  Vec3 position;
  Quat rotation;
  Vec3 scale;

  Matrix4 ToMatrix() {
//    return position * rotation * scale * Matrix4().setIdentity();
  }

};

}
