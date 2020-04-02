#pragma once

#include "graphic/color.hpp"

#include "graphic/impl/stl.hpp"

#include <Eigen/Core>

namespace Shape
{

struct ShapeBase {

    ShapeBase() {}

    virtual void draw() const = 0;
    void start_draw(
        const Eigen::Vector3d& position,
        const Eigen::Vector3d& rotation);
    void end_draw();
};

struct Teapot : public ShapeBase {
    int size;

    Teapot(int size) : size(size) {}

    virtual void draw() const override;
};

struct Sphere : public ShapeBase {
    double radius;

    Sphere(double radius) : radius(radius) {}
    virtual void draw() const override;
};

struct Plane : public ShapeBase {
    double height;
    double width;

    Plane(double height, double width)
        : height(height), width(width) {}
    virtual void draw() const override;
};


struct Rectangular : public ShapeBase {
    Eigen::Vector3d size;

    Rectangular(const Eigen::Vector3d& size) : size(size) {}
    virtual void draw() const override;
};

struct Cylinder : public ShapeBase {
    double radius;
    double height;

    Cylinder(const double radius, const double height)
        : radius(radius), height(height) {}

    virtual void draw() const override;
};

struct STLModel : public ShapeBase {
    STL::Binary data;

    STLModel(const std::string filepath) : data(filepath) {}
    virtual void draw() const override;
};

struct ColoredSTLModel : public ShapeBase {
    STL::ColorBinary data;

    ColoredSTLModel(const std::string filepath)
        : data(filepath) {}
    virtual void draw() const override;
};


}  // namespace Shape
