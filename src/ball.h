#include "main.h"

#ifndef BALL_H
#define BALL_H

class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float turn;
    int banking;
    float incline;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void up();
    void down();
    void right();
    void left();
    void forward();
    void backward();
    void bankright();
    void bankleft();
    void bankcenter();

    double speed;
    double upthrust;
    double downfall;
private:
    VAO *object;
};

class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z,float rot,float incline);
    glm::vec3 position;
    float rotation;
    float revolve;
    float incline;
        float speedx;    float speedy;    float speedz;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);

    void tick();
    bounding_box_t return_box();

private:
    VAO *object;
    VAO *structure;
};

class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z,float rot);
    glm::vec3 position;
    float speedz;
    float rotation;
    float revolve;
    void draw(glm::mat4 VP);
    void tick();
    bounding_box_t return_box();

private:
    VAO *object;
    VAO *structure;
};
#endif // BALL_H
