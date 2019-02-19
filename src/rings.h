#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y, float z, float rot, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);

    void tick();
    bounding_box_t return_box();

private:
    VAO *object;
};

class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);

    void tick();
    bounding_box_t return_box();

private:
    VAO *object;
};

class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);

    void tick();
    bounding_box_t return_box();

private:
    VAO *object;
    VAO *top;
};


#endif // RING_H
