#include "main.h"
#include "timer.h"
#include "ball.h"
#include "sea.h"
#include "coin.h"
#include "rings.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
GLuint textureID;


/**************************
* Customizable functions *
**************************/

Ball ball;
Sea sea;
vector<Coin> coins;
Ring ring;
vector<Missile> missiles;
vector<Bomb> bombs;
vector<Ring> rings;
vector<Ring> comp_rings;

float screen_zoom = 1.0, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
bool clk = false,rclk = false;

float eyex,eyey,eyez;
float targetx,targety,targetz;

int view = 3;
int MISSILE_TIMER=0;
int BOMB_TIMER=0;

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
    eyex = targetx;
    eyey = targety-5;
    eyez = targetz + 30;
    break;

    case 3:
    // camera_rotation_angle = 90;
    targetx = ball.position.x;
    targety = ball.position.y;
    targetz = ball.position.z;
    eyex = 1;
    eyey = 1;
    eyez = 30;
    break;

    case 4:
    // camera_rotation_angle = 90;
    targetx = ball.position.x + 100*sin((180-ball.turn) * M_PI / 180.0f);
    targety = ball.position.y + 100*cos((ball.turn-180) * M_PI / 180.0f);
    targetz = ball.position.z;
    // eyex = targetx + 15*cos(camera_rotation_angle*M_PI/180.0f);
    // eyey = targety - 15*sin(camera_rotation_angle*M_PI/180.0f);
    eyex = ball.position.x - 20*sin((180-ball.turn) * M_PI / 180.0f);
    eyey = ball.position.y - 20*cos((ball.turn-180) * M_PI / 180.0f);
    eyez = ball.position.z+20;
    break;

    case 5:
    // camera_rotation_angle = 90;
    targetx = ball.position.x ;
    targety = ball.position.y ;
    targetz = ball.position.z ;

    mouseuse(window,1000,1000,&eyex,&eyey);
    eyez=30;
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
    // ring.draw(VP);
    for(int i=0;i<coins.size();++i){
      coins[i].draw(VP);
    }
    for(int i=0;i<missiles.size();++i){
      missiles[i].draw(VP);
    }
    for(int i=0;i<bombs.size();++i){
      bombs[i].draw(VP);
    }
    for(int i=0;i<rings.size();++i){
      rings[i].draw(VP);
    }
    for(int i=0;i<comp_rings.size();++i){
      comp_rings[i].draw(VP);
    }
}

void tick_input(GLFWwindow *window) {

    int left1  = glfwGetKey(window, GLFW_KEY_LEFT);
    int left2  = glfwGetKey(window, GLFW_KEY_Q);

    int right1 = glfwGetKey(window, GLFW_KEY_RIGHT);
    int right2 = glfwGetKey(window, GLFW_KEY_E);

    int bankleft  = glfwGetKey(window, GLFW_KEY_A);
    int bankright = glfwGetKey(window, GLFW_KEY_D);

    int forward1 = glfwGetKey(window, GLFW_KEY_UP);
    int forward2 = glfwGetKey(window, GLFW_KEY_W);
    int backward = glfwGetKey(window, GLFW_KEY_DOWN);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int down = glfwGetKey(window, GLFW_KEY_S);

    int plane_view = glfwGetKey(window, GLFW_KEY_P);
    int top_view =  glfwGetKey(window, GLFW_KEY_T);
    int tower_view =  glfwGetKey(window, GLFW_KEY_Y);
    int follow_cam_view =  glfwGetKey(window, GLFW_KEY_F);
    int heli_cam_view =  glfwGetKey(window, GLFW_KEY_H);

    if(plane_view){
      view = 1;
    }
    else if(top_view){
      view = 2;
    }
    else if(tower_view){
      view = 3;
    }
    else if(follow_cam_view){
      view = 4;
    }
    else if(heli_cam_view){
      view = 5;
    }

/////////////////////////////
    if(right1 && forward1 || right2 && forward1 || right1 && forward2 || right2 && forward2 ){
      ball.right();
      ball.forward();
      ball.bankright();
      cout<<"RIGHT FORWARD!\n";
    }
    else if(left1 && forward1 || left2 && forward1 || left1 && forward2 || left2 && forward2){
      ball.left();
      ball.forward();
      ball.bankleft();
      cout<<"LEFT FORWARD!\n";
    }
    else if(right1 || right2){
      ball.right();
      // ball.bankright();
      cout<<"RIGHT!\n";
    }
    else if(left1 || left2){
      ball.left();
      // ball.bankleft();
      cout<<"LEFT!\n";
    }
    else if( (forward1 || forward2) && bankleft) {
      ball.forward();
      ball.banking--;
    }
    else if( (forward1 || forward2) && bankright) {
      ball.forward();
      ball.banking++;
    }
    else if(forward1 || forward2) {
        ball.forward();
        cout<<"FORWARD!\n";
        ball.bankcenter();
    }
    else if(bankleft){
      ball.banking--;
    }
    else if(bankright){
      ball.banking++;
    }
    else{
      ball.bankcenter();
    }

    if(backward){
      ball.backward();
    }

//////////////////////
    if(up){
      cout<<"UP!\n";
      ball.up();// jetpack thrust so put all velocity gained due to falling to zero
      if(ball.incline >= -30)
         ball.incline --;
    }
    else if(down){
      cout<<"DOWN!\n";
      ball.down();
      if(ball.incline <= 30)
         ball.incline ++;
    }
    else{
      // cout<<"NO INCLINE CHANGE\n";
      if(ball.incline<2 && ball.incline>-2)
        ball.incline = 0;
       if(ball.incline>1)
        ball.incline--;
      else if(ball.incline<1)
        ball.incline++;
    }
    /////////////////fire missiles
    if(clk==true && view!=5 && MISSILE_TIMER<=0){
       missiles.push_back(Missile(ball.position.x,ball.position.y,ball.position.z,ball.turn,ball.incline));
       MISSILE_TIMER+=50;
    }
    if(rclk==true && view!=5 && BOMB_TIMER<=0){
       bombs.push_back(Bomb(ball.position.x,ball.position.y,ball.position.z,ball.turn));
       BOMB_TIMER+=50;
    }
}

