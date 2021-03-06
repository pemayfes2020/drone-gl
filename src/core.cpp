#define GL_SILENCE_DEPRECATION

#include "graphic/graphic.hpp"
#include "object_list.hpp"

#include <GL/glut.h>

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/LU>

#include <cmath>
#include <iostream>

namespace Graphic
{

using namespace Eigen;

static callback_type user_callback;
static int window_height = 600;
static int window_width = 600;

static double cam_dist = 4000.0;
static double cam_theta = M_PI / 4.0;
static double cam_phi = M_PI / 5.0;

Vector3d cam;
Vector3d cam_target{0.0, 0.0, 0.0};
Vector3d cam_top;

static Color bg_color{0.0, 0.0, 0.0};

void setWindowSize(int height, int width)
{
    window_height = height;
    window_width = width;
    glutReshapeWindow(width, height);
}

void setCameraTarget(const Eigen::Vector3d& target_pos)
{
    cam_target = target_pos;
}

void setBGColor(Color color)
{
    bg_color = color;
}

void updateCameraPos()
{
    Vector3d cam_dir
        = -cam_dist
          * Vector3d{
                std::cos(cam_theta) * std::cos(cam_phi),
                std::sin(cam_theta) * std::cos(cam_phi),
                std::sin(cam_phi)};
    cam = cam_target - cam_dir;

    double norm = cam_dir.norm();
    double t = cam_dir(2) / (cam_dir(2) - norm * norm);

    cam_top = t * cam_dir + (1 - t) * Vector3d{0.0, 0.0, 1.0};
    if (cam_top(2) < 0) {
        cam_top *= -1.0;
    }
}

void lookat()
{
    gluLookAt(
        cam(0), cam(1), cam(2),
        cam_target(0), cam_target(1), cam_target(2),
        cam_top(0), cam_top(1), cam_top(2));
}

void drawCoordinate(int measure, double size)
{
    const auto drawLine = [](const Vector3d& from, const Vector3d& to) {
        //線幅
        glLineWidth(1.0);
        //線
        glBegin(GL_LINES);
        glVertex3d(from(0), from(1), from(2));
        glVertex3d(to(0), to(1), to(2));
        glEnd();
    };

    glDisable(GL_LIGHTING);
    // xy平面
    glColor4d(0.5, 0.5, 0.5, 0.5);
    for (int x = 0; x <= measure; x++) {
        drawLine(
            {x * size - (size * measure / 2), -(size * measure / 2), 0},
            {x * size - (size * measure / 2), measure * size - (size * measure / 2), 0});
    }
    for (int y = 0; y <= measure; y++) {
        drawLine(
            {-(size * measure / 2), y * size - (size * measure / 2), 0},
            {measure * size - (size * measure / 2), y * size - (size * measure / 2), 0});
    }

    glDisable(GL_DEPTH_TEST);
    Vector3d origin{0, 0, 0};
    // x(Red)
    glColor4f(1.0, 0.0, 0.0, 1.0);
    drawLine(origin, {(measure / 2 + 2) * size, 0, 0});
    // y(Green)
    glColor4f(0.0, 1.0, 0.0, 1.0);
    drawLine(origin, {0, (measure / 2 + 2) * size, 0});
    // z(Blue)
    glColor4f(0.0, 0.0, 1.0, 1.0);
    drawLine(origin, {0, 0, (measure / 2 + 2) * size});

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

static void display(void)
{
    glClearColor(bg_color(0), bg_color(1), bg_color(2), 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);

    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, (double)window_width / window_height, 1.0, 10000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  // 行列を初期化
    updateCameraPos();
    lookat();
    glPopMatrix();

    drawCoordinate(20, 1000);

    for (auto& obj : objects) {
        glColor3d(obj.color(0), obj.color(1), obj.color(2));
        obj.shape->start_draw(obj.pos, obj.rot);
        obj.shape->draw();
        obj.shape->end_draw();
    }

    glutSwapBuffers();
}

static void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    window_width = w;
    window_height = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120.0, (double)window_width / window_height, 1.0, 10000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  // 行列を初期化

    lookat();
}

static void idle()
{
    user_callback();
    glutPostRedisplay();
}

namespace Mouse
{

bool left_button_down = false;
bool right_button_down = false;
bool h_down = false;
Vector2d pos{0, 0};
double theta_ratio = M_PI * 3.0;
double phi_ratio = M_PI * 1.0;
double dist_ratio = 3000.0;

void mouse(int button, int state, int x, int y)
{
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) {
            left_button_down = true;
            pos = Vector2d{x, y};
        } else if (state == GLUT_UP) {
            left_button_down = false;
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN) {
            right_button_down = true;
            pos = Vector2d{x, y};
        } else if (state == GLUT_UP) {
            right_button_down = false;
        }
        break;
    }
}

static void motion(int x, int y)
{
    Vector2d pos_new = Vector2d{x, y};

    if (!left_button_down && !right_button_down) {
        pos = pos_new;
        return;
    }

    if (right_button_down) {
        // zoom mode
        cam_dist += (pos_new(1) - pos(1)) / window_height * dist_ratio;
    } else {
        // rotate mode
        cam_theta -= (pos_new(0) - pos(0)) / window_width * theta_ratio;
        cam_phi += (pos_new(1) - pos(1)) / window_height * phi_ratio;
    }
    pos = pos_new;

    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120.0, (double)window_width / window_height, 1.0, 10000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  // 行列を初期化

    updateCameraPos();

    lookat();

    glPopMatrix();

    glutPostRedisplay();
}

void key(unsigned char key, int x, int y)
{
    if (key == 'h') {
        cam_theta = M_PI / 4.0;
        cam_phi = M_PI / 5.0;
        updateCameraPos();

        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(120.0, (double)window_width / window_height, 1.0, 10000.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();  // 行列を初期化

        lookat();

        glPopMatrix();

        glutPostRedisplay();
    }
}

}  // namespace Mouse


void init(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMouseFunc(Mouse::mouse);
    glutMotionFunc(Mouse::motion);
    glutKeyboardFunc(Mouse::key);

    updateCameraPos();

    // 3D settings
    GLfloat light_position[] = {20.0f, 200.0f, 800.0f, 0.0f};

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void start(callback_type callback)
{
    user_callback = callback;
    glutMainLoop();
}

void setPosition(ObjectId id, const Eigen::Vector3d& pos)
{
    if (id >= objects.size()) {
        std::cerr << "Invalid Object Id was specified." << std::endl;
        return;
    }
    objects[id].pos = pos;
}
void setRotation(ObjectId id, const Eigen::Vector3d& rot)
{
    if (id >= objects.size()) {
        std::cerr << "Invalid Object Id was specified." << std::endl;
        return;
    }
    objects[id].rot = rot;
}

}  // namespace Graphic
