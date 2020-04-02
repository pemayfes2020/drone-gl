#define GL_SILENCE_DEPRECATION
#pragma push
#pragma GCC diagnostic ignored "-Wnarrowing"

#include "graphic/impl/shape.hpp"
#include "graphic/impl/stl.hpp"

#include <Eigen/Core>
#include <GL/glut.h>

#include <cmath>
#include <iostream>

namespace Shape
{

using namespace Eigen;

static double rad2deg(double rad)
{
    return rad / M_PI * 180.0;
}

inline namespace Wrapper
{
static inline void vertex3d(const Vector3d& pos)
{
    glVertex3d(pos(0), pos(1), pos(2));
}
static inline void normal3d(const Vector3d& vec)
{
    glNormal3d(vec(0), vec(1), vec(2));
}
static inline void color3d(const Color& color)
{
    glColor3d(color(0), color(1), color(2));
}

}  // namespace Wrapper

void ShapeBase::start_draw(
    const Eigen::Vector3d& position,
    const Eigen::Vector3d& rotation)
{
    glPushMatrix();

    glMatrixMode(GL_MODELVIEW);

    glTranslatef(position(0), position(1), position(2));

    glRotatef(rad2deg(rotation(0)), 1.0, 0.0, 0.0);
    glRotatef(rad2deg(rotation(1)), 0.0, 1.0, 0.0);
    glRotatef(rad2deg(rotation(2)), 0.0, 0.0, 1.0);
}

void ShapeBase::end_draw()
{
    glPopMatrix();
}

void Teapot::draw() const
{
    glutSolidTeapot(size);
}

void Sphere::draw() const
{
    glutSolidSphere(radius, 20, 20);
}

void Plane::draw() const
{
    double hei = height / 2.0;
    double wid = width / 2.0;
    glBegin(GL_QUADS);


    glNormal3d(0.0, 0.0, 1.0);
    glVertex3d(-hei, -wid, 0);
    glVertex3d(hei, -wid, 0);
    glVertex3d(hei, wid, 0);
    glVertex3d(-hei, wid, 0);

    glEnd();
}

void Rectangular::draw() const
{
    double offset[] = {size(0) / 2., size(1) / 2., size(2) / 2.};

    glBegin(GL_QUADS);
    //前
    glNormal3d(0.0, 0.0, -1.0);
    glVertex3d(offset[0], offset[1], offset[2]);
    glVertex3d(-offset[0], offset[1], offset[2]);
    glVertex3d(-offset[0], -offset[1], offset[2]);
    glVertex3d(offset[0], -offset[1], offset[2]);

    //左
    glNormal3d(1.0, 0.0, 0.0);
    glVertex3d(offset[0], offset[1], offset[2]);
    glVertex3d(offset[0], offset[1], -offset[2]);
    glVertex3d(offset[0], -offset[1], -offset[2]);
    glVertex3d(offset[0], -offset[1], offset[2]);

    //右
    glNormal3d(-1.0, 0.0, 0.0);
    glVertex3d(-offset[0], offset[1], -offset[2]);
    glVertex3d(-offset[0], offset[1], offset[2]);
    glVertex3d(-offset[0], -offset[1], offset[2]);
    glVertex3d(-offset[0], -offset[1], -offset[2]);

    //後
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3d(offset[0], offset[1], -offset[2]);
    glVertex3d(-offset[0], offset[1], -offset[2]);
    glVertex3d(-offset[0], -offset[1], -offset[2]);
    glVertex3d(offset[0], -offset[1], -offset[2]);

    //上
    glNormal3d(0.0, 1.0, 0.0);
    glVertex3d(offset[0], offset[1], offset[2]);
    glVertex3d(-offset[0], offset[1], offset[2]);
    glVertex3d(-offset[0], offset[1], -offset[2]);
    glVertex3d(offset[0], offset[1], -offset[2]);

    //下
    glNormal3d(0.0, -1.0, 0.0);
    glVertex3d(offset[0], -offset[1], offset[2]);
    glVertex3d(-offset[0], -offset[1], offset[2]);
    glVertex3d(-offset[0], -offset[1], -offset[2]);
    glVertex3d(offset[0], -offset[1], -offset[2]);
    glEnd();
}

void Cylinder::draw() const
{
    constexpr int division = 32;
    double dth = 2 * M_PI / division;
    const Vector3d z_offset = {0, 0, height * 0.5};

    // 側面
    glBegin(GL_QUADS);
    for (double theta = 0; theta < 2 * M_PI; theta += dth) {
        Vector3d v0{cos(theta), sin(theta), 0};
        Vector3d v1{cos(theta + dth), sin(theta + dth), 0};
        normal3d(0.5 * (v0 + v1));
        vertex3d(100.0 * v0 - z_offset);
        vertex3d(100.0 * v0 + z_offset);
        vertex3d(100.0 * v1 + z_offset);
        vertex3d(100.0 * v1 - z_offset);
    }
    glEnd();

    // 底面
    for (auto& top : {1, -1}) {
        glBegin(GL_TRIANGLES);
        for (double theta = 0; theta < 2 * M_PI; theta += dth) {
            Vector3d v[2] = {
                {cos(theta), sin(theta), 0},
                {cos(theta + dth), sin(theta + dth), 0}};
            glNormal3d(0, 0, 2 * (top - 0.5));
            vertex3d(100.0 * v[top == 1 ? 0 : 1] + top * z_offset);
            vertex3d(100.0 * v[top == 1 ? 1 : 0] + top * z_offset);
            vertex3d(top * z_offset);
        }
        glEnd();
    }
}

void STLModel::draw() const
{
    glBegin(GL_TRIANGLES);
    for (auto polygon : data.polygons) {
        normal3d(polygon.normal);
        vertex3d(polygon.r1);
        vertex3d(polygon.r2);
        vertex3d(polygon.r3);
    }
    glEnd();
}

void ColoredSTLModel::draw() const
{
    // Uniqueなメッシュだけ色を付けて、終わったら戻す
    // 毎周期色をつけるよりColorSTLの思想に合う
    glBegin(GL_TRIANGLES);
    for (auto polygon : data.polygons) {
        if (polygon.unique) {
            // set unique color
            color3d(polygon.color);
        }

        normal3d(polygon.normal);
        vertex3d(polygon.r1);
        vertex3d(polygon.r2);
        vertex3d(polygon.r3);

        if (polygon.unique) {
            // unset unique color
            color3d(data.overall);
        }
    }
    glEnd();
}

}  // namespace Shape

#pragma pop

