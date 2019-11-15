#pragma once

#include <render/camera/camera.hpp>

namespace ENGH::Render::Camera {

class PerspectiveCamera : public Camera {
  Math::Mat4 projection;
public:
  float aspect;
  float fov;
  float znear;
  float zfar;

  void UpdateProjectionMatrix();

  Math::Mat4 GetProjection() override;

};

}
