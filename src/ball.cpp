#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 90;//fixing the figure lol
    this->turn = 180;
    this->banking = 0;
    this->incline = 0;

    this->speed = 0.5;
    this->upthrust = 0.05;//due to key press
    this->downfall = 0.1;//due to key press

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    const int p = 30;
    const int iter = 54;
    const int r1 = 1;
    const int r2 = 1;
    static GLfloat vertex_buffer_data_frustum[iter*p+8*9];// 8 triangles
    for (int i=0;i<p;++i){
      //front circle
      vertex_buffer_data_frustum[iter*i]=(r1*cos(i*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+1]=(r1*sin(i*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+2]=2.0;

      vertex_buffer_data_frustum[iter*i+3]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+4]=(r1*sin((i+1)*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+5]=2.0;

      vertex_buffer_data_frustum[iter*i+6]=0.0;
      vertex_buffer_data_frustum[iter*i+7]=0.0;
      vertex_buffer_data_frustum[iter*i+8]=2.0;
//back circle
      vertex_buffer_data_frustum[iter*i+9]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+10]=r2*sin(i*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+11]=-2.0;

      vertex_buffer_data_frustum[iter*i+12]=r2*cos((i+1)*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+13]=r2*sin((i+1)*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+14]=-2.0;

      vertex_buffer_data_frustum[iter*i+15]=0;
      vertex_buffer_data_frustum[iter*i+16]=0;
      vertex_buffer_data_frustum[iter*i+17]=-2.0;
//joining cylinder
      vertex_buffer_data_frustum[iter*i+18]=(r1*cos(i*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+19]=(r1*sin(i*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+20]=2.0;

      vertex_buffer_data_frustum[iter*i+21]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+22]=(r1*sin((i+1)*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+23]=2.0;

      vertex_buffer_data_frustum[iter*i+24]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+25]=r2*sin(i*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+26]=-2.0;
//joining cylinder
      vertex_buffer_data_frustum[iter*i+27]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+28]=r2*sin(i*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+29]=-2.0;

      vertex_buffer_data_frustum[iter*i+30]=r2*cos((i+1)*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+31]=r2*sin((i+1)*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+32]=-2.0;

      vertex_buffer_data_frustum[iter*i+33]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+34]=(r1*sin((i+1)*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+35]=2.0;
//cone at back
      vertex_buffer_data_frustum[iter*i+36]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+37]=r2*sin(i*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+38]=-2.0;

      vertex_buffer_data_frustum[iter*i+39]=r2*cos((i+1)*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+40]=r2*sin((i+1)*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+41]=-2.0;

      vertex_buffer_data_frustum[iter*i+42]= 0.0;
      vertex_buffer_data_frustum[iter*i+43]= 3;
      vertex_buffer_data_frustum[iter*i+44]=-3.0;
// nose
      vertex_buffer_data_frustum[iter*i+45]=(r1*cos(i*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+46]=(r1*sin(i*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+47]=2.0;

      vertex_buffer_data_frustum[iter*i+48]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+49]=(r1*sin((i+1)*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+50]=2.0;

      vertex_buffer_data_frustum[iter*i+51]= 0.0;
      vertex_buffer_data_frustum[iter*i+52]= -0.7;
      vertex_buffer_data_frustum[iter*i+53]= 4.2;
    }

    vertex_buffer_data_frustum[iter*p]= 0.8;
    vertex_buffer_data_frustum[iter*p+1]= 0.3;
    vertex_buffer_data_frustum[iter*p+2]= 0.7;

    vertex_buffer_data_frustum[iter*p+3]= 0.8;
    vertex_buffer_data_frustum[iter*p+4]= -0.3;
    vertex_buffer_data_frustum[iter*p+5]= 0.7;

    vertex_buffer_data_frustum[iter*p+6]= 4.2;
    vertex_buffer_data_frustum[iter*p+7]= 0;
    vertex_buffer_data_frustum[iter*p+8]= -0.7;
//
    vertex_buffer_data_frustum[iter*p+9]= 0.8;
    vertex_buffer_data_frustum[iter*p+10]= 0.3;
    vertex_buffer_data_frustum[iter*p+11]= -0.7;

    vertex_buffer_data_frustum[iter*p+12]= 0.8;
    vertex_buffer_data_frustum[iter*p+13]= -0.3;
    vertex_buffer_data_frustum[iter*p+14]= -0.7;

    vertex_buffer_data_frustum[iter*p+15]= 4.2;
    vertex_buffer_data_frustum[iter*p+16]= 0;
    vertex_buffer_data_frustum[iter*p+17]= -0.7;
//
    vertex_buffer_data_frustum[iter*p+18]= 0.8;
    vertex_buffer_data_frustum[iter*p+19]= 0.3;
    vertex_buffer_data_frustum[iter*p+20]= -0.7;

    vertex_buffer_data_frustum[iter*p+21]= 0.8;
    vertex_buffer_data_frustum[iter*p+22]= 0.3;
    vertex_buffer_data_frustum[iter*p+23]= 0.7;

    vertex_buffer_data_frustum[iter*p+24]= 4.2;
    vertex_buffer_data_frustum[iter*p+25]= 0;
    vertex_buffer_data_frustum[iter*p+26]= -0.7;
//
      vertex_buffer_data_frustum[iter*p+27]= 0.8;
      vertex_buffer_data_frustum[iter*p+28]= -0.3;
      vertex_buffer_data_frustum[iter*p+29]= -0.7;

      vertex_buffer_data_frustum[iter*p+30]= 0.8;
      vertex_buffer_data_frustum[iter*p+31]= -0.3;
      vertex_buffer_data_frustum[iter*p+32]= 0.7;

      vertex_buffer_data_frustum[iter*p+33]= 4.2;
      vertex_buffer_data_frustum[iter*p+34]= 0;
      vertex_buffer_data_frustum[iter*p+35]= -0.7;
      ///////////////////
      vertex_buffer_data_frustum[iter*p+36]= -0.8;
      vertex_buffer_data_frustum[iter*p+37]= 0.3;
      vertex_buffer_data_frustum[iter*p+38]= 0.7;

      vertex_buffer_data_frustum[iter*p+39]= -0.8;
      vertex_buffer_data_frustum[iter*p+40]= -0.3;
      vertex_buffer_data_frustum[iter*p+41]= 0.7;

      vertex_buffer_data_frustum[iter*p+42]= -4.2;
      vertex_buffer_data_frustum[iter*p+43]= 0;
      vertex_buffer_data_frustum[iter*p+44]= -0.7;
  //
      vertex_buffer_data_frustum[iter*p+45]= -0.8;
      vertex_buffer_data_frustum[iter*p+46]= 0.3;
      vertex_buffer_data_frustum[iter*p+47]= -0.7;

      vertex_buffer_data_frustum[iter*p+48]= -0.8;
      vertex_buffer_data_frustum[iter*p+49]= -0.3;
      vertex_buffer_data_frustum[iter*p+50]= -0.7;

      vertex_buffer_data_frustum[iter*p+51]= -4.2;
      vertex_buffer_data_frustum[iter*p+52]= 0;
      vertex_buffer_data_frustum[iter*p+53]= -0.7;
  //
      vertex_buffer_data_frustum[iter*p+54]= -0.8;
      vertex_buffer_data_frustum[iter*p+55]= 0.3;
      vertex_buffer_data_frustum[iter*p+56]= -0.7;

      vertex_buffer_data_frustum[iter*p+57]= -0.8;
      vertex_buffer_data_frustum[iter*p+58]= 0.3;
      vertex_buffer_data_frustum[iter*p+59]= 0.7;

      vertex_buffer_data_frustum[iter*p+60]= -4.2;
      vertex_buffer_data_frustum[iter*p+61]= 0;
      vertex_buffer_data_frustum[iter*p+62]= -0.7;
  //
      vertex_buffer_data_frustum[iter*p+63]= -0.8;
      vertex_buffer_data_frustum[iter*p+64]= -0.3;
      vertex_buffer_data_frustum[iter*p+65]= -0.7;

      vertex_buffer_data_frustum[iter*p+66]= -0.8;
      vertex_buffer_data_frustum[iter*p+67]= -0.3;
      vertex_buffer_data_frustum[iter*p+68]= 0.7;

      vertex_buffer_data_frustum[iter*p+69]= -4.2;
      vertex_buffer_data_frustum[iter*p+70]= 0;
      vertex_buffer_data_frustum[iter*p+71]= -0.7;

     this->object = create3DObject(GL_TRIANGLES, (iter/3)*p + 8*3, vertex_buffer_data_frustum, color, GL_LINE);
}


void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate   = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 turned    = glm::rotate((float) (this->turn * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 banked    = glm::rotate((float) (this->banking * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 inclined   = glm::rotate((float) (this->incline * M_PI / 180.0f), glm::vec3(cos((this->turn+90)*M_PI/180.0f),sin((this->turn+90)*M_PI/180.0f), 0));



    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate  * rotate * turned * inclined * banked);
    // Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    // draw3DObject(this->structure);

}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
  // if(this->position.x< screen_center_x+(4.0/screen_zoom))
  //     this->position.x += this->default_speed_x;
  //
  // if(player_max_x<this->position.x){
  //   player_max_x = this->position.x;
  // }
  // std::cout<<"max x "<<player_max_x<<"\n";
  //  std::cout<<this->position.x<<","<<this->position.y<<"\n";
}
void Ball::up() {
    this->position.z += this->upthrust;
  }

void Ball::down() {
  if(this->position.z>-1){
      if(this->position.z-this->downfall<-1)
        {
          this->position.z=-1;
        }
      else{
      this->position.z -= this->downfall;
    }
  }
}


void Ball::right() {
  this->turn--;
}
void Ball::bankright() {
  this->banking =  30;
}
void Ball::left() {
  this->turn++;
}
void Ball::bankleft() {
  this->banking = -30;
}
void Ball::forward() {
    this->position.x += this->speed*sin((180-this->turn) * M_PI / 180.0f);
    this->position.y += this->speed*cos((this->turn-180) * M_PI / 180.0f);
}


// void Ball::gravity_fall(){
//   if(this->position.z>-3){
//     this->speed_y+=this->gravity;
//     if(this->position.y-this->speed_y<-3)
//       {
//         this->position.y=-3;
//         this->speed_y=0;
//       }
//     else{
//     this->position.y -= this->speed_y;
//     }
//   }
//   else{
//     this->speed_y=0;//reached ground
//   }
// }
