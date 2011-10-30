#include "TriangularPyramidAsset.h"

TriangularPyramidAsset::TriangularPyramidAsset() 
  : GameAsset(
	      string("shaders/hello-gl.v.glsl")
	      , string("shaders/hello-gl.f.glsl")
	      )
{
  TriangularPyramidAsset(0, 0, 0);
}

TriangularPyramidAsset::TriangularPyramidAsset(float x, float y, float z) {
  this->li = NULL;
  this->pos = new Point3(x, y, z);
  // A default "unit" triangular pyramid
  num_vertices = 4;
  num_triangles = 4;
  g_vertex_buffer_data = new GLfloat[num_vertices * 3]; // three points per vertex
  g_element_buffer_data = new GLushort[num_triangles * 3]; // three vertices per triangle

  g_vertex_buffer_data[0] = -0.5;
  g_vertex_buffer_data[1] = -0.5;
  g_vertex_buffer_data[2] = 0.5;

  g_vertex_buffer_data[3] = 0.5;
  g_vertex_buffer_data[4] = -0.5;
  g_vertex_buffer_data[5] = 0.5;

  g_vertex_buffer_data[6] = 0.0;
  g_vertex_buffer_data[7] = -0.5;
  g_vertex_buffer_data[8] = -0.5;

  g_vertex_buffer_data[9] = 0.0;
  g_vertex_buffer_data[10] = 0.5;
  g_vertex_buffer_data[11] = 0.0;

  g_element_buffer_data[0] = 0;
  g_element_buffer_data[1] = 1;
  g_element_buffer_data[2] = 3;

  g_element_buffer_data[3] = 1;
  g_element_buffer_data[4] = 2;
  g_element_buffer_data[5] = 3;

  g_element_buffer_data[6] = 2;
  g_element_buffer_data[7] = 0;
  g_element_buffer_data[8] = 3;

  g_element_buffer_data[9] = 2;
  g_element_buffer_data[10] = 0;
  g_element_buffer_data[11] = 1;

  translate[0] = x;
  translate[1] = y;
  translate[2] = z;

  make_resources();
}

TriangularPyramidAsset::~TriangularPyramidAsset() {
  // TODO: do something nice here.
}

void TriangularPyramidAsset::update() {
  if(NULL != this->li) {
    Vector3 v = li->update();
    translate[0] = (*pos+v).getX();
    translate[1] = (*pos+v).getY();
    translate[2] = (*pos+v).getZ();
  }
}

void TriangularPyramidAsset::setInterpolator(IInterpolator * li) {
  this->li = li;
}

void TriangularPyramidAsset::draw() {
  cout << "Drawing pyramid at (" << translate[0] << " ," << translate[1] << " ," << translate[2] << ")" << endl;
  GameAsset::draw();
}
