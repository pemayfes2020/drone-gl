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

ObjectId addSphere(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, double radius, Color color);
ObjectId addPlane(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, double height, double width, Color color);
ObjectId addRectangular(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, const Eigen::Vector3d& size, Color color);
ObjectId addCylinder(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, double radius, double height, Color color);
ObjectId addTeapot(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, int size, Color color);
ObjectId addSTLModel(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, const std::string filepath, bool colored, Color color);

}  // namespace Graphic
