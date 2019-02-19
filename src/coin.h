#include "main.h"

#ifndef COIN_H
#define COIN_H


class Coin {
public:
    Coin() {}
    Coin(float x, float y, color_t color,int special);
    glm::vec3 position;
    float rotation;
    int special;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);

    void tick();
    bounding_box_t return_box();

private:
    VAO *object;
};

class Fuelup {
public:
    Fuelup() {}
    Fuelup(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);

    void tick();

private:
    VAO *object;
    VAO *structure;

};

class Bullet {
public:
    Bullet() {}
    Bullet(float x, float y, float z, float a, float b);
    glm::vec3 position;
    float rotation;
    float norm_x;
    float norm_y;
    float norm_z;
    void draw(glm::mat4 VP);

    void tick();
    bounding_box_t return_box();

private:
    VAO *object;
};

#endif // COIN_H
