#include "rings.h"
#include "main.h"

Ring::Ring(float x, float y,float z, float rot, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = rot;

    const int p = 60;
    const int iter = 54;
    const int r1 = 10;
    const int r2 = 9;
    const int w = 2;
    static GLfloat vertex_buffer_data[iter*p];
    for (int i=0;i<p;++i){
      // face 1
      vertex_buffer_data[iter*i]=(r1*cos(i*2*M_PI/p));
      vertex_buffer_data[iter*i+1]=0;
      vertex_buffer_data[iter*i+2]=(r1*sin(i*2*M_PI/p));

      vertex_buffer_data[iter*i+3]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+4]=0;
      vertex_buffer_data[iter*i+5]=(r1*sin((i+1)*2*M_PI/p));

      vertex_buffer_data[iter*i+6]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data[iter*i+7]=0;
      vertex_buffer_data[iter*i+8]=r2*sin(i*2*M_PI/p);

      vertex_buffer_data[iter*i+9]=r2*cos((i+1)*2*M_PI/p);
      vertex_buffer_data[iter*i+10]=0;
      vertex_buffer_data[iter*i+11]=r2*sin((i+1)*2*M_PI/p);

      vertex_buffer_data[iter*i+12]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data[iter*i+13]=0;
      vertex_buffer_data[iter*i+14]=r2*sin(i*2*M_PI/p);

      vertex_buffer_data[iter*i+15]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+16]=0;
      vertex_buffer_data[iter*i+17]=(r1*sin((i+1)*2*M_PI/p));

      // face 2
      vertex_buffer_data[iter*i+18]=(r1*cos(i*2*M_PI/p));
      vertex_buffer_data[iter*i+19]=w;
      vertex_buffer_data[iter*i+20]=(r1*sin(i*2*M_PI/p));

      vertex_buffer_data[iter*i+21]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+22]=w;
      vertex_buffer_data[iter*i+23]=(r1*sin((i+1)*2*M_PI/p));

      vertex_buffer_data[iter*i+24]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data[iter*i+25]=w;
      vertex_buffer_data[iter*i+26]=r2*sin(i*2*M_PI/p);

      vertex_buffer_data[iter*i+27]=r2*cos((i+1)*2*M_PI/p);
      vertex_buffer_data[iter*i+28]=w;
      vertex_buffer_data[iter*i+29]=r2*sin((i+1)*2*M_PI/p);

      vertex_buffer_data[iter*i+30]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data[iter*i+31]=w;
      vertex_buffer_data[iter*i+32]=r2*sin(i*2*M_PI/p);

      vertex_buffer_data[iter*i+33]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+34]=w;
      vertex_buffer_data[iter*i+35]=(r1*sin((i+1)*2*M_PI/p));

      // joining
      vertex_buffer_data[iter*i+36]=(r1*cos(i*2*M_PI/p));
      vertex_buffer_data[iter*i+37]=0;
      vertex_buffer_data[iter*i+38]=(r1*sin(i*2*M_PI/p));

      vertex_buffer_data[iter*i+39]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+40]=0;
      vertex_buffer_data[iter*i+41]=(r1*sin((i+1)*2*M_PI/p));

      vertex_buffer_data[iter*i+42]=(r1*cos(i*2*M_PI/p));
      vertex_buffer_data[iter*i+43]=w;
      vertex_buffer_data[iter*i+44]=(r1*sin(i*2*M_PI/p));

      vertex_buffer_data[iter*i+45]=(r1*cos(i*2*M_PI/p));
      vertex_buffer_data[iter*i+46]=w;
      vertex_buffer_data[iter*i+47]=(r1*sin(i*2*M_PI/p));

      vertex_buffer_data[iter*i+48]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+49]=w;
      vertex_buffer_data[iter*i+50]=(r1*sin((i+1)*2*M_PI/p));

      vertex_buffer_data[iter*i+51]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+52]=0;
      vertex_buffer_data[iter*i+53]=(r1*sin((i+1)*2*M_PI/p));
    }

    this->object = create3DObject(GL_TRIANGLES, (iter/3)*p, vertex_buffer_data, color, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ring::tick() {
  this->rotation += 1;
  //  std::cout<<"ring :"<<this->position.x<<","<<this->position.y<<"\n";
}

bounding_box_t Ring::return_box(){
  bounding_box_t coin_bb;
  coin_bb.x = this->position.x;
  coin_bb.y = this->position.y;
  coin_bb.width = 0.4f;
  coin_bb.height = 0.4f;
  return coin_bb;
}
////////////////////////////parachoot
Parachute::Parachute(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    const int p = 360;
    const int iter = 54;
    const int r1 = 10;
    const int r2 = 8;
    const int w = 4;
    static GLfloat vertex_buffer_data[iter*90+9*2];
    for (int i=0;i<90;++i){
      // face 1
      vertex_buffer_data[iter*i]=(r1*cos((45 + i)*2*M_PI/p));
      vertex_buffer_data[iter*i+1]=-w/2;
      vertex_buffer_data[iter*i+2]=(r1*sin((45 +i)*2*M_PI/p));

      vertex_buffer_data[iter*i+3]=(r1*cos((45 + (i+1))*2*M_PI/p));
      vertex_buffer_data[iter*i+4]=-w/2;
      vertex_buffer_data[iter*i+5]=(r1*sin((45 +(i+1))*2*M_PI/p));

      vertex_buffer_data[iter*i+6]=r2*cos((45 + i)*2*M_PI/p);
      vertex_buffer_data[iter*i+7]=-w/2;
      vertex_buffer_data[iter*i+8]=r2*sin((45 +i)*2*M_PI/p);

      vertex_buffer_data[iter*i+9]=r2*cos((45 + (i+1))*2*M_PI/p);
      vertex_buffer_data[iter*i+10]=-w/2;
      vertex_buffer_data[iter*i+11]=r2*sin((45 +(i+1))*2*M_PI/p);

      vertex_buffer_data[iter*i+12]=r2*cos((45 + i)*2*M_PI/p);
      vertex_buffer_data[iter*i+13]=-w/2;
      vertex_buffer_data[iter*i+14]=r2*sin((45 +i)*2*M_PI/p);

      vertex_buffer_data[iter*i+15]=(r1*cos((45 + (i+1))*2*M_PI/p));
      vertex_buffer_data[iter*i+16]=-w/2;
      vertex_buffer_data[iter*i+17]=(r1*sin((45 +(i+1))*2*M_PI/p));

      // face 2
      vertex_buffer_data[iter*i+18]=(r1*cos((45 + i)*2*M_PI/p));
      vertex_buffer_data[iter*i+19]=w/2;
      vertex_buffer_data[iter*i+20]=(r1*sin((45 +i)*2*M_PI/p));

      vertex_buffer_data[iter*i+21]=(r1*cos((45 + (i+1))*2*M_PI/p));
      vertex_buffer_data[iter*i+22]=w/2;
      vertex_buffer_data[iter*i+23]=(r1*sin((45 +(i+1))*2*M_PI/p));

      vertex_buffer_data[iter*i+24]=r2*cos((45 + i)*2*M_PI/p);
      vertex_buffer_data[iter*i+25]=w/2;
      vertex_buffer_data[iter*i+26]=r2*sin((45 +i)*2*M_PI/p);

      vertex_buffer_data[iter*i+27]=r2*cos((45 + (i+1))*2*M_PI/p);
      vertex_buffer_data[iter*i+28]=w/2;
      vertex_buffer_data[iter*i+29]=r2*sin((45 +(i+1))*2*M_PI/p);

      vertex_buffer_data[iter*i+30]=r2*cos((45 + i)*2*M_PI/p);
      vertex_buffer_data[iter*i+31]=w/2;
      vertex_buffer_data[iter*i+32]=r2*sin((45 +i)*2*M_PI/p);

      vertex_buffer_data[iter*i+33]=(r1*cos((45 + (i+1))*2*M_PI/p));
      vertex_buffer_data[iter*i+34]=w/2;
      vertex_buffer_data[iter*i+35]=(r1*sin((45 +(i+1))*2*M_PI/p));

      // joining
      vertex_buffer_data[iter*i+36]=(r1*cos((45 + i)*2*M_PI/p));
      vertex_buffer_data[iter*i+37]=-w/2;
      vertex_buffer_data[iter*i+38]=(r1*sin((45 +i)*2*M_PI/p));

      vertex_buffer_data[iter*i+39]=(r1*cos((45 + (i+1))*2*M_PI/p));
      vertex_buffer_data[iter*i+40]=-w/2;
      vertex_buffer_data[iter*i+41]=(r1*sin((45 +(i+1))*2*M_PI/p));

      vertex_buffer_data[iter*i+42]=(r1*cos((45 + i)*2*M_PI/p));
      vertex_buffer_data[iter*i+43]=w/2;
      vertex_buffer_data[iter*i+44]=(r1*sin((45 +i)*2*M_PI/p));

      vertex_buffer_data[iter*i+45]=(r1*cos((45 + i)*2*M_PI/p));
      vertex_buffer_data[iter*i+46]=w/2;
      vertex_buffer_data[iter*i+47]=(r1*sin((45 +i)*2*M_PI/p));

      vertex_buffer_data[iter*i+48]=(r1*cos((45 + (i+1))*2*M_PI/p));
      vertex_buffer_data[iter*i+49]=w/2;
      vertex_buffer_data[iter*i+50]=(r1*sin((45 +(i+1))*2*M_PI/p));

      vertex_buffer_data[iter*i+51]=(r1*cos((45 + (i+1))*2*M_PI/p));
      vertex_buffer_data[iter*i+52]=-w/2;
      vertex_buffer_data[iter*i+53]=(r1*sin((45 +(i+1))*2*M_PI/p));
    }
    vertex_buffer_data[iter*90] = (r2*cos(45*2*M_PI/p));
    vertex_buffer_data[iter*90 + 1]=-w/2;
    vertex_buffer_data[iter*90 + 2] = (r2*sin(45*2*M_PI/p));

    vertex_buffer_data[iter*90 + 3] = (r2*cos(45*2*M_PI/p));
    vertex_buffer_data[iter*90 + 4]=w/2;
    vertex_buffer_data[iter*90 + 5] = (r2*sin(45*2*M_PI/p));

    vertex_buffer_data[iter*90 + 6] = (r2*cos(-90*2*M_PI/p));
    vertex_buffer_data[iter*90 + 7]= 0;
    vertex_buffer_data[iter*90 + 8] = (r2*sin(-90*2*M_PI/p));

    vertex_buffer_data[iter*90 + 9] = (r2*cos(135*2*M_PI/p));
    vertex_buffer_data[iter*90 + 10]=-w/2;
    vertex_buffer_data[iter*90 + 11] = (r2*sin(135*2*M_PI/p));

    vertex_buffer_data[iter*90 + 12] = (r2*cos(135*2*M_PI/p));
    vertex_buffer_data[iter*90 + 13]=w/2;
    vertex_buffer_data[iter*90 + 14] = (r2*sin(135*2*M_PI/p));

    vertex_buffer_data[iter*90 + 15] = (r2*cos(-90*2*M_PI/p));
    vertex_buffer_data[iter*90 + 16]= 0;
    vertex_buffer_data[iter*90 + 17] = (r2*sin(-90*2*M_PI/p));

    this->object = create3DObject(GL_TRIANGLES, (iter/3)*90+6, vertex_buffer_data, COLOR_RUBY, GL_LINE);
}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Parachute::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Parachute::tick() {
  this->rotation += 2;
  this->position.z -= 0.005;
  //  std::cout<<"ring :"<<this->position.x<<","<<this->position.y<<"\n";
}

bounding_box_t Parachute::return_box(){
  bounding_box_t coin_bb;
  coin_bb.x = this->position.x;
  coin_bb.y = this->position.y;
  coin_bb.width = 0.4f;
  coin_bb.height = 0.4f;
  return coin_bb;
}
/////////////////////////////////////////////////

Cannon::Cannon(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = rand()%360;

    const int p = 60;
    const int iter = 54;
    const int r1 = 5;
    const int r2 = 3;
    const int w = 20;
    static GLfloat vertex_buffer_data[iter*p];
    for (int i=0;i<p;++i){
      // face 1
      vertex_buffer_data[iter*i]=(r1*cos(i*2*M_PI/p));
      vertex_buffer_data[iter*i+1]=(r1*sin(i*2*M_PI/p));
      vertex_buffer_data[iter*i+21]=-w/2;

      vertex_buffer_data[iter*i+3]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+4]=(r1*sin((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+5]=-w/2;

      vertex_buffer_data[iter*i+6]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data[iter*i+7]=r2*sin(i*2*M_PI/p);
      vertex_buffer_data[iter*i+8]=-w/2;

      vertex_buffer_data[iter*i+9]=r2*cos((i+1)*2*M_PI/p);
      vertex_buffer_data[iter*i+10]=r2*sin((i+1)*2*M_PI/p);
      vertex_buffer_data[iter*i+11]=-w/2;

      vertex_buffer_data[iter*i+12]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data[iter*i+13]=r2*sin(i*2*M_PI/p);
      vertex_buffer_data[iter*i+14]=-w/2;

      vertex_buffer_data[iter*i+15]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+16]=(r1*sin((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+17]=-w/2;

      // face 2
      vertex_buffer_data[iter*i+18]=(r1*cos(i*2*M_PI/p));
      vertex_buffer_data[iter*i+19]=(r1*sin(i*2*M_PI/p));
      vertex_buffer_data[iter*i+20]=w/2;

      vertex_buffer_data[iter*i+21]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+22]=(r1*sin((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+23]=w/2;

      vertex_buffer_data[iter*i+24]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data[iter*i+25]=r2*sin(i*2*M_PI/p);
      vertex_buffer_data[iter*i+26]=w/2;

      vertex_buffer_data[iter*i+27]=r2*cos((i+1)*2*M_PI/p);
      vertex_buffer_data[iter*i+28]=r2*sin((i+1)*2*M_PI/p);
      vertex_buffer_data[iter*i+29]=w/2;

      vertex_buffer_data[iter*i+30]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data[iter*i+31]=r2*sin(i*2*M_PI/p);
      vertex_buffer_data[iter*i+32]=w/2;

      vertex_buffer_data[iter*i+33]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+34]=(r1*sin((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+35]=w/2;

      // joining
      vertex_buffer_data[iter*i+36]=(r1*cos(i*2*M_PI/p));
      vertex_buffer_data[iter*i+37]=(r1*sin(i*2*M_PI/p));
      vertex_buffer_data[iter*i+38]=-w/2;

      vertex_buffer_data[iter*i+39]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+40]=(r1*sin((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+41]=-w/2;

      vertex_buffer_data[iter*i+42]=(r1*cos(i*2*M_PI/p));
      vertex_buffer_data[iter*i+43]=(r1*sin(i*2*M_PI/p));
      vertex_buffer_data[iter*i+44]=w/2;

      vertex_buffer_data[iter*i+45]=(r1*cos(i*2*M_PI/p));
      vertex_buffer_data[iter*i+46]=(r1*sin(i*2*M_PI/p));
      vertex_buffer_data[iter*i+47]=w/2;

      vertex_buffer_data[iter*i+48]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+49]=(r1*sin((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+50]=w/2;

      vertex_buffer_data[iter*i+51]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+52]=(r1*sin((i+1)*2*M_PI/p));
      vertex_buffer_data[iter*i+53]=-w/2;
    }
    const int iter2 = 18;
    static GLfloat vertex_buffer_data_top[iter2*p];
    for (int i=0;i<p;++i){
      // face 1
    vertex_buffer_data_top[iter2*i]=(r1*cos(i*2*M_PI/p));
    vertex_buffer_data_top[iter2*i+1]=(r1*sin(i*2*M_PI/p));
    vertex_buffer_data_top[iter2*i+2]=w/2+0.1;

    vertex_buffer_data_top[iter2*i+3]=(r1*cos((i+1)*2*M_PI/p));
    vertex_buffer_data_top[iter2*i+4]=(r1*sin((i+1)*2*M_PI/p));
    vertex_buffer_data_top[iter2*i+5]=w/2+0.1;

    vertex_buffer_data_top[iter2*i+6]=r2*cos(i*2*M_PI/p);
    vertex_buffer_data_top[iter2*i+7]=r2*sin(i*2*M_PI/p);
    vertex_buffer_data_top[iter2*i+8]=w/2+0.1;

    vertex_buffer_data_top[iter2*i+9]=r2*cos((i+1)*2*M_PI/p);
    vertex_buffer_data_top[iter2*i+10]=r2*sin((i+1)*2*M_PI/p);
    vertex_buffer_data_top[iter2*i+11]=w/2+0.1;

    vertex_buffer_data_top[iter2*i+12]=r2*cos(i*2*M_PI/p);
    vertex_buffer_data_top[iter2*i+13]=r2*sin(i*2*M_PI/p);
    vertex_buffer_data_top[iter2*i+14]=w/2+0.1;

    vertex_buffer_data_top[iter2*i+15]=(r1*cos((i+1)*2*M_PI/p));
    vertex_buffer_data_top[iter2*i+16]=(r1*sin((i+1)*2*M_PI/p));
    vertex_buffer_data_top[iter2*i+17]=w/2+0.1;
   }
    this->object = create3DObject(GL_TRIANGLES, (iter/3)*p, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->top = create3DObject(GL_TRIANGLES, (iter2/3)*p, vertex_buffer_data_top, COLOR_RUBY, GL_LINE);

}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 incline    = glm::rotate((float) (30 * M_PI / 180.0f), glm::vec3(1, 0, 0 ));

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * incline);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->top);

}

void Cannon::tick() {
  this->rotation += 1;
}
