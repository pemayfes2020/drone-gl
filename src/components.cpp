#include "graphic/components.hpp"
#include "graphic/impl/object_list.hpp"


namespace Graphic
{

using namespace Eigen;

Object& addSphere(const Vector3d& position, const Vector3d& rotation, double radius, Color color)
{
    objects.push_back(
        Object{color, position, rotation,
            std::make_shared<Shape::Sphere>(radius)});
    return objects.back();
}

Object& addPlane(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, double height, double width, Color color)
{
    objects.push_back(
        Object{color, position, rotation,
            std::make_shared<Shape::Plane>(height, width)});
    return objects.back();
}


Object& addRectangular(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, const Eigen::Vector3d& size, Color color)
{
    objects.push_back(
        Object{color, position, rotation,
            std::make_shared<Shape::Rectangular>(size)});
    return objects.back();
}

Object& addCylinder(const Eigen::Vector3d& position, const Eigen::Vector3d& rotation, double radius, double height, Color color)
{

    objects.push_back(
        Object{color, position, rotation,
            std::make_shared<Shape::Cylinder>(radius, height)});
    return objects.back();
}

Object& addTeapot(const Vector3d& position, const Vector3d& rotation, int size, Color color)
{
    objects.push_back(
        Object{color, position, rotation,
            std::make_shared<Shape::Teapot>(size)});
    return objects.back();
}

Object& addSTLModel(const Vector3d& position, const Vector3d& rotation, const std::string filepath, bool colored, Color color)
{
    if (colored) {
        objects.push_back(
            Object{color, position, rotation,
                std::make_shared<Shape::ColoredSTLModel>(filepath)});
    } else {
        objects.push_back(
            Object{color, position, rotation,
                std::make_shared<Shape::STLModel>(filepath)});
    }
    return objects.back();
}

}  // namespace Graphic
