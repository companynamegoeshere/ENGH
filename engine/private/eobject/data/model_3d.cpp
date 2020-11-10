#include <eobject/data/model_3d.hpp>

void ENGH::EObject::Data::Model3D::clearData() {
  vertex.Clear();
  uvCoords.Clear();
  normals.Clear();
  index.Clear();
}
