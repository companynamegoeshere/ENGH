#pragma once

#include <eobject/data/model_3d.hpp>

namespace ENGH::Util::File::Model {

bool parseObj(
    std::istream& fInput,
    EObject::Data::Model3D &model
);

}
