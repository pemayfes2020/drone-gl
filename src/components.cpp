#include "graphic/components.hpp"
#include "graphic/impl/object_list.hpp"


namespace Graphic
{

using namespace Eigen;

Object& addSphere(const Vector3d& position, const Vector3d& rotation, double radius, Color color)
{
    return objects.emplace_back(
        Object{color, position, rotation,
            std::make_shared<Shape::Sphere>(radius)});
}

Object& addPlane(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, double height, double width, Color color)
{
    return objects.emplace_back(
        Object{color, position, rotation,
            std::make_shared<Shape::Plane>(height, width)});
}


Object& addRectangular(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, const Eigen::Vector3d& size, Color color)
{
    return objects.emplace_back(
        Object{color, position, rotation,
            std::make_shared<Shape::Rectangular>(size)});
}

Object& addCylinder(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, double radius, double height, Color color)
{

    return objects.emplace_back(
        Object{color, position, rotation,
            std::make_shared<Shape::Cylinder>(radius, height)});
}

Object& addTeapot(const Vector3d& position, const Vector3d& rotation, int size, Color color)
{
    return objects.emplace_back(
        Object{color, position, rotation,
            std::make_shared<Shape::Teapot>(size)});
}

Object& addSTLModel(const Vector3d& position, const Vector3d& rotation, const std::string filepath, bool colored, Color color)
{
    if (colored) {
        return objects.emplace_back(
            Object{color, position, rotation,
                std::make_shared<Shape::ColoredSTLModel>(filepath)});
    } else {
        return objects.emplace_back(
            Object{color, position, rotation,
                std::make_shared<Shape::STLModel>(filepath)});
    }
}

}  // namespace Graphic
