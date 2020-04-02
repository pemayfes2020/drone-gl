#pragma once

#include "graphic/impl/stl.hpp"

#include <Eigen/Core>

using Color = Eigen::Vector3f;

namespace Shape
{

struct ShapeBase {

    ShapeBase() {}

    virtual void draw() const = 0;
    void start_draw(
        const Eigen::Vector3f& position,
        const Eigen::Vector3f& rotation);
    void end_draw();
};

struct Teapot : public ShapeBase {
    int size;

    Teapot(int size) : size(size) {}

    virtual void draw() const override;
};

struct Sphere : public ShapeBase {
    float radius;

    Sphere(float radius) : radius(radius) {}
    virtual void draw() const override;
};

struct Plane : public ShapeBase {
    float height;
    float width;

    Plane(float height, float width)
        : height(height), width(width) {}
    virtual void draw() const override;
};


struct Rectangular : public ShapeBase {
    Eigen::Vector3f size;

    Rectangular(const Eigen::Vector3f& size) : size(size) {}
    virtual void draw() const override;
};

struct Cylinder : public ShapeBase {
    float radius;
    float height;

    Cylinder(const float radius, const float height)
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
