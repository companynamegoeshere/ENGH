#pragma once

#include <core/data_types.hpp>
#include <mathfu/glsl_mappings.h>

namespace ENGH {

namespace Math {

using Vec3 = mathfu::vec3;
using Vec3i = mathfu::vec3i;

using Quat = mathfu::quat;

using Mat4 = mathfu::mat4;

const Vec3 VEC3_ZERO = Vec3(0, 0, 0);
const Vec3 VEC3_ONE = Vec3(1, 1, 1);
const Vec3 VEC3_RIGHT = Vec3(1, 0, 0);
const Vec3 VEC3_UP = Vec3(0, 1, 0);
const Vec3 VEC3_FORWARD = Vec3(0, 0, 1);

constexpr double PI = 3.14159265358979323846;
constexpr double PI2 = PI * 2;
constexpr double HALF_PI = PI / 2;

constexpr double DEGtoRAD = PI / 180;
constexpr double RADtoDEG = 180 / PI;

}

namespace Mathf {

constexpr float PI = 3.14159265358979323846;
constexpr float PI2 = PI * 2;
constexpr float HALF_PI = PI / 2;

constexpr float DEGtoRAD = PI / 180;
constexpr float RADtoDEG = 180 / PI;

}

}
