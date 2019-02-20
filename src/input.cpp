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

#include "main.h"

bool   cannon_keyboard_input = true;
bool   drag_pan = false, old_cki;
double drag_oldx = -1, drag_oldy = -1;

using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
        // switch (key) {
        // case GLFW_KEY_C:
        // rectangle_rot_status = !rectangle_rot_status;
        // break;
        // case GLFW_KEY_P:
        // triangle_rot_status = !triangle_rot_status;
        // break;
        // case GLFW_KEY_X:
        //// do something ..
        // break;
        // default:
        // break;
        // }
    } else if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            quit(window);
            break;
        default:
            break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key) {
    switch (key) {
    // case 'Q':
    // case 'q':
    //     quit(window);
    //     break;
    default:
        break;
    }
}

/* Executed when a mouse button is pressed/released */
void mouseButton(GLFWwindow *window, int button, int action, int mods) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS) {
            clk = true;
            return;
        } else if (action == GLFW_RELEASE) {
          clk = false;
          return;
        }
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
          if (action == GLFW_PRESS) {
             rclk = true;
             return;
          }
          else if (action == GLFW_RELEASE) {
            rclk = false;
            return;
          }
          break;
    default:
        break;
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
      if(view==5){
          if(yoffset>0 && HELI_R<35){
            HELI_R+=1;
            cout<<"less!"<<HELI_R<<"\n";
          }
          else if(yoffset<0 && HELI_R >5){
            HELI_R-=1;
            cout<<"more!"<<HELI_R<<"\n";
          }
          reset_screen();
    }
}

float prev_xpos=0.0f,prev_ypos=0.0f;

void mouseuse(GLFWwindow *window,int fbwidth, int fbheight,float* eye_x, float* eye_y, float* eye_z,float a, float b, float c)
{
    double xpos,ypos;
    glfwGetCursorPos(window,&xpos,&ypos);
    xpos=(xpos/fbwidth)*20;
    ypos=(ypos/fbheight)*20;

    float dx=(float)xpos-prev_xpos;
    float dy=(float)ypos-prev_ypos;
    //cout<<clk;
    if(clk)
    {
        HELI_THETA+= dx;
        HELI_PHI+= dy;

        *eye_x = a + HELI_R * cos(HELI_THETA*M_PI/180.0f) * cos(HELI_PHI*M_PI/180.0f);
        *eye_y = b + HELI_R * sin(HELI_THETA*M_PI/180.0f) * cos(HELI_PHI*M_PI/180.0f);
        *eye_z = c +HELI_R * sin(HELI_PHI*M_PI/180.0f);
    }

    prev_xpos = xpos;
    prev_ypos = ypos;
}
