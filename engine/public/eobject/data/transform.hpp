#pragma once

#include <core/math.hpp>

namespace ENGH::EObject::Data {

class Transform {
public:
  Transform();

  Math::Vec3 position;
  Math::Quat rotation;
  Math::Vec3 scale;

  inline Math::Mat4 ToMatrix() const {
    return Math::Mat4::Transform(position, rotation.ToMatrix(), scale);
  }

  inline Math::Vec3 GetRightVector() const {
    return rotation * Math::VEC3_RIGHT;
  }

  inline Math::Vec3 GetForwardVector() const {
    return rotation * Math::VEC3_FORWARD;
  }

};

}
