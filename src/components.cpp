#include "graphic/components.hpp"
#include "object_list.hpp"

namespace Graphic
{

using namespace Eigen;

ObjectId addSphere(const Vector3d& position, const Vector3d& rotation, double radius, Color color)
{
    objects.emplace_back(
        Object{color, position, rotation,
            std::make_shared<Shape::Sphere>(radius)});
    return objects.size() - 1;
}

ObjectId addPlane(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, double height, double width, Color color)
{
    objects.emplace_back(
        Object{color, position, rotation,
            std::make_shared<Shape::Plane>(height, width)});
    return objects.size() - 1;
}


ObjectId addRectangular(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, const Eigen::Vector3d& size, Color color)
{
    objects.emplace_back(
        Object{color, position, rotation,
            std::make_shared<Shape::Rectangular>(size)});
    return objects.size() - 1;
}

ObjectId addCylinder(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, double radius, double height, Color color)
{

    objects.emplace_back(
        Object{color, position, rotation,
            std::make_shared<Shape::Cylinder>(radius, height)});
    return objects.size() - 1;
}

ObjectId addTeapot(const Vector3d& position, const Vector3d& rotation, int size, Color color)
{
    objects.emplace_back(
        Object{color, position, rotation,
            std::make_shared<Shape::Teapot>(size)});
    return objects.size() - 1;
}

ObjectId addSTLModel(const Vector3d& position, const Vector3d& rotation, const std::string filepath, bool colored, Color color)
{
    if (colored) {
        objects.emplace_back(
            Object{color, position, rotation,
                std::make_shared<Shape::ColoredSTLModel>(filepath)});
    } else {
        objects.emplace_back(
            Object{color, position, rotation,
                std::make_shared<Shape::STLModel>(filepath)});
    }
    return objects.size() - 1;
}

}  // namespace Graphic
