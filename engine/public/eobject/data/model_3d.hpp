#pragma once

#include <core/data_types.hpp>
#include <core/math.hpp>
#include <util/array.hpp>

#include <string>

namespace ENGH::EObject::Data {

class Model3D {
public:

  std::string name;

  Util::TArray<float> vertexData;
  Util::TArray<uint32> index;

  void ClearData();
};

}
