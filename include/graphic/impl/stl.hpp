#pragma once

#include "graphic/color.hpp"

#include <Eigen/Core>

namespace STL
{

struct Polygon {
    Eigen::Vector3f normal;
    Eigen::Vector3f r1;
    Eigen::Vector3f r2;
    Eigen::Vector3f r3;
};

struct ColoredPolygon {
    Eigen::Vector3f normal;
    Eigen::Vector3f r1;
    Eigen::Vector3f r2;
    Eigen::Vector3f r3;
    bool unique;
    Color color;
};

}  // namespace STL

#include "graphic/impl/stl/binary.hpp"
#include "graphic/impl/stl/color.hpp"
