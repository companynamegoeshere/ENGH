
#include <render/camera/camera.hpp>

using ENGH::Render::Camera::Camera;
using namespace ENGH::Math;

Camera::Camera() :
    position(0.0f, 0.0f, 0.0f),
    rotation(Quat::identity) {}

Mat4 Camera::GetView() {
  return Mat4::FromRotationMatrix(rotation.Inverse().ToMatrix()) * Mat4::FromTranslationVector(position);
}

Camera::~Camera() = default;

