#include "coin.h"
#include "main.h"

Coin::Coin(float x, float y, color_t color,int special) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->special = special;


    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
    -0.2f,0.0f,0.0f,
    0.0f,0.2f,0.0f,
    0.2f,0.0f,0.0f,//

    -0.2f,0.0f,0.0f,
    0.0f,-0.2f,0.0f,
    0.2f,0.0f,0.0f

    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Coin::tick() {
  this->rotation += 2;
  //  std::cout<<"coin :"<<this->position.x<<","<<this->position.y<<"\n";
}

bounding_box_t Coin::return_box(){
  bounding_box_t coin_bb;
  coin_bb.x = this->position.x;
  coin_bb.y = this->position.y;
  coin_bb.width = 0.4f;
  coin_bb.height = 0.4f;
  return coin_bb;
}

///////////////////////////////

 Fuelup::Fuelup(float x, float y, float z) {
     this->position = glm::vec3(x, y, z);
     this->rotation = 0;


     // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
     // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
     static const GLfloat vertex_buffer_data[] = {
              -1.5f,-1.5f,-3.0f, // triangle 1 : begin
              -1.5f,-1.5f, 3.0f,
              -1.5f, 1.5f, 3.0f, // triangle 1 : end

              1.5f, 1.5f,-3.0f, // triangle 2 : begin
              -1.5f,-1.5f,-3.0f,
              -1.5f, 1.5f,-3.0f, // triangle 2 : end

              1.5f,-1.5f, 3.0f,
              -1.5f,-1.5f,-3.0f,
              1.5f,-1.5f,-3.0f,

              1.5f, 1.5f,-3.0f,
              1.5f,-0.5f,-3.0f,
              -1.5f,-1.5f,-3.0f,

              -1.5f,-1.5f,-3.0f,
              -1.5f, 1.5f, 3.0f,
              -1.5f, 1.5f,-3.0f,

               1.5f,-1.5f, 3.0f,
              -1.5f,-1.5f, 3.0f,
              -1.5f,-1.5f,-3.0f,

              -1.5f, 1.5f, 3.0f,
              -1.5f,-1.5f, 3.0f,
              1.5f,-1.5f, 3.0f,

              1.5f, 1.5f, 3.0f,
              1.5f,-1.5f,-3.0f,
              1.5f, 1.5f,-3.0f,

              1.5f,-1.5f,-3.0f,
              1.5f, 1.5f, 3.0f,
              1.5f,-1.5f, 3.0f,

              1.5f, 1.5f, 3.0f,
              1.5f, 1.5f,-3.0f,
              -1.5f, 1.5f,-3.0f,

              1.5f, 1.5f, 3.0f,
              -1.5f, 1.5f,-3.0f,
              -1.5f, 1.5f, 3.0f,

              1.5f, 1.5f, 3.0f,
              -1.5f, 1.5f, 3.0f,
              1.5f,-1.5f, 3.0f
     };
     static const GLfloat vertex_buffer_data_structure[] = {

            -1.0f,1.6f,1.0f,
            -1.0f,1.6f,0,
             1.0f,1.6f,1.0f,

              1.0f,1.6f,1.0f,
              1.0f,1.6f,0,
              -1.0f,1.6f,0,

              -1.0f,-1.6f,1.0f,
              -1.0f,-1.6f,0,
               1.0f,-1.6f,1.0f,

                1.0f,-1.6f,1.0f,
                1.0f,-1.6f,0,
                -1.0f,-1.6f,0,
//
              1.5f,0,2.5f,
              3.5f,0,1.0f,
              1.5f,0,1.0f,

              3.5f,0,1.0f,
              3.5f,0,-2.5f,
              1.5f,0,1.0f,

              1.5f,0,1.0f,
              1.5f,0,-2.5f,
              3.5f,0,-2.5f,
//

              1.5f,0.5f,2.5f,
              3.5f,0.5f,1.0f,
              1.5f,0.5f,1.0f,

              3.5f,0.5f,1.0f,
              3.5f,0.5f,-2.5f,
              1.5f,0.5f,1.0f,

              1.5f,0.5f,1.0f,
              1.5f,0.5f,-2.5f,
              3.5f,0.5f,-2.5f,
//

              1.5f,-0.5f,2.5f,
              3.5f,-0.5f,1.0f,
              1.5f,-0.5f,1.0f,

              3.5f,-0.5f,1.0f,
              3.5f,-0.5f,-2.5f,
              1.5f,-0.5f,1.0f,

              1.5f,-0.5f,1.0f,
              1.5f,-0.5f,-2.5f,
              3.5f,-0.5f,-2.5f,


     };
     this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_GOLD, GL_FILL);
     this->structure = create3DObject(GL_TRIANGLES, 13*3, vertex_buffer_data_structure, COLOR_RED, GL_FILL);

 }

 void Fuelup::draw(glm::mat4 VP) {
     Matrices.model = glm::mat4(1.0f);
     glm::mat4 translate = glm::translate (this->position);    // glTranslatef
     glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
     // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
     // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
     Matrices.model *= (translate * rotate);
     glm::mat4 MVP = VP * Matrices.model;
     glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
     draw3DObject(this->object);
     draw3DObject(this->structure);

 }

 void Fuelup::set_position(float x, float y) {
     this->position = glm::vec3(x, y, 0);
 }

 void Fuelup::tick() {
   this->rotation += 2;
   //  std::cout<<"coin :"<<this->position.x<<","<<this->position.y<<"\n";
 }
///////////////////////////////////
Bullet::Bullet(float x, float y, float z, float a, float b) {
    this->position = glm::vec3(a, b, 0);
    this->rotation = 0;
    float p = sqrt(pow(x-a,2) + pow(y-b,2) + pow(z,2));
    this->norm_x = (x-a)/p;
    this->norm_y = (y-b)/p;
    this->norm_z = z/p;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
    0.5f,0,0,
    0,0.5f,0,
    0,0,0.5f,

    -0.5f,0,0,
    0,0.5f,0,
    0,0,0.5f,

    0.5f,0,0,
    0,-0.5f,0,
    0,0,0.5f,

    -0.5f,0,0,
    0,-0.5f,0,
    0,0,0.5f,

    0.5f,0,0,
    0,0.5f,0,
    0,0,-0.5f,

    -0.5f,0,0,
    0,0.5f,0,
    0,0,-0.5f,

    0.5f,0,0,
    0,-0.5f,0,
    0,0,-0.5f,

    -0.5f,0,0,
    0,-0.5f,0,
    0,0,-0.5f

    };

    this->object = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data, COLOR_PINK, GL_FILL);
}

void Bullet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Bullet::tick() {

  this->rotation += 2;
  this->position.x += 1.0 * this->norm_x ;//*sin(this->phi*M_PI/180.0f);
  this->position.y += 1.0 * this->norm_y ;//*sin(this->phi*M_PI/180.0f);
  this->position.z += 1.0 * this->norm_z;
  // this->position.z+=0.1;

}

bounding_box_t Bullet::return_box(){
  bounding_box_t coin_bb;
  coin_bb.x = this->position.x;
  coin_bb.y = this->position.y;
  coin_bb.width = 0.4f;
  coin_bb.height = 0.4f;
  return coin_bb;
}
