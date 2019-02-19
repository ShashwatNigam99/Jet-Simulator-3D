#include "sea.h"
#include "main.h"

Sea::Sea(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
      -1000,-1000,0,
      -1000,1000,0,
      1000,1000,0,

      -1000,-1000,0,
      1000,-1000,0,
      1000,1000,0
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BLUE, GL_FILL);
}
void Sea::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
///////////////////////////// Land
Land::Land(float x, float y,float rot) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = rot;
    const int xx = -8 + rand()%8;
    const int yy = -8 + rand()%8;
    const int zz = 10 + rand()%15;
    this->height = zz;

    GLfloat vertex_buffer_data[] = {
      -15,15,0,
      -13,12,0,
      xx,yy,zz,

      -13,12,0,
      -16,2,0,
      xx,yy,zz,

      -16,2,0,
      -8,-7,0,
      xx,yy,zz,

      -8,-7,0,
      -15,-14,0,
      xx,yy,zz,

      -15,-14,0,
      -3,-12,0,
      xx,yy,zz,

      -3,-12,0,
      7,-9,0,
      xx,yy,zz,

      7,-9,0,
      16,2,0,
      xx,yy,zz,

      16,2,0,
      8,7,0,
      xx,yy,zz,

      8,7,0,
      2,14,0,
      xx,yy,zz,

      2,14,0,
      -7,12,0,
      xx,yy,zz,

      -7,12,0,
      -15,15,0,
      xx,yy,zz,

    };
    const int p = 30;
    const int iter = 9;
    const int r1 = 21;
    GLfloat vertex_buffer_data_frustum[iter*p];// 8 triangles
    for (int i=0;i<p;++i){
      //front circle
      vertex_buffer_data_frustum[iter*i]=(r1*cos(i*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+1]=(r1*sin(i*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+2]=0.1;

      vertex_buffer_data_frustum[iter*i+3]=(r1*cos((i+1)*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+4]=(r1*sin((i+1)*2*M_PI/p));
      vertex_buffer_data_frustum[iter*i+5]=0.1;

      vertex_buffer_data_frustum[iter*i+6]=0.0;
      vertex_buffer_data_frustum[iter*i+7]=0.0;
      vertex_buffer_data_frustum[iter*i+8]=0.1;
   }
    this->sand = create3DObject(GL_TRIANGLES, (iter/3)*p, vertex_buffer_data_frustum, COLOR_SAND, GL_FILL);
    this->object = create3DObject(GL_TRIANGLES, 11*3, vertex_buffer_data, COLOR_DARKGREEN, GL_FILL);
}
void Land::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->sand);
    draw3DObject(this->object);
}
