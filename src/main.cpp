#include "main.h"
#include "timer.h"
#include "ball.h"
#include "sea.h"
#include "coin.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
GLuint textureID;


/**************************
* Customizable functions *
**************************/

Ball ball;
// Ball ball2;
Sea sea;
vector<Coin> coins;


// Sea sea;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

float eyex,eyey,eyez;
float targetx,targety,targetz;

int view = 3;
// view 1 plane view
// view 2 top view
// view 3 tower view
// view 4 follow cam
// view 5 helicopter cam

void view_mapper(int view, float &eyex,float &eyey,float &eyez,float &targetx,float &targety,float &targetz){
  switch(view){
    case 1:
    eyex = ball.position.x;
    eyey = ball.position.y;
    eyez = ball.position.z+3;
    targetx = eyex + 50*sin((180-ball.turn) * M_PI / 180.0f);
    targety = eyey + 50*cos((ball.turn-180) * M_PI / 180.0f);
    targetz = ball.position.z;
    break;

    case 2:
    // camera_rotation_angle = 90;
    targetx = ball.position.x;
    targety = ball.position.y;
    targetz = ball.position.z;
    // eyex = targetx + 15*cos(camera_rotation_angle*M_PI/180.0f);
    // eyey = targety - 15*sin(camera_rotation_angle*M_PI/180.0f);
    eyex = targetx + 15;
    eyey = targety - 15;
    eyez = targetz + 30;
    break;

    case 3:
    // camera_rotation_angle = 90;
    targetx = ball.position.x;
    targety = ball.position.y;
    targetz = ball.position.z;
    // eyex = targetx + 15*cos(camera_rotation_angle*M_PI/180.0f);
    // eyey = targety - 15*sin(camera_rotation_angle*M_PI/180.0f);
    eyex = -30;
    eyey = -30;
    eyez = 40;
    break;
  }

}



Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    view_mapper(view,eyex, eyey, eyez,targetx, targety, targetz);
    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( eyex, eyey, eyez );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (targetx, targety, targetz);
    // glm::vec3 target (0,0,0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 0, 1);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball.draw(VP);
    // ball2.draw(VP);
    sea.draw(VP);
    for(int i=0;i<coins.size();++i){
      coins[i].draw(VP);
    }
}

void tick_input(GLFWwindow *window) {

    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int forward = glfwGetKey(window, GLFW_KEY_UP);

    int up = glfwGetKey(window, GLFW_KEY_W);
    int down = glfwGetKey(window, GLFW_KEY_S);

    int plane_view = glfwGetKey(window, GLFW_KEY_P);
    int top_view =  glfwGetKey(window, GLFW_KEY_T);
    int tower_view =  glfwGetKey(window, GLFW_KEY_Y);

    if(plane_view){
      view = 1;
    }
    if(top_view){
      view = 2;
    }
    if(tower_view){
      view = 3;
    }

    if(right && forward){
      ball.right();
      ball.forward();
      ball.bankright();
    }
    else if(left && forward){
      ball.left();
      ball.forward();
      ball.bankleft();
    }
    else if(right){
      ball.right();
      // ball.bankright();
      cout<<"RIGHT!\n";
    }
    else if(left){
      ball.left();
      // ball.bankleft();
      cout<<"LEFT!\n";
    }
    else if(forward) {
        ball.forward();
        cout<<"FORWARD!\n";
        ball.banking=0;
    }
    else{
      ball.banking=0;
    }


    if (up){
      cout<<"UP!\n";
      ball.up();// jetpack thrust so put all velocity gained due to falling to zero
      ball.incline = 30;
    }
    else if(down){
      cout<<"DOWN!\n";
      ball.down();
      ball.incline = -30;
    }
    else{
      ball.incline = 0;
    }
}

void tick_elements() {
    ball.tick();
    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball       = Ball(0, 0, COLOR_RED);
    // ball2       = Ball(-5,0, COLOR_GREEN);
    for(int i=0;i<1000;i++){
       // int p = (rand()%5==0)?1:0;
            coins.push_back(Coin(-100+rand()%200,-100+rand()%200,COLOR_GREEN,0));
    }
    // GLuint seaTextureID = createTexture("../images/sea.jpg");
    sea        = Sea( 0, 0);

    	// textureProgramID = LoadShaders( "TextureRender.vert", "TextureRender.frag" );
    	// Matrices.TexMatrixID = glGetUniformLocation(textureProgramID, "MVP");

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 10 / screen_zoom;
    float bottom = screen_center_y - 10 / screen_zoom;
    float left   = screen_center_x - 10 / screen_zoom;
    float right  = screen_center_x + 10 / screen_zoom;
    // Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::perspective(glm::radians(90.0), 1.0, 1.0, 500.0);

}