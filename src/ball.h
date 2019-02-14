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
    void bankright();
    void bankleft();
    void bankcenter();

    double speed;
    double upthrust;
    double downfall;
private:
    VAO *object;
    // VAO *structure;

};

#endif // BALL_H
