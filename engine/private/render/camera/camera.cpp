
#include <render/camera/camera.hpp>

using ENGH::Render::Camera::Camera;
using namespace ENGH::Math;

Camera::Camera() :
    position(0.0f, 0.0f, 0.0f),
    rotation(Quat::identity) {}

Mat4 Camera::GetView() {
  Vec3 pos = position;
  pos.x = -pos.x;
  return Mat4::FromRotationMatrix(rotation.ToMatrix()) * Mat4::FromTranslationVector(pos);
}

Camera::~Camera() {}

