#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 1);
    this->rotation = 90;//fixing the figure lol
    this->turn = 180;
    this->banking = 0;
    this->incline = 0;

    this->speed = 0;
    this->upthrust = 0.1;//due to key press
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
    // glm::mat4 inclined   = glm::rotate((float) (this->incline * M_PI / 180.0f), glm::vec3(sin((this->turn+90)*M_PI/180.0f), 0, cos((this->turn+90)*M_PI/180.0f)));
    glm::mat4 inclined   = glm::rotate((float) (this->incline * M_PI / 180.0f), glm::vec3(1, 0, 0));



    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate * turned * rotate * inclined * banked);
    Matrices.model *= (translate * rotate * turned * banked * inclined);

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
  if(this->position.x<MAX_X && this->position.y<MAX_Y && this->position.x>MIN_X && this->position.y>MIN_Y  ){
  this->position.x += this->speed*sin((180-this->turn) * M_PI / 180.0f);
  this->position.y += this->speed*cos((this->turn-180) * M_PI / 180.0f);
   }
}
void Ball::up() {
  if(this->position.z<MAX_ALTITUDE)
    this->position.z += this->upthrust;
  }

void Ball::down() {
  // if(this->position.z>=0.5){
  //     if(this->position.z-this->downfall<0.5)
  //       {
  //         this->position.z=0.5;
  //       }
  //     else{
         this->position.z -= this->downfall;
        // }
  // }
}


void Ball::right() {
     this->turn--;
}
void Ball::bankright() {
    if(abs(this->banking-45)<=2)
       this->banking=45;
    else
      {
        if(this->banking>45 && this->banking<225)
             this->banking-=2;
         else
             this->banking+=2;
      }
   }

void Ball::left() {
     this->turn++;
}
void Ball::bankleft() {
  if(abs(this->banking-315)<=2)
     this->banking=315;
  else
    {
    if(this->banking>315 || this->banking<135)
     this->banking -=2;
    else
      this->banking +=2;
    }
}
void Ball::forward() {
   if(this->speed<=0.8)
     this->speed+=0.01;
}
void Ball::backward() {
    if(this->speed>0)
      this->speed-=0.01;
    if(this->speed<0)
      this->speed = 0;
}
void Ball::bankcenter() {
  if(abs(this->banking)<=2 || this->banking >=358)
     this->banking=0;
  else
    {
    if(this->banking>0 && this->banking<180)
     this->banking -=2;
    else
      this->banking +=2;
    }
}

