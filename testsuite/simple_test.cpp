#include "graphic/graphic.hpp"

#include <vector>

void callback()
{
}

int main(int argc, char** argv)
{
    Graphic::init(argc, argv);

    Graphic::setWindowSize(800, 800);
    Graphic::setBGColor(Color{0.2, 0.2, 0.2});

    Graphic::start(callback);

    return 0;
}
