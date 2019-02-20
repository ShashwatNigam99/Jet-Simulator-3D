#include "score.h"
#include "main.h"
#include <stdlib.h>

Rectangle::Rectangle(float x, float y,float l,float b,float rot) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = rot;
    this->length= l;
    this->breadth = b;


    GLfloat vertex_buffer_data_rectangle[]={
    -l/2,-b/2,0.0,
    l/2,-b/2,0.0,
    -l/2,b/2,0.0,

    l/2,b/2,0.0,
    l/2,-b/2,0.0,
    -l/2,b/2,0.0
  };
    this->rectangle = create3DObject(GL_TRIANGLES,6, vertex_buffer_data_rectangle, COLOR_GREEN, GL_FILL);

}

void Rectangle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->rectangle);
}

void Rectangle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
/////////////////////////////////////////////////////////////
Number::Number(float x, float y,int number) {
    this->position = glm::vec3(x, y, 0);
    this->number = number;
    this->seg1 = Rectangle(x-3.5,3.8,0.2,0.02,0);
    this->seg5 = Rectangle(x-3.6,3.5,0.2,0.02,-90);
    this->seg6 = Rectangle(x-3.4,3.5,0.2,0.02,-90);
    this->seg7 = Rectangle(x-3.5,3.4,0.2,0.02,0);
    this->seg3 = Rectangle(x-3.4,3.7,0.2,0.02,-90);
    this->seg4 = Rectangle(x-3.5,3.6,0.2,0.02,0);
    this->seg2 = Rectangle(x-3.6,3.7,0.2,0.02,-90);
}

void Number::draw(glm::mat4 VP) {

       if(this->number==0){
            this->seg1.draw(VP);
            this->seg2.draw(VP);
            this->seg3.draw(VP);
            this->seg5.draw(VP);
            this->seg6.draw(VP);
            this->seg7.draw(VP);
          }
      else if(this->number==1){
            this->seg3.draw(VP);
            this->seg6.draw(VP);
          }
      else if(this->number==2){
            this->seg1.draw(VP);
            this->seg3.draw(VP);
            this->seg4.draw(VP);
            this->seg5.draw(VP);
            this->seg7.draw(VP);
          }
      else if(this->number==3){
            this->seg1.draw(VP);
            this->seg3.draw(VP);
            this->seg4.draw(VP);
            this->seg6.draw(VP);
            this->seg7.draw(VP);
          }
      else if(this->number==4){
            this->seg2.draw(VP);
            this->seg3.draw(VP);
            this->seg4.draw(VP);
            this->seg6.draw(VP);
         }
      else if(this->number==5){
            this->seg1.draw(VP);
            this->seg2.draw(VP);
            this->seg4.draw(VP);
            this->seg6.draw(VP);
            this->seg7.draw(VP);
      }
      else if(this->number==6){
            this->seg1.draw(VP);
            this->seg2.draw(VP);
            this->seg4.draw(VP);
            this->seg5.draw(VP);
            this->seg6.draw(VP);
            this->seg7.draw(VP);
      }
      else if(this->number==7){
            this->seg1.draw(VP);
            this->seg3.draw(VP);
            this->seg6.draw(VP);
      }
      else if(this->number==8){
            this->seg1.draw(VP);
            this->seg2.draw(VP);
            this->seg3.draw(VP);
            this->seg4.draw(VP);
            this->seg5.draw(VP);
            this->seg6.draw(VP);
            this->seg7.draw(VP);
      }
      else if(this->number==9){
            this->seg1.draw(VP);
            this->seg2.draw(VP);
            this->seg3.draw(VP);
            this->seg4.draw(VP);
            this->seg6.draw(VP);
            this->seg7.draw(VP);
    }
}

void Number::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->seg1.set_position(x-3.5,3.8);
    this->seg5.set_position(x-3.6,3.5);
    this->seg6.set_position(x-3.4,3.5);
    this->seg7.set_position(x-3.5,3.4);
    this->seg3.set_position(x-3.4,3.7);
    this->seg4.set_position(x-3.5,3.6);
    this->seg2.set_position(x-3.6,3.7);
}

