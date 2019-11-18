#include <render/camera/perspective_camera.hpp>

using ENGH::Render::Camera::PerspectiveCamera;
using namespace ENGH::Math;

Mat4 PerspectiveCamera::GetProjection() {
  return Mat4::Perspective(fov, aspect, znear, zfar);
}