/////////////////////////////////////////////// missiles
Missile::Missile(float x, float y,float z,float rot,float incline) {
    this->position = glm::vec3(x, y, z);
    this->rotation = rot+180;
    this->revolve = 0;
    this->incline = incline;

    const int speed = 1;
    this->speedx = speed * sin((180-rot)*M_PI/180.0f);
    this->speedy = speed * cos((180-rot)*M_PI/180.0f);
    this->speedz = speed * sin(incline*M_PI/180.0f);

    const int p = 60;
    const int iter = 18;
    const float r1 = 0.3;
    const float r2 = 0.15;
    const float w = 1.5;
    const int iter2 = 9;
    const float h = 0.8;

    static GLfloat vertex_buffer_data[iter*p];
    for (int i=0;i<p;++i){
      // face 1
      vertex_buffer_data[iter*i]=(r1*cos(i*2*M_PI/p));
      vertex_buffer_data[iter*i+1]=-w/2;
      vertex_buffer_data[iter*i+2]=(r1*sin(i*2*M_PI/p));

      vertex_buffer_data[iter*i+3]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+4]=-w/2;
      vertex_buffer_data[iter*i+5]=(r1*sin((i+1)*2*M_PI/p));

      vertex_buffer_data[iter*i+6]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data[iter*i+7]=w/2;
      vertex_buffer_data[iter*i+8]=r2*sin(i*2*M_PI/p);

      vertex_buffer_data[iter*i+9]=r2*cos((i+1)*2*M_PI/p);
      vertex_buffer_data[iter*i+10]=w/2;
      vertex_buffer_data[iter*i+11]=r2*sin((i+1)*2*M_PI/p);

      vertex_buffer_data[iter*i+12]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data[iter*i+13]=w/2;
      vertex_buffer_data[iter*i+14]=r2*sin(i*2*M_PI/p);

      vertex_buffer_data[iter*i+15]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+16]=-w/2;
      vertex_buffer_data[iter*i+17]=(r1*sin((i+1)*2*M_PI/p));

     }

     static GLfloat vertex_buffer_data_structure[iter2*p+9*2];
     for (int i=0;i<p;++i){
     vertex_buffer_data_structure[iter2*i]=r2*cos((i+1)*2*M_PI/p);
     vertex_buffer_data_structure[iter2*i+1]=w/2;
     vertex_buffer_data_structure[iter2*i+2]=r2*sin((i+1)*2*M_PI/p);

     vertex_buffer_data_structure[iter2*i+3]=r2*cos(i*2*M_PI/p);
     vertex_buffer_data_structure[iter2*i+4]=w/2;
     vertex_buffer_data_structure[iter2*i+5]=r2*sin(i*2*M_PI/p);

     vertex_buffer_data_structure[iter2*i+6]=0;
     vertex_buffer_data_structure[iter2*i+7]=(w/2)+0.5;
     vertex_buffer_data_structure[iter2*i+8]=0;
    }
      vertex_buffer_data_structure[iter2*p] = 0;
      vertex_buffer_data_structure[iter2*p+1] = 0;
      vertex_buffer_data_structure[iter2*p+2] = 0;

      vertex_buffer_data_structure[iter2*p+3] = 0;
      vertex_buffer_data_structure[iter2*p+4] = -w/2;
      vertex_buffer_data_structure[iter2*p+5] = 0.8;

      vertex_buffer_data_structure[iter2*p+6] = 0;
      vertex_buffer_data_structure[iter2*p+7] = -w/2;
      vertex_buffer_data_structure[iter2*p+8] = -0.8;
  //
      vertex_buffer_data_structure[iter2*p+9] = 0;
      vertex_buffer_data_structure[iter2*p+10] = 0;
      vertex_buffer_data_structure[iter2*p+11] = 0;

      vertex_buffer_data_structure[iter2*p+12] = 0.8;
      vertex_buffer_data_structure[iter2*p+13] = -w/2;
      vertex_buffer_data_structure[iter2*p+14] = 0;

      vertex_buffer_data_structure[iter2*p+15] = -0.8;
      vertex_buffer_data_structure[iter2*p+16] = -w/2;
      vertex_buffer_data_structure[iter2*p+17] = 0;

    this->object = create3DObject(GL_TRIANGLES, (iter/3)*p, vertex_buffer_data, COLOR_GOLD, GL_FILL);
    this->structure = create3DObject(GL_TRIANGLES, (iter2/3)*p+6, vertex_buffer_data_structure, COLOR_RUBY, GL_FILL);

}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 revolve    = glm::rotate((float) (this->revolve * M_PI / 180.0f), glm::vec3(0, 1, 0));


    Matrices.model *= (translate * rotate * revolve);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->structure);

}

void Missile::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Missile::tick() {
    this->revolve += 3;
    this->position.x += this->speedx;
    this->position.y += this->speedy;
    this->position.z -= this->speedz;
    // this->speedz += 0.001;//gravity

}

bounding_box_t Missile::return_box(){
  bounding_box_t coin_bb;
  coin_bb.x = this->position.x;
  coin_bb.y = this->position.y;
  coin_bb.width = 0.4f;
  coin_bb.height = 0.4f;
  return coin_bb;
}


