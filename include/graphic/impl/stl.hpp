#pragma once

#include "graphic/color.hpp"

#include <Eigen/Core>

namespace STL
{

struct Polygon {
    Eigen::Vector3d normal;
    Eigen::Vector3d r1;
    Eigen::Vector3d r2;
    Eigen::Vector3d r3;
};

struct ColoredPolygon {
    Eigen::Vector3d normal;
    Eigen::Vector3d r1;
    Eigen::Vector3d r2;
    Eigen::Vector3d r3;
    bool unique;
    Color color;
};

}  // namespace STL

#include "graphic/impl/stl/binary.hpp"
#include "graphic/impl/stl/color.hpp"
