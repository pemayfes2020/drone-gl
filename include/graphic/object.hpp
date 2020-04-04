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

    void setPosition(Eigen::Vector3d _pos)
    {
        pos = _pos;
    }
    void setRotation(Eigen::Vector3d _rot)
    {
        rot = _rot;
    }

    Object(
        Color color,
        Eigen::Vector3d pos,
        Eigen::Vector3d rot,
        std::shared_ptr<Shape::ShapeBase> shape) : color(color), pos(pos), rot(rot), shape(shape)
    {
    }

    Object(const Object& obj) : color(obj.color), pos(obj.pos), rot(obj.rot), shape(obj.shape)
    {
    }

    Object(Object&& obj) : color(obj.color), pos(obj.pos), rot(obj.rot), shape(obj.shape)
    {
    }

    Object& operator=(const Object& obj) = default;
};

using ObjectId = unsigned int;

}  // namespace Graphic
