#include <eobject/data/transform.hpp>

using namespace ENGH::Math;

ENGH::EObject::Data::Transform::Transform() :
    position(0.0f, 0.0f, 0.0f),
    rotation(Quat::identity),
    scale(1.0f, 1.0f, 1.0f) {
}

Mat4 ENGH::EObject::Data::Transform::ToMatrix() const {
  return Mat4::FromTranslationVector(position) * rotation.ToMatrix4() * Mat4::FromScaleVector(scale);
}