void Number::tick(float x,float y, int number) {
   this->set_position(x,3.0);
   this->number = number;
}
/////////////////////////////////////////////////////////////
Score::Score(float x, float y,long long int score) {
    this->position = glm::vec3(x, y, 0);
    this->score = score;

    this->d1 = Number(x+2.0,4.0,score%10);
    this->d2 = Number(x+1.7,4.0,(score/10)%10);
    this->d3 = Number(x+1.4,4.0,(score/100)%10);
    this->d4 = Number(x+1.1,4.0,(score/1000)%10);
    this->d5 = Number(x+0.8,4.0,(score/10000)%10);
    this->d6 = Number(x+0.5,4.0,(score/100000)%10);
}

void Score::draw(glm::mat4 VP) {
  this->d1.draw(VP);
  this->d2.draw(VP);
  this->d3.draw(VP);
  this->d4.draw(VP);
  this->d5.draw(VP);
  this->d6.draw(VP);
}

void Score::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Score::tick(float x,float y,long long int score) {

      this->score = score;
      this->d1.tick(x+2.0,4.0,score%10);
      this->d2.tick(x+1.7,4.0,(score/10)%10);
      this->d3.tick(x+1.4,4.0,(score/100)%10);
      this->d4.tick(x+1.1,4.0,(score/1000)%10);
      this->d5.tick(x+0.8,4.0,(score/10000)%10);
      this->d6.tick(x+0.5,4.0,(score/100000)%10);
}
//////////////////////////////////////////////////////
Speedometer::Speedometer(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    const int p = 60;
    const int iter = 18;
    const float r1 = 1;
    const float r2 = 0.8;
    static GLfloat vertex_buffer_data[iter*p];
    for (int i=0;i<p;++i){
      // face 1
      vertex_buffer_data[iter*i]=(r1*cos(i*2*M_PI/(2*p)));
      vertex_buffer_data[iter*i+1]=(r1*sin(i*2*M_PI/(2*p)));
      vertex_buffer_data[iter*i+2]=0;

      vertex_buffer_data[iter*i+3]=(r1*cos((i+1)*2*M_PI/(2*p)));
      vertex_buffer_data[iter*i+4]=(r1*sin((i+1)*2*M_PI/(2*p)));
      vertex_buffer_data[iter*i+5]=0;

      vertex_buffer_data[iter*i+6]=r2*cos(i*2*M_PI/(2*p));
      vertex_buffer_data[iter*i+7]=r2*sin(i*2*M_PI/(2*p));
      vertex_buffer_data[iter*i+8]=0;

      vertex_buffer_data[iter*i+9]=r2*cos((i+1)*2*M_PI/(2*p));
      vertex_buffer_data[iter*i+10]=r2*sin((i+1)*2*M_PI/(2*p));
      vertex_buffer_data[iter*i+11]=0;

      vertex_buffer_data[iter*i+12]=r2*cos(i*2*M_PI/(2*p));
      vertex_buffer_data[iter*i+13]=r2*sin(i*2*M_PI/(2*p));
      vertex_buffer_data[iter*i+14]=0;

      vertex_buffer_data[iter*i+15]=(r1*cos((i+1)*2*M_PI/(2*p)));
      vertex_buffer_data[iter*i+16]=(r1*sin((i+1)*2*M_PI/(2*p)));
      vertex_buffer_data[iter*i+17]=0;
      }


    this->object = create3DObject(GL_TRIANGLES, (iter/3)*p, vertex_buffer_data, COLOR_GOLD, GL_LINE );
}

void Speedometer::draw(glm::mat4 VP) {
  // std::cout<<"madar";
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

/////////////
Marker::Marker(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 90;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
    -0.05f,0.0f,0.0f,
     0.05f,0.8f,0.0f,
     0.05f,0.0f,0.0f,//

    -0.05f,0.0f,0.0f,
    -0.05f,0.8f,0.0f,
     0.05f,0.8f,0.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_GRAY, GL_FILL);
}

