#include "main.h"
#include "timer.h"
#include "ball.h"
#include "sea.h"
#include "coin.h"
#include "rings.h"
#include "arrow.h"
#include "score.h"

using namespace std;

GLMatrices Matrices;
GLMatrices Matrices_dash;

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
vector<Parachute> parachutes;
vector<Fuelup> fuelups;
vector<Volcano> volcanoes;
vector<Land> lands;
vector<Cannon> cannons;
vector<Bullet> bullets;

Score display;
Score altitude;
Speedometer speed_frame;
Marker marker;
Fuel fuel_meter;
Ring next_check;

vector<Arrow> arrow;


long long int score = 123456;
float fuel = 100;

float screen_zoom = 1.0, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
bool clk = false,rclk = false;

float eyex,eyey,eyez;
float targetx,targety,targetz;

int view = 3;
int MISSILE_TIMER=0;
int BOMB_TIMER=0;
int ATTACK_TIMER=0;

float MAX_ALTITUDE = 150;
float MAX_X = 1000;
float MAX_Y = 1000;
float MIN_X = -1000;
float MIN_Y = -1000;


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
    targetx = ball.position.x;
    targety = ball.position.y;
    targetz = ball.position.z;
    eyex = targetx;
    eyey = targety-5;
    eyez = targetz + 30;
    break;

    case 3:
    targetx = ball.position.x;
    targety = ball.position.y;
    targetz = ball.position.z;
    eyex = 1;
    eyey = 1;
    eyez = 30;
    break;

    case 4:
    targetx = ball.position.x + 100*sin((180-ball.turn) * M_PI / 180.0f);
    targety = ball.position.y + 100*cos((ball.turn-180) * M_PI / 180.0f);
    targetz = ball.position.z;
    eyex = ball.position.x - 20*sin((180-ball.turn) * M_PI / 180.0f);
    eyey = ball.position.y - 20*cos((ball.turn-180) * M_PI / 180.0f);
    eyez = ball.position.z + 20;
    break;

    case 5:
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
    glm::vec3 eye_dash ( screen_center_x,screen_center_y,100 );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (targetx, targety, targetz);
    glm::vec3 target_dash (screen_center_x, screen_center_y, 0);
    // glm::vec3 target (0,0,0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 0, 1);
    glm::vec3 up_dash (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    Matrices_dash.view = glm::lookAt( eye_dash, target_dash, up_dash ); // Rotating Camera for 3D

    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP_dash = Matrices_dash.projection * Matrices_dash.view;
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball.draw(VP);
    sea.draw(VP);
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
    for(int i=0;i<parachutes.size();++i){
      parachutes[i].draw(VP);
    }
    for(int i=0;i<fuelups.size();++i){
      fuelups[i].draw(VP);
    }
    for(int i=0;i<volcanoes.size();++i){
      volcanoes[i].draw(VP);
    }
    for(int i=0;i<lands.size();++i){
      lands[i].draw(VP);
    }
    for(int i=0;i<cannons.size();++i){
      cannons[i].draw(VP);
    }
    for(int i=0;i<bullets.size();++i){
      bullets[i].draw(VP);
    }
    for(int i=0;i<arrow.size();++i){
      arrow[i].draw(VP);
    }


    display.draw(VP_dash);
    altitude.draw(VP_dash);
    speed_frame.draw(VP_dash);
    marker.draw(VP_dash);
    fuel_meter.draw(VP_dash);

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
    if(right1 && backward || right2 && backward ){
      ball.right();
      ball.backward();
      ball.bankright();
      cout<<"RIGHT backward!\n";
    }
    else if(left1 && backward || left2 && backward ){
      ball.left();
      ball.backward();
      ball.bankleft();
      cout<<"LEFT FORWARD!\n";
    }
    else if(right1 || right2){
      ball.right();
      ball.bankright();
      cout<<"RIGHT!\n";
    }
    else if(left1 || left2){
      ball.left();
      ball.bankleft();
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
    else if(backward && bankleft) {
      ball.backward();
      ball.banking--;
    }
    else if( backward && bankright) {
      ball.backward();
      ball.banking++;
    }
    else if(backward) {
        ball.backward();
        cout<<"backward!\n";
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

//////////////////////
    if(up){
      cout<<"UP!\n";
      ball.up();
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
      if(ball.incline<2 && ball.incline>-2)
        ball.incline = 0;
       if(ball.incline>1)
        ball.incline--;
      else if(ball.incline<1)
        ball.incline++;
    }
//////////////////////////////
    display.tick(screen_center_x-1,4.0,score);
    altitude.tick(screen_center_x+5,4.0,ball.position.z*100);

/////////////////fire missiles and bombs
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

            if(rings.size()<=0)
            arrow.erase(arrow.begin());

            arrow[0].set_position(rings[0].position.x,rings[0].position.y,rings[0].position.z+20);

            fuel -=0.01;
            fuel_meter.set_fuel(fuel);

            ball.tick();
            ball.banking = ball.banking % 360;

                if(ball.banking<0){
                  ball.banking+=360;
                }

            marker.set_speed(ball.speed);

            for(int t=0;t<parachutes.size();++t){
              if(parachutes[t].position.z<=0)
                   parachutes.erase(parachutes.begin()+t);
              else
                   parachutes[t].tick();
              }

            for(int t=0;t<bullets.size();++t){
              if(bullets[t].position.z> MAX_ALTITUDE || bullets[t].position.x > MAX_X || bullets[t].position.x < MIN_X ||  bullets[t].position.y < MIN_Y || bullets[t].position.y > MAX_Y  )
                 bullets.erase(bullets.begin()+t);
               else
                bullets[t].tick();
              }

            if(ATTACK_TIMER>0)
               ATTACK_TIMER--;

            for(int t=0;t<cannons.size();++t){
               cannons[t].tick();
               if(detect_vicinity(ball.position.x,ball.position.y,cannons[t].position.x,cannons[t].position.y) && ATTACK_TIMER<=0)
                 {
                   cout<<"firing!\n";
                   bullets.push_back(Bullet(ball.position.x,ball.position.y,ball.position.z,cannons[t].position.x,cannons[t].position.y));
                   ATTACK_TIMER+=50;
                 }
              }

            for(int t=0;t<fuelups.size();++t){
               fuelups[t].tick();
              }
            ///////////Missiles
            if(MISSILE_TIMER>0)
               MISSILE_TIMER--;
            for(int i=0;i<missiles.size();++i){

                missiles[i].tick();

                if(missiles[i].position.x>(ball.position.x+500) || missiles[i].position.x<(ball.position.x-500)
                ||  missiles[i].position.y>(ball.position.y+500) || missiles[i].position.y<(ball.position.y-500))
                missiles.erase(missiles.begin()+i);

                else {

                  for(int t=0;t<parachutes.size();++t){
                      if(detect_para_shoot(missiles[i].position.x,missiles[i].position.y,missiles[i].position.z,
                        parachutes[t].position.x,parachutes[t].position.y,parachutes[t].position.z)){
                          cout<<"maaar sale ko\n";
                          missiles.erase(missiles.begin()+i);
                          parachutes.erase(parachutes.begin()+t);
                            }
                      }

                  for(int t=0;t<cannons.size();++t){
                      if(detect_cannon(missiles[i].position.x,missiles[i].position.y,missiles[i].position.z,
                          cannons[t].position.x,cannons[t].position.y)){
                            missiles.erase(missiles.begin()+i);
                            cannons.erase(cannons.begin()+t);
                           }
                       }
                    }
                }
            ////////////Bombs
             if(BOMB_TIMER>0)
                BOMB_TIMER--;


             for(int i=0;i<bombs.size();++i){

               bombs[i].tick();

               if(bombs[i].position.z<=0)
                 bombs.erase(bombs.begin()+i);

               else{
                 for(int t=0;t<cannons.size();++t){
                     if(detect_cannon(bombs[i].position.x,bombs[i].position.y,bombs[i].position.z,
                         cannons[t].position.x,cannons[t].position.y)){
                           bombs.erase(bombs.begin()+i);
                           cannons.erase(cannons.begin()+t);
                          }
                      }
                  }
             }
              /////////////////Rings passing through
            if(detect_passthrough(rings[0].position.x,rings[0].position.y,rings[0].position.z)){
              cout<<"whoah";
              comp_rings.push_back(Ring(rings[0].position.x,rings[0].position.y,rings[0].position.z,rings[0].rotation,COLOR_LAWNGREEN));
              rings.erase(rings.begin());
            }

            for(int i=0;i<volcanoes.size();++i)
            {
              if(detect_volcano(ball.position.x,ball.position.y,ball.position.z,volcanoes[i].position.x,volcanoes[i].position.y,volcanoes[i].height))
              {
                cout<<"OH FUCK BITCH";
                exit(0);
              }
            }

            for(int i=0;i<lands.size();++i)
            {
              if(detect_islands(ball.position.x,ball.position.y,ball.position.z,lands[i].position.x,lands[i].position.y,lands[i].height))
              {
                cout<<"OH FUCK dekh ke";
                exit(0);
              }
            }

            for(int i=0;i<fuelups.size();++i)
            {
              if(detect_fuelup(ball.position.x,ball.position.y,ball.position.z,fuelups[i].position.x,fuelups[i].position.y,fuelups[i].position.z))
              {
                cout<<"OH noice";
                fuelups.erase(fuelups.begin()+i);
              }
            }
            for(int i=0;i<cannons.size();++i)
            {
              if(detect_cannon(ball.position.x,ball.position.y,ball.position.z,cannons[i].position.x,cannons[i].position.y))
              {
                cannons.erase(cannons.begin()+i);
                exit(0);
              }
            }

            // cout<<parachutes.size()<<" number of parcahutes\n";
      }

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    ball       = Ball(0, 0, COLOR_RED);
    for(int i=0;i<2500;i++){
            coins.push_back(Coin(-1000+rand()%2000,-1000+rand()%2000,COLOR_LAWNGREEN,0));
    }
    // GLuint seaTextureID = createTexture("../images/sea.jpg");
     sea        = Sea( 0, 0);

     arrow.push_back(Arrow(0,100,35));

     rings.push_back(Ring(0,100,20,0,COLOR_SKYBLUE));
     rings.push_back(Ring(-200,300,40,30,COLOR_SKYBLUE));
     rings.push_back(Ring(-400,500,30,-30,COLOR_SKYBLUE));
     rings.push_back(Ring(-500,400,40,30,COLOR_SKYBLUE));
     rings.push_back(Ring(-600,500,20,-30,COLOR_SKYBLUE));
     rings.push_back(Ring(-500,300,30,30,COLOR_SKYBLUE));
     rings.push_back(Ring(-300,100,20,40,COLOR_SKYBLUE));
     rings.push_back(Ring(-100,-200,30,30,COLOR_SKYBLUE));
     rings.push_back(Ring(-300,-300,40,-30,COLOR_SKYBLUE));
     rings.push_back(Ring(-500,-400,50,30,COLOR_SKYBLUE));
     rings.push_back(Ring(-300,-500,30,-30,COLOR_SKYBLUE));
     rings.push_back(Ring(-100,-350,20,30,COLOR_SKYBLUE));
     rings.push_back(Ring(100,-250,20,30,COLOR_SKYBLUE));
     rings.push_back(Ring(250,-400,30,0,COLOR_SKYBLUE));
     rings.push_back(Ring(400,-500,25,0,COLOR_SKYBLUE));
     rings.push_back(Ring(500,-300,20,30,COLOR_SKYBLUE));
     rings.push_back(Ring(300,-150,30,-30,COLOR_SKYBLUE));
     rings.push_back(Ring(150,100,35,0,COLOR_SKYBLUE));
     rings.push_back(Ring(350,200,45,0,COLOR_SKYBLUE));
     rings.push_back(Ring(500,350,30,0,COLOR_SKYBLUE));
     rings.push_back(Ring(350,500,30,0,COLOR_SKYBLUE));

     cannons.push_back(Cannon(5,95));
     cannons.push_back(Cannon(-210,310));
     cannons.push_back(Cannon(-410,510));
     cannons.push_back(Cannon(-495,410));
     cannons.push_back(Cannon(-610,500));
     cannons.push_back(Cannon(-510,295));
     cannons.push_back(Cannon(-310,100));
     cannons.push_back(Cannon(-100,-210));
     cannons.push_back(Cannon(-310,-295));
     cannons.push_back(Cannon(-506,-408));
     cannons.push_back(Cannon(-307,-502));
     cannons.push_back(Cannon(-110,-350));
     cannons.push_back(Cannon(90,-255));
     cannons.push_back(Cannon(255,-410));
     cannons.push_back(Cannon(407,-496));
     cannons.push_back(Cannon(510,-306));
     cannons.push_back(Cannon(310,-155));
     cannons.push_back(Cannon(153,106));
     cannons.push_back(Cannon(355,210));
     cannons.push_back(Cannon(503,355));
     cannons.push_back(Cannon(345,495));
     //
     // for(int i=0;i<30;i++){
     //   fuelups.push_back(Fuelup(-850+rand()%1700, -850+rand()%1700, 20 + rand()% 40));
     // }

     for(float i = -1000.0;i<1000.0; i+=250.0){
        for(float j = -1000.0;j<1000.0; j+=250.0){
            volcanoes.push_back(Volcano(17+i+rand()%100,17+j+rand()%100, 10+rand()%7));
            parachutes.push_back(Parachute(i+rand()%250, j+rand()%250, 50 + rand()% 50));
            fuelups.push_back(Fuelup(i+rand()%200, j+rand()%200, 20 + rand()% 50));
        }
     }

     for(float i = -875.0;i<1000.0; i+=250.0){
        for(float j = -875.0;j<1000.0; j+=250.0){
            lands.push_back(Land(i+rand()%100,j+rand()%100, rand()%180));
        }
     }


     // lands.push_back(Land(-50,50,45));

     // lands.push_back(Land(50,-50,125));

     display = Score(screen_center_x-1,4.0,score);
     altitude = Score(screen_center_x+5,4.0,ball.position.z*100);
     speed_frame = Speedometer(screen_center_x-3,-4.0);
     marker = Marker(screen_center_x-3,-4.0);
     fuel_meter =  Fuel(100.0);


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
bool detect_passthrough(float x,float y,float z) {
  return ( (pow((ball.position.x - x),2)+pow((ball.position.z - z),2)) < 75 && ball.position.y < y+2 && ball.position.y > y-2 );
}
bool detect_para_shoot(float a,float b,float c ,float x,float y,float z) {
  return ( (pow((a - x),2)+pow((b - y),2)+pow((c - z),2)) < 64 );
}

bool detect_volcano(float a,float b,float c ,float x,float y,float h){
  // cout<<" volc"<<( ( pow(a-x,2) + pow(b-y,2)) < 400 && c < (h+40) )<<"volcano";
  return ( ( pow(a-x,2) + pow(b-y,2)) < 400 && c < (h+40) );
}

bool detect_islands(float a,float b,float c ,float x,float y,float h){
  return ( ( pow(a-x,2) + pow(b-y,2)) < 200 && c < h );
}
bool detect_fuelup(float a,float b,float c ,float x,float y,float z){
  // cout<<"detect"<<( abs(a-x)<2.5 && abs(b-y)<2.5 && abs(c-z)<3)<<"\n";
  return ( abs(a-x)<2.5 && abs(b-y)<2.5 && abs(c-z)<3) ;
}
bool detect_vicinity(float a,float b,float x,float y){
  return ( ( pow(a-x,2) + pow(b-y,2)) < 1500  );
}
// a b c --plane and x y -- cannon
bool detect_cannon(float a,float b, float c,float x,float y){
  return  ( pow(a-x,2) + pow(b-y,2) < 40 && c<10 );
}

void reset_screen() {

    Matrices.projection = glm::perspective(glm::radians(90.0), 1.0, 1.0, 500.0);
    // GLfloat fov = screen_zoom;
    // Matrices.projection = glm::perspective(fov, 1.0f, 1.0f, 500.0f);
    float top    = screen_center_y + (4 / screen_zoom);
    float bottom = screen_center_y - (4 / screen_zoom);
    float left   = screen_center_x - (4 / screen_zoom);
    float right  = screen_center_x + (4 / screen_zoom);
    Matrices_dash.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);

}
