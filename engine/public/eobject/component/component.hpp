#pragma once

#include <eobject/object.hpp>
#include <eobject/data/transform.hpp>

namespace ENGH::EObject {

class Component : EObject {

public:
  Data::Transform transform;

};

}
