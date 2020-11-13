#include <eobject/data/model_3d.hpp>

void ENGH::EObject::Data::Model3D::ClearData() {
  name.clear();
  vertexData.Clear();
  index.Clear();
}
