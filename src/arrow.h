#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
  private:
    VAO *object;
};

class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y , float h);
    glm::vec3 position;
    float height;
    void draw(glm::mat4 VP);
private:
    VAO *object;
    VAO *top;
};

#endif // ARROW_H
