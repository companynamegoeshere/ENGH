#pragma once

#include <core/data_types.hpp>
#include <Eigen3.hpp>

namespace ENGH::Math {

using Vec3 = Eigen::Vector3<float>;
using Vec3i = Eigen::Vector3<int32>;

using Quat = Eigen::Quaternionf;

using Matrix4 = Eigen::Matrix4<float>;
using MatrixX = Eigen::MatrixXf;

}