void Marker::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) ((90-this->rotation) * M_PI / 180.0f), glm::vec3(0, 0, 1));

    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Marker::set_speed(float speed) {
  this->rotation = (speed/0.8)*180;
}
/////////////////////
Fuel::Fuel(float fuel) {
    this->fuel = fuel;

    this->d1 = Rectangle(3.5, -2.5,  0.75,  0.25, 0);
    this->d2 = Rectangle(3.5, -2.8,  0.75,  0.25, 0);
    this->d3 = Rectangle(3.5, -3.1,  0.75,  0.25, 0);
    this->d4 = Rectangle(3.5, -3.4,  0.75,  0.25, 0);
    this->d5 = Rectangle(3.5, -3.7,  0.75,  0.25, 0);
}

void Fuel::draw(glm::mat4 VP) {
  if(this->fuel>80){
  this->d1.draw(VP);
  this->d2.draw(VP);
  this->d3.draw(VP);
  this->d4.draw(VP);
  this->d5.draw(VP);
  }
  else if(this->fuel>60){
  this->d2.draw(VP);
  this->d3.draw(VP);
  this->d4.draw(VP);
  this->d5.draw(VP);
  }
  else if(this->fuel>40){
  this->d3.draw(VP);
  this->d4.draw(VP);
  this->d5.draw(VP);
  }
  else if(this->fuel>20){
  this->d4.draw(VP);
  this->d5.draw(VP);
  }
  else if(this->fuel>0){
  this->d5.draw(VP);
  }
  else{
   //
  }
}

void Fuel::set_fuel(float fuel){
  this->fuel = fuel;
}
/////////////////////////////////

Compass::Compass(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    const int p = 60;
    const int iter = 18;
    const float r1 = 0.5;
    const float r2 = 0.4;
    static GLfloat vertex_buffer_data[iter*p];
    for (int i=0;i<p;++i){
      // face 1
      vertex_buffer_data[iter*i]=(r1*cos(i*2*M_PI/(p)));
      vertex_buffer_data[iter*i+1]=(r1*sin(i*2*M_PI/(p)));
      vertex_buffer_data[iter*i+2]=0;

      vertex_buffer_data[iter*i+3]=(r1*cos((i+1)*2*M_PI/(p)));
      vertex_buffer_data[iter*i+4]=(r1*sin((i+1)*2*M_PI/(p)));
      vertex_buffer_data[iter*i+5]=0;

      vertex_buffer_data[iter*i+6]=r2*cos(i*2*M_PI/(p));
      vertex_buffer_data[iter*i+7]=r2*sin(i*2*M_PI/(p));
      vertex_buffer_data[iter*i+8]=0;

      vertex_buffer_data[iter*i+9]=r2*cos((i+1)*2*M_PI/(p));
      vertex_buffer_data[iter*i+10]=r2*sin((i+1)*2*M_PI/(p));
      vertex_buffer_data[iter*i+11]=0;

      vertex_buffer_data[iter*i+12]=r2*cos(i*2*M_PI/(p));
      vertex_buffer_data[iter*i+13]=r2*sin(i*2*M_PI/(p));
      vertex_buffer_data[iter*i+14]=0;

      vertex_buffer_data[iter*i+15]=(r1*cos((i+1)*2*M_PI/(p)));
      vertex_buffer_data[iter*i+16]=(r1*sin((i+1)*2*M_PI/(p)));
      vertex_buffer_data[iter*i+17]=0;
      }


    this->object = create3DObject(GL_TRIANGLES, (iter/3)*p, vertex_buffer_data, COLOR_GRAY, GL_LINE );
}
void Compass::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
/////////////
Needle::Needle(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
    -0.05f,0.0f,0.0f,
     0.05f,0.0f,0.0f,
     0.0f,0.4f,0.0f
   };

    this->north = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, COLOR_RED, GL_FILL);
    static const GLfloat vertex_buffer_data_b[] = {
    -0.05f,0.0f,0.0f,
     0.05f,0.0f,0.0f,
     0.0f,-0.4f,0.0f
   };

    this->south = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_b, COLOR_WHITE, GL_FILL);
}

void Needle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) ((180-this->rotation) * M_PI / 180.0f), glm::vec3(0, 0, 1));

    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->north);
    draw3DObject(this->south);
}

void Needle::set_dir(float rot) {
  this->rotation = rot;
}
