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

Object& addSphere(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, double radius, Color color);
Object& addPlane(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, double height, double width, Color color);
Object& addRectangular(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, const Eigen::Vector3d& size, Color color);
Object& addCylinder(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, double radius, double height, Color color);
Object& addTeapot(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, int size, Color color);
Object& addSTLModel(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, const std::string filepath, bool colored, Color color);

}  // namespace Graphic