void tick_elements() {
    ball.tick();
    // mis.tick();
    ball.banking = ball.banking % 360;
    if(ball.banking<0){
      ball.banking+=360;
    }
    if(MISSILE_TIMER>0)
       MISSILE_TIMER--;
    for(int i=0;i<missiles.size();++i){
        if(missiles[i].position.x>(ball.position.x+500) || missiles[i].position.x<(ball.position.x-500)
        ||  missiles[i].position.y>(ball.position.y+500) || missiles[i].position.y<(ball.position.y-500))
        missiles.erase(missiles.begin()+i);
    }
    cout<<missiles.size()<<" chut \n";
     for(int i=0;i<missiles.size();++i){
       missiles[i].tick();
     }
     if(BOMB_TIMER>0)
        BOMB_TIMER--;
     for(int i=0;i<bombs.size();++i){
         if(bombs[i].position.z<=0)
         bombs.erase(bombs.begin()+i);
     }
     cout<<bombs.size()<<" boom \n";
      for(int i=0;i<bombs.size();++i){
        bombs[i].tick();
      }
  for(int i=0;i<rings.size();i++){
    if(detect_passthrough(rings[i].position.x,rings[i].position.y,rings[i].position.z,rings[i].rotation)){
      cout<<"whoah";
      rings.erase(rings.begin()+i);
      comp_rings.push_back(Ring(10,10,20,30,COLOR_GREEN));
    }
  }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball       = Ball(0, 0, COLOR_RED);
    // ball2       = Ball(-5,0, COLOR_GREEN);
    for(int i=0;i<1000;i++){
            coins.push_back(Coin(-200+rand()%400,-200+rand()%400,COLOR_GREEN,0));
    }
    // GLuint seaTextureID = createTexture("../images/sea.jpg");
     sea        = Sea( 0, 0);
     rings.push_back(Ring(10,10,20,30,COLOR_SKYBLUE));
     // mis   =  Missile(20,30,30);

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
            reshapeWindow (window, width, height);//added now

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
bool detect_passthrough(float x,float y,float z,float rot) {
  return ( (pow((ball.position.x - x),2)+pow((ball.position.y - y),2)+pow((ball.position.z - z),2)) < 64 );
}

void reset_screen() {

    Matrices.projection = glm::perspective(glm::radians(90.0), 1.0, 1.0, 500.0);
    // GLfloat fov = screen_zoom;
    // Matrices.projection = glm::perspective(fov, 1.0f, 1.0f, 500.0f);

}
