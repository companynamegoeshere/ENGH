#include <eobject/data/transform.hpp>

namespace ENGH::EObject::Data {

Transform::Transform() :
    position(0.0f, 0.0f, 0.0f),
    rotation(Math::Quat::identity),
    scale(1.0f, 1.0f, 1.0f) {}

}
