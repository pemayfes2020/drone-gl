#pragma once

#include <memory>

#include <Eigen/Core>

#include "graphic/color.hpp"
#include "graphic/impl/shape.hpp"

namespace Graphic
{

struct Object {
    Color color;
    Eigen::Vector3f pos;
    Eigen::Vector3f rot;
    std::shared_ptr<Shape::ShapeBase> shape;
};

}  // namespace Graphic
