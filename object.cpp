#include <windows.h>

struct Point {
    float x;
    float y;
};

class Object {
private:
    Point position;
    float width;
    float height;
    float dx;
    float dy;

public:
    Object(Point pos): {
        this->position = pos;
        this->width;
        this->height;
        this->dx = 15;
        this->dy = 15;
    }

    void update() {
        this->position.x += dx;
        this->position.y += dy;
    }

    void bounce(int width, int height) {
        if (x <= 0 || x + width >= width) dx = -dx;
        if (y <= 0 || y + height >= height) dy = -dy;
    }

    void draw(HDC hdc) const {
        Rectangle(
            hdc,
            this->position.x,
            this->position.y,
            this->position.x + width,
            this->position.y + height);
    }
};
