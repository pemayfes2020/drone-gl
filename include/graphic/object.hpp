#pragma once

#include <memory>

#include <Eigen/Core>

#include "graphic/color.hpp"
#include "graphic/impl/shape.hpp"

namespace Graphic
{

struct Object {
    Color color;
    Eigen::Vector3d pos;
    Eigen::Vector3d rot;
    std::shared_ptr<Shape::ShapeBase> shape;
};

}  // namespace Graphic