//////////////////////////////// bombs
Bomb::Bomb(float x, float y,float z,float rot) {
    this->position = glm::vec3(x, y, z-1);
    this->speedz = 0;
    this->rotation = 180+rot;
    this->revolve = 0;


    const int p = 60;
    const int iter = 18;
    const float r1 = 0.4;
    const float r2 = 0.3;
    const float w = 2;
    const int iter2 = 9;
    const float h = 1;

    static GLfloat vertex_buffer_data[iter*p];
    for (int i=0;i<p;++i){
      // face 1
      vertex_buffer_data[iter*i]=(r1*cos(i*2*M_PI/p));
      vertex_buffer_data[iter*i+1]=-w/2;
      vertex_buffer_data[iter*i+2]=(r1*sin(i*2*M_PI/p));

      vertex_buffer_data[iter*i+3]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+4]=-w/2;
      vertex_buffer_data[iter*i+5]=(r1*sin((i+1)*2*M_PI/p));

      vertex_buffer_data[iter*i+6]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data[iter*i+7]=w/2;
      vertex_buffer_data[iter*i+8]=r2*sin(i*2*M_PI/p);

      vertex_buffer_data[iter*i+9]=r2*cos((i+1)*2*M_PI/p);
      vertex_buffer_data[iter*i+10]=w/2;
      vertex_buffer_data[iter*i+11]=r2*sin((i+1)*2*M_PI/p);

      vertex_buffer_data[iter*i+12]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data[iter*i+13]=w/2;
      vertex_buffer_data[iter*i+14]=r2*sin(i*2*M_PI/p);

      vertex_buffer_data[iter*i+15]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+16]=-w/2;
      vertex_buffer_data[iter*i+17]=(r1*sin((i+1)*2*M_PI/p));

     }

     static GLfloat vertex_buffer_data_structure[iter2*p+9*2];
     for (int i=0;i<p;++i){
     vertex_buffer_data_structure[iter2*i]=r2*cos((i+1)*2*M_PI/p);
     vertex_buffer_data_structure[iter2*i+1]=w/2;
     vertex_buffer_data_structure[iter2*i+2]=r2*sin((i+1)*2*M_PI/p);

     vertex_buffer_data_structure[iter2*i+3]=r2*cos(i*2*M_PI/p);
     vertex_buffer_data_structure[iter2*i+4]=w/2;
     vertex_buffer_data_structure[iter2*i+5]=r2*sin(i*2*M_PI/p);

     vertex_buffer_data_structure[iter2*i+6]=0;
     vertex_buffer_data_structure[iter2*i+7]=(w/2)+0.5;
     vertex_buffer_data_structure[iter2*i+8]=0;
    }
      vertex_buffer_data_structure[iter2*p] = 0;
      vertex_buffer_data_structure[iter2*p+1] = 0;
      vertex_buffer_data_structure[iter2*p+2] = 0;

      vertex_buffer_data_structure[iter2*p+3] = 0;
      vertex_buffer_data_structure[iter2*p+4] = -w/2;
      vertex_buffer_data_structure[iter2*p+5] = h;

      vertex_buffer_data_structure[iter2*p+6] = 0;
      vertex_buffer_data_structure[iter2*p+7] = -w/2;
      vertex_buffer_data_structure[iter2*p+8] = -h;
  //
      vertex_buffer_data_structure[iter2*p+9] = 0;
      vertex_buffer_data_structure[iter2*p+10] = 0;
      vertex_buffer_data_structure[iter2*p+11] = 0;

      vertex_buffer_data_structure[iter2*p+12] = h;
      vertex_buffer_data_structure[iter2*p+13] = -w/2;
      vertex_buffer_data_structure[iter2*p+14] = 0;

      vertex_buffer_data_structure[iter2*p+15] = -h;
      vertex_buffer_data_structure[iter2*p+16] = -w/2;
      vertex_buffer_data_structure[iter2*p+17] = 0;

    this->object = create3DObject(GL_TRIANGLES, (iter/3)*p, vertex_buffer_data, COLOR_SKYBLUE, GL_FILL);
    this->structure = create3DObject(GL_TRIANGLES, (iter2/3)*p+6, vertex_buffer_data_structure, COLOR_BROWN, GL_FILL);

}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 revolve    = glm::rotate((float) (this->revolve * M_PI / 180.0f), glm::vec3(0, 1, 0));

    Matrices.model *= (translate*rotate*revolve);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->structure);
}

void Bomb::tick() {
    this->revolve +=2;
    this->position.z -= this->speedz;
    this->speedz += 0.01;//gravity
}

bounding_box_t Bomb::return_box(){
  bounding_box_t coin_bb;
  coin_bb.x = this->position.x;
  coin_bb.y = this->position.y;
  coin_bb.width = 0.4f;
  coin_bb.height = 0.4f;
  return coin_bb;
}
