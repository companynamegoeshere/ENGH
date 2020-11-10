#pragma once

#include <core/data_types.hpp>
#include <core/math.hpp>
#include <util/array.hpp>

namespace ENGH::EObject::Data {

class Model3D {
public:
  Util::TArray<float> vertex;   // 3 float per vertex
  Util::TArray<float> uvCoords; // 2 float per vertex
  Util::TArray<float> normals;  // 3 float per vertex
  Util::TArray<uint32> index;

  void clearData();
};

}
