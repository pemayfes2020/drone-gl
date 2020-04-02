#pragma once

#include "graphic/color.hpp"
#include "graphic/impl/shape.hpp"
#include "graphic/object.hpp"

#include <Eigen/Core>

#include <memory>
#include <vector>


namespace Graphic
{

void init(int argc, char** argv);
void start(void (*callback)(std::vector<Object>&));

void rotateCamera(const Eigen::Vector3d& rotation);

void setWindowSize(int height, int width);
void setBGColor(Color color);

}  // namespace Graphic
