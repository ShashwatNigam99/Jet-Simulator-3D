#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;


    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
    -2.0f,-2.0f,2.5f,
    -2.0f, 2.0f,2.5f,
     2.0f,-2.0f,2.5f,

      2.0f,-2.0f,2.5f,
      2.0f, 2.0f,2.5f,
     -2.0f, 2.0f,2.5f,
/////////////
     -2.0f,-2.0f,2.5f,
     -2.0f, 2.0f,2.5f,
     0,0,0,

     2.0f,-2.0f,2.5f,
     2.0f, 2.0f,2.5f,
     0,0,0,

     2.0f, 2.0f,2.5f,
    -2.0f, 2.0f,2.5f,
     0,0,0,

     2.0f, -2.0f,2.5f,
    -2.0f, -2.0f,2.5f,
     0,0,0,
//////
     -1.0f,-1.0f,2.5f,
     -1.0f, 1.0f,2.5f,
      1.0f,-1.0f,2.5f,

       1.0f,-1.0f,2.5f,
       1.0f, 1.0f,2.5f,
      -1.0f, 1.0f,2.5f,
/////
      -1.0f,-1.0f,10.0f,
      -1.0f, 1.0f,10.0f,
       1.0f,-1.0f,10.0f,

        1.0f,-1.0f,10.0f,
        1.0f, 1.0f,10.0f,
       -1.0f, 1.0f,10.0f,
////////
      -1.0f,-1.0f,2.5f,
      -1.0f, 1.0f,2.5f,
      -1.0f, 1.0f,10.0f,

      -1.0f,-1.0f,10.0f,
      -1.0f, 1.0f,10.0f,
      -1.0f, -1.0f,2.5f,
      //
      1.0f,-1.0f,2.5f,
      1.0f, 1.0f,2.5f,
      1.0f, 1.0f,10.0f,

      1.0f,-1.0f,10.0f,
      1.0f, 1.0f,10.0f,
      1.0f, -1.0f,2.5f,
      //
      -1.0f,-1.0f,2.5f,
       1.0f,-1.0f,2.5f,
      -1.0f,-1.0f,10.0f,

      -1.0f,-1.0f,10.0f,
       1.0f,-1.0f,10.0f,
       1.0f,-1.0f,2.5f,
       //
       -1.0f,1.0f,2.5f,
        1.0f,1.0f,2.5f,
       -1.0f,1.0f,10.0f,

       -1.0f,1.0f,10.0f,
        1.0f,1.0f,10.0f,
        1.0f,1.0f,2.5f,

    };

    this->object = create3DObject(GL_TRIANGLES, 18*3, vertex_buffer_data, COLOR_RUBY, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
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

void Arrow::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Arrow::tick() {
  this->rotation += 2;
}

//////////Volcano

Volcano::Volcano(float x, float y, float h){
    this->position = glm::vec3(x, y, 0);
    this->height = h;
    const int p = 60;
    const int iter = 27;
    const int r1 = 6;
    const int r2 = 20;
    static GLfloat vertex_buffer_data_frustum[iter*p];// 8 triangles
    for (int i=0;i<p;++i){
    //joining cylinder
      vertex_buffer_data_frustum[iter*i]=(r1*cos(i*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+1]=(r1*sin(i*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+2]=h;

      vertex_buffer_data_frustum[iter*i+3]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+4]=(r1*sin((i+1)*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+5]=h;

      vertex_buffer_data_frustum[iter*i+6]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+7]=r2*sin(i*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+8]=0;
    //joining cylinder
      vertex_buffer_data_frustum[iter*i+9]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+10]=r2*sin(i*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+11]=0;

      vertex_buffer_data_frustum[iter*i+12]=r2*cos((i+1)*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+13]=r2*sin((i+1)*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+14]=0;

      vertex_buffer_data_frustum[iter*i+15]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+16]=(r1*sin((i+1)*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+17]=h;
//
      vertex_buffer_data_frustum[iter*i+18]=r2*cos(i*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+19]=r2*sin(i*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+20]=0.1;

      vertex_buffer_data_frustum[iter*i+21]=r2*cos((i+1)*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+22]=r2*sin((i+1)*2*M_PI/p);
      vertex_buffer_data_frustum[iter*i+23]=0.1;

      vertex_buffer_data_frustum[iter*i+24]=0;
      vertex_buffer_data_frustum[iter*i+25]=0;
      vertex_buffer_data_frustum[iter*i+26]=0.1;
      }
      const int iter2 = 18;
      static GLfloat vertex_buffer_data_top[iter2*p];// 8 triangles
      for (int i=0;i<p;++i){
      //joining cylinder
        vertex_buffer_data_top[iter2*i]=(r1*cos(i*2*M_PI/p));
        vertex_buffer_data_top[iter2*i+1]=(r1*sin(i*2*M_PI/p));
        vertex_buffer_data_top[iter2*i+2]=h;

        vertex_buffer_data_top[iter2*i+3]=(r1*cos((i+1)*2*M_PI/p));
        vertex_buffer_data_top[iter2*i+4]=(r1*sin((i+1)*2*M_PI/p));
        vertex_buffer_data_top[iter2*i+5]=h;

        vertex_buffer_data_top[iter2*i+6]=r1*cos(i*2*M_PI/p);
        vertex_buffer_data_top[iter2*i+7]=r1*sin(i*2*M_PI/p);
        vertex_buffer_data_top[iter2*i+8]=1+h;
      //joining cylinder
        vertex_buffer_data_top[iter2*i+9]=r1*cos(i*2*M_PI/p);
        vertex_buffer_data_top[iter2*i+10]=r1*sin(i*2*M_PI/p);
        vertex_buffer_data_top[iter2*i+11]=1+h;

        vertex_buffer_data_top[iter2*i+12]=r1*cos((i+1)*2*M_PI/p);
        vertex_buffer_data_top[iter2*i+13]=r1*sin((i+1)*2*M_PI/p);
        vertex_buffer_data_top[iter2*i+14]=1+h;

        vertex_buffer_data_top[iter2*i+15]=(r1*cos((i+1)*2*M_PI/p));
        vertex_buffer_data_top[iter2*i+16]=(r1*sin((i+1)*2*M_PI/p));
        vertex_buffer_data_top[iter2*i+17]=h;
        }
    this->object = create3DObject(GL_TRIANGLES, (iter/3)*p , vertex_buffer_data_frustum, COLOR_BROWN, GL_FILL);
    this->top = create3DObject(GL_TRIANGLES, (iter2/3)*p , vertex_buffer_data_top, COLOR_RED, GL_FILL);

}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->top);

}
