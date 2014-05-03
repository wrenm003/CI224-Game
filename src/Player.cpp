#include "Player.h"

Player::Player(): GameAsset()
{
  Player(0, 0, 0);
}

Player::Player(float x, float y, float z):GameAsset(

  string("shaders/hello-gl.v.glsl"),

  string("shaders/hello-gl.red.glsl")) {
  //this->li = nullptr;

  // A default unit triangle
  num_vertices = 4;
  num_triangles = 4;
  g_vertex_buffer_data = new GLfloat[num_vertices * 3]{

//x     y    z
-0.5, -0.5, -0.5, //F - 0  //base of the triangle player
 0.5, -0.5, -0.5, //F - 1
 0.0, -0.5,  0.5, //F - 2
 0.0,  0.0,  0.0, //F - 3  //top point og the triangle player
}; // three points per vertex

  g_element_buffer_data = new GLushort[num_triangles * 3]{

F0, F1, F2,   //Base
F0, F1, F3,   //Back
F1, F2, F3,   //RightSide
F2, F0, F0    //LeftSide

}; // three vertices per triangle

  bbox.reset();
  bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(x, y, z), 1.0, 1.0, 1.0));

  make_resources();
}

Player::~Player() {
  // TODO: do something nice and fun here.
}

void Player::MoveLeft() {
  shared_ptr<Point3> L = this->bbox->getCentre();
    *L = Point3(L->getX()-1, L->getY(), (L->getZ()));
}
void Player::MoveRight() {
  shared_ptr<Point3> R = this->bbox->getCentre();
    *R = Point3((R->getX() + 1), R->getY(), R->getZ());
}  

void Player::update() {
}

void Player::draw() {
  GameAsset::draw();
}

void Player::clean() { } 
