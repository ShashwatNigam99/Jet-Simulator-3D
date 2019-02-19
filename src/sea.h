#include "main.h"

#ifndef SEA_H
#define SEA_H


class Sea {
public:
    Sea() {}
    Sea(float x, float y);
    glm::vec3 position;
    void draw(glm::mat4 VP);

private:
    VAO *object;
};

class Land {
public:
    Land() {}
    Land(float x, float y,float rot);
    glm::vec3 position;
    float rotation;
    float height;
    void draw(glm::mat4 VP);

private:
    VAO *object;
    VAO *sand;
};

#endif // SEA_H
