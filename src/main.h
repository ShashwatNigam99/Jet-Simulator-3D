#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <pthread.h>
#include <ao/ao.h>
#include <mpg123.h>

struct color_t {
    int r;
    int g;
    int b;
};

// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
void       draw3DObject(struct VAO *vao);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void mouseuse(GLFWwindow *window,int fbwidth, int fbheight,float* eye_x, float* eye_y,float *eye_z,float a,float b, float c);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);
void* play_audio(void *ptr);

// Types
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int    NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint    MatrixID;
};

extern GLMatrices Matrices;

// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

struct bounding_box_t {
    float x;
    float y;
    float width;
    float height;
};

bool detect_collision(bounding_box_t a, bounding_box_t b);
bool detect_passthrough(float x,float y,float z);
bool detect_para_shoot(float a,float b,float c ,float x,float y,float z);
bool detect_volcano(float a,float b,float c ,float x,float y,float z);
bool detect_islands(float a,float b,float c ,float x,float y,float z);
bool detect_fuelup(float a,float b,float c ,float x,float y,float z);
bool detect_vicinity(float a,float b,float x,float y);
bool detect_cannon(float a,float b,float c,float x,float y);
bool detect_bullet(float a,float b,float c);

extern float screen_zoom, screen_center_x, screen_center_y;
extern bool clk,rclk,pause;
extern float MAX_X,MAX_Y,MIN_X,MIN_Y,MAX_ALTITUDE;
extern float HELI_PHI,HELI_THETA,HELI_R;
extern int view;

void reset_screen();

// ---- Colors ----
extern const color_t COLOR_RED;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_LAWNGREEN;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_BLUE;
extern const color_t COLOR_BROWN;
extern const color_t COLOR_ORANGE;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_GOLD ;
extern const color_t COLOR_RUBY;
extern const color_t COLOR_DARKGREEN;
extern const color_t COLOR_SKYBLUE;
extern const color_t COLOR_WHITE;
extern const color_t COLOR_PURPLE;
extern const color_t COLOR_PINK;
extern const color_t COLOR_GRAY;
extern const color_t COLOR_SAND;


#endif
