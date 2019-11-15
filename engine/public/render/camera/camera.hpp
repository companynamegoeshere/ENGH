#pragma once

#include <core/math.hpp>

namespace ENGH::Render::Camera {

class Camera {
public:
  Math::Vec3 position;
  Math::Quat rotation;

  Camera();

  virtual Math::Mat4 GetView();

  virtual Math::Mat4 GetProjection() = 0;

  virtual ~Camera() = 0;
};

}
