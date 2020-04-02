#pragma once

#include "graphic/color.hpp"
#include "graphic/core.hpp"
#include "graphic/impl/shape.hpp"
#include "graphic/object.hpp"

#include <Eigen/Core>

#include <memory>
#include <vector>


namespace Graphic
{

Object& addSphere(const Eigen::Vector3f& position, const Eigen::Vector3f& rotation, float radius, Color color);
Object& addPlane(const Eigen::Vector3f& position, const Eigen::Vector3f& rotation, float height, float width, Color color);
Object& addRectangular(const Eigen::Vector3f& position, const Eigen::Vector3f& rotation, const Eigen::Vector3f& size, Color color);
Object& addCylinder(const Eigen::Vector3f& position, const Eigen::Vector3f& rotation, float radius, float height, Color color);
Object& addTeapot(const Eigen::Vector3f& position, const Eigen::Vector3f& rotation, int size, Color color);
Object& addSTLModel(const Eigen::Vector3f& position, const Eigen::Vector3f& rotation, const std::string filepath, bool colored, Color color);

}  // namespace Graphic
