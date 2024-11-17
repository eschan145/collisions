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
    Object(Point pos, float dx, float dy) {
        this->position = pos;
        this->width = 15;
        this->height = 15;
        this->dx = dx;
        this->dy = dy;
    }

    void update() {
        this->position.x += dx;
        this->position.y += dy;
    }

    void bounce(int width, int height) {
        if (this->position.x <= 0 || this->position.x + width >= width) this->dx = -this->dx;
        if (this->position.y <= 0 || this->position.y + height >= height) this->dy = -this->dy;
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
