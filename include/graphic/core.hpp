#pragma once

#include "graphic/color.hpp"
#include "graphic/impl/shape.hpp"
#include "graphic/object.hpp"

#include <Eigen/Core>

#include <memory>
#include <vector>


namespace Graphic
{

using callback_type = std::function<void(void)>;

void init(int argc, char** argv);
void start(callback_type callback);

void setCameraTarget(const Eigen::Vector3d& target_pos);

void setWindowSize(int height, int width);
void setBGColor(Color color);

void setPosition(ObjectId id, const Eigen::Vector3d& pos);
void setRotation(ObjectId id, const Eigen::Vector3d& rot);


}  // namespace Graphic
